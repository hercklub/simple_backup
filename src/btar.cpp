#include "btar.h"

using namespace std;
CBtar::~CBtar(){
	while(!m_TOCrecords.empty()){
		delete m_TOCrecords.front();
		m_TOCrecords.pop_front();
	}

}
CBtar::Memorz *  CBtar::ReadFromBtar (ifstream & src,int offset){

	TARheader * m_Header = new TARheader();
	memset(m_Header,0,sizeof(TARheader));

	src.seekg (offset, src.beg);
	Memorz * test = new Memorz();

	// Read header from btar file
	src.read ((char *) &m_Header->filename , sizeof (m_Header->filename));
	src.read ((char *) &m_Header->mode, sizeof (m_Header->mode));
	src.read ((char *) &m_Header->uid, sizeof (m_Header->uid));
	src.read ((char *) &m_Header->gid, sizeof (m_Header->gid));
	src.read ((char *) &m_Header->size, sizeof (m_Header->size));
	src.read ((char *) &m_Header->mtime, sizeof (m_Header->mtime));
	src.read ((char *) &m_Header->checksum, sizeof (m_Header->checksum));
	src.read ((char *) &m_Header->typeflag, sizeof (m_Header->typeflag));
	src.read ((char *) &m_Header->uname, sizeof (m_Header->uname));
	src.read ((char *) &m_Header->gname, sizeof (m_Header->gname));
	src.read ((char *) &m_Header->padding, sizeof (m_Header->padding));
	
	// Read data if there are some
	test->data = NULL;
	if (atoi(m_Header->size) > 0){
		char * data = new char [atoi(m_Header->size)];
		src.read ((char *) data, atoi(m_Header->size));
		test->data = data;
	}
	test->header = m_Header;
	// Move cause of "\n" after every record
	src.seekg (1, src.cur);

	return test;

}
bool CBtar::WriteToBtar (ofstream & dst,const string & fileToProccess){
	struct stat buf;

	ifstream src (fileToProccess,ios::in | ios::binary );

	if (!src.is_open())
		return false;

	TARheader * m_Header = new TARheader();
	memset(m_Header,0,sizeof(TARheader));

	// Get files stats
	stat(fileToProccess.c_str(),&buf); 
	long unsigned int zero = 0;

	 // Regural file or directory
	 if (S_ISREG (buf.st_mode)){
     	sprintf(m_Header->typeflag,"%u",REGTYPE);
     	sprintf(m_Header->size,"%lu",buf.st_size);
     }
     else if (S_ISDIR(buf.st_mode)){
     	sprintf(m_Header->typeflag,"%u",DIRTYPE);
     	sprintf(m_Header->size,"%lu",zero);
     }
     else{ 
     	delete m_Header;
     	return false;
     }
     
	sprintf(m_Header->filename,"%s",fileToProccess.c_str());
	sprintf(m_Header->mode,"%u",buf.st_mode);
	sprintf(m_Header->uid,"%u",buf.st_uid);
	sprintf(m_Header->gid,"%u",buf.st_gid);
	sprintf(m_Header->mtime,"%lu",buf.st_mtime);

	// Save acutall position in file as offset for TOC
	unsigned int offset =  dst.tellp();
	dst.write ((char *) m_Header , sizeof(TARheader));

	if (S_ISREG (buf.st_mode)){
		if (atoi(m_Header->size) == 0){
			dst << '\n';
		}	
		else
			dst << src.rdbuf();
			dst << '\n';
	}
     else if (S_ISDIR(buf.st_mode))
   		dst << '\n';


   	TOCrecord * item = new TOCrecord();
   	memset(item,0,sizeof(TOCrecord));

   	// Prepare TOC record
   	sprintf(item->filename,"%s",fileToProccess.c_str());
   	sprintf(item->offset,"%u",offset);

   	// Saves TOC record to list for later use
   	m_TOCrecords.push_back(item);

   	delete m_Header;
	return true;
}
bool CBtar::WriteTOC(ofstream & dst){
	for (auto it = m_TOCrecords.begin();it!= m_TOCrecords.end();it++){
		dst.write ((char *) *it , sizeof(TOCrecord));
		dst << '\n';
	}
	TOCfooter * item = new TOCfooter();
	memset(item,0,sizeof(TOCfooter));

	sprintf(item->name,"%s","BTAR");
	sprintf(item->itemcount,"%lu",m_TOCrecords.size());
	dst.write ((char *) item , sizeof(TOCfooter));
	dst << '\n';
	delete item;
	return true;
}
list <int> CBtar::ReadTOC(ifstream & src){
	list <int> result;
	TOCfooter * footer = new TOCfooter;
	src.seekg(- (int) sizeof (TOCfooter) - 1 ,src.end); // -1 for newline
	src.read ((char *) &footer->name, sizeof (footer->name));
	src.read ((char *) &footer->itemcount, sizeof (footer->itemcount));

	//FOOTER READING
	if (strcmp (footer->name,"BTAR")!=0){
		delete footer;
		throw runtime_error("Can not regognize file.");
	}
	int PosFromEnd = - (int) sizeof (TOCfooter) - 1 - (atoi(footer->itemcount) * (int) sizeof(TOCrecord) ) - atoi(footer->itemcount) ;
	src.seekg(PosFromEnd ,src.end); 

	TOCrecord * item = new TOCrecord;

	for (int i = 0;i < atoi(footer->itemcount) ; i++ ){

		src.read ((char *) &item->filename, sizeof (item->filename));
		src.read ((char *) &item->offset, sizeof (item->offset));
		src.seekg(1,src.cur); // FOR NEW LINE

		result.push_back(atoi(item->offset));
	}
	delete footer;
	delete item;
	return result;
}
