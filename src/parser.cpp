
#include "parser.h"
#include <ctime>
using namespace std;

list <string> CParser::getCmdOption (const string & option,bool mulval){
	list <string> result; 
   	auto itr = std::find(m_begin,m_end, option);
 	if (itr == m_end )
 		return result;
 	m_arguments -= 1;
   	while (++itr!=m_end && *itr[0]!='-'){
   		m_arguments -= 1;
   		result.push_back(*itr);
   		if (!mulval)
   			return result;
   	}
   	return result;
 
}
bool CParser::CmdOptionExist (const string & option){
	if (find(m_begin,m_end, option) != m_end){
		m_arguments -= 1;
		return true;
	}
	else
		return false;
}


void CParser::ShowHelp(bool ShowFull) {
	string help = "\
Usage:  -B -f SOURCE -o DEST -c CONFIG FILE\n\
   or:  -R -f SOURCE [-i FILES]\n";
	if (ShowFull){
   		help +="\
-B (BackUp) \n\
\n\
MANDATORY:\n\
	-f SOURCE		files|directories to backUp\n\
	-o DEST			name of output file\n\
OPTIONAL:\n\
	-c CONF FILE 		config file\n\
\n\
 -R (Recovery)\n\
 \n\
MANDATORY:\n\
	-f SOURCE		btar backup file\n\
OPTIONAL:\n\
	-i 			specific files to recover\n\
";
   }
  	cout << help;
}



bool CParser::ParseConfig (ifstream & src){
	time_t rawtime;
  	struct tm * timeinfo;
  	char day [10];
  	time (&rawtime);
  	timeinfo = localtime (&rawtime);
  	strftime (day,10,"%a",timeinfo);

	string tmp;
	while (getline(src,tmp)){
		if (strcmp(tmp.c_str(),day)==0)
			return true;
	}
	return false;
}
bool CParser::FinishParsing(){
	if (m_arguments!=0)
		return false;
	else 
		return true;
}