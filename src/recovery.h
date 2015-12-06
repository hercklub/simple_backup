#ifndef __RECOVERY__
#define __RECOVERY__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <fstream>
#include <utime.h>
#include <fcntl.h>
#include <algorithm> 
#include <map>
#include <exception>


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <utime.h>

#include "search.h"

using namespace std;

/** @brief Class used for recovering files and direcotries from back up.

  */
class CRecovery:public CBtar{
public:
	/**
	  Constructor 
	  @param  _in input file to do recovery from
	  @param  _files specific files to recover

	*/
	CRecovery (const string & _in,const  list<string> & _files):m_InFilename(_in),m_FilesToRcv(_files){};
	/**
	  Constructor 
	  @param  _in input file to do recovery from

	*/
	CRecovery (const string & _in):m_InFilename(_in){};
	/**
	  Tries to recover files from backup file/s
	  

	*/
	bool DoIt ();
	/**
	    Tries to recover files from backup file/s
	  	Called only when program is performing recovering from incremental backup.
		@return list of files to recover
	*/
	list <string> GetListOfNames();
	void Show()const;

protected:
	string m_InFilename;
	list <string> m_FilesToRcv;
};

#endif /* __RECOVERY__ */



