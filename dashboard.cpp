#include "dashboard.h"

#include <optional>

using namespace std;



// setup values and arrays
Dashboard::Dashboard()
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



    monthFiles[0] = "january";
    monthFiles[1] = "february";
    monthFiles[2] = "march";
    monthFiles[3] = "april";
    monthFiles[4] = "may";
    monthFiles[5] = "june";
    monthFiles[6] = "july";
    monthFiles[7] = "august";
    monthFiles[8] = "september";
    monthFiles[9] = "october";
    monthFiles[10] = "november";
    monthFiles[11] = "december";



    selectedMonth = 0;
    selectedStep = 0;
    selectedDomain = 0;
    activeField = -1;

    restartApp = false;



    userName = "";
    nameText = "";
    salaryText = "";
    spendLimitText = "";
    domainText = "";
    domainLimitText = "";
    actualText = "";

    domainCount = 0;



    for (int i = 0; i < 12; i++)
    {
        monthlySalary[i] = 0;
        monthlySpendLimit[i] = 0;

        for (int j = 0; j < 30; j++)
        {
            actualSpend[i][j] = 0;
        }
    }



    for (int i = 0; i < 30; i++)
    {
        domainName[i] = "";
        domainLimit[i] = 0;
    }
}



// starts the full dashboard app
void Dashboard::run()
{
    if (loadFont() == false)
    {
        return;
    }



    bool keepRunning = true;



    while (keepRunning == true)
    {
        restartApp = false;



        loadProfile();



        if (runNameWindow() == false)
        {
            return;
        }



        loadDomains();



        // budget domain menu before dashboard
        if (runDomainWindow() == false)
        {
            return;
        }



        loadAllMonths();



        runMainWindow();



        if (restartApp == true)
        {
            keepRunning = true;
        }
        else
        {
            keepRunning = false;
}
    }
}



// loads font for dashboard text
bool Dashboard::loadFont()
{
    if (font.openFromFile("assets/Roboto-Regular.ttf"))
    {
        return true;
    }

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


    cout << "Font not found. Add arial.ttf or Roboto-Regular.ttf." << endl;

    return false;
}



// checks mouse inside button or box
bool Dashboard::isInside(float mouseX, float mouseY, float x, float y, float width, float height)
{
    if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height)
    {
        return true;
    }

    return false;
}



// converts text input to number
double Dashboard::toDouble(string text)
{
    if (text == "")
    {
        return 0;
    }



    try
    {
        return stod(text);
    }
    catch (...)
    {
        return 0;
    }
}



// formats money text
string Dashboard::money(double amount)
{
    stringstream ss;

    ss << "Rs. " << fixed << setprecision(0) << amount;

    return ss.str();
}



// shortens long dashboard text
string Dashboard::shortText(string text, int limit)
{
    if (text.length() <= limit)
    {
        return text;
    }

    return text.substr(0, limit - 3) + "...";
}



// formats percentage text
string Dashboard::percentText(double value)
{
    stringstream ss;

    ss << fixed << setprecision(1) << value << "%";

    return ss.str();
}



// calculates total actual spending
double Dashboard::getTotalActual(int monthIndex)
{
    double total = 0;



    for (int i = 0; i < domainCount; i++)
    {
        total = total + actualSpend[monthIndex][i];
    }



    return total;
}



// calculates total category limits
double Dashboard::getTotalDomainLimit()
{
    double total = 0;



    for (int i = 0; i < domainCount; i++)
    {
        total = total + domainLimit[i];
    }



    return total;
}



// gets selected month name
string Dashboard::getMonthName(int index)
{
    if (index < 0 || index >= 12)
    {
        return "Month";
    }

    return months[index];
}



// gets file name for selected month
string Dashboard::getMonthFileName(int index)
{
    if (index < 0 || index >= 12)
    {
        return "month";
    }

    return monthFiles[index];
}



// loads user name
void Dashboard::loadProfile()
{
    ifstream file;

    file.open("profile.txt");



    if (file.is_open())
    {
        getline(file, userName);
        file.close();
    }



    nameText = userName;
}



// saves user name
void Dashboard::saveProfile()
{
    ofstream file;

    file.open("profile.txt");

    file << userName << endl;

    file.close();
}



// loads expense domains
void Dashboard::loadDomains()
{
    ifstream file;

    file.open("budget_domains.txt");



    domainCount = 0;



    if (file.is_open())
    {
        string countText;

        getline(file, countText);

        int savedCount = 0;



        try
        {
            savedCount = stoi(countText);
        }
        catch (...)
        {
            savedCount = 0;
        }



        for (int i = 0; i < savedCount && i < 30; i++)
        {
            string limitText;

            getline(file, domainName[i]);
            getline(file, limitText);

            domainLimit[i] = toDouble(limitText);

            domainCount++;
        }



        file.close();
    }
}



// saves expense domains
void Dashboard::saveDomains()
{
    ofstream file;

    file.open("budget_domains.txt");



    file << domainCount << endl;



    for (int i = 0; i < domainCount; i++)
    {
        file << domainName[i] << endl;
        file << domainLimit[i] << endl;
    }



    file.close();
}



// loads all month data
void Dashboard::loadAllMonths()
{
    for (int i = 0; i < 12; i++)
    {
        loadMonth(i);
    }
}



