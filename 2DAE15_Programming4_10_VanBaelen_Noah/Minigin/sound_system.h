#pragma once
#include <iostream>
#include <SDL_mixer.h>
using sound_id = unsigned short;
class sound_system //Interface
{
public:
	sound_system() = default;

	sound_system(const sound_system& other) = delete;
	sound_system(sound_system&& other) = delete;
	sound_system& operator=(const sound_system& other) = delete;
	sound_system& operator=(sound_system&& other) = delete;

	virtual ~sound_system() = default;
	virtual void play(const sound_id, const float) = 0;
	virtual void playMusic(const sound_id) = 0;
	virtual int AddSound(std::string) = 0;
	virtual int AddMusic(std::string) = 0;
	virtual void OpenAudio() = 0;
	virtual void CloseAudio() = 0;
	virtual void MuteToggle() = 0;
};

