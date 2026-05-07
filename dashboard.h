#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <optional>
#include <cstdio>

using namespace std;



class Dashboard
{

private:

    sf::Font font;

    string userName;

    string months[12];
    string monthFiles[12];

    int selectedMonth;
    int selectedStep;
    int selectedDomain;
    int activeField;
    int domainScroll;

    bool restartApp;



    double monthlySalary[12];
    double monthlySpendLimit[12];
    double actualSpend[12][30];



    string domainName[30];
    double domainLimit[30];
    int domainCount;



    string nameText;
    string salaryText;
    string spendLimitText;
    string domainText;
    string domainLimitText;
    string actualText;



public:

    Dashboard();

    void run();



private:

    bool loadFont();

    bool isInside(float mouseX, float mouseY, float x, float y, float width, float height);

    double toDouble(string text);

    string money(double amount);

    string shortText(string text, int limit);

    string percentText(double value);

    double getTotalActual(int monthIndex);

    double getTotalDomainLimit();

    string getMonthName(int index);

    string getMonthFileName(int index);



    void loadProfile();

    void saveProfile();

    void loadDomains();

    void saveDomains();

    void loadAllMonths();

    void loadMonth(int index);

    void saveMonth(int index);

    void saveReport(int index);

    void saveAnnualReport();

    void exportAnnualReportToWord();

    void showAnnualReportWindow();

    void clearEverything();



    void typeInto(string& text, char32_t value, bool onlyNumber);



    void drawText(sf::RenderWindow& window, string textValue, int size, float x, float y, sf::Color color, bool bold);

    void drawCenteredText(sf::RenderWindow& window, string textValue, int size, float x, float y, float width, float height, sf::Color color, bool bold);

    void drawRoundFill(sf::RenderWindow& window, float x, float y, float width, float height, float radius, sf::Color color);

    void drawRoundBox(sf::RenderWindow& window, float x, float y, float width, float height, float radius, sf::Color fillColor, sf::Color borderColor);

    void drawPanel(sf::RenderWindow& window, float x, float y, float width, float height);

    void drawBar(sf::RenderWindow& window, float x, float y, float width, float height, double ratio, sf::Color color);

    void drawButton(sf::RenderWindow& window, float x, float y, float width, float height, string textValue, bool selected);

    void drawInputBox(sf::RenderWindow& window, float x, float y, float width, float height, string label, string value, bool selected);

    void drawCard(sf::RenderWindow& window, float x, float y, float width, float height, string title, string value, string note, sf::Color accent);

    void drawMonthMenu(sf::RenderWindow& window, float startX, float startY);

    void drawTopBar(sf::RenderWindow& window);

    void drawStepMenu(sf::RenderWindow& window);

    void drawVerticalScrollBar(sf::RenderWindow& window, float x, float y, float height, int scrollValue, int maxScroll, int visibleRows, int totalRows);



    bool runNameWindow();

    bool runDomainWindow();

    void runMainWindow();



    void drawFoundationPanel(sf::RenderWindow& window);

    void drawLimitPanel(sf::RenderWindow& window);

    void drawActualPanel(sf::RenderWindow& window);

    void drawReportPanel(sf::RenderWindow& window);

    void drawDashboard(sf::RenderWindow& window);



    void handleMainMouse(float mouseX, float mouseY, sf::RenderWindow& window);

    void handleEnterKey();

};