// loads selected month files
void Dashboard::loadMonth(int index)
{
    string fileName = getMonthFileName(index);



    ifstream infoFile;

    infoFile.open(fileName + "_month_info.txt");



    if (infoFile.is_open())
    {
        string salaryLine;
        string limitLine;

        getline(infoFile, salaryLine);
        getline(infoFile, limitLine);

        monthlySalary[index] = toDouble(salaryLine);
        monthlySpendLimit[index] = toDouble(limitLine);

        infoFile.close();
    }



    ifstream actualFile;

    actualFile.open(fileName + "_actuals.txt");



    if (actualFile.is_open())
    {
        for (int i = 0; i < domainCount; i++)
        {
            string actualLine;

            if (getline(actualFile, actualLine))
            {
                actualSpend[index][i] = toDouble(actualLine);
            }
        }

        actualFile.close();
    }
}



// saves selected month files
void Dashboard::saveMonth(int index)
{
    string fileName = getMonthFileName(index);



    ofstream infoFile;

    infoFile.open(fileName + "_month_info.txt");

    infoFile << monthlySalary[index] << endl;
    infoFile << monthlySpendLimit[index] << endl;

    infoFile.close();



    ofstream actualFile;

    actualFile.open(fileName + "_actuals.txt");

    for (int i = 0; i < domainCount; i++)
    {
        actualFile << actualSpend[index][i] << endl;
    }

    actualFile.close();



    saveReport(index);
}



// creates report text file
void Dashboard::saveReport(int index)
{
    string fileName = getMonthFileName(index);



    ofstream file;

    file.open(fileName + "_report.txt");



    double totalActual = getTotalActual(index);

    file << "Budget & Expense Report" << endl;
    file << "Month: " << getMonthName(index) << endl;
    file << "Name: " << userName << endl;
    file << endl;

    file << "Salary: " << monthlySalary[index] << endl;
    file << "Total Spending Limit: " << monthlySpendLimit[index] << endl;
    file << "Actual Spend: " << totalActual << endl;
    file << "Savings: " << monthlySalary[index] - totalActual << endl;
    file << endl;

    file << "Category | Limit | Actual | Variance | Percent" << endl;



    for (int i = 0; i < domainCount; i++)
{
        double percent = 0;

        if (totalActual > 0)
        {
            percent = (actualSpend[index][i] / totalActual) * 100;
        }

        file << domainName[i] << " | "
            << domainLimit[i] << " | "
            << actualSpend[index][i] << " | "
            << domainLimit[i] - actualSpend[index][i] << " | "
            << percent << "%" << endl;
    }



    file.close();
}



// clean slate reset button
void Dashboard::clearEverything()
{
    remove("profile.txt");
    remove("budget_domains.txt");



    for (int i = 0; i < 12; i++)
    {
        string base = getMonthFileName(i);

        remove((base + "_month_info.txt").c_str());
        remove((base + "_actuals.txt").c_str());
        remove((base + "_report.txt").c_str());
    }



    userName = "";
    nameText = "";

    salaryText = "";
    spendLimitText = "";
    domainText = "";
    domainLimitText = "";
    actualText = "";

    domainCount = 0;
    selectedMonth = 0;
    selectedStep = 0;
    selectedDomain = 0;



    for (int i = 0; i < 12; i++)
    {
        monthlySalary[i] = 0;
        monthlySpendLimit[i] = 0;

        for (int j = 0; j < 30; j++)
        {
            actualSpend[i][j] = 0;
        }
    }



    restartApp = true;
}



// typing inside input boxes
void Dashboard::typeInto(string& text, char32_t value, bool onlyNumber)
{
    if (value == 8)
    {
        if (text.length() > 0)
        {
            text.erase(text.length() - 1, 1);
        }

        return;
    }



    if (value < 32 || value > 126)
    {
        return;
    }



    char ch = static_cast<char>(value);



    if (onlyNumber == true)
    {
        if ((ch >= '0' && ch <= '9') || ch == '.')
        {
            text = text + ch;
        }

        return;
    }



    if (text.length() < 28)
    {
        text = text + ch;
    }
}



// normal dashboard text
void Dashboard::drawText(sf::RenderWindow& window, string textValue, int size, float x, float y, sf::Color color, bool bold)
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



// centered button text
void Dashboard::drawCenteredText(sf::RenderWindow& window, string textValue, int size, float x, float y, float width, float height, sf::Color color, bool bold)
{
    sf::Text text(font);

    text.setString(textValue);
    text.setCharacterSize(size);
    text.setFillColor(color);



    if (bold == true)
    {
        text.setStyle(sf::Text::Bold);
    }



    sf::FloatRect bounds = text.getLocalBounds();

    text.setOrigin({ bounds.position.x + bounds.size.x / 2, bounds.position.y + bounds.size.y / 2 });
    text.setPosition({ x + width / 2, y + height / 2 - 1 });



    window.draw(text);
}



