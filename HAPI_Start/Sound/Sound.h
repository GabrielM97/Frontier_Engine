#pragma once
#include <iostream>
#include <unordered_map>
#include <HAPI_lib.h>

using namespace HAPISPACE;
class Sound
{
public:
	Sound();
	bool LoadSound(std::string file);
	//volume must be between 0-1(full)
	void ModifySoundSettings(int instanceid , bool loops, float vol);
	bool PlaySound(std::string file, int instanceid);
	bool PlayStreamedSounds(std::string file, int instanceid);
	void StopSound(int instanceid);
	virtual ~Sound();

private:
	HAPI_TSoundOptions options;
	std::unordered_map<int, int> soundInstances;
	

};

