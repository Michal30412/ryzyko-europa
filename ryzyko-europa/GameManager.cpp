#include "GameManager.h"
#include <string>
#include <iomanip>
#include <sstream>

GameManager::GameManager()
{
	players_vec.push_back(Player(0, sf::Color::Cyan));
	players_vec.push_back(Player(1, sf::Color::Magenta));
	players_vec.push_back(Player(2, sf::Color(255, 127, 0)));

	stage = 0;

	begun = false;
	current_player = 0;
	current_phase = PlayerPhase::Recruit;
}

GameManager::GameManager(Map* _map, Gui* _gui, sf::Font &font) : GameManager()
{
	map = _map;
	gui = _gui;

	red_rectangle.setPosition((1280 - 600) / 2, 720 - 100);
	red_rectangle.setSize({ 600, 100 });
	red_rectangle.setFillColor(sf::Color::Red);

	float start_x = red_rectangle.getPosition().x + (red_rectangle.getSize().x - 3 * 100 - 2 * 20) / 2;

	text.setFont(font);
	text.setCharacterSize(32);
	text.setFillColor(sf::Color::Black);
	setText("Recruit");

	for (int i = 0; i < 3; ++i)
	{
		small_rectangles[i].setPosition(start_x + i * (100 + 20), red_rectangle.getPosition().y + 65);
		small_rectangles[i].setSize({ 100, 25 });
		small_rectangles[i].setFillColor(i == 0 ? sf::Color(255, 127, 0) : sf::Color::Yellow);
	}

	active_province_texts[0];

	active_province_rectangle.setPosition(1280 - 160, (720 - 300) / 2);
	active_province_rectangle.setSize({ 150, 300 });
	active_province_rectangle.setFillColor(sf::Color::Green);

	for (int i = 0; i < 3; ++i)
	{
		active_province_texts[i].setFont(font);
		active_province_texts[i].setCharacterSize(20);
		active_province_texts[i].setFillColor(sf::Color::Black);
		setActiveProvinceText(i, "0");

		small_texts[i].setFont(font);
		small_texts[i].setCharacterSize(20);
		small_texts[i].setFillColor(sf::Color::Black);

		small_texts_2[i].setFont(font);
		small_texts_2[i].setCharacterSize(20);
		small_texts_2[i].setFillColor(sf::Color::Black);
	}

	setSmallText(0, "I");
	setSmallText(1, "C");
	setSmallText(2, "A");

	setSmallText2(0, "I");
	setSmallText2(1, "C");
	setSmallText2(2, "A");

	terrain_rectangle.setPosition(1280 - 160, 100);
	terrain_rectangle.setSize({ 150, 50 });
	terrain_rectangle.setFillColor(sf::Color::Red);

	terrain_text.setFont(font);
	terrain_text.setCharacterSize(20);
	terrain_text.setFillColor(sf::Color::Black);
	setText("Terrain");

	result_rectangle.setPosition(1280 - 260, (720 - 500) / 2);
	result_rectangle.setSize({ 260, 500 });
	result_rectangle.setFillColor(sf::Color::Yellow);

	result_text.setFont(font);
	result_text.setCharacterSize(16);
	result_text.setFillColor(sf::Color::Black);
	setResultText("");
}

void GameManager::setActiveProvinceText(int id, const sf::String &_text)
{
	active_province_texts[id].setString(_text);
	sf::FloatRect r = active_province_texts[id].getLocalBounds();

	active_province_texts[id].setPosition((float)active_province_rectangle.getPosition().x + ((float)active_province_rectangle.getSize().x - r.width) / 2.f - r.left, (float)active_province_rectangle.getPosition().y + (id * 100.f) + (100.f - r.height) / 2.f - r.top);
}

void GameManager::setSmallText(int id, const sf::String &_text)
{
	small_texts[id].setString(_text);
	sf::FloatRect r = small_texts[id].getLocalBounds();

	small_texts[id].setPosition(140, 310.f + (id * 60.f) + (50.f - r.height) / 2.f - r.top);
}

void GameManager::setSmallText2(int id, const sf::String &_text)
{
	small_texts_2[id].setString(_text);
	sf::FloatRect r = small_texts_2[id].getLocalBounds();

	small_texts_2[id].setPosition(1280 - 150, (float)active_province_rectangle.getPosition().y + (id * 100.f) + (100.f - r.height) / 2.f - r.top);
}

