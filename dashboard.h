#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;



class DashboardMemberA
{

private:

    sf::Font font;

    string months[12];



public:

    DashboardMemberA();



    bool loadFont();

    bool isInside(float mouseX, float mouseY, float x, float y, float width, float height);

    string money(double amount);

    string shortText(string text, int limit);



    void drawText(sf::RenderWindow& window, string text, int size, float x, float y, sf::Color color, bool bold);

    void drawRoundFill(sf::RenderWindow& window, float x, float y, float width, float height, float radius, sf::Color color);

    void drawRoundBox(sf::RenderWindow& window, float x, float y, float width, float height, float radius, sf::Color fillColor, sf::Color borderColor);

    void drawButton(sf::RenderWindow& window, float x, float y, float width, float height, string text, bool selected);

    void drawCard(sf::RenderWindow& window, float x, float y, float width, float height, string title, string value, string note);

    void drawMonthMenu(sf::RenderWindow& window, int selectedMonth);

    void drawStarterDashboard(sf::RenderWindow& window, string userName, int selectedMonth);



    void runStarterDashboard();

};