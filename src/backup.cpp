#include "backup.h"

using namespace std;

void CBackUp::DoIt(){
	ofstream dst (out_filename,ios::out | ios::binary | ios::app);
	if (!dst.is_open()){
		throw runtime_error("Problem occured while opening file.");
	}
	for (auto it = in_filenames.begin();it!=in_filenames.end();it++){
		CDir search (*it);
		if (!search.ListFiles())
			throw runtime_error("Problem occured while opening file.");
		else {
			list <string> result = search .GetPaths();
			for (auto it = result.begin();it!=result.end();it++){
				if (!WriteToBtar(dst,*it))
					throw runtime_error("Problem occured while writing to file.");
			}
			WriteTOC(dst);		
		}
	}

}
void CBackUp::LoadPrevBckps(){
	int counter=1;
	list <string> resfilenames;
	string temp = out_filename;
	struct stat buffer;

	while (stat (temp.c_str(), &buffer) == 0){
		resfilenames.push_back(temp);
		temp = out_filename;
		temp = temp + "_" + to_string(counter);
		counter ++;
	}
	map <string,long int> files;
	for (auto it = resfilenames.begin();it!=resfilenames.end();it++){
		ifstream src (*it,ios::in | ios::binary);	
		
		list<int> off = ReadTOC(src);
		for (auto it = off.begin();it!=off.end();it++){
			Memorz * tst=ReadFromBtar(src,*it);
			//cout << tst->header->filename  << tst->header->mtime << endl;
			files[string(tst->header->filename)]=strtoul (tst->header->mtime, NULL, 10);
			delete tst;
		}
		
	}

	ofstream dst (temp,ios::out | ios::binary | ios::app);
	if (!dst.is_open()){
		throw runtime_error("Problem occured while opening file.");
	}
	for (auto it = in_filenames.begin();it!=in_filenames.end();it++){
		CDir search (*it);
		if (!search.ListFiles())
			throw runtime_error("Problem occured while opening file.");

		else {
			list <string> result = search .GetPaths();
			for (auto it = result.begin();it!=result.end();it++){
				 auto it1 = files.find(*it);

				if (it1!= files.end()){
					struct stat buf;
					stat(string(*it).c_str(),&buf); // Get files stats
					if (buf.st_mtime != it1->second)
						WriteToBtar(dst,*it);
					}
				else{
					WriteToBtar(dst,*it);
				}	
			}
			WriteTOC(dst);		
		}
	}


}
