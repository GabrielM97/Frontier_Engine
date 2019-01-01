#include "Sound.h"



Sound::Sound()
{
}

bool Sound::LoadSound(std::string file)
{

	if (HAPI.LoadSound(file))
		return true;
	else
	{
		std::cerr <<"Error! \nUnable to find media file" << std::endl;
		return false;

	}
		
}


void Sound::ModifySoundSettings(int instanceid, bool loops, float vol)
{
	options = HAPI_TSoundOptions(vol ,loops);
	HAPI.ChangePlayingSoundOptions(instanceid, options);
}



bool Sound::PlaySound(std::string file, int instanceid)
{
	
	int id;
	if (HAPI.PlaySound(file, options, id))
	{
		soundInstances.insert(std::pair<int, int>(instanceid, id));
		return true;
	}	
	else
	{
		std::cerr << "Error. \n Failed to locate media file" << std::endl;
		return false;
	}

}

bool Sound::PlayStreamedSounds(std::string file, int instanceid)
{
	
	int id;
	if (HAPI.PlayStreamedMedia(file, options, id))
	{
		soundInstances.insert(std::pair<int, int>(instanceid, id));
		return true;
	}
	else
	{
		std::cerr << "Error. \n Failed to locate media file" << std::endl;
		return false;
	}

}

void Sound::StopStreamedSounds(int instanceid)
{
	if (soundInstances.find(instanceid) != soundInstances.end())
		HAPI.StopStreamedMedia(soundInstances.at(instanceid));
}

void Sound::StopSound(int instanceid)
{
	if(soundInstances.find(instanceid) != soundInstances.end())
		if(soundInstances.at(instanceid) != NULL)
			HAPI.StopSound(soundInstances.at(instanceid));
}

Sound::~Sound()
{

}
