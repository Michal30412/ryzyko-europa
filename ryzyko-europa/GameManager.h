#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML/Graphics.hpp>

#include "Map.h"
#include "Gui.h"
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
	Map *map;
	Gui *gui;

	vector<Player> players_vec;
	
	int stage;

	int first_id;

	bool begun; // begun normal game (after start)
	int current_player;
	PlayerPhase current_phase;

	sf::Text text;
	sf::RectangleShape red_rectangle;
	sf::RectangleShape small_rectangles[3];
	sf::Text small_texts[3];

	sf::Text active_province_texts[3];
	sf::RectangleShape active_province_rectangle;
	sf::Text small_texts_2[3];

	sf::Text terrain_text;
	sf::RectangleShape terrain_rectangle;

	sf::Text result_text;
	sf::RectangleShape result_rectangle;

public:
	GameManager();
	GameManager(Map* _map, Gui* _gui, sf::Font &_font);
	void handleEvent(sf::Event &event);
	void setActiveProvinceText(int id, const sf::String &_text);
	void setSmallText(int id, const sf::String &_text);
	void setSmallText2(int id, const sf::String &_text);
	void setActiveProvinceTexts();
	void setCurrentPlayer(int curr);
	void setTerrainText();
	void setText(const string &str);
	void setResultText(const sf::String &str);
	void NumberInputsEvent(int clicked_id);
	void resetNumberInputsValues(int a, int b, int c);
	int changeCurrentPlayer();
	int getCurrentPlayerId() const;
	void nextTurn();
	const Player& getCurrentPlayer() const;
	void draw(sf::RenderWindow &window) const;
};

int rollDice(int numDice);
int getTerrainBonus(UnitType unit, TerrainType terrain, bool isAttack, bool isCapital);
pair<bool, wstring> resolveBattle(TerrainType terrain, bool isDefenderCapital, int attackerUnits[3], int defenderUnits[3]);

#endif