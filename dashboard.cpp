#include "dashboard.h"

#include <optional>

using namespace std;



DashboardMemberA::DashboardMemberA()
{
    months[0] = "Jan";
    months[1] = "Feb";
    months[2] = "Mar";
    months[3] = "Apr";
    months[4] = "May";
    months[5] = "Jun";
    months[6] = "Jul";
    months[7] = "Aug";
    months[8] = "Sep";
    months[9] = "Oct";
    months[10] = "Nov";
    months[11] = "Dec";
}



bool DashboardMemberA::loadFont()
{
    if (font.openFromFile("assets/arial.ttf"))
    {
        return true;
    }

    if (font.openFromFile("arial.ttf"))
    {
        return true;
    }

    if (font.openFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        return true;
    }

    cout << "Font file not found." << endl;

    return false;
}



bool DashboardMemberA::isInside(float mouseX, float mouseY, float x, float y, float width, float height)
{
    if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height)
    {
        return true;
    }

    return false;
}



string DashboardMemberA::money(double amount)
{
    stringstream ss;

    ss << "Rs. " << fixed << setprecision(0) << amount;

    return ss.str();
}



string DashboardMemberA::shortText(string text, int limit)
{
    if (text.length() <= limit)
    {
        return text;
    }

    return text.substr(0, limit - 3) + "...";
}



void DashboardMemberA::drawText(sf::RenderWindow& window, string textValue, int size, float x, float y, sf::Color color, bool bold)
{
    sf::Text text(font);

    text.setString(textValue);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition({ x, y });

    if (bold == true)
    {
        text.setStyle(sf::Text::Bold);
    }

    window.draw(text);
}



void DashboardMemberA::drawRoundFill(sf::RenderWindow& window, float x, float y, float width, float height, float radius, sf::Color color)
{
    // rounded fill

    if (radius < 1)
    {
        sf::RectangleShape box({ width, height });
        box.setPosition({ x, y });
        box.setFillColor(color);

        window.draw(box);

        return;
    }

    sf::RectangleShape middleOne({ width - radius * 2, height });
    middleOne.setPosition({ x + radius, y });
    middleOne.setFillColor(color);

    window.draw(middleOne);



    sf::RectangleShape middleTwo({ width, height - radius * 2 });
    middleTwo.setPosition({ x, y + radius });
    middleTwo.setFillColor(color);

    window.draw(middleTwo);



    sf::CircleShape circle(radius);
    circle.setPointCount(24);
    circle.setFillColor(color);



    circle.setPosition({ x, y });
    window.draw(circle);



    circle.setPosition({ x + width - radius * 2, y });
    window.draw(circle);



    circle.setPosition({ x, y + height - radius * 2 });
    window.draw(circle);



    circle.setPosition({ x + width - radius * 2, y + height - radius * 2 });
    window.draw(circle);
}



void DashboardMemberA::drawRoundBox(sf::RenderWindow& window, float x, float y, float width, float height, float radius, sf::Color fillColor, sf::Color borderColor)
{
    // rounded border box

    drawRoundFill(window, x, y, width, height, radius, borderColor);

    drawRoundFill(window, x + 1, y + 1, width - 2, height - 2, radius - 1, fillColor);
}



void DashboardMemberA::drawButton(sf::RenderWindow& window, float x, float y, float width, float height, string textValue, bool selected)
{
    // button

    sf::Color fillColor = sf::Color(15, 15, 18);
    sf::Color borderColor = sf::Color(55, 55, 62);
    sf::Color textColor = sf::Color(225, 225, 230);

    if (selected == true)
    {
        fillColor = sf::Color(45, 212, 191);
        borderColor = sf::Color(45, 212, 191);
        textColor = sf::Color(0, 0, 0);
    }

    drawRoundBox(window, x, y, width, height, height / 2, fillColor, borderColor);



    sf::Text text(font);

    text.setString(textValue);
    text.setCharacterSize(14);
    text.setFillColor(textColor);

    if (selected == true)
    {
        text.setStyle(sf::Text::Bold);
    }



    sf::FloatRect bounds = text.getLocalBounds();

    text.setOrigin({ bounds.position.x + bounds.size.x / 2, bounds.position.y + bounds.size.y / 2 });
    text.setPosition({ x + width / 2, y + height / 2 - 1 });

    window.draw(text);
}



