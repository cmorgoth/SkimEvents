//C++ INCLUDES
//ROOT INCLUDES
//LOCAL INCLUDES
#include "ReadEventlist.hh"

bool FillMap( std::map<RunAndEvent, bool>& map, std::string fname )
{
  RunAndEvent tmp_struct;
  std::ifstream file ( fname.c_str(), std::ifstream::in );
  if ( file.is_open() )
    {
      while ( file.good() )
	{
	  if ( file.eof() ) break;
	  file >> tmp_struct.run >> tmp_struct.event;
	  std::cout << tmp_struct.run << " " << tmp_struct.event << std::endl;
	}
    }
  else
    {
      std::cerr << "[ERROR:] Failed to open file: " << fname << std::endl;
    }
};
