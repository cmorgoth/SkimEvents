//C++ INCLUDES
#include <iostream>
#include <map>
#include <string>
//ROOT INCLUDES
//LOCAL INCLUDES
#include "ReadEventlist.hh"

int main( int argc, char* argv[] )
{
  std::map< std::string , RunAndEvent > mymap;
  std::string fname( argv[1] );
  std::string list_name( argv[2] );
  
  FillMap( mymap, fname);

  /*
  for ( auto& tmp : mymap )
    {
      std::cout << tmp.second.run << " "  << tmp.second.event << std::endl;
    }
  */
  
  SkimTree( mymap, list_name, "ntp1", "runNumber", "eventNumber");
  return 0;
}
