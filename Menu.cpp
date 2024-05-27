#include "Menu.h"

void Menu::setInitText(sf::Text& text, sf::String str, float xpos, float ypos) { //настройки текстовых объектов пунктов игрового меню
	text.setFont(font); // шрифт
	text.setFillColor(menuTextColor); // цвет 
	text.setString(str); // текст
	text.setCharacterSize(sizeFont); // размер шрифта
	text.setPosition(xpos, ypos); // координаты текстового объекта
	text.setOutlineThickness(0.5); // толщина контура обводки текста
	text.setOutlineColor(borderColor); // цвет контура обводки текста
}

void Menu::alignMenu(int posx) { // выравнивание пунктов меню по левому по правому по центру 
	float nullx = 0;
	for (int i = 0; i < maxMenu; i++) {
		switch (posx)
		{
		case 0:
			nullx = 0; // выравнивание по правому краю от установленных координат
			break;
		case 1:
			nullx = mainMenu[i].getLocalBounds().width;  // по левому краю
			break;
		case 2:
			nullx = nullx = mainMenu[i].getLocalBounds().width / 2;  // по центру
			break;
		}
		mainMenu[i].setPosition(mainMenu[i].getPosition().x - nullx, mainMenu[i].getPosition().y);
	}

}

Menu::Menu(sf::RenderWindow& window, float menux, float menuy,
	int index, sf::String name[], int sizeFont, int step)
	:mywindow(window), menuX(menux), menuY(menuy), sizeFont(sizeFont), menuStep(step) {
	// Загрузка шрифта
	if (!font.loadFromFile("ArialRegular.ttf")) exit(32); // загрузка шрифта
	maxMenu = index; // количество элементов меню 
	mainMenu = new sf::Text[maxMenu]; // динамический массив пунктов меню
	for (int i = 0, ypos = menuY; i < maxMenu; i++, ypos += menuStep) // выстраивание элементов меню
		setInitText(mainMenu[i], name[i], menuX, ypos);
	mainMenuSelected = 0; // задание начальное положения выбраного пункта меню
	mainMenu[mainMenuSelected].setFillColor(choseTextColor); // цвет выбраного пункта меню
}

void Menu::MoveUp()
{
	mainMenuSelected--;
	if (mainMenuSelected >= 0) { // подсвечивание выбранного пункта меню
		mainMenu[mainMenuSelected].setFillColor(choseTextColor);
		mainMenu[mainMenuSelected + 1].setFillColor(menuTextColor);
	}
	else
	{
		mainMenu[0].setFillColor(menuTextColor);
		mainMenuSelected = maxMenu - 1;
		mainMenu[mainMenuSelected].setFillColor(choseTextColor);
	}
}

void Menu::MoveDown() {
	mainMenuSelected++;
	if (mainMenuSelected < maxMenu) { // подсвечивание выбранного пункта меню
		mainMenu[mainMenuSelected - 1].setFillColor(menuTextColor);
		mainMenu[mainMenuSelected].setFillColor(choseTextColor);
	}
	else
	{
		mainMenu[maxMenu - 1].setFillColor(menuTextColor);
		mainMenuSelected = 0;
		mainMenu[mainMenuSelected].setFillColor(choseTextColor);
	}

}

void Menu::draw() {
	for (int i = 0; i < maxMenu; i++) mywindow.draw(mainMenu[i]); // перебор для отрисовки существующих текстовых объектов пунктов меню 
}

void Menu::setColorTextMenu(sf::Color menColor, sf::Color ChoColor, sf::Color BordColor) {
	menuTextColor = menColor; // цвет пунктов меню
	choseTextColor = ChoColor; // цвет выбраного пункта меню
	borderColor = BordColor; // цвет контура пунктов меню

	for (int i = 0; i < maxMenu; i++) {
		mainMenu[i].setFillColor(menuTextColor);
		mainMenu[i].setOutlineColor(borderColor);
	}

	mainMenu[mainMenuSelected].setFillColor(choseTextColor);
}