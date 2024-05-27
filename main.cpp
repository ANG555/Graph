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
    RenderWindow window; // �������� ���� windows
    window.create(VideoMode(1300, 900), L"����", sf::Style::Close); // ��������� ����
    float width = VideoMode::getDesktopMode().width; // ��������� �������� ������� ������
    float height = VideoMode::getDesktopMode().height; // ��������� �������� ������� ������

    RectangleShape background(Vector2f(width, height)); // ������� ������������� ��� �����������
    Texture texture_window;
    if (!texture_window.loadFromFile("koshka.jpg")) return 4; // �������� � ������������� �������� � ������������ 
    background.setTexture(&texture_window);

    Font font;
    if (!font.loadFromFile("ArialRegular.ttf")) return 5; // ��������� ������ ��� ��������
    Text Titul;
    Titul.setFont(font);
    InitText(Titul, 590, 50, L"����", 70, Color(245, 245, 220), 3); // ��������� ��� ���������

    String nameMenu[]{ L"������ �����", L"������� ��������� �����",L"����� ����� � �������", L"����� ����� � ������", L"�������� ��������", L"�����"};
    Menu mymenu(window, 650, 200, 6, nameMenu, 55, 120); // ������ ����
    mymenu.setColorTextMenu(sf::Color(245, 245, 220), Color::Magenta, Color::Black); // ��������� ����� ��������� ������� ����
    mymenu.alignMenu(2); // ������������ �� ������ ������� ���� 

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Up) { mymenu.MoveUp(); } // ������� ������� �� ���������� ������� �����
                if (event.key.code == Keyboard::Down) { mymenu.MoveDown(); } // ������� ������� �� ���������� ������� ����
                if (event.key.code == Keyboard::Return) { // ������� ������� �� ���������� ������� Enter
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
    Color menu_text_color, int bord, Color border_color) { // ��������� ��������
    mtext.setCharacterSize(size_font);
    mtext.setPosition(xpos, ypos);
    mtext.setString(str);
    mtext.setFillColor(menu_text_color);
    mtext.setOutlineThickness(bord);
    mtext.setOutlineColor(border_color);
}






























//int main() {
//	setlocale(LC_ALL, "Russian"); 
//		Graph<int> graph(7);	/* �������� �����, ����������� ������� � �������� ������ ���� */
//		int amountVerts, amountEdges, vertex, sourceVertex, targetVertex, edgeWeight;
//		/* �������� ����������� ��� ����� ����� ����������
//		(���������� ���������� edgeWeight) */
//		cout << "������� ���������� ������ �����: ";
//		cin >> amountVerts; cout << endl;
//		// ���� ���������� ����� ����� � ���������� amountVerts
//		cout << "������� ���������� ����� �����: "; cin >> amountEdges;
//		cout << endl;
//		// ���� ���������� ����� ����� � amountEdges 
//		for (int i = 0; i < amountVerts; ++i) {
//			cout << "�������: "; 
//			cin >> vertex; // ���� �������
//			int* vertPtr = &vertex;
//			/* ���������� ����� ������� � ������� ��������� */
//			graph.InsertVertex(*vertPtr);
//			/* �������� ������ �� ������� � ������� InsertVertex;
//			���������� ������� ������� � ������ ������ */
//			cout << endl;
//		}
//	for (int i = 0; i < amountEdges; ++i) {
//		cout << "�������� �������: "; cin >> sourceVertex;
//		cout << endl;	// ���� �������� �������
//		int* sourceVertPtr = &sourceVertex;
//		/* ���������� ����� �������� ������� */
//		cout << "�������� �������: "; 
//		cin >> targetVertex;
//		cout << endl;
//		/* ���� �������, �� ������� ����� ���� ����� �� �������� ������� (���� �������� �������) */
//		int* targetVertPtr = &targetVertex;
//		// ���������� ����� �������� ������� 
//		cout << "��� �����: ";
//		 cin >> edgeWeight; 
//		 cout << endl;
//		 graph.InsertEdge(*sourceVertPtr, *targetVertPtr,edgeWeight);
//
//	}
//	/* ���� ��������� �������� ���� ����� �
//���������� edgeWeight */ 
//	cout << endl;
//	graph.Print();
//	cout << "������� �������, �� ������� ������ ����� ���������� �� ���������: ";
//	cin >> vertex;
//	cout << endl;	/* ���� ��������� �������, � ������� �������� ����� ����� � ������� (� ����� ������ ��� 0) */ 
//	int* vertPtr = &vertex;	/* ���������� �����
//	��������� ������� */
//	/* �������� ������� ������ ����� � �������, � ������� ���������� ������ �� ��������� �������
//	� ������ ���������� ������ */ 
//	graph.FillLabels(*vertPtr);
//	graph.Dijkstra(*vertPtr);
//}
