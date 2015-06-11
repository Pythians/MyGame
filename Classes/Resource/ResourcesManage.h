/*
* ResourcesManage.h
* Demo
* Used: Manage Resourse
*
* Create by K on 15/4/13
* Last change by K on 15/4/16
*/

#ifndef ResourcesManage_H_
#define ResourcesManage_H_

#include "Config.h"
#include "Data/Data.h"

using std::string;
using std::vector;
using std::multimap;

class ResourcesManage : public cocos2d::Ref
{
public:
	ResourcesManage( );
	~ResourcesManage( );

private:
	
	string _rootPath;
	vector<string> * _folders;
	multimap<string, string> * _allFiles;

	void getFiles( string path, string folder, multimap<string, string>* folders );
public:
	string getRootPath( );
	multimap<string, string>* getAllFiles( );
	vector<string> * getFolders( );

private:
	BgLayerData * _bgLayerData;

public:
	BgLayerData * getBgLayerDataFromFile( std::string && fileName );
	void saveBgLayerDataToFile( std::string && fileName );
};

#endif