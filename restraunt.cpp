#include <iostream>
#include <iomanip>
#include <conio.h>
#include <stdlib.h>
#include <unordered_map>
#include <queue>
#include <map>
#include <limits>

using namespace std;

unordered_map<int, unordered_map<int, int>> viewBill;

map<int, int> table = {
    {2, 4},
    {4, 6},
    {6, 2}};

unordered_map<int, int> tableBill = {
    {21, 0},
    {22, 0},
    {23, 0},
    {24, 0},
    {41, 0},
    {42, 0},
    {43, 0},
    {44, 0},
    {45, 0},
    {46, 0},
    {61, 0},
    {62, 0},
};

map<int, pair<string, int>> menu{
    {1, {"Vada", 10}},
    {2, {"Dosa", 70}},
    {3, {"Idly", 50}},
    {4, {"Pizza", 175}},
    {5, {"Burger", 160}},
    {6, {"Upma", 60}},
    {7, {"Meals", 80}},
    {8, {"Naan", 18}},
    {9, {"Curry", 210}},
    {10, {"Ice", 250}}};

queue<int> waiting2;
queue<int> waiting4;
queue<int> waiting6;

void allocation()
{
    int people, tableId = 0;
    cout << "Enter number of people: ";
    cin >> people;
    for (auto it : table)
    {
        if (it.first >= people && it.second > 0)
        {
            tableId = it.first * 10 + it.second;
            table[it.first]--;
            break;
        }
        else if (it.first >= people)
        {
            break;
        }
    }
    if (tableId != 0)
    {
        cout << "You have been allocated table id: " << tableId << endl;
    }
    else
    {
        int custId;
        cout << "Tables are full, you are in queue!" << endl;
        cout << "Enter your ID: ";
        cin >> custId;
        if (people <= 2)
            waiting2.push(custId);
        if (people <= 4)
            waiting4.push(custId);
        if (people <= 6)
            waiting6.push(custId);
        cout << "Thankyou,  just wait for a while!" << custId << endl;
    }
    system("pause");
    return;
}

void orderFood()
{
    int tableId;
    cout << "Enter table id: ";
    cin >> tableId;
    cout << "-----------MENU-----------" << endl;
    cout << "S.No\tItem\tPrice" << endl;
    for (auto it : menu)
    {
        cout << it.first << ".\t" << it.second.first << "\t" << it.second.second << endl;
    }
    int orderNo;
    cout << "Enter the numbers you want to order one by one." << endl
         << "When you finish, enter any charachter: ";
    while (1)
    {
        cin >> orderNo;
        if (cin.fail() || orderNo > 10 || orderNo < 1)
            break;
        viewBill[tableId][orderNo]++;
        tableBill[tableId] += menu[orderNo].second;
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Order has been placed successfully...!" << endl;
    system("pause");
    return;
}

void billing()
{
    int tno, total = 0;
    cout << "Enter table number: ";
    cin >> tno;
    cout << "--------------------BILL--------------------" << endl;
    int i = 1;
    cout << "\nS.No\tItem\t\t\tCount\tPrice\n";
    for (auto it : viewBill[tno])
    {
        cout << i << ".\t" << menu[it.first].first << "\t\t\t" << it.second << "\t" << menu[it.first].second * it.second << endl;
        total += menu[it.first].second * it.second;
        i++;
    }
    cout << endl
         << "\t\tTotal:\t" << total << endl;
    cout << "Continue after payment." << endl;
    system("pause");
    cout << endl;
    cout << "    Thankyou! Visit again...!" << endl;
    system("pause");
    viewBill[tno].clear();
    if (waiting2.size() > 0 || waiting4.size() > 0 || waiting6.size() > 0)
    {
        int custId;
        if (tno / 10 <= 2)
        {
            custId = waiting2.front();
            waiting2.pop();
        }
        else if (tno / 10 <= 4)
        {
            custId = waiting4.front();
            waiting4.pop();
        }
        else if (tno / 10 <= 6)
        {
            custId = waiting6.front();
            waiting6.pop();
        }
        cout << "Seats are available" << endl
             << "Table no " << tno << " is allotted for " << custId << endl;
        system("pause");
    }
    return;
}

int main()
{
    while (1)
    {
        int option;
        cout << "     Welcome to restraunt management system" << endl;
        cout << "*************************************************" << endl;
        cout << "1. Table allocation" << endl
             << "2. Order food" << endl
             << "3. View Bill" << endl
             << "4. Exit" << endl
             << "Enter your choice: ";
        cin >> option;
        switch (option)
        {
        case 1:
            allocation();
            break;
        case 2:
            orderFood();
            break;
        case 3:
            billing();
            break;
        case 4:
            exit(0);
            break;
        default:
            cout << "Invalid" << endl;
        }
    }
    return 0;
}