#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
class Menu {
	float menuX; // координаты меню по x
	float menuY; // координаты меню по y
	int menuStep; // расстояние между пунктами меню
	int maxMenu; // максимальное количество пунктов меню
	int sizeFont; // размер шрифта
	int mainMenuSelected; // номер текущего пункта меню 
	sf::Font font; // шрифт меню 
	sf::Text* mainMenu; // динамический массив текстовых объектов названий пунктов меню
	sf::Color menuTextColor = sf::Color::White; // цвет пунктов меню
	sf::Color choseTextColor = sf::Color::Yellow; // цвет выбора пункта меню
	sf::Color borderColor = sf::Color::Black; // цвет обводки текста пунктов меню
	sf::RenderWindow& mywindow; // ссылка на графическое окно

	void setInitText(sf::Text& text, sf::String str, float xpos, float ypos); // настройка текста пунктов меню
public:
	Menu(sf::RenderWindow& window, float menux, float menuy,
		int index, sf::String name[], int sizeFont = 60, int step = 80); // конструктор

	~Menu() { // деструктор
		delete[] mainMenu;
	}

	void draw(); // рисовка меню
	void MoveUp(); // перемещение выбора меню вверх
	void MoveDown(); // перемещение выбора меню вниз
	void setColorTextMenu(sf::Color menColor, sf::Color ChoColor,
		sf::Color BordColor); // цвет элементов игрового меню
	void alignMenu(int posx); // выравнивание положения меню
	int getSelectedMenuNumber() { // возвращает номер выбранного элемента меню
		return mainMenuSelected;
	}
};