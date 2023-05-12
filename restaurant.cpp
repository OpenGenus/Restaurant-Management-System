#include <iostream>
#include <iomanip>
#include <conio.h>
#include <stdlib.h>
#include <unordered_map>
#include <queue>
#include <map>
#include <limits>

using namespace std;

class Table
{

private:
    map<int, int> tableCount = {
        {2, 4},
        {4, 6},
        {6, 2}};

public:
    unordered_map<int, pair<bool, int>> tableStatus = {
        {21, {true, 0}},
        {22, {true, 0}},
        {23, {true, 0}},
        {24, {true, 0}},
        {41, {true, 0}},
        {42, {true, 0}},
        {43, {true, 0}},
        {44, {true, 0}},
        {45, {true, 0}},
        {46, {true, 0}},
        {61, {true, 0}},
        {62, {true, 0}},
    };
    queue<int> waiting2;
    queue<int> waiting4;
    queue<int> waiting6;

    void allocation()
    {
        int people, tableId = 0;
        cout << "Enter number of people: ";
        cin >> people;
        if (people > 6)
        {
            cout << "Sorry we don't have that capacity" << endl;
            system("pause");
            return;
        }
        for (auto it : tableCount)
        {
            if (it.first >= people && it.second > 0)
            {
                tableId = it.first * 10 + it.second;
                tableCount[it.first]--;
                tableStatus[tableId].first = false;
                tableStatus[tableId].second = people;
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
            else if (people <= 4)
                waiting4.push(custId);
            else if (people <= 6)
                waiting6.push(custId);
            cout << "Thankyou,  just wait for a while!" << endl;
        }
        system("pause");
        return;
    }
    bool isValid(int tno)
    {
        if (tableStatus.find(tno) == tableStatus.end())
            return false;
        else if (tableStatus[tno].first == true)
            return false;
        return true;
    }
};

class Order : public Table
{
public:
    unordered_map<int, unordered_map<int, int>> viewBill;

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
        {10, {"Ice", 250}},
        {11, {"Chai", 15}},
        {12, {"Coffee", 250}}};

    void orderFood()
    {
        int tableId;
        cout << "Enter table id: ";
        cin >> tableId;
        if (!isValid(tableId))
        {
            cout << "INVALID" << endl;
            system("pause");
            return;
        }
        cout << "-----------MENU-----------" << endl;
        cout << "S.No\tItem\tPrice" << endl;
        for (auto it : menu)
        {
            cout << it.first << ".\t" << it.second.first << "\t" << it.second.second << endl;
        }
        int orderNo;
        cout << "Enter the numbers you want to order one by one." << endl
             << "When you finish, enter any character: ";
        while (1)
        {
            cin >> orderNo;
            if (cin.fail() || orderNo > 12 || orderNo < 1)
                break;
            viewBill[tableId][orderNo]++;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Order has been placed successfully...!" << endl;
        system("pause");
        return;
    }
};

class Bill : public Order
{
public:
    void printBill(int tno)
    {
        int i = 1, total = 0;
        cout << "\nS.No\tItem\t\t\tCount\tPrice\n";
        for (auto it : viewBill[tno])
        {
            cout << i << ".\t" << menu[it.first].first << "\t\t\t" << it.second << "\t" << menu[it.first].second * it.second << endl;
            total += menu[it.first].second * it.second;
            i++;
        }
        cout << endl
             << "\t\tTotal:\t" << total << endl;
    }
    void billing()
    {
        int tno, total = 0;
        cout << "Enter table number: ";
        cin >> tno;
        if (!isValid(tno))
        {
            cout << "INVALID" << endl;
            system("pause");
            return;
        }
        cout << "--------------------BILL--------------------" << endl;

        printBill(tno);

        cout << "Continue after payment." << endl;
        system("pause");
        cout << endl;
        cout << "    Thankyou! Visit again...!" << endl;
        system("pause");
        viewBill[tno].clear();
        allocateQueue(tno);
        return;
    }

private:
    void allocateQueue(int tno)
    {
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
            int peopleCount;
            cout << "Enter number of people: ";
            cin >> peopleCount;
            tableStatus[tno].second = peopleCount;
            system("pause");
        }
        else
        {
            tableStatus[tno].first = true;
            tableStatus[tno].second = 0;
        }
    }
};

class Overview : public Bill
{
public:
    void detailedOverview()
    {
        cout << "Number of groups in queue (2-seater): " << waiting2.size() << endl
             << "Number of groups in queue (4-seater): " << waiting4.size() << endl
             << "Number of groups in queue (6-seater): " << waiting6.size() << endl;
        system("pause");
        cout << "\t---------Table Status---------" << endl;
        cout << "Available tables are: ";
        for (auto it : tableStatus)
        {
            if (it.second.first == true)
            {
                cout << it.first << " ";
            }
        }
        cout << endl;
        system("pause");
        for (auto it : tableStatus)
        {
            if (it.second.first == false)
            {
                cout << "Table " << it.first << " is allotted, " << it.second.second << " people occupied the table, order details: " << endl;
                printBill(it.first);
            }
        }
        system("pause");
    }
};

int main()
{
    Overview ov;
    while (1)
    {
        int option;
        cout << "     Welcome to restaurant management system" << endl;
        cout << "*************************************************" << endl;
        cout << "1. Table allocation" << endl
             << "2. Order food" << endl
             << "3. View Bill" << endl
             << "4. Manager overview" << endl
             << "5. Exit" << endl
             << "Enter your choice: ";
        cin >> option;
        switch (option)
        {
        case 1:
            ov.allocation();
            break;
        case 2:
            ov.orderFood();
            break;
        case 3:
            ov.billing();
            break;
        case 4:
            ov.detailedOverview();
            break;
        case 5:
            exit(0);
            break;
        default:
            cout << "Invalid" << endl;
        }
    }
    return 0;
}
