#include "HighScoreListComponent.h"
#include "TextComponent.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

HighScoreListComponent::HighScoreListComponent(dae::GameObject* pOwner)
	:BaseComponent(pOwner)
{
}

void HighScoreListComponent::SetFilePath(std::string file)
{
	m_TextFilePath = file;
}

void HighScoreListComponent::SetHighScoreList()
{
	ReadFile();

	std::reverse(m_Scores.begin(), m_Scores.end());//becose we read a file from the top

	int indexHighScore{ static_cast<int>(m_Scores.size()) };

	for (int i = 0; i < static_cast<int>(m_Scores.size()); i++)
	{
		if (m_Scores[i] < m_Score)
		{
			indexHighScore = i;
		}
	}

	if (indexHighScore != static_cast<int>(m_Scores.size()))
	{
		int NewValue{ m_Score };
		int OldValue{};
		for (int i = indexHighScore; i > 0; i--)
		{
			OldValue = m_Scores[i];
			m_Scores[i] = NewValue;
			NewValue = OldValue;
		}
	}
	std::reverse(m_Scores.begin(), m_Scores.end());//becose we write a file from the top

	for (int i = 0; i < static_cast<int>(m_Scores.size()); i++)
	{
		if (i == static_cast<int>(m_Scores.size()-1))
		{
			GetOwner()->GetChildAt(i+1)->GetComponent<TextComponent>()->SetText("Your Score: " + std::to_string(m_Score));
		}
		GetOwner()->GetChildAt(i)->GetComponent<TextComponent>()->SetText(std::to_string(i + 1) + ": " + std::to_string(m_Scores[i]));
	}
	WriteFile();
	m_Score = 0;
	m_Subjects->NotifyObservers(Observer::Event::SCORE_CHANGE, GetOwner());
}

void HighScoreListComponent::AddScore(int points)
{
	m_Score += points;
	m_Subjects->NotifyObservers(Observer::Event::SCORE_CHANGE, GetOwner());
}

int HighScoreListComponent::GetScore()
{
	return m_Score;
}

void HighScoreListComponent::AddObserver(Observer* observer)
{
	m_Subjects->AddObserver(observer);
}

void HighScoreListComponent::ReadFile()
{
	std::ifstream read(m_TextFilePath);

	std::string score;
	while (std::getline(read, score))
	{
		m_Scores.push_back(std::stoi(score));
	}
	read.close();
}

void HighScoreListComponent::WriteFile()
{
	std::ofstream write(m_TextFilePath);

	for (int const score : m_Scores)
	{
		write << std::to_string(score) << "\n";
	}
	write.close();
}
