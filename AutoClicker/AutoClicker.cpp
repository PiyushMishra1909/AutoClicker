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

int clickMode;
int delay;
double cps;

DWORD downFlag; // MOUSE CLICK PRESSED OR DOWN
DWORD upFlag;   // MOUSE CLICK PRESSED AGAIN OR UP

void click();
void starting();
double CalculateDelay(double cps);

map<string, string> Text_Messages = {
    {"Banner", "************************************\n"},
    {"Welcome", "       WELCOME TO AUTOCLICKER       \n"},
    {"Choice", "Select mouse button [1] Left  [2] Right :- "}};

int main()
{
    cout << "\033[32m";     //CHANGES THE COLOUR OF TEXT TO GREEN

    starting();

    while (true)
    {
        bool ispressed = GetAsyncKeyState(VK_F6) & 0x8000;

        if (ispressed && !waspressed)
        {
            Working = !Working;
            cout << "AutoClicker Working\n";
        }

        if (Working)
        {
            click();
        }

        if (GetAsyncKeyState(VK_F7) & 0x8000)
        {
            cout << "AutoClicker Stopped\n";
            break;
        }

        waspressed = ispressed;

        Sleep(delay);
    }

    return 0;
}

void starting() // CONTAINS ALL THE INSTRUCTION AND CHOICES
{
    bool firstTry = true;

    cout << Text_Messages["Banner"];
    cout << Text_Messages["Welcome"];
    cout << Text_Messages["Banner"];
    cout << endl;
    cout << endl;
    cout << endl;

    do
    {
        if (!firstTry)
        {
            cout << Text_Messages["Banner"];
            cout << "Enter valid CPS!";
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

    cout << "\nPlease press f6 to start!\n";
}

double CalculateDelay(double cps) // CONVERTS CPS INTO MS DELAY
{
    return 1000.0 / cps;
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