void DashboardMemberA::drawCard(sf::RenderWindow& window, float x, float y, float width, float height, string title, string value, string note)
{
    // summary card

    drawRoundFill(window, x + 6, y + 8, width, height, 24, sf::Color(0, 0, 0, 120));

    drawRoundBox(window, x, y, width, height, 24, sf::Color(10, 10, 12), sf::Color(48, 48, 55));

    drawRoundFill(window, x + 20, y + 16, 40, 4, 2, sf::Color(45, 212, 191));



    drawText(window, title, 14, x + 20, y + 36, sf::Color(165, 170, 180), false);

    drawText(window, value, 24, x + 20, y + 68, sf::Color(245, 245, 248), true);

    drawText(window, note, 12, x + 20, y + height - 32, sf::Color(125, 130, 140), false);
}



void DashboardMemberA::drawMonthMenu(sf::RenderWindow& window, int selectedMonth)
{
    // month menu

    float startX = 900;
    float startY = 132;

    int monthNumber = 0;

    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            float x = startX + col * 125;
            float y = startY + row * 44;

            drawButton(window, x, y, 112, 36, months[monthNumber], selectedMonth == monthNumber);

            monthNumber++;
        }
    }
}



void DashboardMemberA::drawStarterDashboard(sf::RenderWindow& window, string userName, int selectedMonth)
{
    // background

    window.clear(sf::Color(0, 0, 0));



    // top bar

    sf::RectangleShape topBar({ 1360, 78 });
    topBar.setPosition({ 0, 0 });
    topBar.setFillColor(sf::Color(3, 3, 5));

    window.draw(topBar);



    drawRoundFill(window, 0, 76, 1360, 2, 0, sf::Color(45, 212, 191));



    drawText(window, "Budget & Expense Architect", 30, 32, 15, sf::Color(245, 245, 248), true);

    drawText(window, "Welcome, " + shortText(userName, 20), 14, 34, 50, sf::Color(160, 165, 175), false);



    // main title

    drawText(window, "Starter Dashboard", 24, 32, 110, sf::Color(245, 245, 248), true);

    drawText(window, "This is first SFML layout before final merging.", 14, 32, 143, sf::Color(150, 155, 165), false);



    // cards

    drawCard(window, 32, 205, 290, 132, "Monthly Salary", money(0), "will connect real input");

    drawCard(window, 350, 205, 290, 132, "Spend Limit", money(0), "Limit card placeholder");

    drawCard(window, 668, 205, 290, 132, "Actual Spend", money(0), "Expense tracking placeholder");

    drawCard(window, 986, 205, 290, 132, "Savings", money(0), "Final report placeholder");



    // left panel

    drawRoundBox(window, 32, 380, 590, 300, 28, sf::Color(10, 10, 12), sf::Color(48, 48, 55));

    drawText(window, "Input Area", 22, 62, 420, sf::Color(245, 245, 248), true);

    drawText(window, "created the visual section.", 14, 62, 456, sf::Color(155, 160, 170), false);

    drawText(window, "will continue this with actual fields.", 14, 62, 482, sf::Color(155, 160, 170), false);



    drawButton(window, 62, 545, 220, 44, "Foundation", true);

    drawButton(window, 304, 545, 220, 44, "Next", false);



    // right panel

    drawRoundBox(window, 660, 380, 668, 300, 28, sf::Color(10, 10, 12), sf::Color(48, 48, 55));

    drawText(window, "Month Selection", 22, 690, 420, sf::Color(245, 245, 248), true);

    drawText(window, "Month buttons are centered inside each box.", 14, 690, 456, sf::Color(155, 160, 170), false);



    drawMonthMenu(window, selectedMonth);



    // footer message

    drawText(window, "basic window, cards, buttons, rounded boxes, and month menu.", 13, 32, 725, sf::Color(125, 130, 140), false);
}



void DashboardMemberA::runStarterDashboard()
{
    if (loadFont() == false)
    {
        return;
    }

    sf::RenderWindow window(sf::VideoMode({ 1360, 768 }), "Starter Dashboard");

    window.setFramerateLimit(60);



    string userName = "User";

    int selectedMonth = 0;



    while (window.isOpen())
    {
        while (const optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }



            if (const auto* key = event->getIf<sf::Event::KeyPressed>())
            {
                if (key->code == sf::Keyboard::Key::Escape)
                {
                    window.close();
                }
            }



            if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouse->button == sf::Mouse::Button::Left)
                {
                    float mouseX = static_cast<float>(mouse->position.x);
                    float mouseY = static_cast<float>(mouse->position.y);



                    int monthNumber = 0;

                    for (int row = 0; row < 4; row++)
                    {
                        for (int col = 0; col < 3; col++)
                        {
                            float x = 900 + col * 125;
                            float y = 132 + row * 44;

                            if (isInside(mouseX, mouseY, x, y, 112, 36))
                            {
                                selectedMonth = monthNumber;
                            }

                            monthNumber++;
                        }
                    }
                }
            }
        }



        drawStarterDashboard(window, userName, selectedMonth);

        window.display();
    }
}