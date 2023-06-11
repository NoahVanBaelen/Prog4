#pragma once
#include "BaseComponent.h"
#include "Subject.h"

class HighScoreListComponent final : public BaseComponent
{
public:
	HighScoreListComponent(dae::GameObject* pOwner);

	HighScoreListComponent(const HighScoreListComponent& other) = delete;
	HighScoreListComponent(HighScoreListComponent&& other) = delete;
	HighScoreListComponent& operator=(const HighScoreListComponent& other) = delete;
	HighScoreListComponent& operator=(HighScoreListComponent&& other) = delete;

	void SetFilePath(std::string file);
	void SetHighScoreList();
	void AddScore(int points);
	int GetScore();
	void AddObserver(Observer* observer);

private:

	void ReadFile();
	void WriteFile();

	std::string m_TextFilePath{};
	std::vector<int>m_Scores{};
	int m_Score{};

	std::unique_ptr<Subject> m_Subjects = std::make_unique<Subject>();
};

