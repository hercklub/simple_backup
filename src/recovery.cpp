#include "recovery.h"

using namespace std;

bool CRecovery::DoIt(){

	list <string> files = GetListOfNames();
	//cout << files.size() << endl;
	for (auto it_l = files.begin();it_l!=files.end();it_l++){
		cout << *it_l << endl;
		ifstream src (*it_l,ios::in | ios::binary);	
		if (!src.is_open())
			throw runtime_error("Can not open file.");
		list<int> off = ReadTOC(src);
		struct timespec new_times[2];
		for (auto it = off.begin();it!=off.end();it++){

			Memorz * tst = ReadFromBtar(src,*it);
			// Recover only files requested by user
			if (m_FilesToRcv.size()>0){
			auto found = find (m_FilesToRcv.begin(),m_FilesToRcv.end(),string(tst->header->filename));
			if (found == m_FilesToRcv.end())
				continue;
			}
			
			new_times[1].tv_sec = strtoul (tst->header->mtime, NULL, 10);
			new_times[1].tv_nsec = 0;
			new_times[0].tv_sec = strtoul (tst->header->mtime, NULL, 10);
			new_times[0].tv_nsec = 0;

			if (atoi(tst->header->typeflag)== REGTYPE){ // FILE
				ofstream dst (tst->header->filename,ios_base::out | ios_base::binary);
				dst.write ((char *) tst->data , atoi(tst->header->size));

				dst.close();

			}
			else if (atoi(tst->header->typeflag) == DIRTYPE) {// DIRECTORY

				 mkdir(tst->header->filename, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);


			}
			
			 chown(tst->header->filename,strtoul(tst->header->uid,NULL,10),strtoul(tst->header->gid,NULL,10)); 
			 chmod(tst->header->filename,strtoul(tst->header->mode,NULL,10));

			
			if (utimensat(AT_FDCWD, tst->header->filename, new_times, 0) < 0 ){
				perror(tst->header->filename);
			} 
			delete tst;
		}
		
	}
return true;
	
}
list <string> CRecovery::GetListOfNames(){
	list <string> filesToRec;
	string temp = m_InFilename;
	if (temp.size() > 2){
		if (temp[temp.size()-2] == '_'){
		
			int lastnum =(int)temp.back() - '0';
			
			temp.resize(temp.length() - 2);
			for (int i=0; i <= lastnum; i++){
				if (i == 0){
					filesToRec.push_back(temp);
					continue;
				}
				else
					filesToRec.push_back(temp + "_" + to_string(i));
			}
		}
		else {
	
			filesToRec.push_back(m_InFilename);}
	}
	else {
	
		filesToRec.push_back(m_InFilename);
	}
	return filesToRec;


}
void CRecovery::Show() const{



}