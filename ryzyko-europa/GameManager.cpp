#include "GameManager.h"

GameManager::GameManager()
{
	players_vec.assign(3, Player());

	current_player = 0;
	current_phase = PlayerPhase::Recruit;
}

GameManager::GameManager(sf::Font &font) : GameManager()
{
	red_rectangle.setPosition((1280 - 600) / 2, 720 - 100);
	red_rectangle.setSize({ 600, 100 });
	red_rectangle.setFillColor(sf::Color::Red);

	float start_x = red_rectangle.getPosition().x + (red_rectangle.getSize().x - 3 * 100 - 2 * 20) / 2;

	for (int i = 0; i < 3; ++i)
	{
		small_rectangles[i].setPosition(start_x + i * (100 + 20), red_rectangle.getPosition().y + 65);
		small_rectangles[i].setSize({ 100, 25 });
		small_rectangles[i].setFillColor(i == 0 ? sf::Color(255, 127, 0) : sf::Color::Yellow);
	}

	text.setFont(font);
	text.setCharacterSize(32);
	text.setFillColor(sf::Color::Black);
	setText("Recruit");
}

void GameManager::setText(const string &str)
{
	text.setString(str);

	sf::FloatRect rect = text.getLocalBounds();
	text.setPosition(red_rectangle.getPosition().x + (red_rectangle.getSize().x - rect.width) / 2 - rect.left, red_rectangle.getPosition().y + (75 - rect.height) / 2 - rect.top);
}

void GameManager::setCurrentPlayer(int curr)
{
	current_player = curr;
}

int GameManager::changeCurrentPlayer()
{
	current_player = (current_player + 1) % players_vec.size();
	return current_player;
}

int GameManager::getCurrentPlayerId() const
{
	return current_player;
}

void GameManager::nextTurn()
{
	if (current_phase == PlayerPhase::Attack)
		changeCurrentPlayer();

	current_phase = (PlayerPhase)((current_phase + 1) % 4);

	switch (current_phase)
	{
	case PlayerPhase::Recruit:
		small_rectangles[0].setFillColor(sf::Color(255, 127, 0));
		small_rectangles[1].setFillColor(sf::Color::Yellow);
		small_rectangles[2].setFillColor(sf::Color::Yellow);
		setText("Recruit");
		break;
	case PlayerPhase::Move:
		small_rectangles[0].setFillColor(sf::Color::Green);
		small_rectangles[1].setFillColor(sf::Color(255, 127, 0));
		setText("Move");
		break;
	case PlayerPhase::Attack:
		small_rectangles[1].setFillColor(sf::Color::Green);
		small_rectangles[2].setFillColor(sf::Color(255, 127, 0));
		setText("Attack");
		break;
	case PlayerPhase::NextPlayer:
		small_rectangles[2].setFillColor(sf::Color::Green);
		setText("Next Player");
		break;
	}
}

const Player& GameManager::getCurrentPlayer() const
{
	return players_vec.at(current_player);
}

void GameManager::draw(sf::RenderWindow &window) const
{
	window.draw(red_rectangle);
	window.draw(text);

	for (int i = 0; i < 3; ++i)
		window.draw(small_rectangles[i]);
}