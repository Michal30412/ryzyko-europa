#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SfML/Graphics.hpp>

#include "Player.h"

enum PlayerPhase
{
	Recruit,
	Move,
	Attack,
	NextPlayer
};

class GameManager
{
	vector<Player> players_vec;
	
	int current_player;
	PlayerPhase current_phase;

	sf::Text text;
	sf::RectangleShape red_rectangle;
	sf::RectangleShape small_rectangles[3];

	void setText(const string &str);

public:
	GameManager();
	GameManager(sf::Font &_font);
	void setCurrentPlayer(int curr);
	int changeCurrentPlayer();
	int getCurrentPlayerId() const;
	void nextTurn();
	const Player& getCurrentPlayer() const;
	void draw(sf::RenderWindow &window) const;
};

#endif