// rounded filled shapes
void Dashboard::drawRoundFill(sf::RenderWindow& window, float x, float y, float width, float height, float radius, sf::Color color)
{
    if (radius <= 1)
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

    sf::RectangleShape one({ width - radius * 2, height });
    one.setPosition({ x + radius, y });
    one.setFillColor(color);

    window.draw(one);

    sf::RectangleShape middleTwo({ width, height - radius * 2 });
    middleTwo.setPosition({ x, y + radius });
    middleTwo.setFillColor(color);

    window.draw(middleTwo);

    sf::RectangleShape two({ width, height - radius * 2 });
    two.setPosition({ x, y + radius });
    two.setFillColor(color);

    window.draw(two);



    sf::CircleShape circle(radius);
    circle.setPointCount(30);
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



// rounded boxes and cards
void Dashboard::drawRoundBox(sf::RenderWindow& window, float x, float y, float width, float height, float radius, sf::Color fillColor, sf::Color borderColor)
{
    // rounded border box

    drawRoundFill(window, x, y, width, height, radius, borderColor);

    drawRoundFill(window, x + 1, y + 1, width - 2, height - 2, radius - 1, fillColor);
}



// main dark panel
void Dashboard::drawPanel(sf::RenderWindow& window, float x, float y, float width, float height)
{
    drawRoundFill(window, x + 8, y + 9, width, height, 24, sf::Color(0, 0, 0, 130));

    drawRoundBox(window, x, y, width, height, 24, sf::Color(10, 10, 12), sf::Color(52, 52, 58));
}



// progress bar
void Dashboard::drawBar(sf::RenderWindow& window, float x, float y, float width, float height, double ratio, sf::Color color)
{
    if (ratio < 0)
    {
        ratio = 0;
    }

    if (ratio > 1)
    {
        ratio = 1;
    }

    drawRoundFill(window, x, y, width, height, height / 2, sf::Color(28, 28, 34));

    drawRoundFill(window, x, y, static_cast<float>(width * ratio), height, height / 2, color);
}



// dashboard buttons
void Dashboard::drawButton(sf::RenderWindow& window, float x, float y, float width, float height, string textValue, bool selected)
{
    sf::Color fillColor = sf::Color(17, 17, 20);
    sf::Color borderColor = sf::Color(63, 63, 70);
    sf::Color textColor = sf::Color(218, 220, 226);



    if (selected == true)
    {
        fillColor = sf::Color(45, 212, 191);
        borderColor = sf::Color(45, 212, 191);
        textColor = sf::Color(0, 0, 0);
    }



    drawRoundBox(window, x, y, width, height, height / 2, fillColor, borderColor);

    drawCenteredText(window, textValue, 14, x, y, width, height, textColor, selected);
}


    sf::Text text(font);

// input fields
void Dashboard::drawInputBox(sf::RenderWindow& window, float x, float y, float width, float height, string label, string value, bool selected)
{
    sf::Color border = sf::Color(58, 58, 65);



    if (selected == true)
    {
        border = sf::Color(45, 212, 191);
    }



    drawText(window, label, 14, x, y - 25, sf::Color(165, 170, 180), false);

    drawRoundBox(window, x, y, width, height, 18, sf::Color(4, 4, 6), border);

    window.draw(text);
}


    string shown = value;

    if (selected == true)
{
        shown = shown + "|";
    }

    drawText(window, shortText(shown, 32), 16, x + 16, y + 15, sf::Color(240, 241, 245), false);
}

    drawRoundBox(window, x, y, width, height, 24, sf::Color(10, 10, 12), sf::Color(48, 48, 55));

    drawRoundFill(window, x + 20, y + 16, 40, 4, 2, sf::Color(45, 212, 191));

// top summary cards
void Dashboard::drawCard(sf::RenderWindow& window, float x, float y, float width, float height, string title, string value, string note, sf::Color accent)
{
    drawPanel(window, x, y, width, height);

    drawRoundFill(window, x + 20, y + 16, 38, 4, 2, accent);

    drawText(window, title, 14, x + 20, y + 34, sf::Color(165, 170, 180), false);

    drawText(window, value, 24, x + 20, y + 62, sf::Color(242, 243, 248), true);

    drawText(window, note, 11, x + 20, y + height - 28, sf::Color(130, 135, 145), false);
}



// month selection buttons
void Dashboard::drawMonthMenu(sf::RenderWindow& window, float startX, float startY)
{
    int num = 0;

    float startX = 900;
    float startY = 132;

    int monthNumber = 0;

    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            float x = startX + col * 120;
            float y = startY + row * 40;

            drawButton(window, x, y, 112, 34, months[num], selectedMonth == num);

            num++;
        }
    }
}



// top header bar
void Dashboard::drawTopBar(sf::RenderWindow& window)
{
    sf::RectangleShape bar({ 1360, 76 });
    bar.setPosition({ 0, 0 });
    bar.setFillColor(sf::Color(3, 3, 5));

    window.draw(bar);



    drawRoundFill(window, 0, 76, 1360, 2, 0, sf::Color(45, 212, 191));



    drawText(window, "Financial Management System", 29, 30, 14, sf::Color(246, 247, 250), true);

    drawText(window, "Welcome, " + shortText(userName, 20) + "  |  all-black monthly planner", 14, 30, 48, sf::Color(160, 165, 176), false);

    drawText(window, "ESC save + exit  |  TAB fields  |  ENTER action", 14, 828, 30, sf::Color(160, 165, 176), false);



    drawButton(window, 1160, 18, 170, 42, "Clear Data", false);
}



// step navigation menu
void Dashboard::drawStepMenu(sf::RenderWindow& window)
{
    string steps[4];

    steps[0] = "1  Foundation";
    steps[1] = "2  Budget Domains";
    steps[2] = "3  Actual Spend";
    steps[3] = "4  Report";



    for (int i = 0; i < 4; i++)
    {
        drawButton(window, 30 + i * 318, 228, 302, 42, steps[i], selectedStep == i);
    }
}



