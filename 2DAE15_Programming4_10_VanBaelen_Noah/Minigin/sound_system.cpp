#include "sound_system.h"
#include <SDL_mixer.h>
#include <Vector>
#include <mutex>
#include <queue>
#include <thread>

class sound_system::sound_system_impl //ChatGPT
{
public:
	sound_system_impl();
	~sound_system_impl();

	void play(const sound_id, const float);
	int AddSound(std::string);
	void OpenAudio();
	void CloseAudio();
	void ProccesSoundEvents();

private:
	std::vector<std::string> m_AudioclipsPath;
	std::vector<std::shared_ptr<Mix_Chunk>> m_Audioclips;
	std::mutex m_Mutex;
	std::queue<std::pair<sound_id, float>> m_SoundQueue;
	std::condition_variable m_Condition;
	bool m_IsAllowedToProcces = false;
	std::thread m_Thread;
};

sound_system::sound_system() : impl(new sound_system_impl()) {}
sound_system::~sound_system() { delete impl; }

void sound_system::play(const sound_id id, const float volume) { impl->play(id, volume); }
int sound_system::AddSound(std::string filePath) { return impl->AddSound(filePath); }
void sound_system::OpenAudio() { impl->OpenAudio(); }
void sound_system::CloseAudio() { impl->CloseAudio(); }

sound_system::sound_system_impl::sound_system_impl() = default;
sound_system::sound_system_impl::~sound_system_impl() = default;

void sound_system::sound_system_impl::play(const sound_id id, const float volume)
{
	std::lock_guard<std::mutex> lock(m_Mutex);
	m_SoundQueue.push(std::pair<sound_id, float>(id, volume));
	m_Condition.notify_one();
}

int sound_system::sound_system_impl::AddSound(std::string filePath)
{
	m_AudioclipsPath.push_back(filePath);
	m_Audioclips.push_back(std::make_shared<Mix_Chunk>());

	return static_cast<int>(m_AudioclipsPath.size()) - 1;
}

void sound_system::sound_system_impl::OpenAudio()
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	m_IsAllowedToProcces = true;
	m_Thread = std::thread(&sound_system::sound_system_impl::ProccesSoundEvents, this);
}

void sound_system::sound_system_impl::CloseAudio()
{
	m_IsAllowedToProcces = false;
	m_Condition.notify_one();
	m_Thread.join();
	Mix_CloseAudio();
}

void sound_system::sound_system_impl::ProccesSoundEvents()
{
	while (m_IsAllowedToProcces)
	{
		std::unique_lock<std::mutex> lock(m_Mutex);
		m_Condition.wait(lock);

		if (!m_SoundQueue.empty())
		{
			std::pair<sound_id, float>sound = m_SoundQueue.front();
			m_SoundQueue.pop();

			auto audioclip = m_Audioclips[sound.first];
			if (!audioclip->abuf)
			{
				audioclip = std::make_shared<Mix_Chunk>(*Mix_LoadWAV(m_AudioclipsPath[sound.first].c_str()));
				if (!audioclip)
				{
					std::cout << "Error loading sound: " << Mix_GetError();
				}
			}

			audioclip->volume = static_cast<Uint8>(sound.second);
			Mix_PlayChannel(-1, audioclip.get(), 0);
		}
	}
}