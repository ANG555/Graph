#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
using namespace sf;
void drawGraph() { // отрисовка графа
	RenderWindow window(VideoMode(1300, 700), L"Граф", sf::Style::Close);
	Font font;
	if (!font.loadFromFile("ArialRegular.ttf")) exit(32); // установка шрифта для названия
	sf::Color backgroundСolor(255, 192, 203);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { // событие для закрытия окна
                window.close();
            }
        }
        window.clear(backgroundСolor); // установка фона

        sf::Vector2f positions[] = { // позиции для каждой окружности
            sf::Vector2f(200.f, 50.f),
            sf::Vector2f(280.f, 200.f),
            sf::Vector2f(360.f, 350.f),
            sf::Vector2f(550.f, 490.f),
            sf::Vector2f(540.f, 10.f),
            sf::Vector2f(750.f, 100.f),
            sf::Vector2f(900.f, 300.f)
        };
        int masData[7] = { 7, 6, 4, 2, 1 , 3, 5 };
        for (int i = 0; i < 7; ++i) {
            sf::CircleShape circle(50.f); // создание окружности
            circle.setPosition(positions[i]);
            circle.setFillColor(sf::Color(245, 245, 220));

            string data = to_string(masData[i]);
            sf::Text text(data, font, 24); // устновка данных и их параметров
            text.setPosition(positions[i].x + 30, positions[i].y + 30);
            text.setFillColor(sf::Color::Black);

            window.draw(circle);
            window.draw(text);
        }

        sf::Vector2f positionsS[] = { // позиции начала линий, соединяющих окружности
            sf::Vector2f(275.f, 145.f),
            sf::Vector2f(350.f, 295.f),
            sf::Vector2f(440.f, 440.f),
            sf::Vector2f(640.f, 510.f),
            sf::Vector2f(540.f, 70.f),
            sf::Vector2f(755.f, 130.f),
            sf::Vector2f(940.f, 305.f),
            sf::Vector2f(295.f, 120.f),
            sf::Vector2f(375.f, 250.f),
            sf::Vector2f(600.f, 490.f),
        };
        sf::Vector2f positionsS2[] = { // позиции конца линий, соединяющих окружности
            sf::Vector2f(310.f, 208.f),
            sf::Vector2f(390.f, 360.f),
            sf::Vector2f(560.f, 510.f),
            sf::Vector2f(910.f, 380.f),
            sf::Vector2f(300.f, 90.f),
            sf::Vector2f(630.f, 80.f),
            sf::Vector2f(830.f, 190.f),
            sf::Vector2f(900.f, 340.f),
            sf::Vector2f(750.f, 160.f),
            sf::Vector2f(590.f, 110.f),
        };
        sf::Vector2f positionsForWeight[] = { // позиции конца линий, соединяющих окружности
            sf::Vector2f(260.f, 170.f),
            sf::Vector2f(350.f, 330.f),
            sf::Vector2f(485.f, 480.f),
            sf::Vector2f(780.f, 440.f),
            sf::Vector2f(440.f, 50.f),
            sf::Vector2f(690.f, 80.f),
            sf::Vector2f(875.f, 190.f),
            sf::Vector2f(320.f, 100.f),
            sf::Vector2f(450.f, 240.f),
            sf::Vector2f(610.f, 110.f),
        };
        int masWeight[10] = { 26, 9, 23, 19, 12 , 19, 34, 47, 30, 42 };
        for (size_t i = 0; i < 10; ++i) { // добавление линий между окружностями
            sf::Vertex line[] = {
                sf::Vertex(positionsS[i]),
                sf::Vertex(positionsS2[i]),
            };
            string weight = to_string(masWeight[i]);
            sf::Text text(weight, font, 24); // устновка данных и их параметров
            text.setPosition(positionsForWeight[i].x, positionsForWeight[i].y);
            text.setFillColor(sf::Color::Black);
            window.draw(text);
            window.draw(line, 2, sf::Lines);
        }
        window.display(); // отображение на экране рисунков
    }
}

