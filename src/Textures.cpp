#include "Textures.h"
#include <sstream>
#include <io.h>

Textures::Textures(void)
{
	FindAndLoad(top32, "data\\Textures\\top32\\*.png","data\\Textures\\top32\\");
	FindAndLoad(top64, "data\\Textures\\top64\\*.png","data\\Textures\\top64\\");
	FindAndLoad(mid32, "data\\Textures\\mid32\\*.png","data\\Textures\\mid32\\");
	FindAndLoad(mid64, "data\\Textures\\mid64\\*.png","data\\Textures\\mid64\\");
	FindAndLoad(back32, "data\\Textures\\back32\\*.png","data\\Textures\\back32\\");
	FindAndLoad(back64, "data\\Textures\\back64\\*.png","data\\Textures\\back64\\");

	FindAndLoad(characters, "data\\Textures\\characters\\*.png","data\\Textures\\characters\\");
}


Textures::~Textures(void)
{
}

void Textures::FindAndLoad(std::map<std::string, sf::Texture*> & textureList, const char * path, std::string path_)
{
	textureList.clear();

	std::ostringstream ss;

	_finddata_t fileData;
	long handle = _findfirst( path, & fileData );

	if(handle != -1)
	{
		sf::Texture tmp;
		ss.str("");
		ss << path_ << fileData.name;
		tmp.loadFromFile(ss.str());

		textureList[fileData.name] = new sf::Texture(tmp);

		int keepLook = _findnext( handle, & fileData );
			
		while(keepLook != -1)
		{
			ss.str("");
			ss << path_ << fileData.name;
			tmp.loadFromFile(ss.str());

			textureList[fileData.name] = new sf::Texture(tmp);

			keepLook = _findnext( handle, & fileData );
		}
	}
}