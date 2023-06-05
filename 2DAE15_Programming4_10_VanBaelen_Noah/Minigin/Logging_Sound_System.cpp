#include "Logging_Sound_System.h"

void Logging_Sound_System::play(const sound_id id, const float volume)
{
	_real_ss->play(id, volume);
	std::cout << "playing " << id << " at volume " << volume << std::endl;
}

int Logging_Sound_System::AddSound(std::string filePath)
{
	int newID = _real_ss->AddSound(filePath);
	std::cout << "added sound with filePath: " << filePath << " with ID " << newID << std::endl;
	return newID;
}

void Logging_Sound_System::OpenAudio()
{
	_real_ss->OpenAudio();
	std::cout << "Open Audio" << std::endl;
}

void Logging_Sound_System::CloseAudio()
{
	_real_ss->CloseAudio();
	std::cout << "Close Audio" << std::endl;
}
