//C++ INCLUDES
//ROOT INCLUDES
#include <TString.h>
#include <TTree.h>
#include <TChain.h>
#include <TFile.h>
//LOCAL INCLUDES
#include "ReadEventlist.hh"

bool FillMap( std::map< std::string , RunAndEvent >& mymap, std::string fname )
{
  RunAndEvent tmp_struct;
    
  std::ifstream file ( fname.c_str(), std::ifstream::in );
  if ( file.is_open() )
    {
      while ( file.good() )
	{
	  std::stringstream tmp;
	  std::string tmp_s;
	  if ( file.eof() ) break;
	  file >> tmp_struct.run >> tmp_struct.event;
	  tmp << tmp_struct.run << " " << tmp_struct.event;
	  tmp_s = tmp.str();
	  if( mymap.find( tmp_s ) == mymap.end() ) mymap[tmp_s] = tmp_struct;
	}
    }
  else
    {
      std::cerr << "[ERROR:] Failed to open file: " << fname << std::endl;
      return false;
    }
  
  if ( mymap.size() == 0 )
    {
      std::cerr << "[ERROR:] Empty Map " << std::endl;
      return false;
    }
  std::cout << "[INFO:] map size: " << mymap.size() << std::endl;
  return true;
};

void SkimTree( std::map< std::string, RunAndEvent > mymap, std::string list_name,
	       std::string tree_name, std::string run_branch, std::string event_branch)
{
  int run;
  unsigned long long event;
  int ctr = 1;//file counter
  TChain* chain = new TChain( tree_name.c_str() );
  std::ifstream file ( list_name.c_str(), std::ifstream::in );
  if ( file.is_open() )
    {
      while ( file.good() )
        {
	  TString s;
	  file >> s;
	  if( s != "" ) 
	    {
	      std::cout << "[INFO]: adding file #" << ctr << ": " << s << std::endl;
	      chain->Add(s);
	      ctr++;
	    }
        }
    }
  else
    {
      std::cerr << "[ERROR]: Failed to open file: " << list_name << std::endl;
    }

  long long nentries = chain->GetEntries();
  std::cout << "[INFO]: " << nentries << " Total Entries" << std::endl;
  chain->SetBranchAddress(run_branch.c_str(), &run);
  chain->SetBranchAddress(event_branch.c_str(), &event);
  
  //Create a new file + a clone of old tree in new file
  TFile *newfile = new TFile("small.root","recreate");
  TTree *newtree = chain->CloneTree(0);
  
  for ( long long i = 0; i < nentries; i++ )
    {
      if ( i%100000 == 0 ) std::cout << "[INFO]: " << i << " entry" << std::endl;
      chain->GetEntry(i);
      std::stringstream tmp;
      std::string tmp_s;
      tmp << run << " " << event;
      tmp_s = tmp.str();
      if( mymap.find( tmp_s ) != mymap.end() )newtree->Fill();
    }
  
  newtree->Print();
  newtree->AutoSave();
  delete chain;
  delete newfile;
};
