#include "Util.h"
#include <ctime>
#include <fstream>
#include <string>

// public functions:

string Util::logger(int level, string message)
{
    /*(
    * input: 
    * - int level
    * - string message, what is happening
    * 
    * output:
    * - returns string with date, time, log leve, and message
    * - prints string in logs.txt file
    
    */
    string text;
    string l;
    string m = message;

    // generate log message
    switch (level)
    {
    case 1:
        l = "INFO";
    case 2:
        l = "Warning";
    case 3:
        l = "Failure";
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