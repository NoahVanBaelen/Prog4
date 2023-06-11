#pragma once
#include <iostream>
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
	virtual int AddSound(std::string) = 0;
	virtual void OpenAudio() = 0;
	virtual void CloseAudio() = 0;
	virtual void ProccesSoundEvents() = 0;

private:
	class sound_system_impl;
	sound_system_impl* impl;
};

