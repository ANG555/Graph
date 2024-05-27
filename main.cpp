#include "Graphs.h"
#include "Menu.h"
#include "WorkButton.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
using namespace std;
using namespace sf;
void InitText(Text& mtext, float xpos, float ypos, String str, int size_font = 60,
    Color menu_text_color = Color::White, int bord = 0, Color border_color = Color::Black);
int main() {
    system("chcp 1251 > Null");
    RenderWindow window; // создание окна windows
    window.create(VideoMode(1300, 900), L"Меню", sf::Style::Close); // параметры окна
    float width = VideoMode::getDesktopMode().width; // получение текущего размера экрана
    float height = VideoMode::getDesktopMode().height; // получение текущего размера экрана

    RectangleShape background(Vector2f(width, height)); // создаем прямоугольник для изображения
    Texture texture_window;
    if (!texture_window.loadFromFile("koshka.jpg")) return 4; // загрузка в прямоугольник текстуру с изображением 
    background.setTexture(&texture_window);

    Font font;
    if (!font.loadFromFile("ArialRegular.ttf")) return 5; // установка шрифта для названия
    Text Titul;
    Titul.setFont(font);
    InitText(Titul, 590, 50, L"Граф", 70, Color(245, 245, 220), 3); // параметры для заголовка

    String nameMenu[]{ L"Печать графа", L"Матрица смежности графа",L"Обход графа в глубину", L"Обход графа в ширину", L"Алгоритм Дейкстры", L"Выход"};
    Menu mymenu(window, 650, 200, 6, nameMenu, 55, 120); // объект меню
    mymenu.setColorTextMenu(sf::Color(245, 245, 220), Color::Magenta, Color::Black); // установка цвета элементов пунктов меню
    mymenu.alignMenu(2); // выравнивание по центру пунктов меню 

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Up) { mymenu.MoveUp(); } // событие нажатия на клавиатуре стрелки вверх
                if (event.key.code == Keyboard::Down) { mymenu.MoveDown(); } // событие нажатия на клавиатуре стрелки вниз
                if (event.key.code == Keyboard::Return) { // событие нажатия на клавиатуре клавиши Enter
                    switch (mymenu.getSelectedMenuNumber()) {
                    case 0: drawGraph(); break;
                    case 1: drawMatrix(); break;
                    case 2: drawDFS(); break;
                    case 3: drawBFS(); break;
                    case 4: drawDijkstra(); break;
                    case 5: window.close();
                    }
                }
            }
        }
        window.draw(background);
        window.draw(Titul);
        mymenu.draw();
        window.display();
    }
    return 0;
}
void InitText(Text& mtext, float xpos, float ypos, String str, int size_font,
    Color menu_text_color, int bord, Color border_color) { // установка настроек
    mtext.setCharacterSize(size_font);
    mtext.setPosition(xpos, ypos);
    mtext.setString(str);
    mtext.setFillColor(menu_text_color);
    mtext.setOutlineThickness(bord);
    mtext.setOutlineColor(border_color);
}






























//int main() {
//	setlocale(LC_ALL, "Russian"); 
//		Graph<int> graph(7);	/* Создание графа, содержащего вершины с номерами целого типа */
//		int amountVerts, amountEdges, vertex, sourceVertex, targetVertex, edgeWeight;
//		/* Создание необходимых для ввода графа переменных
//		(добавилась переменная edgeWeight) */
//		cout << "Введите количество вершин графа: ";
//		cin >> amountVerts; cout << endl;
//		// Ввод количества ребер графа в переменную amountVerts
//		cout << "Введите количество ребер графа: "; cin >> amountEdges;
//		cout << endl;
//		// Ввод количества ребер графа в amountEdges 
//		for (int i = 0; i < amountVerts; ++i) {
//			cout << "Вершина: "; 
//			cin >> vertex; // Ввод вершины
//			int* vertPtr = &vertex;
//			/* Запоминаем адрес вершины с помощью указателя */
//			graph.InsertVertex(*vertPtr);
//			/* Передаем ссылку на вершину в функцию InsertVertex;
//			происходит вставка вершины в вектор вершин */
//			cout << endl;
//		}
//	for (int i = 0; i < amountEdges; ++i) {
//		cout << "Исходная вершина: "; cin >> sourceVertex;
//		cout << endl;	// ввод исходной вершины
//		int* sourceVertPtr = &sourceVertex;
//		/* Запоминаем адрес исходной вершины */
//		cout << "Конечная вершина: "; 
//		cin >> targetVertex;
//		cout << endl;
//		/* Ввод вершины, до которой будет идти ребро от исходной вершины (ввод конечной вершины) */
//		int* targetVertPtr = &targetVertex;
//		// Запоминаем адрес конечной вершины 
//		cout << "Вес ребра: ";
//		 cin >> edgeWeight; 
//		 cout << endl;
//		 graph.InsertEdge(*sourceVertPtr, *targetVertPtr,edgeWeight);
//
//	}
//	/* Ввод числового значения веса ребра в
//переменную edgeWeight */ 
//	cout << endl;
//	graph.Print();
//	cout << "Введите вершину, от которой хотите найти расстояния до остальных: ";
//	cin >> vertex;
//	cout << endl;	/* Ввод начальной вершины, с которой начнется обход графа в глубину (в нашем случае это 0) */ 
//	int* vertPtr = &vertex;	/* Запоминаем адрес
//	введенной вершины */
//	/* Вызываем функцию обхода графа в глубину, в функцию передаются ссылка на введенную вершину
//	и вектор посещенных вершин */ 
//	graph.FillLabels(*vertPtr);
//	graph.Dijkstra(*vertPtr);
//}
