
#ifndef __PARSER___
#define __PARSER___


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <map>
#include <time.h>  

using namespace std;


/** @brief Class used for parsing command line arguments and config files.


    */
class CParser{
public:
	CParser (){};
	~CParser (){};
	/**
	  *Constructor that takes 3 arguments 
	  @param beg is poitner to begining of the array
	  @param end is poitner to end of the array
	  @param num size of array
	*/
	CParser (char ** beg, char ** end,int _num):m_begin(beg),m_end(end),m_arguments(_num){};
	/**
	  Parse specified option.
	  @param option defines parsing specifier (-f)
	  @param mulval allows multiple items after parsing specifier
	  @return List of items defined by parsing option
	*/
	list <string> getCmdOption (const string & option, bool mulval);
	/**
	  * Chech for existnece of option.
	  @param option defines parsing specifier (-f)
	  @return boolean depending on the input.
	*/
	bool CmdOptionExist (const string & option);
	/**
	  * Parse config file 
	  @param  src opened file stream for reading
	  @return True if current day is in config file
	*/
	bool ParseConfig (ifstream & src);
	/**
	  @param ShowFull show extented help
	*/
	void ShowHelp(bool ShowFull	);
	bool FinishParsing();
private:
	char ** m_begin;
	char ** m_end;
	int m_arguments;
};

#endif /* __PARSER___ */