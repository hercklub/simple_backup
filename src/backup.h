#ifndef __BACK_UP__
#define __BACK_UP__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <fstream>
#include <map>
#include <dirent.h>
#include <exception>
#include "search.h"

using namespace std;

/** @brief Class used for full and incremental backup

 */

class CBackUp:public CBtar{
public:
	/**
	  Constructor 
	  @param  _in list of input files
	  @param  _out output file

	*/
	CBackUp (const  list<string> & _in,const string & _out):in_filenames(_in),out_filename(_out){};
	/**

	Perform FULL back up of input files.

	*/
	void DoIt ();

	/**
	
	Perform Incremental back up of input files.

	*/
	void LoadPrevBckps();

protected:
	list <string> in_filenames;
	string out_filename;
};

#endif /* __BACK_UP__*/




















































