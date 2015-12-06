#include "search.h"

using namespace std;

bool CDir::ListFiles(){
	
	/// Open Directory for reading
	DIR * direc = opendir(m_Path.c_str()); 
	if (direc == NULL)
		return false;
	
	struct dirent * item = readdir (direc); 
	if (m_Paths.size()==0)
		m_Paths.push_back(GetFullPath (m_Path));
		
	while (item){
		//Skips "." and ".." 
		if (strcmp(item->d_name,".") == 0 || strcmp(item->d_name,"..") == 0){ 
			item = readdir (direc);
			continue;
		}
		// item is directory
		if(item->d_type == DT_DIR){
			Directory(item->d_name);
		}
		// item directory
		else if (item->d_type == DT_REG) {
			RegularFile(item->d_name);

		}
		item = readdir (direc);
	}
	return true;

}
void CDir::Directory(const string & dir){

	m_Path = m_Path + "/" + dir;
	m_Paths.push_back(GetFullPath (m_Path));
	if ( ListFiles() == false)
		throw runtime_error("Could not open file/directory");
	m_Path.resize(m_Path.length() - 1 - dir.length());

}
void CDir::RegularFile(const string & filename){

	m_Paths.push_back(GetFullPath(m_Path + "/" + filename));

}
list <string> CDir::GetPaths()const{
	return m_Paths;
}
string CDir::GetFullPath (const string & rel_path)const{
	char resolved_path[100];
	char * res = realpath(rel_path.c_str(),resolved_path);
	if (!res)
		throw runtime_error("Can not resolve full path of file/directory");
	return string(resolved_path);
}


//