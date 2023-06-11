#include "SDL_Sound_System.h"

void SDL_Sound_System::play(const sound_id id, const float volume)
{
	std::lock_guard<std::mutex> lock(m_Mutex);
	m_SoundQueue.push(std::pair<sound_id, float>(id, volume));
	m_Condition.notify_one();
}

int SDL_Sound_System::AddSound(std::string filePath)
{
    m_AudioclipsPath.push_back(filePath);
    m_pAudioclips.push_back(std::make_shared<Mix_Chunk>());

    return static_cast<int>(m_AudioclipsPath.size()) - 1;
}

int SDL_Sound_System::AddMusic(std::string filePath)
{
	m_MusicPath.push_back(filePath);
	return static_cast<int>(m_MusicPath.size()) - 1;
}

void SDL_Sound_System::OpenAudio()
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	m_IsAllowedToProcces = true;
	m_Thread = std::thread(&SDL_Sound_System::ProccesSoundEvents, this);
}

void SDL_Sound_System::CloseAudio()
{
	m_IsAllowedToProcces = false;
	m_Condition.notify_one();
	m_Thread.join();
	Mix_CloseAudio();
	Mix_HaltMusic();
	Mix_CloseAudio();
}

void SDL_Sound_System::ProccesSoundEvents()
{
	while (m_IsAllowedToProcces)
	{
		std::unique_lock<std::mutex> lock(m_Mutex);
		m_Condition.wait(lock);

		if (!m_SoundQueue.empty())
		{
			std::pair<sound_id, float>sound = m_SoundQueue.front();
			m_SoundQueue.pop();

			auto audioclip = m_pAudioclips[sound.first];
			if (!audioclip->abuf)
			{
				audioclip = std::make_shared<Mix_Chunk>(*Mix_LoadWAV(m_AudioclipsPath[sound.first].c_str()));
				if (!audioclip)
				{
					std::cout << "Error loading sound: " << Mix_GetError();
				}
			}

			audioclip->volume = static_cast<Uint8>(sound.second);
			if (m_IsMuted)
			{
				audioclip->volume = static_cast<Uint8>(0);
			}
			Mix_PlayChannel(-1, audioclip.get(), 0);
		}
	}
}

void SDL_Sound_System::playMusic(const sound_id id)
{
	Mix_Music* currentMusic = Mix_LoadMUS(m_MusicPath[id].c_str());
	Mix_PlayMusic(currentMusic, 100);
}

void SDL_Sound_System::MuteToggle()
{
	m_IsMuted = !m_IsMuted;

	if (m_IsMuted)
	{
		Mix_PauseMusic();
	}
	else
	{
		Mix_ResumeMusic();
	}
}
