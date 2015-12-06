#ifndef __B_TAR__
#define __B_TAR__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <cstdlib>
#include <cstring>
#include <cctype>
#include <map>
#include <exception>
#include <dirent.h>
#include <sys/stat.h>

#include <list>

#define REGTYPE  0
#define DIRTYPE  5


using namespace std;


/** @brief Class used for manipulation with files.

    
*/
class CBtar
{
protected:
	/** @brief Format for header of every record.

	*/
	struct TARheader {
		char filename [100];
		char mode[8];
		char uid[8];
		char gid[8];
		char size[12];
		char mtime[12];
		char checksum[8];
		char typeflag[1];
		char uname[32];
		char gname[32];
		char padding[35];
	};

	/** @brief Format of Table of Content footer

	*/
	struct TOCfooter{
		char name [12];
		char itemcount [12];
	};
	/** @brief Format of Table of content record

	*/
	struct TOCrecord{
		char filename[100];
		char offset[12];
	};
	/** @brief Format for 

	*/
	struct Memorz {
		TARheader * header;
		char * data;
		~Memorz(){
			delete header;
			if (data!=NULL)
				delete [] data;
		}
	};
	TOCfooter * m_TOCfooter; 
	list <TOCrecord*> m_TOCrecords;
public:
	CBtar(){};
	~CBtar();
	/**
	  * Read single record from btar file.
	  @param  src input file
	  @param  offset position relative to begiging of the file, where header is located
	  @return Pointer to Memorz data structure
	*/
	Memorz * ReadFromBtar(ifstream & src,int offset);
	/**
	  * Read table of content from btar file
	  @param  src input file
	  @return list of offsets that we read from btar file
	*/
	list<int> ReadTOC(ifstream & src);
	/**
	  Write header file and data to btra file
	  @param  dst output file
	  @param fileToProccess path of file to proccess 
	*/
	bool WriteToBtar (ofstream & dst,const string & fileToProccess);
	/**
	  Write header file and data to btra file
	  @param  dst output file
	  @param fileToProccess path of file to proccess 
	*/
	bool WriteTOC(ofstream & dst);
	
};


#endif /* __B_TAR__ */