void GameManager::setActiveProvinceTexts()
{
	if (map->active_province_id == -1)
		return;

	Units& units = map->getActiveProvince().getUnits();
	for (int i = 0; i < 3; ++i)
		setActiveProvinceText(i, to_string(units.count_tab[i]));
}

void GameManager::handleEvent(sf::Event &event)
{
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
	{
		GuiCompType type = gui->handleEvent(event);

		switch (type)
		{
		case GuiCompType::Butt1: // Next turn
			if (!begun)
			{
				nextTurn();
				break;
			}

			switch (current_phase)
			{
			case PlayerPhase::Recruit:
				nextTurn();
				break;
			case PlayerPhase::Move:
				if (stage == 0)
				{
					first_id = map->getActiveProvinceId();
					if (first_id == -1)
						break;
					Units& units = map->getActiveProvince().getUnits();
					resetNumberInputsValues(units.count_tab[0], units.count_tab[1], units.count_tab[2]);
					++stage;
				}
				else if (stage == 1)
				{
					if (map->getActiveProvinceId() == -1)
						break;
					++stage;
				}
				else if (stage >= 2)
				{
					nextTurn();
				}
				break;
			case PlayerPhase::Attack:
				if (stage == 0)
				{
					first_id = map->getActiveProvinceId();
					if (first_id == -1)
						break;
					Units& units = map->getActiveProvince().getUnits();
					resetNumberInputsValues(units.count_tab[0], units.count_tab[1], units.count_tab[2]);
					++stage;
				}
				else if (stage == 1)
				{
					if (map->getActiveProvinceId() == -1)
						break;
					++stage;
				}
				else if (stage >= 2)
				{
					pair<bool, wstring> succ = resolveBattle(map->getActiveProvince().getType(), map->getActiveProvince().getCapital(), map->provinces_vec[first_id].getUnits().count_tab, map->getActiveProvince().getUnits().count_tab);
					if (succ.first)
					{
						map->getActiveProvince().setPlayerIndex(current_player);
						map->getActiveProvince().setBasicColor(players_vec[current_player].getColor(), map->image);
						map->texture.loadFromImage(map->image);

						swap(map->getActiveProvince().getUnits(), map->provinces_vec[first_id].getUnits());
					}
					setResultText(succ.second); // text
					nextTurn();
				}
				break;
			case PlayerPhase::NextPlayer:
				nextTurn();
				break;
			}
			break;
		case GuiCompType::NumInp1:
			NumberInputsEvent(0);
			break;
		case GuiCompType::NumInp2:
			NumberInputsEvent(1);
			break;
		case GuiCompType::NumInp3:
			NumberInputsEvent(2);
			break;
		default: // not clicked on any of gui components
		{
			if (!begun)
			{
				map->updateActiveProvince(event.mouseButton.x, event.mouseButton.y, false);
				setTerrainText();
				break;
			}

			switch (current_phase)
			{
			case Recruit:
				map->updateActiveProvince(event.mouseButton.x, event.mouseButton.y, false);
				break;
			case Move:
				if (stage == 0 || stage == 1)
					map->updateActiveProvince(event.mouseButton.x, event.mouseButton.y, false);
				break;
			case Attack:
				if (stage == 0)
					map->updateActiveProvince(event.mouseButton.x, event.mouseButton.y, true);
				else if (stage == 1)
					map->updateActiveProvince(event.mouseButton.x, event.mouseButton.y, false);
				break;
			case NextPlayer:
				break;
			}

			setActiveProvinceTexts();
			setTerrainText();
			break;
		}
		}
	}
	}
}

void GameManager::setCurrentPlayer(int curr)
{
	current_player = curr;
}

void GameManager::setTerrainText()
{
	if (map->active_province_id == -1)
		return;

	switch (map->getActiveProvince().getType())
	{
	case TerrainType::Plains:
		terrain_text.setString("Plains");
		break;
	case TerrainType::Forest:
		terrain_text.setString("Forest");
		break;
	case TerrainType::City:
		terrain_text.setString("City");
		break;
	case TerrainType::Mountains:
		terrain_text.setString("Mountains");
		break;
	}
	sf::FloatRect rect = terrain_text.getLocalBounds();
	terrain_text.setPosition(terrain_rectangle.getPosition().x + (terrain_rectangle.getSize().x - rect.width) / 2 - rect.left, terrain_rectangle.getPosition().y + (terrain_rectangle.getSize().y - rect.height) / 2 - rect.top);
}

