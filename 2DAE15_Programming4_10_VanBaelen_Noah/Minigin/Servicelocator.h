#pragma once
#include "sound_system.h"

class Null_Sound_System final : public sound_system
{
	void play(const sound_id, const float) override {}
	int AddSound(std::string) override { return -1; }
	void OpenAudio() override {};
	void CloseAudio() override {};
};

static std::unique_ptr<sound_system> _ss_instance;

class Servicelocator final
{

public:

	Servicelocator(const Servicelocator& other) = delete;
	Servicelocator(Servicelocator&& other) = delete;
	Servicelocator& operator=(const Servicelocator& other) = delete;
	Servicelocator& operator=(Servicelocator&& other) = delete;

	static sound_system& get_sound_system() { return *_ss_instance; }
	static void register_sound_system(std::unique_ptr<sound_system>&& ss) { _ss_instance = ss == nullptr ? std::make_unique<Null_Sound_System>() : std::move(ss); }
};
