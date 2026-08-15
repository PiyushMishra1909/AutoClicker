// Learning about windows api by leaning how to make an autoclicker :)
#include <windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <map>
#include <string>

using namespace std;

bool waspressed = false;
bool Working = false;

int startStopKey;
int exitKey;
int clickMode;
int delay;
double cps;

DWORD downFlag; // MOUSE CLICK PRESSED OR DOWN
DWORD upFlag;   // MOUSE CLICK PRESSED AGAIN OR UP

void userMenu();
void defaultKeys();
void configuehotkeys();
void starting();
void click();
double CalculateDelay(double cps);

map<string, string> Text_Messages = {
    {"Banner", "************************************\n"},
    {"Welcome", "       WELCOME TO AUTOCLICKER       \n"},
    {"Choice", "Select mouse Click [1] Left  [2] Right : "}};

int main()
{
    cout << "\033[32m"; // CHANGES THE COLOUR OF TEXT TO GREEN

    defaultKeys();
    userMenu();

    while (true)
    {
        bool ispressed = GetAsyncKeyState(startStopKey) & 0x8000;

        if (ispressed && !waspressed)
        {
            Working = !Working;
            if (Working)
            {
                cout << "\nAutoClicker Working\n";
            }
            else
            {
                cout << "\nAutoClicker Stopped\n" ;
            }
        }

        if (Working)
        {
            click();
        }

        if (GetAsyncKeyState(exitKey) & 0x8000)
        {
            cout << "Exiting...\n";
            break;
        }

        waspressed = ispressed;

        Sleep(delay);
    }

    return 0;
}

void defaultKeys()
{
    startStopKey = VK_F6;
    exitKey = VK_F7;
}

void userMenu()
{
    bool userMenuloop = true;
    int userchoice;

    cout << Text_Messages["Banner"];
    cout << Text_Messages["Welcome"];
    cout << Text_Messages["Banner"];
    cout << endl;

    while (userMenuloop)
    {

        cout << "-> Choose an option to continue: ";
        cout << endl;
        cout << "1. Set click mode\n";
        cout << "2. Configure hotkeys\n";
        cout << "3. Exit Usermenu\n";

        cout << "\n-> Select an option: ";
        cin >> userchoice;
        cout << endl;

        switch (userchoice)
        {
        case 1:
            starting();
            userMenuloop = false;
            break;
        case 2:
            configuehotkeys();
            break;
        case 3:
            userMenuloop = false;
            break;
        default:
            cout << "Invalid Choice!\n";
            cout << endl;
            break;
        }
    }
}

void starting() // CONTAINS ALL THE INSTRUCTION AND CHOICES
{
    bool firstTry = true;

    do
    {
        if (!firstTry)
        {

            cout << endl;
            cout << "Enter valid choice!";
            cout << endl;
            cout << endl;
        }

        cout << Text_Messages["Choice"];
        cin >> clickMode;

        firstTry = false;

    } while ((clickMode != 1) && (clickMode != 2));

    if (clickMode == 1) // FOR CHOOSING LEFT CLICK
    {
        downFlag = MOUSEEVENTF_LEFTDOWN;
        upFlag = MOUSEEVENTF_LEFTUP;
    }
    else if (clickMode == 2) // FOR CHOOSING RIGHT CLICK
    {
        downFlag = MOUSEEVENTF_RIGHTDOWN;
        upFlag = MOUSEEVENTF_RIGHTUP;
    }

    do // THIS LOOP WILL STOP USER FROM ENTERING INVALID CPS
    {
        cout << "\nEnter ClicksPerSecond :- ";
        cin >> cps;
        delay = CalculateDelay(cps);

        if (cps <= 0 || delay <= 10)
        {
            cout << "\nPlease enter valid Cps!\n";
        }
    } while (cps <= 0 || delay <= 10);

    if (startStopKey == VK_F6)
    {
        cout << "\nPlease press f6 to start : " ;
        cout << endl ;
    }
    else
    {
        cout << "\nPlease press "<< char(startStopKey) << " to start!";
        cout << endl ;
    }
    
}

void configuehotkeys()
{
    bool configureLoop = true;
    int configureChoice;
    char userStart_Stopkey, userExitkey;
    toupper(userStart_Stopkey);
    toupper(userExitkey);

    while (configureLoop)
    {
        cout << "\nSelect key to configure : ";
        cout << "\n1. Configure Start/Stop key\n";
        cout << "2. Configure Exit key\n";
        cout << "3. Exit configure mode\n";
        cin >> configureChoice;

        switch (configureChoice)
        {
        case 1:
            cout << "\nSelect Start/Stop key : ";
            cin >> userStart_Stopkey;
            startStopKey = userStart_Stopkey;
            break;

        case 2:
            cout << "\nSelect Exit key : ";
            cin >> userExitkey;
            exitKey = userExitkey;
            break;
        case 3:
            configureLoop = false;
            break;
        default:
            cout << "Invalid Choice!\n";
            break;
        }
    }
}

void click() // TELLS THE OS TO CLICK
{

    INPUT input = {};
    input.type = INPUT_MOUSE;

    input.mi.dwFlags = downFlag;
    SendInput(1, &input, sizeof(INPUT));

    input.mi.dwFlags = upFlag;
    SendInput(1, &input, sizeof(INPUT));
}

double CalculateDelay(double cps) // CONVERTS CPS INTO MS DELAY
{
    return 1000.0 / cps;
}