void GameManager::setText(const string &str)
{
	text.setString(str);

	sf::FloatRect rect = text.getLocalBounds();
	text.setPosition(red_rectangle.getPosition().x + (red_rectangle.getSize().x - rect.width) / 2 - rect.left, red_rectangle.getPosition().y + (75 - rect.height) / 2 - rect.top);
}

void GameManager::setResultText(const sf::String &str)
{
	result_text.setString(str);

	sf::FloatRect rect = result_text.getLocalBounds();
	result_text.setPosition(result_rectangle.getPosition().x + (result_rectangle.getSize().x - rect.width) / 2 - rect.left, result_rectangle.getPosition().y + (result_rectangle.getSize().y - rect.height) / 2 - rect.top);
}

void GameManager::NumberInputsEvent(int clicked_id)
{
	if (!begun)
		return;

	switch (current_phase)
	{
	case Recruit:
	{
		NumberInput* num_inp = (NumberInput*)gui->getComponent(clicked_id + 1);

		int diff = num_inp->getDifference();

		players_vec[current_player].getCards().count_tab[clicked_id] += diff;
		map->getActiveProvince().getUnits().count_tab[clicked_id] -= diff;

		setActiveProvinceTexts();
	}
		break;
	case Move:
	{
		if (stage == 2)
		{
			NumberInput* num_inp = (NumberInput*)gui->getComponent(clicked_id + 1);

			int diff = num_inp->getDifference();

			map->provinces_vec[first_id].getUnits().count_tab[clicked_id] += diff;
			map->getActiveProvince().getUnits().count_tab[clicked_id] -= diff;

			setActiveProvinceTexts();
		}
	}
		break;
	case Attack:
		break;
	case NextPlayer:
		break;
	default:
		break;
	}
}

void GameManager::resetNumberInputsValues(int a, int b, int c)
{
	((NumberInput*)gui->getComponent(GuiCompType::NumInp1))->setValue(a);
	((NumberInput*)gui->getComponent(GuiCompType::NumInp2))->setValue(b);
	((NumberInput*)gui->getComponent(GuiCompType::NumInp3))->setValue(c);
}

int GameManager::changeCurrentPlayer()
{
	current_player = (current_player + 1) % players_vec.size();

	if (current_player == 0)
		begun = true;

	players_vec[current_player].startTurn();
	Units& cards = players_vec[current_player].getCards();
	resetNumberInputsValues(cards.count_tab[0], cards.count_tab[1], cards.count_tab[2]);

	return current_player;
}

int GameManager::getCurrentPlayerId() const
{
	return current_player;
}

void GameManager::nextTurn()
{
	// end turn

	if (!begun)
	{
		if (map->getActiveProvinceId() == -1)
			return;

		Province& active_province = map->getActiveProvince();
		if (active_province.getPlayerIndex() != -1)
			return;

		active_province.setPlayerIndex(current_player);
		active_province.setBasicColor(players_vec[current_player].getColor(), map->image);
		map->texture.loadFromImage(map->image);

		changeCurrentPlayer();
		map->setActiveProvince(-1);
		if (current_player == 0)
		{
			((Button*)gui->getComponent(GuiCompType::Butt1))->setText("Recruit");
			cout << "The game has begun\n";
		}
		return;
	}

	// start new turn

	current_phase = (PlayerPhase)((current_phase + 1) % 4);
	map->setActiveProvince(-1);

	if (current_phase == 0)
		changeCurrentPlayer();

	switch (current_phase)
	{
	case PlayerPhase::Recruit:
		((Button*)gui->getComponent(GuiCompType::Butt1))->setText("Recruit");

		small_rectangles[0].setFillColor(sf::Color(255, 127, 0));
		small_rectangles[1].setFillColor(sf::Color::Yellow);
		small_rectangles[2].setFillColor(sf::Color::Yellow);
		setText("Recruit");
		break;
	case PlayerPhase::Move:
		((Button*)gui->getComponent(GuiCompType::Butt1))->setText("Select Province");

		small_rectangles[0].setFillColor(sf::Color::Green);
		small_rectangles[1].setFillColor(sf::Color(255, 127, 0));
		setText("Move");
		break;
	case PlayerPhase::Attack:
		((Button*)gui->getComponent(GuiCompType::Butt1))->setText("Select Province");

		small_rectangles[1].setFillColor(sf::Color::Green);
		small_rectangles[2].setFillColor(sf::Color(255, 127, 0));
		setText("Attack");
		break;
	case PlayerPhase::NextPlayer:
		((Button*)gui->getComponent(GuiCompType::Butt1))->setText("Next");

		small_rectangles[2].setFillColor(sf::Color::Green);
		setText("Next Player");
		break;
	}

	stage = 0;
}

