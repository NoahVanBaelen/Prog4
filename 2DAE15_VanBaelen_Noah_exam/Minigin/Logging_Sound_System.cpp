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

void Logging_Sound_System::playMusic(const sound_id id)
{
	_real_ss->playMusic(id);
	std::cout << "Play Music" << std::endl;
}

int Logging_Sound_System::AddMusic(std::string filePath)
{
	std::cout << "Add Music" << std::endl;
	return _real_ss->AddMusic(filePath);
}

void Logging_Sound_System::MuteToggle()
{
	_real_ss->MuteToggle();
	std::cout << "Toggle Mute" << std::endl;
}