// name setup window
bool Dashboard::runNameWindow()
{
    sf::RenderWindow window(sf::VideoMode({ 760, 430 }), "Welcome Setup");

    window.setFramerateLimit(60);



    activeField = 0;



    while (window.isOpen())
    {
        while (const optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();

                return false;
            }



            if (const auto* text = event->getIf<sf::Event::TextEntered>())
            {
                if (activeField == 0)
                {
                    typeInto(nameText, text->unicode, false);
                }
            }



            if (const auto* key = event->getIf<sf::Event::KeyPressed>())
            {
                if (key->code == sf::Keyboard::Key::Escape)
                {
                    window.close();

                    return false;
                }



                if (key->code == sf::Keyboard::Key::Enter)
                {
                    if (nameText != "")
                    {
                        userName = nameText;

                        saveProfile();

                        window.close();

                        return true;
                    }
        }
    }



            if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouse->button == sf::Mouse::Button::Left)
                {
                    float mx = static_cast<float>(mouse->position.x);
                    float my = static_cast<float>(mouse->position.y);



                    if (isInside(mx, my, 125, 242, 510, 56))
                    {
                        activeField = 0;
}



                    if (isInside(mx, my, 125, 324, 510, 46))
                    {
                        if (nameText != "")
{
                            userName = nameText;

                            saveProfile();

                            window.close();

                            return true;
                        }
                    }
                }
            }
        }



    window.clear(sf::Color(0, 0, 0));



        drawPanel(window, 70, 52, 620, 326);

        drawRoundFill(window, 70, 52, 620, 3, 1, sf::Color(45, 212, 191));



        drawText(window, "Financial Management System", 30, 125, 92, sf::Color(246, 247, 250), true);

        drawText(window, "Black monthly planner setup", 14, 125, 132, sf::Color(160, 165, 176), false);

        drawText(window, "Before the program starts", 15, 125, 190, sf::Color(45, 212, 191), true);



        drawInputBox(window, 125, 242, 510, 56, "Your Name", nameText, activeField == 0);

        drawButton(window, 125, 324, 510, 46, "Continue", true);



        window.display();
    }



    return false;
}



// budget domain menu before dashboard
bool Dashboard::runDomainWindow()
{
    sf::RenderWindow window(sf::VideoMode({ 980, 720 }), "Private Domain Setup");

    window.setFramerateLimit(60);



    activeField = 0;



    while (window.isOpen())
    {
        while (const optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();

                return false;
            }

    sf::RectangleShape topBar({ 1360, 78 });
    topBar.setPosition({ 0, 0 });
    topBar.setFillColor(sf::Color(3, 3, 5));

    window.draw(topBar);

            if (const auto* text = event->getIf<sf::Event::TextEntered>())
            {
                if (activeField == 0)
                {
                    typeInto(domainText, text->unicode, false);
                }

                if (activeField == 1)
                {
                    typeInto(domainLimitText, text->unicode, true);
                }
            }

    drawRoundFill(window, 0, 76, 1360, 2, 0, sf::Color(45, 212, 191));


            if (const auto* key = event->getIf<sf::Event::KeyPressed>())
            {
                if (key->code == sf::Keyboard::Key::Escape)
                {
                    window.close();

                    return false;
                }

    drawText(window, "Welcome, " + shortText(userName, 20), 14, 34, 50, sf::Color(160, 165, 175), false);


                if (key->code == sf::Keyboard::Key::Tab)
                {
                    activeField++;

                    if (activeField > 1)
                    {
                        activeField = 0;
                    }
                }

    drawText(window, "Starter Dashboard", 24, 32, 110, sf::Color(245, 245, 248), true);

    drawText(window, "This is first SFML layout before final merging.", 14, 32, 143, sf::Color(150, 155, 165), false);

                if (key->code == sf::Keyboard::Key::Enter)
                {
                    if (domainText != "" && domainLimitText != "" && domainCount < 30)
                    {
                        domainName[domainCount] = domainText;
                        domainLimit[domainCount] = toDouble(domainLimitText);

                        domainCount++;

                        domainText = "";
                        domainLimitText = "";

                        activeField = 0;

                        saveDomains();
                    }
                }
            }

    drawCard(window, 668, 205, 290, 132, "Actual Spend", money(0), "Expense tracking placeholder");

    drawCard(window, 986, 205, 290, 132, "Savings", money(0), "Final report placeholder");

            if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouse->button == sf::Mouse::Button::Left)
                {
                    float mx = static_cast<float>(mouse->position.x);
                    float my = static_cast<float>(mouse->position.y);


    // left panel

                    if (isInside(mx, my, 64, 214, 380, 56))
                    {
                        activeField = 0;
                    }

    drawText(window, "Input Area", 22, 62, 420, sf::Color(245, 245, 248), true);

    drawText(window, "created the visual section.", 14, 62, 456, sf::Color(155, 160, 170), false);

                    if (isInside(mx, my, 64, 304, 380, 56))
                    {
                        activeField = 1;
                    }



                    if (isInside(mx, my, 64, 392, 380, 46))
                    {
                        if (domainText != "" && domainLimitText != "" && domainCount < 30)
                        {
                            domainName[domainCount] = domainText;
                            domainLimit[domainCount] = toDouble(domainLimitText);

                            domainCount++;

                            domainText = "";
                            domainLimitText = "";

                            activeField = 0;

                            saveDomains();
                        }
                    }

    drawRoundBox(window, 660, 380, 668, 300, 28, sf::Color(10, 10, 12), sf::Color(48, 48, 55));

    drawText(window, "Month Selection", 22, 690, 420, sf::Color(245, 245, 248), true);

                    if (isInside(mx, my, 64, 610, 380, 48))
                    {
                        if (domainCount > 0)
                        {
                            saveDomains();

                            window.close();

                            return true;
                        }
                    }
                }
            }
        }

    drawMonthMenu(window, selectedMonth);


        window.clear(sf::Color(0, 0, 0));

    // footer message


        drawPanel(window, 34, 36, 912, 636);

        drawRoundFill(window, 34, 36, 912, 3, 1, sf::Color(190, 120, 255));



        drawText(window, "Private Budget Domain Setup", 30, 64, 76, sf::Color(246, 247, 250), true);

        drawText(window, "This separate window is used before the main dashboard.", 14, 64, 116, sf::Color(160, 165, 176), false);

        drawText(window, "Welcome, " + shortText(userName, 22), 14, 64, 144, sf::Color(45, 212, 191), true);



        drawInputBox(window, 64, 214, 380, 56, "Expense Domain", domainText, activeField == 0);

        drawInputBox(window, 64, 304, 380, 56, "Maximum Limit", domainLimitText, activeField == 1);



        drawButton(window, 64, 392, 380, 46, "Add Domain", true);

        drawButton(window, 64, 610, 380, 48, "Start Dashboard", domainCount > 0);



        drawText(window, "Saved Domains", 20, 510, 198, sf::Color(246, 247, 250), true);

        drawText(window, "These stay the same for all months.", 13, 510, 226, sf::Color(160, 165, 176), false);



        int count = domainCount;



        if (count > 10)
        {
            count = 10;
}



        if (count == 0)
{
            drawText(window, "No domains added yet.", 15, 510, 278, sf::Color(120, 125, 135), false);
        }



        for (int i = 0; i < count; i++)
    {
            float y = 270 + i * 34;



            drawRoundBox(window, 510, y, 380, 28, 14, sf::Color(4, 4, 6), sf::Color(46, 46, 54));

            drawText(window, shortText(domainName[i], 22), 13, 528, y + 6, sf::Color(246, 247, 250), true);

            drawText(window, money(domainLimit[i]), 13, 760, y + 6, sf::Color(160, 165, 176), false);
    }

    sf::RenderWindow window(sf::VideoMode({ 1360, 768 }), "Starter Dashboard");

    window.setFramerateLimit(60);

        window.display();
    }


    string userName = "User";

    return false;
}