const Player& GameManager::getCurrentPlayer() const
{
	return players_vec.at(current_player);
}

void GameManager::draw(sf::RenderWindow &window) const
{
	map->draw(window);

	window.draw(red_rectangle);
	window.draw(text);

	if ((current_phase == PlayerPhase::Recruit || current_phase == PlayerPhase::NextPlayer || stage == 2) && begun)
	{
		gui->draw(window, true);

		for (int i = 0; i < 3; ++i)
			window.draw(small_texts[i]);
	}
	else
		gui->draw(window, false);

	if (current_phase == PlayerPhase::NextPlayer)
	{
		window.draw(result_rectangle);
		window.draw(result_text);
	}

	if (map->active_province_id != -1)
	{
		window.draw(terrain_rectangle);
		window.draw(terrain_text);
	}

	if (begun)
	{
		for (int i = 0; i < 3; ++i)
			window.draw(small_rectangles[i]);

		if (map->active_province_id != -1)
		{
			window.draw(active_province_rectangle);
			for (int i = 0; i < 3; ++i)
			{
				window.draw(active_province_texts[i]);
				window.draw(small_texts_2[i]);
			}
		}
	}
}

// Pomocnicza funkcja: losowanie sumy oczek z koœci
int rollDice(int numDice)
{
	int total = 0;
	for (int i = 0; i < numDice; ++i)
		total += (rand() % 6) + 1;
	return total;
}

// Funkcja pomocnicza do bonusu za teren
int getTerrainBonus(UnitType unit, TerrainType terrain, bool isAttack, bool isCapital)
{
	int bonus = 0;
	if (unit == UnitType::Infantry) {
		if (isAttack) {
			if (terrain == TerrainType::City || terrain == TerrainType::Forest) bonus += 1;
		}
		else {
			if (terrain == TerrainType::City || terrain == TerrainType::Forest) bonus += 2;
			if (terrain == TerrainType::Mountains) bonus += 3;
			if (terrain == TerrainType::Plains) bonus -= 2;
		}
	}
	else if (unit == UnitType::Cavalry) {
		if (isAttack) {
			if (terrain == TerrainType::Plains) bonus += 3;
			if (terrain == TerrainType::Mountains) bonus -= 3;
		}
		else {
			if (terrain == TerrainType::Plains) bonus += 3;
			if (terrain == TerrainType::Mountains) bonus -= 2;
			if (terrain == TerrainType::Forest) bonus -= 1;
		}
	}
	else if (unit == UnitType::Artillery) {
		if (isAttack) {
			if (terrain == TerrainType::Plains) bonus += 1;
			if (terrain == TerrainType::City) bonus += 2;
			if (terrain == TerrainType::Forest) bonus -= 1;
			if (terrain == TerrainType::Mountains) bonus -= 2;
		}
		else {
			if (terrain == TerrainType::Mountains) bonus += 2;
			if (terrain == TerrainType::Forest) bonus -= 1;
			if (terrain == TerrainType::Plains) bonus += 1;
			if (terrain == TerrainType::City) bonus += 2;
		}
	}
	if (!isAttack && isCapital)
		bonus += 3;

	return bonus;
}