void drawDFS() { // обход графа в глубину
    sf::RenderWindow window(sf::VideoMode(1300, 700), L"Обход графа в глубину"); // создание окна
    sf::Color backgroundСolor(255, 192, 203);
    Font font;
    if (!font.loadFromFile("ArialRegular.ttf")) exit(32); // установка шрифта для названия

    vector<CircleShape> circles; // вектор для хранения всех окружностей
    vector<Text> numbers; // вектор для хранения всех номеров вершин
    vector<Vertex> lines; // вектор для хранения всех координат начала линий
    vector<Vertex> Lines; // вектор для хранения всех координат конца линий
    vector<Text> weights; // вектор для хранения всех весов 
    int masData[7] = { 1, 2, 3, 4, 5 , 6, 7 };
    sf::Vector2f positions[] = { // позиции для каждой окружности
        sf::Vector2f(540.f, 10.f),
        sf::Vector2f(550.f, 490.f),
        sf::Vector2f(750.f, 100.f),
        sf::Vector2f(360.f, 350.f),
        sf::Vector2f(900.f, 300.f),
        sf::Vector2f(280.f, 200.f),
        sf::Vector2f(200.f, 50.f),
    };
    sf::Vector2f positionsForWeight[] = { // позиции конца линий, соединяющих окружности
            sf::Vector2f(260.f, 170.f),
            sf::Vector2f(350.f, 330.f),
            sf::Vector2f(485.f, 480.f),
            sf::Vector2f(780.f, 440.f),
            sf::Vector2f(440.f, 50.f),
            sf::Vector2f(690.f, 80.f),
            sf::Vector2f(875.f, 190.f),
            sf::Vector2f(320.f, 100.f),
            sf::Vector2f(450.f, 240.f),
            sf::Vector2f(610.f, 110.f),
    };
    sf::Vector2f positionsS[] = { // позиции начала линий, соединяющих окружности
        sf::Vector2f(375.f, 250.f),
        sf::Vector2f(755.f, 130.f),
        sf::Vector2f(600.f, 490.f),
        sf::Vector2f(440.f, 440.f),
        sf::Vector2f(940.f, 305.f),
        sf::Vector2f(295.f, 120.f),
        sf::Vector2f(275.f, 145.f), 
        sf::Vector2f(350.f, 295.f),
        sf::Vector2f(640.f, 510.f),
        sf::Vector2f(540.f, 70.f),
    };
    sf::Vector2f positionsS2[] = { // позиции конца линий, соединяющих окружности
        sf::Vector2f(750.f, 160.f),
        sf::Vector2f(630.f, 80.f),
        sf::Vector2f(590.f, 110.f),
        sf::Vector2f(560.f, 510.f),
        sf::Vector2f(830.f, 190.f),
        sf::Vector2f(900.f, 340.f),
        sf::Vector2f(310.f, 208.f),
        sf::Vector2f(390.f, 360.f),
        sf::Vector2f(910.f, 380.f),
        sf::Vector2f(300.f, 90.f),
    };
    int masWeight[10] = { 26, 9, 23, 19, 12 , 19, 34, 47, 30, 42 };
    int order[7] = { 6,3,1,2,4,5,7 };
    int cnt = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && cnt < 10) { // рисование при нажатии Enter
                if (cnt < 7) {
                    sf::CircleShape circle(50.f); // размер окружности
                    circle.setFillColor(sf::Color(245, 245, 220)); // цвет заливки
                    circle.setPosition(positions[order[cnt]-1].x, positions[order[cnt]-1].y); // позиция окружности
                    circle.setOutlineThickness(4);
                    circles.push_back(circle); // добавление окружности в список
                    string data = to_string(masData[order[cnt]-1]);
                    sf::Text text(data, font, 24); // устновка данных и их параметров
                    text.setPosition(positions[order[cnt]-1].x + 30, positions[order[cnt]-1].y + 30);
                    text.setFillColor(sf::Color::Black);
                    numbers.push_back(text);
                }
                string weight = to_string(masWeight[cnt]);
                sf::Text text(weight, font, 24); // устновка данных и их параметров
                text.setPosition(positionsForWeight[cnt].x, positionsForWeight[cnt].y);
                text.setFillColor(sf::Color::Black);
                weights.push_back(text);
                lines.push_back(positionsS[cnt]);
                Lines.push_back(positionsS2[cnt]);
                cnt++;
            }
        }
        window.clear(backgroundСolor); // установка фона

        for (const auto& circle : circles) { // рисование окружностей
            window.draw(circle);
        }
        for (const auto& number : numbers) { // рисование номеров вершин
            window.draw(number);
        }
        for (const auto& text  : weights) { // рисование весов
            window.draw(text);
        }
        for (size_t i = 0; i < lines.size(); ++i) { // рисование линий
            const Vertex& linE = lines[i];
            const Vertex& linE2 = Lines[i];

            sf::Vertex line0[] = {
                {linE},
                {linE2}
            };

            window.draw(line0, 2, sf::Lines);
        }
        sf::Text text1;
        text1.setFont(font);
        text1.setString(L"Порядок посещенных вершин: ");
        text1.setFillColor(sf::Color::Black);
        text1.setCharacterSize(30);
        text1.setPosition(450, 600);
        window.draw(text1);
        sf::Text text2;
        text2.setFont(font);
        text2.setString(L"6->3->1->2->4->5->7");
        text2.setFillColor(sf::Color::Black);
        text2.setCharacterSize(30);
        text2.setPosition(900, 600);
        window.draw(text2);
        window.display();
    }
}
void drawBFS() { // обход графа в ширину
    sf::RenderWindow window(sf::VideoMode(1300, 700), L"Обход графа в ширину"); // создание окна
    sf::Color backgroundСolor(255, 192, 203);
    Font font;
    if (!font.loadFromFile("ArialRegular.ttf")) exit(32); // установка шрифта для названия

    vector<CircleShape> circles; // вектор для хранения всех окружностей
    vector<Text> numbers; // вектор для хранения всех номеров вершин
    vector<Vertex> lines; // вектор для хранения всех координат начала линий
    vector<Vertex> Lines; // вектор для хранения всех координат конца линий
    vector<Text> weights; // вектор для хранения всех весов 
    int masData[7] = { 1, 2, 3, 4, 5 , 6, 7 };
    sf::Vector2f positions[] = { // позиции для каждой окружности
        sf::Vector2f(540.f, 10.f),
        sf::Vector2f(550.f, 490.f),
        sf::Vector2f(750.f, 100.f),
        sf::Vector2f(360.f, 350.f),
        sf::Vector2f(900.f, 300.f),
        sf::Vector2f(280.f, 200.f),
        sf::Vector2f(200.f, 50.f),
    };
    sf::Vector2f positionsForWeight[] = { // позиции конца линий, соединяющих окружности
            sf::Vector2f(260.f, 170.f),
            sf::Vector2f(350.f, 330.f),
            sf::Vector2f(485.f, 480.f),
            sf::Vector2f(780.f, 440.f),
            sf::Vector2f(440.f, 50.f),
            sf::Vector2f(690.f, 80.f),
            sf::Vector2f(875.f, 190.f),
            sf::Vector2f(320.f, 100.f),
            sf::Vector2f(450.f, 240.f),
            sf::Vector2f(610.f, 110.f),
    };
    sf::Vector2f positionsS[] = { // позиции начала линий, соединяющих окружности
        sf::Vector2f(375.f, 250.f),
        sf::Vector2f(350.f, 295.f), 
        sf::Vector2f(275.f, 145.f), 
        sf::Vector2f(540.f, 70.f),
        sf::Vector2f(940.f, 305.f),
        sf::Vector2f(440.f, 440.f),
        sf::Vector2f(640.f, 510.f),
        sf::Vector2f(755.f, 130.f), 
        sf::Vector2f(295.f, 120.f),
        sf::Vector2f(600.f, 490.f),
    };
    sf::Vector2f positionsS2[] = { // позиции конца линий, соединяющих окружности
        sf::Vector2f(750.f, 160.f),
        sf::Vector2f(390.f, 360.f),
        sf::Vector2f(310.f, 208.f), 
        sf::Vector2f(300.f, 90.f),
        sf::Vector2f(830.f, 190.f),
        sf::Vector2f(560.f, 510.f),
        sf::Vector2f(910.f, 380.f),
        sf::Vector2f(630.f, 80.f),
        sf::Vector2f(900.f, 340.f),
        sf::Vector2f(590.f, 110.f),
    };
    int masWeight[10] = { 26, 9, 23, 19, 12 , 19, 34, 47, 30, 42 };
    int order[7] = { 6,3,4,7,1,5,2 };
    int cnt = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && cnt < 10) { // рисование при нажатии Enter
                if (cnt < 7) {
                    sf::CircleShape circle(50.f); // размер окружности
                    circle.setFillColor(sf::Color(245, 245, 220)); // цвет заливки
                    circle.setPosition(positions[order[cnt] - 1].x, positions[order[cnt] - 1].y); // позиция окружности
                    circle.setOutlineThickness(4);
                    circles.push_back(circle); // добавление окружности в список
                    string data = to_string(masData[order[cnt] - 1]);
                    sf::Text text(data, font, 24); // устновка данных и их параметров
                    text.setPosition(positions[order[cnt] - 1].x + 30, positions[order[cnt] - 1].y + 30);
                    text.setFillColor(sf::Color::Black);
                    numbers.push_back(text);
                }
                string weight = to_string(masWeight[cnt]);
                sf::Text text(weight, font, 24); // устновка данных и их параметров
                text.setPosition(positionsForWeight[cnt].x, positionsForWeight[cnt].y);
                text.setFillColor(sf::Color::Black);
                weights.push_back(text);
                lines.push_back(positionsS[cnt]);
                Lines.push_back(positionsS2[cnt]);
                cnt++;
            }
        }
        window.clear(backgroundСolor); // установка фона

        for (const auto& circle : circles) { // рисование всех окружностей
            window.draw(circle);
        }
        for (const auto& number : numbers) { // рисование всех номеров вершин
            window.draw(number);
        }
        for (const auto& text : weights) { // рисование всех весов
            window.draw(text);
        }
        for (size_t i = 0; i < lines.size(); ++i) {
            const Vertex& linE = lines[i];
            const Vertex& linE2 = Lines[i];

            sf::Vertex line0[] = {
                {linE},
                {linE2}
            };

            window.draw(line0, 2, sf::Lines);
        }
        sf::Text text1;
        text1.setFont(font);
        text1.setString(L"Порядок посещенных вершин: ");
        text1.setFillColor(sf::Color::Black);
        text1.setCharacterSize(30);
        text1.setPosition(450, 600);
        window.draw(text1);
        sf::Text text2;
        text2.setFont(font);
        text2.setString(L"6->3->4->7->1->5->2");
        text2.setFillColor(sf::Color::Black);
        text2.setCharacterSize(30);
        text2.setPosition(900, 600);
        window.draw(text2);
        window.display();
    }
    return;
}
void drawDijkstra() { // алгоритм декстра
    RenderWindow window(VideoMode(1500, 700), L"Алгоритм Дейкстры", sf::Style::Close);
    Font font;
    Font font2;
    if (!font2.loadFromFile("ArialRegular.ttf")) exit(32); // установка шрифта для расстояний
    if (!font.loadFromFile("ArialRegular.ttf")) exit(32); // установка шрифта для названия
    sf::Color backgroundСolor(255, 192, 203);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { // событие для закрытия окна
                window.close();
            }
        }
        window.clear(backgroundСolor); // установка фона

        sf::Vector2f positions[] = { // позиции для каждой окружности
            sf::Vector2f(340.f, 100.f),
            sf::Vector2f(350.f, 590.f),
            sf::Vector2f(550.f, 200.f),
            sf::Vector2f(160.f, 450.f),
            sf::Vector2f(700.f, 400.f),
            sf::Vector2f(80.f, 300.f),
            sf::Vector2f(10.f, 150.f),
        };
        int masData[7] = { 1, 2, 3, 4, 5 , 6, 7 };
        int masDistance[7] = { 38, 32, 30, 9, 51 , 0, 26 };
        for (int i = 0; i < 7; ++i) {
            sf::CircleShape circle(50.f); // создание окружности
            circle.setPosition(positions[i]);
            circle.setFillColor(sf::Color(245, 245, 220));

            string data = to_string(masData[i]);
            sf::Text text(data, font, 24); // устновка данных и их параметров
            text.setPosition(positions[i].x + 30, positions[i].y + 30);
            text.setFillColor(sf::Color::Black);

            string distance = to_string(masDistance[i]);
            sf::Text text2(distance, font2, 24); // устновка данных и их параметров
            text2.setPosition(positions[i].x +30, positions[i].y - 40);
            text2.setFillColor(sf::Color::Black);

            window.draw(circle);
            window.draw(text);
            window.draw(text2);
        }

        sf::Vector2f positionsS[] = { // позиции начала линий, соединяющих окружности
            sf::Vector2f(75.f, 245.f),
            sf::Vector2f(150.f, 395.f),
            sf::Vector2f(240.f, 540.f),
            sf::Vector2f(440.f, 610.f),
            sf::Vector2f(340.f, 170.f),
            sf::Vector2f(555.f, 230.f),
            sf::Vector2f(740.f, 405.f),
            sf::Vector2f(95.f, 220.f),
            sf::Vector2f(175.f, 350.f),
            sf::Vector2f(400.f, 590.f),
        };
        sf::Vector2f positionsS2[] = { // позиции конца линий, соединяющих окружности
            sf::Vector2f(110.f, 308.f),
            sf::Vector2f(190.f, 460.f),
            sf::Vector2f(360.f, 610.f),
            sf::Vector2f(710.f, 480.f),
            sf::Vector2f(100.f, 190.f),
            sf::Vector2f(430.f, 180.f),
            sf::Vector2f(630.f, 290.f),
            sf::Vector2f(700.f, 440.f),
            sf::Vector2f(550.f, 260.f),
            sf::Vector2f(390.f, 210.f),
        };
        sf::Vector2f positionsForWeight[] = { // позиции конца линий, соединяющих окружности
            sf::Vector2f(60.f, 270.f),
            sf::Vector2f(150.f, 430.f),
            sf::Vector2f(285.f, 580.f),
            sf::Vector2f(580.f, 540.f),
            sf::Vector2f(240.f, 150.f),
            sf::Vector2f(490.f, 180.f),
            sf::Vector2f(675.f, 290.f),
            sf::Vector2f(120.f, 200.f),
            sf::Vector2f(250.f, 340.f),
            sf::Vector2f(410.f, 210.f),
        };
        int masWeight[10] = { 26, 9, 23, 19, 12 , 19, 34, 47, 30, 42 };
        for (size_t i = 0; i < 10; ++i) { // добавление линий между окружностями
            sf::Vertex line[] = {
                sf::Vertex(positionsS[i]),
                sf::Vertex(positionsS2[i]),
            };
            string weight = to_string(masWeight[i]);
            sf::Text text(weight, font, 24); // устновка данных и их параметров
            text.setPosition(positionsForWeight[i].x, positionsForWeight[i].y);
            text.setFillColor(sf::Color::Black);
            window.draw(text);
            window.draw(line, 2, sf::Lines);
        }
        sf::Text text(L"Кратчайшее расстояние от вершины 6 до вершины 1 равно 38", font, 24); // устновка данных и их параметров
        text.setPosition(700, 10);
        text.setFillColor(sf::Color::Black);
        window.draw(text);
        sf::Text text2(L"Кратчайшее расстояние от вершины 6 до вершины 2 равно 32", font, 24); // устновка данных и их параметров
        text2.setPosition(700, 40);
        text2.setFillColor(sf::Color::Black);
        window.draw(text2);
        sf::Text text3(L"Кратчайшее расстояние от вершины 6 до вершины 3 равно 30", font, 24); // устновка данных и их параметров
        text3.setPosition(700, 70);
        text3.setFillColor(sf::Color::Black);
        window.draw(text3);
        sf::Text text4(L"Кратчайшее расстояние от вершины 6 до вершины 4 равно 9", font, 24); // устновка данных и их параметров
        text4.setPosition(700, 100);
        text4.setFillColor(sf::Color::Black);
        window.draw(text4);
        sf::Text text5(L"Кратчайшее расстояние от вершины 6 до вершины 5 равно 51", font, 24); // устновка данных и их параметров
        text5.setPosition(700, 130);
        text5.setFillColor(sf::Color::Black);
        window.draw(text5);
        sf::Text text6(L"Кратчайшее расстояние от вершины 6 до вершины 7 равно 26", font, 24); // устновка данных и их параметров
        text6.setPosition(700, 160);
        text6.setFillColor(sf::Color::Black);
        window.draw(text6);
        window.display(); // отображение на экране рисунков
    }
}