// main dashboard window
void Dashboard::runMainWindow()
{
    sf::RenderWindow window(sf::VideoMode({ 1360, 900 }), "Financial Management System");

    window.setFramerateLimit(60);



    while (window.isOpen())
    {
        while (const optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                saveMonth(selectedMonth);

                window.close();
            }



            if (const auto* text = event->getIf<sf::Event::TextEntered>())
            {
                if (selectedStep == 0)
                {
                    if (activeField == 0)
                    {
                        typeInto(salaryText, text->unicode, true);
                    }

                    if (activeField == 1)
                    {
                        typeInto(spendLimitText, text->unicode, true);
                    }
                }



                if (selectedStep == 2)
                {
                    if (activeField == 2)
                    {
                        typeInto(actualText, text->unicode, true);
                    }
                }
            }



            if (const auto* key = event->getIf<sf::Event::KeyPressed>())
            {
                if (key->code == sf::Keyboard::Key::Escape)
                {
                    saveMonth(selectedMonth);

                    window.close();
                }



                if (key->code == sf::Keyboard::Key::Tab)
                {
                    if (selectedStep == 0)
                    {
                        activeField++;

                        if (activeField > 1)
                        {
                            activeField = 0;
            }
                    }
                }



                if (key->code == sf::Keyboard::Key::Enter)
                {
                    handleEnterKey();
                }
            }



            if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouse->button == sf::Mouse::Button::Left)
                {
                    float mx = static_cast<float>(mouse->position.x);
                    float my = static_cast<float>(mouse->position.y);

                    handleMainMouse(mx, my, window);
                }
            }
        }



        drawDashboard(window);

        window.display();
    }
}



// salary and spend limit panel
void Dashboard::drawFoundationPanel(sf::RenderWindow& window)
{
    drawPanel(window, 24, 286, 420, 580);

    drawRoundFill(window, 24, 286, 420, 3, 1, sf::Color(45, 212, 191));



    drawText(window, "Step 1", 14, 54, 312, sf::Color(45, 212, 191), true);

    drawText(window, "The Foundation", 26, 54, 336, sf::Color(246, 247, 250), true);

    drawText(window, "Enter salary, spending limit, and month.", 13, 54, 374, sf::Color(160, 165, 176), false);



    drawInputBox(window, 54, 428, 340, 52, "Monthly Take-Home Salary", salaryText, activeField == 0);

    drawInputBox(window, 54, 515, 340, 52, "Total Monthly Spending Limit", spendLimitText, activeField == 1);



    drawText(window, "Select Month", 14, 54, 608, sf::Color(160, 165, 176), false);

    drawMonthMenu(window, 54, 635);



    drawButton(window, 54, 812, 340, 40, "Next", false);
}



