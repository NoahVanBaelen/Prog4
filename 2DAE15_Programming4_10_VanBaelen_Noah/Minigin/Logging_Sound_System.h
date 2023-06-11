#pragma once
#include "sound_system.h"
#include <iostream>

class Logging_Sound_System final : public sound_system
{
	std::unique_ptr<sound_system> _real_ss;
public:

	Logging_Sound_System(const Logging_Sound_System& other) = delete;
	Logging_Sound_System(Logging_Sound_System&& other) = delete;
	Logging_Sound_System& operator=(const Logging_Sound_System& other) = delete;
	Logging_Sound_System& operator=(Logging_Sound_System&& other) = delete;

	Logging_Sound_System(std::unique_ptr<sound_system>&& ss) { _real_ss = std::move(ss);}
	void play(const sound_id id, const float volume) override;
	int AddSound(std::string filePath) override;
	void OpenAudio() override;
	void CloseAudio() override;
	virtual void playMusic(const sound_id) override;
	virtual int AddMusic(std::string) override;
	virtual void MuteToggle() override;
};

