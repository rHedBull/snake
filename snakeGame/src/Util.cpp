#include <ctime>
#include <fstream>
#include <string>

#include "Util.h"
#include <SFML/Graphics.hpp>

/*
prints string with message  level of message and metadata into logFile and the debug console
parameters:
int level;
string message;

return:
 string with date, time, log leve, and message

levels:
1 = INFO
2 = Warning
3 = Failure
*/
string logger(int level, string message)
{
    string text;
    string l;
    string m = message;

    // generate log message
    switch (level)
    {
    case 1:
        l = "INFO";
        break;
    case 2:
        l = "Warning";
        break;
    case 3:
        l = "Failure";
        break;
    }

    // generate date and time
    time_t currenTime = time(0);

#pragma warning(suppress : 4996)
    tm* t = localtime(&currenTime);

    string year = std::to_string((t->tm_year) + 1900);
    string month = std::to_string((t->tm_mon) + 1);
    string day = std::to_string(t->tm_mday);
    string hour = std::to_string(t->tm_hour);
    string min = std::to_string(t->tm_hour);
    string sec = std::to_string(t->tm_sec);

    string dateTime = '[' + year + "." + month + "." + day + "--" + hour + ":" + min + ":" + sec + "]";

    text = dateTime + "  [" + l + "]" + "  " + m;
    cout << text << endl;

    ofstream logfile;
    logfile.open("logs.txt", std::ios_base::app);
    logfile << text << " \n";

    for (int i = 1; i <= 150; i++)
    {
        logfile << "*";
    }
    logfile << " \n";

    logfile.close();

    return text;
}

/*
sf::Font font;
if(!font.loadFromFile(".\res\ARCADECLASSIC.TTF"))
{
    logger(1, "error loading the ARCADECLASSIC.TTF font file at relative position: \".\res\ARCADECLASSIC.TTF\"");
}*/