// W³aœciwa funkcja bitwy
pair<bool, wstring> resolveBattle(TerrainType terrain, bool isDefenderCapital, int attackerUnits[3], int defenderUnits[3])
{
	int attackStrength = 0, defenseStrength = 0;
	wostringstream log;

	// --- Atak ---
	log << L"[ATAK]\n";
	for (int i = 0; i < 3; ++i) {
		UnitType type = static_cast<UnitType>(i);
		int diceCount = (type == UnitType::Infantry ? 2 : (type == UnitType::Cavalry ? 3 : 1));
		wstring typeName = (i == 0 ? L"Piechota" : (i == 1 ? L"Kawaleria" : L"Artyleria"));

		if (attackerUnits[i] > 0)
			log << typeName << L" (" << attackerUnits[i] << L" jednostek):\n";

		for (int j = 0; j < attackerUnits[i]; ++j) {
			int unitTotal = 0;
			log << L"  Jednostka " << j + 1 << L": ";
			for (int d = 0; d < diceCount; ++d) {
				int roll = rollDice(1);
				unitTotal += roll;
				log << roll << L" ";
			}
			int bonus = getTerrainBonus(type, terrain, true, false);
			unitTotal += bonus;
			attackStrength += unitTotal;
			log << L"+ premia " << bonus << L" = " << unitTotal << L"\n";
		}
	}

	// --- Obrona ---
	log << L"\n[OBRONA]\n";
	for (int i = 0; i < 3; ++i) {
		UnitType type = static_cast<UnitType>(i);
		int diceCount = (type == UnitType::Infantry ? 2 : (type == UnitType::Cavalry ? 1 : 3));
		wstring typeName = (i == 0 ? L"Piechota" : (i == 1 ? L"Kawaleria" : L"Artyleria"));

		if (defenderUnits[i] > 0)
			log << typeName << L" (" << defenderUnits[i] << L" jednostek):\n";

		for (int j = 0; j < defenderUnits[i]; ++j) {
			int unitTotal = 0;
			log << L"  Jednostka " << j + 1 << L": ";
			for (int d = 0; d < diceCount; ++d) {
				int roll = rollDice(1);
				unitTotal += roll;
				log << roll << L" ";
			}
			int bonus = getTerrainBonus(type, terrain, false, isDefenderCapital);
			unitTotal += bonus;
			defenseStrength += unitTotal;
			log << L"+ premia " << bonus << L" = " << unitTotal << L"\n";
		}
	}

	log << L"\nSi³a ataku: " << attackStrength << L", si³a obrony: " << defenseStrength << L"\n";

	// --- Wynik i straty ---
	if (attackStrength > defenseStrength) {
		log << L"Atakuj¹cy wygrywa!\n";
		int totalAttackers = attackerUnits[0] + attackerUnits[1] + attackerUnits[2];
		float lossRatio = (float)defenseStrength / attackStrength;
		int totalLoss = static_cast<int>(lossRatio * totalAttackers);

		attackerUnits[0] = max(0, attackerUnits[0] - totalLoss);
		attackerUnits[1] = max(0, attackerUnits[1] - (totalLoss > 1 ? 1 : 0));
		attackerUnits[2] = max(0, attackerUnits[2] - (totalLoss > 2 ? 1 : 0));

		defenderUnits[0] = defenderUnits[1] = defenderUnits[2] = 0;

		log << L"Pozostali atakuj¹cy: P: " << attackerUnits[0]
			<< L", K: " << attackerUnits[1]
			<< L", A: " << attackerUnits[2] << L"\n";

		return { true, log.str() };
	}
	else {
		log << L"Obroñca wygrywa!\n";
		int totalDefenders = defenderUnits[0] + defenderUnits[1] + defenderUnits[2];
		float lossRatio = (float)attackStrength / defenseStrength;
		int totalLoss = static_cast<int>(lossRatio * totalDefenders);

		defenderUnits[0] = max(0, defenderUnits[0] - totalLoss);
		defenderUnits[1] = max(0, defenderUnits[1] - (totalLoss > 1 ? 1 : 0));
		defenderUnits[2] = max(0, defenderUnits[2] - (totalLoss > 2 ? 1 : 0));

		attackerUnits[0] = attackerUnits[1] = attackerUnits[2] = 0;

		log << L"Pozostali obroñcy: P: " << defenderUnits[0]
			<< L", K: " << defenderUnits[1]
			<< L", A: " << defenderUnits[2] << L"\n";

		return { false, log.str() };
	}
}