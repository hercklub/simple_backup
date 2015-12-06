#include <iostream>
#include <exception>
#include "parser.h"
#include "backup.h"
#include "recovery.h"

using namespace std;
 
int main (int argc, char ** argv){

	CParser parser(argv,argv+argc,argc-1);

	if (parser.CmdOptionExist("-B")){

		list <string> in_filenames = parser.getCmdOption("-f",true); 
		//Parse input files or directories from command line
		if (in_filenames.size() == 0){
			parser.ShowHelp(false);
			return 1;
		}

		list<string> config_file =  parser.getCmdOption("-c",false);
		if (config_file.size() != 0){
			ifstream src (config_file.front(),ios::in);
			if (src.is_open()){
				if (!parser.ParseConfig(src)){
					return 0;
				}
			}
			else {
				cout << "ERROR: Can not open config file !" << endl;
				return 1;
			}
				
		}
		list <string> out_filenames = parser.getCmdOption("-o",false);
		/*Parse name of output file from command line*/
		if (out_filenames.size() == 0){
			parser.ShowHelp(false);
			return 1;
		}
		if (!parser.FinishParsing()){
			cout << "ERROR: Wrong number of arguments !" << endl;
			return 1;
		}
			
		struct stat buffer;   
  		if (stat (out_filenames.front().c_str(), &buffer) == 0){
  			try {
  				CBackUp bck(in_filenames,out_filenames.front());
				bck.LoadPrevBckps();
			}
			catch (exception& e){
				cout << "ERROR: " << e.what() << endl;
			}
  			return 1;
  		}
  		else {
  			try{
  				CBackUp bck(in_filenames,out_filenames.front());
				bck.DoIt();
			}
			catch (exception& e){
				cout << "ERROR: " << e.what() << endl;
			}

  		}
  		/*Chechs if output file already exist, if true program will perfrom incrementall backup*/
  		/*Signalize of parsing*/
	}
	else if (parser.CmdOptionExist("-R")){
		list <string> in_filename = parser.getCmdOption("-f",false); 

		if (in_filename.size() == 0){
			parser.ShowHelp(false);
			return 1;
		}

		list <string> filesTorcv = parser.getCmdOption("-i",true);
		/*Specifie if user want to recover only specific files, default: ALL*/
		if (!parser.FinishParsing()){	
			cout << "ERROR: Wrong number of arguments !" << endl;
			return 1;
		}

		if ( filesTorcv.size() == 0){
			cout << in_filename.front() << endl;
			try {
				CRecovery rec(in_filename.front()); // RECOVER ALL FILES
				rec.DoIt();
			}
			catch (exception& e){
				cout << "ERROR: " << e.what() << endl;
			}
		}
		else {
			try{
				CRecovery rec(in_filename.front(),filesTorcv); // RECOVER ONLY FILES FROM LIST
				rec.DoIt();
			}
			catch (exception& e){
				cout << "ERROR: " << e.what() << endl;
			}
		}


	}
	else if (parser.CmdOptionExist("-S")){
		list <string> in_filename = parser.getCmdOption("-f",false); 

		if (in_filename.size() == 0){
			parser.ShowHelp(false);
			return 1;
		}

		if (!parser.FinishParsing()){
			cout << "ERROR: Wrong number of arguments !" << endl;
			return 1;
		}

	}
	else if (parser.CmdOptionExist("-h")){
		parser.ShowHelp(true);

		if (!parser.FinishParsing()){
			cout << "ERROR: Wrong number of arguments !" << endl;
			return 1;
		}

	}
	else 
	 {
		parser.ShowHelp(false);
		return 1;
	}
	return 0;

}