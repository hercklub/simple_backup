#ifndef __C_SEARCH__
#define __C_SEARCH__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>
#include <dirent.h>
#include <exception>
#include <list>
#include <map>
#include "btar.h"

using namespace std;

/** @brief Recursivly search trough data structure 


	
 */
class CDir{
public:
	/**
	  Constructor with parameter
	  @param _path file or directory 

	*/
	CDir(string _path):m_Path(_path){};
	/**
	  Constructor with parameter
	  @param _path file or directory 

	*/
	bool ListFiles();
	list <string> GetPaths()const;

protected:

	string m_Path;
	list <string> m_Paths; //< list of all found paths
	/**
	  Resolve full path of file or directory
	  @param rel_path relative path to file or directory 

	*/
	string GetFullPath (const string & rel_path) const;
	/**
	  Method is called when listed item is directory and program need to
	  proceed in listing items.

	*/
	void Directory(const string & dir);
	/**
		Method saves path to listed file.
	*/
	void RegularFile (const string & filename);

	
};

#endif /* __C_SEARCH__ */