//C++ INCLUDES
#include <iostream>
#include <map>
#include <string>
//ROOT INCLUDES
//LOCAL INCLUDES
#include "ReadEventlist.hh"

int main( int argc, char* argv[] )
{
  std::map<RunAndEvent, bool> mymap;
  std::string fname( argv[1] );
  
  FillMap( mymap, fname);
  
  return 0;
}
