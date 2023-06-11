#pragma once
#include "sound_system.h"
#include "string.h"
#include <iostream>
#include <vector>
#include <mutex>
#include <queue>
#include <thread>

class SDL_Sound_System final : public sound_system
{
public:

	SDL_Sound_System() = default;
	~SDL_Sound_System() = default;
	SDL_Sound_System(const SDL_Sound_System& other) = delete;
	SDL_Sound_System(SDL_Sound_System&& other) = delete;
	SDL_Sound_System& operator=(const SDL_Sound_System& other) = delete;
	SDL_Sound_System& operator=(SDL_Sound_System&& other) = delete;

	void playMusic(const sound_id id) override;
	void MuteToggle() override;
	void play(const sound_id id, const float volume) override;
	int AddSound(std::string filePath) override;
	int AddMusic(std::string filePath) override;
	void OpenAudio() override;
	void CloseAudio() override;

protected:
	void ProccesSoundEvents();
	std::vector<std::string> m_AudioclipsPath;
	std::vector<std::string> m_MusicPath;
	std::vector<std::shared_ptr<Mix_Chunk>> m_pAudioclips;
	std::vector<std::shared_ptr<Mix_Music>> m_pMusic;
	std::mutex m_Mutex;
	std::queue<std::pair<sound_id, float>> m_SoundQueue;
	std::condition_variable m_Condition;
	bool m_IsAllowedToProcces = false;
	bool m_IsMuted = false;
	std::thread m_Thread;
};