// budget limits panel
void Dashboard::drawLimitPanel(sf::RenderWindow& window)
{
    drawPanel(window, 24, 286, 420, 580);

    drawRoundFill(window, 24, 286, 420, 3, 1, sf::Color(45, 212, 191));



    drawText(window, "Step 2", 14, 54, 312, sf::Color(45, 212, 191), true);

    drawText(window, "Budget Domains", 26, 54, 336, sf::Color(246, 247, 250), true);

    drawText(window, "Domains are created only in setup window.", 13, 54, 374, sf::Color(160, 165, 176), false);

    drawText(window, "They stay same for every month.", 13, 54, 397, sf::Color(160, 165, 176), false);



    drawText(window, "Fixed Domain List", 15, 54, 455, sf::Color(160, 165, 176), false);



    int count = domainCount;



    if (count > 8)
    {
        count = 8;
    }



    for (int i = 0; i < count; i++)
    {
        drawRoundBox(window, 54, 490 + i * 36, 340, 30, 15, sf::Color(4, 4, 6), sf::Color(48, 48, 55));

        drawText(window, shortText(domainName[i], 18), 13, 70, 496 + i * 36, sf::Color(246, 247, 250), true);

        drawText(window, money(domainLimit[i]), 13, 265, 496 + i * 36, sf::Color(160, 165, 176), false);
    }



    drawButton(window, 54, 812, 160, 40, "Back", false);

    drawButton(window, 234, 812, 160, 40, "Next", true);
}



// actual expense panel
void Dashboard::drawActualPanel(sf::RenderWindow& window)
{
    double totalActual = getTotalActual(selectedMonth);

    double limitLeft = monthlySpendLimit[selectedMonth] - totalActual;



    drawPanel(window, 24, 286, 420, 580);

    drawRoundFill(window, 24, 286, 420, 3, 1, sf::Color(45, 212, 191));



    drawText(window, "Step 3", 14, 54, 312, sf::Color(45, 212, 191), true);

    drawText(window, "Actual Spend", 26, 54, 336, sf::Color(246, 247, 250), true);

    drawText(window, "Choose a category and add spending.", 13, 54, 374, sf::Color(160, 165, 176), false);

    drawText(window, "Limit left: " + money(limitLeft), 13, 54, 397, limitLeft < 0 ? sf::Color(255, 77, 141) : sf::Color(45, 212, 191), false);



    int count = domainCount;



    if (count > 6)
    {
        count = 6;
    }



    drawText(window, "Choose Category", 14, 54, 440, sf::Color(160, 165, 176), false);



    for (int i = 0; i < count; i++)
    {
        drawButton(window, 54, 468 + i * 42, 340, 34, shortText(domainName[i], 28), selectedDomain == i);
    }



    drawInputBox(window, 54, 736, 340, 52, "Actual Amount Spent", actualText, activeField == 2);



    drawButton(window, 54, 812, 160, 40, "Add Actual", false);

    drawButton(window, 234, 812, 160, 40, "Report", false);
}



// final report panel
void Dashboard::drawReportPanel(sf::RenderWindow& window)
{
    drawPanel(window, 464, 286, 872, 580);

    drawRoundFill(window, 464, 286, 872, 3, 1, sf::Color(190, 120, 255));



    double salary = monthlySalary[selectedMonth];
    double limit = monthlySpendLimit[selectedMonth];
    double spend = getTotalActual(selectedMonth);
    double savings = salary - spend;
    double left = limit - spend;
    double salaryPercent = 0;



    if (salary > 0)
    {
        salaryPercent = (spend / salary) * 100;
    }



    drawText(window, "Final Intelligence Report", 25, 496, 312, sf::Color(246, 247, 250), true);

    drawText(window, getMonthName(selectedMonth) + " spending analysis", 14, 496, 346, sf::Color(160, 165, 176), false);



    drawCard(window, 496, 370, 248, 120, "Total Spend", money(spend), percentText(salaryPercent) + " of salary", sf::Color(255, 77, 141));

    drawCard(window, 766, 370, 248, 120, "Spend Limit", money(limit), "monthly allowed limit", sf::Color(190, 120, 255));

    drawCard(window, 1036, 370, 248, 120, "Savings", money(savings), "salary left over", savings < 0 ? sf::Color(255, 77, 141) : sf::Color(52, 211, 153));



    drawText(window, "Summary Table", 18, 496, 518, sf::Color(246, 247, 250), true);

    drawText(window, "Category", 12, 510, 548, sf::Color(160, 165, 176), false);

    drawText(window, "Limit", 12, 690, 548, sf::Color(160, 165, 176), false);

    drawText(window, "Actual", 12, 830, 548, sf::Color(160, 165, 176), false);

    drawText(window, "Variance", 12, 982, 548, sf::Color(160, 165, 176), false);

    drawText(window, "% Spend", 12, 1188, 548, sf::Color(160, 165, 176), false);



    int count = domainCount;



    if (count > 5)
    {
        count = 5;
    }



    for (int i = 0; i < count; i++)
    {
        double bLimit = domainLimit[i];
        double actual = actualSpend[selectedMonth][i];
        double variance = bLimit - actual;
        double percent = 0;



        if (spend > 0)
        {
            percent = (actual / spend) * 100;
        }



        string varianceText = "Under " + money(variance);

        sf::Color varianceColor = sf::Color(52, 211, 153);



        if (variance < 0)
        {
            varianceText = "Over " + money(-variance) + " !";
            varianceColor = sf::Color(255, 77, 141);
        }



        float y = 570 + i * 36;



        sf::RectangleShape row({ 790, 34 });
        row.setPosition({ 496, y });
        row.setFillColor(sf::Color(5, 5, 7));
        row.setOutlineThickness(1);
        row.setOutlineColor(sf::Color(42, 42, 48));

        window.draw(row);



        drawText(window, shortText(domainName[i], 15), 13, 508, y + 8, sf::Color(246, 247, 250), true);

        drawText(window, money(bLimit), 13, 690, y + 8, sf::Color(218, 220, 226), false);

        drawText(window, money(actual), 13, 830, y + 8, sf::Color(218, 220, 226), false);

        drawText(window, varianceText, 13, 982, y + 8, varianceColor, false);

        drawText(window, percentText(percent), 13, 1190, y + 8, sf::Color(160, 165, 176), false);
    }



    drawText(window, "Expense Bars", 18, 496, 758, sf::Color(246, 247, 250), true);

    drawText(window, "Bars show each category share of total spending.", 12, 496, 782, sf::Color(160, 165, 176), false);



    int barCount = domainCount;



    if (barCount > 3)
    {
        barCount = 3;
    }



    for (int i = 0; i < barCount; i++)
    {
        double ratio = 0;



        if (spend > 0)
        {
            ratio = actualSpend[selectedMonth][i] / spend;
        }



        sf::Color color = sf::Color(45, 212, 191);



        if (actualSpend[selectedMonth][i] > domainLimit[i])
        {
            color = sf::Color(255, 77, 141);
        }
        else if (ratio > 0.35)
        {
            color = sf::Color(190, 120, 255);
        }



        float y = 808 + i * 25;



        drawText(window, shortText(domainName[i], 12), 13, 496, y - 4, sf::Color(246, 247, 250), true);

        drawBar(window, 640, y, 560, 12, ratio, color);

        drawText(window, percentText(ratio * 100), 12, 1215, y - 4, sf::Color(160, 165, 176), false);
    }



    if (left < 0)
    {
        drawText(window, "Insight: spending limit exceeded by " + money(-left) + ".", 13, 835, 758, sf::Color(255, 77, 141), true);
    }
    else
    {
        drawText(window, "Insight: you still have " + money(left) + " left from your spending limit.", 13, 835, 758, sf::Color(52, 211, 153), true);
    }
}