void drawMatrix() { // отрисовка матрицы смежности
    RenderWindow window(VideoMode(600, 500), L"Матрица смежности", sf::Style::Close);
    Font font;
    if (!font.loadFromFile("ArialRegular.ttf")) exit(32); // установка шрифта для названия
    sf::Color backgroundСolor(255, 192, 203);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { // событие для закрытия окна
                window.close();
            }
        }
        window.clear(backgroundСolor); // установка фона

        sf::Text text(L"Матрица смежности", font, 50); // устновка данных и их параметров
        text.setPosition(70, 50);
        text.setFillColor(sf::Color::Black);
        window.draw(text);
        sf::Text text1(L"1 0 42 19 0 0 0 12", font, 35); // устновка данных и их параметров
        text1.setPosition(170, 150);
        text1.setFillColor(sf::Color::Black);
        window.draw(text1);
        sf::Text text2(L"2 42 0 0 23 19 0 0", font, 35); // устновка данных и их параметров
        text2.setPosition(170, 190);
        text2.setFillColor(sf::Color::Black);
        window.draw(text2);
        sf::Text text3(L"3 19 0 0 0 34 30 0", font, 35); // устновка данных и их параметров
        text3.setPosition(170, 230);
        text3.setFillColor(sf::Color::Black);
        window.draw(text3);
        sf::Text text4(L"4 0 23 0 0 0 9 0", font, 35); // устновка данных и их параметров
        text4.setPosition(170, 270);
        text4.setFillColor(sf::Color::Black);
        window.draw(text4);
        sf::Text text5(L"5 0 19 34 0 0 0 47", font, 35); // устновка данных и их параметров
        text5.setPosition(170, 310);
        text5.setFillColor(sf::Color::Black);
        window.draw(text5);
        sf::Text text6(L"6 0 0 30 9 0 0 26", font, 35); // устновка данных и их параметров
        text6.setPosition(170, 350);
        text6.setFillColor(sf::Color::Black);
        window.draw(text6);
        sf::Text text7(L"7 12 0 0 0 47 26 0", font, 35); // устновка данных и их параметров
        text7.setPosition(170, 390);
        text7.setFillColor(sf::Color::Black);
        window.draw(text7);
        window.display(); // отображение на экране рисунков
    } 
}