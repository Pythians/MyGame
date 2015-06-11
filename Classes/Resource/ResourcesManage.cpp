#include "ResourcesManage.h"
#include "tinyxml2/tinyxml2.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include <io.h>
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include <dirent.h>
#endif

USING_NS_CC;
ResourcesManage::ResourcesManage( )
	: _allFiles( new multimap<string, string>( ) )
	, _folders( new vector<string>( ) )
	, _bgLayerData( new BgLayerData( ) )
{
	_rootPath = FileUtils::getInstance( )->fullPathForFilename( r_File );
	_rootPath = _rootPath.substr( 0, _rootPath.rfind( "/" ) );
}

ResourcesManage::~ResourcesManage( )
{
	_allFiles->clear( );
	_folders->clear( );
	delete _folders;
	delete _allFiles;
	delete _bgLayerData;
}

void ResourcesManage::getFiles( string path, string folder, multimap<string, string>* folders )
{
	folders->insert( std::pair<string, string>( folder, folder ) );
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	long hFile = 0;
	string p = path + "/\*";
	_finddata_t fileinfo;
	if( ( hFile = _findfirst( p.c_str( ), &fileinfo ) ) != -1 )
	{
		do
		{
			p = path + "/" + fileinfo.name;
			if( fileinfo.name[ 0 ] == '.' )
			{
				continue;
			}
			else if( fileinfo.attrib == _A_SUBDIR )
			{
				getFiles( p, fileinfo.name, folders );
			}
			else
			{
				folders->insert( std::pair<string, string>( folder, fileinfo.name ) );
			}
		} while( _findnext( hFile, &fileinfo ) == 0 );
		_findclose( hFile );
	}
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	string p = path + "/";
	dirent * ptr;
	DIR * dir = opendir( p.c_str( ) );

	while( ( ptr = readdir( dir ) ) != NULL )
	{
		p = path + "/" + ptr->d_name;
		if( ptr->d_name[ 0 ] == '.' )
		{
			continue;
		}
		else if( ptr->d_type == DT_DIR )
		{
			getFiles( p, ptr->d_name, folders );
		}
		else
		{
			folders->insert( std::pair<string, string>( folder, ptr->d_name ) );
		}
	}
	closedir( dir );
#endif
}

string ResourcesManage::getRootPath( )
{
	return _rootPath;
}

multimap<string, string>* ResourcesManage::getAllFiles( )
{
	if( _allFiles->empty( ) )
	{
		getFiles( _rootPath, r_Folder, _allFiles );
	}
	return _allFiles;
}

vector<string>* ResourcesManage::getFolders( )
{
	if( _folders->empty( ) )
	{
		if( _allFiles->empty( ) )
		{
			getFiles( _rootPath, r_Folder, _allFiles );
		}
		for( auto i = _allFiles->begin( ); i != _allFiles->end( ); ++i )
		{
			if( i->first == i->second )
			{
				_folders->push_back( i->first );
			}
		}
	}
	return _folders;
}

BgLayerData * ResourcesManage::getBgLayerDataFromFile( std::string && fileName )
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile( fileName.c_str( ) );
	auto elemRoot = doc.RootElement( );
	auto layers = elemRoot->FirstChildElement( "Layers" );
	auto elemLayer = layers->FirstChildElement( );
	while( elemLayer != 0 )
	{
		//auto elem = elemLayer->FirstChildElement( );
		auto bezier = elemLayer->FirstChildElement( "Beziers" );
		auto bz = bezier->FirstChildElement( );
		auto color = elemLayer->FirstChildElement( "Colors" );
		auto co = color->FirstChildElement( );
		auto layer = new LineLayer( );
		while( bz != 0 && co != 0 )
		{
			float bx = atof( bz->Attribute( "bx" ) );
			float by = atof( bz->Attribute( "by" ) );
			float ex = atof( bz->Attribute( "ex" ) );
			float ey = atof( bz->Attribute( "ey" ) );
			float c1x = atof( bz->Attribute( "c1x" ) );
			float c1y = atof( bz->Attribute( "c1y" ) );
			float c2x = atof( bz->Attribute( "c2x" ) );
			float c2y = atof( bz->Attribute( "c2y" ) );
			float r = atof( co->Attribute( "r" ) );
			float g = atof( co->Attribute( "g" ) );
			float b = atof( co->Attribute( "b" ) );
			float a = atof( co->Attribute( "a" ) );

			layer->AddBezier( bx, by, ex, ey, c1x, c1y, c2x, c2y, r, g, b, a );
			bz = bz->NextSiblingElement( );
			co = co->NextSiblingElement( );
		}
		if( !layer->isEmpty( ) )
		{
			_bgLayerData->AddLineLayer( layer );
		}
		elemLayer = elemLayer->NextSiblingElement( );
	}
	return _bgLayerData;
}

void ResourcesManage::saveBgLayerDataToFile( std::string && fileName )
{
	tinyxml2::XMLDocument doc;

	auto elemRootLayer = doc.NewElement( "RootLayer" );
	doc.InsertEndChild( elemRootLayer );

	auto layer = _bgLayerData->getLineLayer( );
	for( int i = 0; i < layer->size( ); i++ )
	{
		char * ch = new char[ 20 ];
		sprintf( ch, "layer%d", i + 1 );
		auto elemLine = doc.NewElement( ch );
		elemRootLayer->InsertEndChild( elemLine );

		auto line = layer->at( i )->getLines( );
		for( int i = 0; i < line.size( ); i++ )
		{
			auto b = line.at( i );
			auto emleB = doc.NewElement( "Bezier" );
			emleB->SetAttribute( "bx", b.begin.x );
			emleB->SetAttribute( "by", b.begin.y );
			emleB->SetAttribute( "ex", b.end.x );
			emleB->SetAttribute( "ey", b.end.y );
			emleB->SetAttribute( "c1x", b.control1.x );
			emleB->SetAttribute( "c1y", b.control1.y );
			emleB->SetAttribute( "c2x", b.control2.x );
			emleB->SetAttribute( "c2y", b.control2.y );
			elemLine->InsertEndChild( emleB );
		}
	}

	doc.SaveFile( fileName.c_str( ) );
}