// full dashboard screen
void Dashboard::drawDashboard(sf::RenderWindow& window)
{
    window.clear(sf::Color(0, 0, 0));



    drawTopBar(window);

    drawStepMenu(window);



    double totalActual = getTotalActual(selectedMonth);
    double savings = monthlySalary[selectedMonth] - totalActual;
    double limitLeft = monthlySpendLimit[selectedMonth] - totalActual;



    drawCard(window, 30, 92, 305, 120, "Monthly Salary", money(monthlySalary[selectedMonth]), getMonthName(selectedMonth), sf::Color(45, 212, 191));

    drawCard(window, 365, 92, 305, 120, "Total Spend Limit", money(monthlySpendLimit[selectedMonth]), "your spending ceiling", sf::Color(190, 120, 255));

    drawCard(window, 700, 92, 305, 120, "Actual Spend", money(totalActual), "entered this month", sf::Color(255, 77, 141));

    drawCard(window, 1035, 92, 295, 120, "Savings", money(savings), "salary left", savings < 0 ? sf::Color(255, 77, 141) : sf::Color(52, 211, 153));



    if (selectedStep == 0)
    {
        drawFoundationPanel(window);
    }

    if (selectedStep == 1)
    {
        drawLimitPanel(window);
    }

    if (selectedStep == 2)
    {
        drawActualPanel(window);
    }



    if (selectedStep == 3)
    {
        drawPanel(window, 24, 286, 420, 580);

        drawRoundFill(window, 24, 286, 420, 3, 1, sf::Color(45, 212, 191));



        drawText(window, "Step 4", 14, 54, 312, sf::Color(45, 212, 191), true);

        drawText(window, "Final Report", 26, 54, 336, sf::Color(246, 247, 250), true);

        drawText(window, "Select any month to view its report.", 13, 54, 374, sf::Color(160, 165, 176), false);



        drawText(window, "Report Month", 14, 54, 420, sf::Color(160, 165, 176), false);

        drawMonthMenu(window, 54, 448);



        drawText(window, "Savings", 14, 54, 642, sf::Color(160, 165, 176), false);

        drawText(window, money(savings), 27, 54, 668, savings < 0 ? sf::Color(255, 77, 141) : sf::Color(52, 211, 153), true);



        drawText(window, "Spend Limit Left", 14, 54, 738, sf::Color(160, 165, 176), false);

        drawText(window, money(limitLeft), 20, 54, 764, limitLeft < 0 ? sf::Color(255, 77, 141) : sf::Color(52, 211, 153), true);



        drawButton(window, 54, 812, 340, 40, "Back to Actuals", false);



        drawReportPanel(window);
    }
    else
    {
        drawPanel(window, 464, 286, 872, 580);

        drawRoundFill(window, 464, 286, 872, 3, 1, sf::Color(190, 120, 255));



        drawText(window, "Live Monthly Intelligence", 24, 496, 312, sf::Color(246, 247, 250), true);

        drawText(window, "Your global domains are reused for every selected month.", 14, 496, 344, sf::Color(160, 165, 176), false);



        drawCard(window, 496, 380, 248, 120, "Salary", money(monthlySalary[selectedMonth]), getMonthName(selectedMonth), sf::Color(45, 212, 191));

        drawCard(window, 766, 380, 248, 120, "Spend Limit", money(monthlySpendLimit[selectedMonth]), "maximum allowed spend", sf::Color(190, 120, 255));

        drawCard(window, 1036, 380, 248, 120, "Limit Left", money(limitLeft), "from total spend limit", limitLeft < 0 ? sf::Color(255, 77, 141) : sf::Color(52, 211, 153));



        drawText(window, "Budget Domains", 20, 496, 535, sf::Color(246, 247, 250), true);

        drawText(window, "Allocated: " + money(getTotalDomainLimit()) + " / " + money(monthlySpendLimit[selectedMonth]), 13, 666, 541, sf::Color(160, 165, 176), false);



        int count = domainCount;



        if (count > 5)
        {
            count = 5;
        }



        for (int i = 0; i < count; i++)
        {
            double ratio = 0;



            if (domainLimit[i] > 0)
            {
                ratio = actualSpend[selectedMonth][i] / domainLimit[i];
            }



            sf::Color color = sf::Color(45, 212, 191);



            if (actualSpend[selectedMonth][i] > domainLimit[i])
            {
                color = sf::Color(255, 77, 141);
            }
            else if (ratio >= 0.8)
            {
                color = sf::Color(255, 190, 55);
            }



            float y = 580 + i * 50;



            drawText(window, shortText(domainName[i], 22), 15, 496, y, sf::Color(246, 247, 250), true);

            drawText(window, money(actualSpend[selectedMonth][i]) + " / " + money(domainLimit[i]), 13, 1050, y, sf::Color(160, 165, 176), false);

            drawBar(window, 496, y + 28, 780, 10, ratio, color);
        }
    }
}



