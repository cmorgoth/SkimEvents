#ifndef READ_EVENT_LIST_HH
#define READ_EVENT_LIST_HH 1

//C++ INCLUDES
#include <iostream>
#include <map>
#include <fstream>
//ROOT INCLUDES
//LOCAL INCLUDES

struct RunAndEvent
{
  int run;
  unsigned long event;
};


bool FillMap( std::map<RunAndEvent, bool>& map, std::string fname );

#endif