// mouse clicks on dashboard
void Dashboard::handleMainMouse(float mouseX, float mouseY, sf::RenderWindow& window)
{
    activeField = -1;



    if (isInside(mouseX, mouseY, 1160, 18, 170, 42))
    {
        clearEverything();

        window.close();

        return;
    }



    for (int i = 0; i < 4; i++)
    {
        if (isInside(mouseX, mouseY, 30 + i * 318, 228, 302, 42))
        {
            selectedStep = i;

            return;
        }
    }



    if (selectedStep == 0)
    {
        if (isInside(mouseX, mouseY, 54, 428, 340, 52))
        {
            activeField = 0;

            return;
        }



        if (isInside(mouseX, mouseY, 54, 515, 340, 52))
        {
            activeField = 1;

            return;
        }



                    int monthNumber = 0;



                    for (int row = 0; row < 4; row++)
                    {
                        for (int col = 0; col < 3; col++)
                        {
                if (isInside(mouseX, mouseY, 54 + col * 120, 635 + row * 40, 112, 34))
                {
                    saveMonth(selectedMonth);

                    selectedMonth = monthNumber;

                    salaryText = "";
                    spendLimitText = "";
                    actualText = "";

                    return;
                }

                monthNumber++;
            }
        }



        if (isInside(mouseX, mouseY, 54, 812, 340, 40))
        {
            monthlySalary[selectedMonth] = toDouble(salaryText);
            monthlySpendLimit[selectedMonth] = toDouble(spendLimitText);

            saveMonth(selectedMonth);

            selectedStep = 2;
            activeField = 2;

            return;
        }
    }



    if (selectedStep == 1)
    {
        if (isInside(mouseX, mouseY, 54, 812, 160, 40))
        {
            selectedStep = 0;

            return;
        }



        if (isInside(mouseX, mouseY, 234, 812, 160, 40))
        {
            selectedStep = 2;

            return;
        }
    }



    if (selectedStep == 2)
    {
        int count = domainCount;



        if (count > 6)
        {
            count = 6;
        }



        for (int i = 0; i < count; i++)
        {
            if (isInside(mouseX, mouseY, 54, 468 + i * 42, 340, 34))
            {
                selectedDomain = i;

                return;
            }
        }



        if (isInside(mouseX, mouseY, 54, 736, 340, 52))
        {
            activeField = 2;

            return;
        }



        if (isInside(mouseX, mouseY, 54, 812, 160, 40))
        {
            actualSpend[selectedMonth][selectedDomain] = toDouble(actualText);

            saveMonth(selectedMonth);

            actualText = "";

            activeField = 2;

            return;
        }



        if (isInside(mouseX, mouseY, 234, 812, 160, 40))
        {
            selectedStep = 3;

            return;
        }
    }



    if (selectedStep == 3)
    {
        int monthNumber = 0;



        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                if (isInside(mouseX, mouseY, 54 + col * 120, 448 + row * 40, 112, 34))
                            {
                    saveMonth(selectedMonth);

                                selectedMonth = monthNumber;

                    return;
                            }

                            monthNumber++;
                        }
        }



        if (isInside(mouseX, mouseY, 54, 812, 340, 40))
        {
            selectedStep = 2;

            return;
                    }
                }
            }



// enter key actions
void Dashboard::handleEnterKey()
{
    if (selectedStep == 0)
    {
        monthlySalary[selectedMonth] = toDouble(salaryText);
        monthlySpendLimit[selectedMonth] = toDouble(spendLimitText);

        saveMonth(selectedMonth);

        selectedStep = 2;

        activeField = 2;
        }



    else if (selectedStep == 2)
    {
        actualSpend[selectedMonth][selectedDomain] = toDouble(actualText);

        saveMonth(selectedMonth);

        actualText = "";

        activeField = 2;
    }
}