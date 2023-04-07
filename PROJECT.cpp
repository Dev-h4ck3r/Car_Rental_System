#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <regex>
#include <sstream>
#include <string>
using namespace std;
void welcome();
void thankyou();
void menuimage();
void QRimage();
void menu();
void admincust();
void admincars();
void admenu();
void customer_menu();
void Quit();
void insert();
void display();
void delete_record(int);
void log();
void modify();
void block();
void backadcust();
void backdcars();
void backadbm();
void Password(char *);
void login();
void insert_car();
void delete_car();
void modify_car();
void display_cars();
void book_trip();
void cancel_trip();
void reschedule();
void review();
int rent(int, char *);
void booking_menu();
bool phone_num_valid(long long);
bool adharcard_num_valid(long long);
int valid_date(int, int, int);
void QR_printer(char *);

int j;

class customer
{
private:
    long long phone_num;
    char name[100];
    char email_id[50];
    int user_id;
    long long adharcard_num;

public:
    char pwd[100];
    void create_account();
    void userdata();
    customer()
    {
        strcpy(name, "name");
        phone_num = 0;
        adharcard_num = 0;
        strcpy(email_id, "E-mail");
    }
    int retuserid()
    {
        return user_id;
    }
    long long retadhnum()
    {
        return adharcard_num;
    }
};
void customer::create_account()
{
    cout << "\n\n\t\t\t\t\t\tEnter your user name\t\t";
    cin.getline(name, 100);
    do
    {
        cout << "\n\t\t\t\t\t\tEnter your phone number\t\t";
        cin >> phone_num;
        if (phone_num_valid(phone_num))
        {
            break;
        }
        else
        {
            cout << "\n\t\t\t\t\t\t\tINVALID PHONE NUMBER";
        }
    } while (1);
    cout << "\n\t\t\t\t\t\tEnter Email ID\t\t\t";
    cin >> email_id;
    while (1)
    {
        cout << "\n\t\t\t\t\t\tEnter your Adhar Card Number\t";
        cin >> adharcard_num;
        if (adharcard_num_valid(adharcard_num))
        {
            break;
        }
        else
        {
            cout << "\n\t\t\t\t\t\t\tINVALID ADHARCARD NUMBER";
        }
    }
    ifstream f;
    int n;
    f.open("block.dat", ios::binary | ios::out);
    while (!f.eof() && f.read(reinterpret_cast<char *>(&n), sizeof(n)))
    {
        if (adharcard_num == n)
        {
            cout << "\n\n\n\t\t\t\t\t\t\tYou are blocked by the Admin\n";
            Sleep(2000);
            Quit();
        }
    }
    f.close();
    cout << "\n";
    Password(pwd);
    srand(time(0));
    user_id = (rand() % 100000) + 1;
    cout << "\n\n\t\t\t\t\t\tyour user_id is:\t\t" << user_id << endl;
}
void customer::userdata()
{
    cout << "\t|  " << setw(6) << user_id << setw(25) << name << setw(20) << phone_num << setw(20) << adharcard_num << setw(40) << email_id << setw(15) << pwd << "  |" << endl;
}

void insert()
{
    customer c;
    ofstream fout;
    fout.open("Account.dat", ios::binary | ios::app);
    if (fout)
    {
        cout << "\n\t\t\t\t\t\t\tENTER YOUR DETAILS";
        c.create_account();
        fout.write(reinterpret_cast<char *>(&c), sizeof(customer));
    }
    fout.close();
    int ch;
    cout << "\n\n\t\t\t\t\t\t\t1: MAIN MENU";
    cout << "\t2: EXIT";
    cout << "\n\t\t\t\t\t\t\t\tINPUT ";
    fflush(stdin);
    cin >> ch;
    if (ch == 1)
    {
        menu();
    }
    else if (ch == 2)
    {
        Quit();
    }
}
void display()
{
    customer d;
    ifstream fop;
    fop.open("Account.dat", ios::binary | ios::out);
    if (fop)
        cout << "\t| USER_ID               NAME                PHONE_NUM         ADHARCARD_NUM                    EMAIL_ID                 PASSWORD   |" << endl;
    cout << "\t|==================================================================================================================================|" << endl;
    {
        while (fop.read(reinterpret_cast<char *>(&d), sizeof(customer)))
        {
            d.userdata();
        }
    }
    fop.close();
}
void delete_record(int n)
{
    customer c;
    ifstream f1;
    f1.open("Account.dat", ios::in | ios::binary);
    ofstream f2;
    f2.open("Temp.dat", ios::out | ios::binary);
    while (f1.read((char *)&c, sizeof(c)))
    {
        if ((c.retuserid() != n))
        {
            f2.write(reinterpret_cast<char *>(&c), sizeof(customer));
        }
    }
    f1.close();
    f2.close();
    remove("Account.dat");
    rename("Temp.dat", "Account.dat");
    cout << "\n\n\t\t\t\t\tRecord of customer with user id " << n << " has been deleted" << endl;
}
void modify()
{
    int n;
    cout << "\n\n\t\t\t\t\t\tenter the customer's user_id\t";
    cin >> n;
    cin.clear();
    cout << "\n"
         << endl;
    bool found = false;
    customer c;
    fstream File;
    File.open("Account.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "\n\t\t\tFile could not be open !! Press any Key...";
        return;
    }
    if (File)
    {
        while (!File.eof() && found == false)
        {
            File.read(reinterpret_cast<char *>(&c), sizeof(customer));
            if (c.retuserid() == n)
            {
                cout << "\t| USER_ID               NAME                PHONE_NUM         ADHARCARD_NUM                    EMAIL_ID                 PASSWORD   |" << endl;
                cout << "\t|==================================================================================================================================|" << endl;
                c.userdata();
                cin.ignore();
                cout << "\n\t\t\t\t\t\tEnter The New Details of account\n"
                     << endl;
                c.create_account();
                int pos = (-1) * static_cast<int>(sizeof(customer));
                File.seekp(pos, ios::cur);
                File.write(reinterpret_cast<char *>(&c), sizeof(customer));
                cout << "\n\n\t\t\t\t\t\t\t\t Record Updated";
                found = true;
            }
        }
    }
    File.close();
    if (found == false)
    {
        cout << "\n\n \t\t\t\tRecord Not Found ";
    }
}
void block()
{
    long long n;
    cout << "\n\t\tEnter the Adharcard number of the customer to blocked\t";
    cin >> n;
    customer c;
    ifstream f1;
    f1.open("Account.dat", ios::in | ios::binary);
    ofstream f2;
    f2.open("Temp.dat", ios::out | ios::binary);
    while (f1.read((char *)&c, sizeof(c)))
    {
        if ((c.retadhnum() != n))
        {
            f2.write(reinterpret_cast<char *>(&c), sizeof(customer));
        }
    }
    f1.close();
    f2.close();
    remove("Account.dat");
    rename("Temp.dat", "Account.dat");
    ofstream f;
    f.open("block.dat", ios::binary | ios::app);
    f.write(reinterpret_cast<char *>(&n), sizeof(n));
    cout << "\n\t\t\tCustomer with Adharcard number " << n << " has been blocked";
    f.close();
}

class car
{
private:
    char car_name[50];
    char numplate[11];
    char color[20];
    char brand[50];
    int mileage;
    int seats;
    char model[20];
    char trans[20];
    int price_1;
    int price_24;

public:
    void car_details();
    void new_car();
    void retnum_plate(char *str)
    {
        fflush(stdin);
        strcpy(str, numplate);
    }
    int retprice1()
    {
        return price_1;
    }
    int retprice24()
    {
        return price_24;
    }
};
void car ::new_car()
{
    cout << "\n\t\t\t\t\t\tEnter Brand of Car :\t" << setw(15);
    cin.getline(brand, 50);
    cin.ignore();
    cout << "\t\t\t\t\t\tEnter Name of Car :\t" << setw(15);
    cin >> car_name;
    cout << "\n\t\t\t\t\t\tEnter Number Plate :\t" << setw(15);
    cin >> numplate;
    cout << "\n\t\t\t\t\t\tEnter Color :\t" << setw(15);
    cin >> color;
    cout << "\n\t\t\t\t\t\tEnter Mileage :\t" << setw(15);
    cin >> mileage;
    cout << "\n\t\t\t\t\t\tEnter Seats :\t" << setw(15);
    cin >> seats;
    cout << "\n\t\t\t\t\t\tEnter Model :\t" << setw(15);
    cin >> model;
    cout << "\n\t\t\t\t\t\tEnter Transmission :\t" << setw(15);
    cin >> trans;
    cout << "\n\t\t\t\t\t\tenter Rent per Hour :\t" << setw(15);
    cin >> price_1;
    cout << "\n\t\t\t\t\t\tEnter Price per Day :\t" << setw(15);
    cin >> price_24;
}
void car ::car_details()
{
    cout << "\t| " << setw(10) << numplate << setw(15) << brand << setw(13) << car_name << setw(15) << model << setw(10) << seats << setw(15) << color << setw(10) << mileage << setw(15) << price_1 << setw(20) << price_24 << setw(22) << trans << " |" << endl;
}
void insert_car()
{
    car ca;
    ofstream fout;
    fout.open("Car.dat", ios::binary | ios::app);
    cout << "\t\t\t\t\t\t\tEnter Car's Details\n\n";
    if (fout)
    {
        cin.ignore();
        ca.new_car();
        fout.write(reinterpret_cast<char *>(&ca), sizeof(car));
    }
    fout.close();
}
void display_cars()
{
    car ca;
    ifstream fop;
    fop.open("Car.dat", ios::binary | ios::out);
    cout << "\t| Plate Number      Brand          Name           Model     Capacity       Colour     Mileage     Rate Per Hour      Rate Per 24 Hour  Transmission |" << endl;
    cout << "\t|===================================================================================================================================================|" << endl;
    if (fop)
    {
        while (fop.read(reinterpret_cast<char *>(&ca), sizeof(car)))
        {
            fflush(stdout);
            ca.car_details();
            fflush(stdout);
        }
    }
    fop.close();
}

void delete_car()
{
    car ca;
    char ch[11];
    char chn[11];
    cin.ignore();
    cout << "\n\t\t\t\t\t\tEnter the Number plate of the car\t";
    cin >> chn;
    ifstream f1;
    f1.open("Car.dat", ios::in | ios::binary);
    ofstream f2;
    f2.open("Temp.dat", ios::out | ios::binary);
    while (f1.read((char *)&ca, sizeof(ca)))
    {
        fflush(stdin);
        ca.retnum_plate(ch);
        fflush(stdin);
        if (strcmp(chn, ch) != 0)
        {
            cout << "";
            f2.write(reinterpret_cast<char *>(&ca), sizeof(car));
        }
    }
    f1.close();
    f2.close();
    remove("Car.dat");
    rename("Temp.dat", "Car.dat");
    cout << "\n\n\t\t\t\t\t\t\tCar with Number plate " << chn << " has been deleted" << endl;
}

void modify_car()
{
    char ch[11], p[11];
    cin.ignore();
    cout << "\n\t\t\t\t\t\tEnter the Number Plate of Car\t";
    cin >> p;
    bool found = false;
    car ca;
    fstream File;
    File.open("Car.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "\t\t\t\t\t\tFile could not be open !! Press any Key...";
        return;
    }
    if (File)
    {
        while (!File.eof() && found == false)
        {
            File.read(reinterpret_cast<char *>(&ca), sizeof(car));
            ca.retnum_plate(ch);
            if (strcmp(ch, p) == 0)
            {
                cout << "\t| Plate Number      Brand         Name         Model     Capacity     Colour     Mileage     Rate Per Hour     Rate Per 24 Hour      Transmission   |" << endl;
                cout << "\t|===================================================================================================================================================|" << endl;
                ca.car_details();
                cout << "\n\t\t\t\t\t\t\tEnter The New Details of car\n"
                     << endl;
                ca.new_car();
                cin.ignore();
                int pos = (-1) * static_cast<int>(sizeof(car));
                File.seekp(pos, ios::cur);
                File.write(reinterpret_cast<char *>(&ca), sizeof(car));
                cout << "\n\n\t\t\t\t\t\t\t\tRescheduling Successful";
                found = true;
            }
        }
    }
    if (found == false)
    {
        cout << "\n\n Record Not Found ";
    }
    File.close();
}
class cust_front
{
private:
    char from[100];
    char to[100];
    int t_hour;
    long t_rent;
    int day1, mon1, year1;
    int day2, mon2, year2;
    int h1, min1;
    int h2, min2;
    char n[50];
    int b_num = 1000;
    int uid;

public:
    void rental_data_input();
    void rental_data_output();
    int ret_booknum()
    {
        return b_num;
    }
    int retuid()
    {
        return uid;
    }
};
void cust_front ::rental_data_input()
{
    uid = j;
    cout << "\n\n\t\t\t\t\t\tUSER_ID\t" << j;
    cout << "\n\t\t\t\t\t\tenter the number plate of chosen car:\t";
    cin >> n;
    cin.ignore();
    cout << "\t\t\t\t\t\tEnter the pickup destination\t";
    cin.getline(from, 100);
    cin.ignore();
    fflush(stdin);
    cout << "\t\t\t\t\t\tEnter the returning destination\t";
    cin.getline(to, 100);
    fflush(stdin);
    while (1)
    {
        cout << "\n\t\t\t\t\t\tEnter Pickup Date(dd/mm/yyyy)";
        cout << "\n\t\t\t\t\t\tDay:\t";
        cin >> day1;
        cout << "\t\t\t\t\t\tMonth:\t";
        cin >> mon1;
        cout << "\t\t\t\t\t\tYear:\t";
        cin >> year1;
        fflush(stdin);
        if (valid_date(day1, mon1, year1) == 0)
        {
            cout << "\n\t\t\t\t\t\t\tInvalid Date";
        }
        else
        {
            break;
        }
    }
    while (1)
    {
        cout << "\n\t\t\t\t\t\tEnter returning Date(dd/mm/yyyy)\t";
        cout << "\n\t\t\t\t\t\tDay:\t";
        cin >> day2;
        cout << "\t\t\t\t\t\tMonth:\t";
        cin >> mon2;
        cout << "\t\t\t\t\t\tYear:\t";
        cin >> year2;
        fflush(stdin);
        if (valid_date(day2, mon2, year2) == 0)
        {
            cout << "\n\t\t\t\t\t\t\tInvalid Date";
        }
        else
        {
            break;
        }
    }
    while (1)
    {
        cout << "\n\t\t\t\t\t\tEnter Pickup Time(HH:MM)[24 hour Format]";
        cout << "\n\t\t\t\t\t\tHour:\t";
        cin >> h1;
        cout << "\n\t\t\t\t\t\tMinute:\t";
        cin >> min1;
        fflush(stdin);
        if (h1 > 23 || min1 > 59)
        {
            cout << "Invalid Pick up Time";
        }
        else
        {
            break;
        }
    }
    while (1)
    {
        cout << "\n\t\t\t\t\t\tEnter Returning Time(HH:MM)[24 hour Format]";
        cout << "\n\t\t\t\t\t\tHour\t";
        cin >> h2;
        cout << "\n\t\t\t\t\t\tMinute:\t";
        cin >> min2;
        fflush(stdin);
        if (h2 > 23 || min2 > 59)
        {
            cout << "Invalid Pick up Time";
        }
        else
        {
            break;
        }
    }
    cout << "\n\t\t\t\t\t\tEnter Hours of rent:\t";
    cin >> t_hour;
    t_rent = rent(t_hour, n);
    fflush(stdin);
    cout << "\n\t\t\t\t\t\tTotal Rental charges:\t" << t_rent;
    srand(time(0));
    b_num = (rand() % 50000) + 1;
    cout << "\n\n\t\t\t\t\t\tYour Booking Number is:\t" << b_num;
}
void cust_front ::rental_data_output()
{
    cin.ignore();
    cout << "\t| " << setw(5) << b_num << setw(13) << uid << setw(15) << n << setw(8) << h1 << ":" << min1 << setw(9) << h2 << ":" << min2 << setw(11) << day1 << "/" << mon1 << "/" << year1 << setw(9) << day2 << "/" << mon2 << "/" << year2 << setw(16) << from << setw(19) << to << setw(10) << t_hour << setw(12) << t_rent << "     |" << endl;
    fflush(stdout);
}
void book_trip()
{
    cust_front c;
    display_cars();
    ofstream fout;
    fout.open("Log.dat", ios::binary | ios::app);
    cout << "\n\n\t\t\t\t\t\t\t\tEnter the details\n\n";
    if (fout)
    {
        cin.ignore();
        c.rental_data_input();
        fout.write(reinterpret_cast<char *>(&c), sizeof(cust_front));
    }
    fout.close();
    cout<<"\n\n\t\t\t\t\t\t\tScan the QR code for payment\n\n";
    QRimage();
}
void review()
{
    cust_front c;
    ifstream fop;
    fop.open("Log.dat", ios::binary | ios::out);
    cout << "\t| BookingNum   USER_ID   PLATE NUM   PICKUP TIME  RETURNING TIME  PICKUP DATE  RETURNING DATE     START POINT       END POINT    RENTAL HOUR   TOTAL RENT |" << endl;
    cout << "\t|=========================================================================================================================================================|" << endl;
    if (fop)
    {
        while (fop.read(reinterpret_cast<char *>(&c), sizeof(cust_front)))
        {
            if (c.retuid() == j)
            {
                c.rental_data_output();
            }
        }
    }
    fop.close();
}
void log()
{
    cust_front c;
    ifstream fop;
    fop.open("Log.dat", ios::binary | ios::out);
    cout << "\t| BookingNum   USER_ID   PLATE NUM   PICKUP TIME  RETURNING TIME  PICKUP DATE  RETURNING DATE     START POINT       END POINT    RENTAL HOUR   TOTAL RENT |" << endl;
    cout << "\t|=========================================================================================================================================================|" << endl;
    if (fop)
    {
        while (fop.read(reinterpret_cast<char *>(&c), sizeof(cust_front)))
        {
            c.rental_data_output();
        }
    }
    fop.close();
}
void reschedule()
{
    display_cars();
    cust_front c;
    int n;
    cout << "\n\t\t\t\tEnter the booking number\t\n\n";
    cin >> n;
    fstream File;
    bool found = false;
    File.open("Log.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "\n\t\t\t\t\tFile could not be open !! Press any Key...";
        return;
    }
    if (File)
    {
        while (!File.eof() && found == false)
        {
            File.read(reinterpret_cast<char *>(&c), sizeof(cust_front));
            if (c.retuid() == j)
            {
                cout << "\t| BookingNum   USER_ID   PLATE NUM   PICKUP TIME  RETURNING TIME  PICKUP DATE  RETURNING DATE     START POINT       END POINT    RENTAL HOUR   TOTAL RENT |" << endl;
                cout << "\t|=========================================================================================================================================================|" << endl;
                c.rental_data_output();
                if (c.ret_booknum() == n)
                {
                    cin.ignore();
                    cout << "\n\t\t\t\t\t\t\tEnter The New Details of your trip\n"
                         << endl;
                    c.rental_data_input();
                    int pos = (-1) * static_cast<int>(sizeof(cust_front));
                    File.seekp(pos, ios::cur);
                    File.write(reinterpret_cast<char *>(&c), sizeof(cust_front));
                    cout << "\n\n\t\t\t\t\t\t Rescheduled Successfully";
                    found = true;
                }
            }
        }
    }
    File.close();
    if (found == false)
    {
        cout << "\n\n\t\t\t\t\t Booking Cannot be Rescheduled!";
    }
}

void cancel_trip()
{
    int n;
    cout << "\n\n\t\t\t\t\t\tEnter the booking Number\t";
    cin >> n;
    cust_front c;
    ifstream f1;
    f1.open("Log.dat", ios::in | ios::binary);
    ofstream f2;
    f2.open("Temp.dat", ios::out | ios::binary);
    while (f1.read((char *)&c, sizeof(c)))
    {
        if (c.ret_booknum() != n)
        {
            f2.write(reinterpret_cast<char *>(&c), sizeof(cust_front));
        }
    }
    f1.close();
    f2.close();
    remove("Log.dat");
    rename("Temp.dat", "Log.dat");
    cout << "\n\n\t\t\t\t\t\tYour booking has been cancelled" << endl;
}

int rent(int hour, char *n)
{
    car c;
    char ch[50];
    int price24, price1;
    bool found = false;
    ifstream f;
    f.open("Car.dat", ios::binary | ios::out);
    while (f.read((char *)&c, sizeof(c)))
    {
        c.retnum_plate(ch);
        if (strcmp(ch, n) == 0)
        {

            price1 = c.retprice1();
            price24 = c.retprice24();
            found = true;
        }
    }
    f.close();
    if (found == false)
    {
        return 1;
    }
    int hour_24, hour_1;
    int total, total_24, total_1;
    hour_24 = hour / 24;
    hour_1 = (hour - hour_24 * 24);
    total_24 = hour_24 * price24;
    total_1 = hour_1 * price1;
    total = total_24 + total_1;
    return total;
}

bool phone_num_valid(long long n)
{
    string s = to_string(n);
    const regex pattern("(0|91)?[6-9][0-9]{9}");
    if (regex_match(s, pattern))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool adharcard_num_valid(long long n)
{
    string s = to_string(n);
    const regex pattern("^[2-9]{1}[0-9]{3}[0-9]{4}[0-9]{4}$");
    if (regex_match(s, pattern))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int valid_date(int day, int mon, int year)
{
    int is_valid = 1, is_leap = 0;

    if (year >= 1800 && year <= 9999)
    {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
            is_leap = 1;
        }
        if (mon >= 1 && mon <= 12)
        {
            if (mon == 2)
            {
                if (is_leap && day == 29)
                {
                    is_valid = 1;
                }
                else if (day > 28)
                {
                    is_valid = 0;
                }
            }
            else if (mon == 4 || mon == 6 || mon == 9 || mon == 11)
            {
                if (day > 30)
                {
                    is_valid = 0;
                }
            }
            else if (day > 31)
            {
                is_valid = 0;
            }
        }

        else
        {
            is_valid = 0;
        }
    }
    else
    {
        is_valid = 0;
    }

    return is_valid;
}
void booking_menu()
{
    menuimage();
    system("color 07");
    int ch;
    cout << "\n\n\n\n\t\t\t\t\t\t\t\t Booking Management \n\n";
    cout << "\t\t\t\t\t\t\t1:Book a car\n";
    cout << "\t\t\t\t\t\t\t2:Reschedule Your Booking\n";
    cout << "\t\t\t\t\t\t\t3:Cancel your Booking\n";
    cout << "\t\t\t\t\t\t\t4:Review your Booking\n";
    cout << "\t\t\t\t\t\t\t5:Main Menu\n\n";
    cout << "\t\t\t\t\t\t\t\tInput:\t";
    cin >> ch;
    switch (ch)
    {
    case 1:
        menuimage();
        book_trip();
        backadbm();
        break;
    case 2:
        menuimage();
        reschedule();
        backadbm();
        break;
    case 3:
        menuimage();
        cancel_trip();
        backadbm();
        break;
    case 4:
        menuimage();
        review();
        backadbm();
        break;
    case 5:
        menu();
        break;
    case 347:
        log();
    default:
        cout << "\n\t\t\t\t\tWrong Choice";
        booking_menu();
        break;
    }
}
void welcome()
{
    system("mode 650");
    //system("mode con COLS=700");
    //ShowWindow(GetConsoleWindow(),SW_MAXIMIZE);
    //SendMessage(GetConsoleWindow(),WM_SYSKEYDOWN,VK_RETURN,0x20000000);
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    ifstream ifs("welcome.txt");
    string Lines = "";
    if (ifs)
    {
        while (ifs.good())
        {
            string t;
            getline(ifs, t);
            t += "\n";
            Lines += t;
        }
        cout << Lines;
    }
    cout << "\n\t  |\t\t\t\t\t\t\t\n\n\n\n\n\n\n\n\n\n";
    ifs.close();
    Sleep(2000);
}

void QR_printer(char *ch)
{  
    char d = (unsigned char)226;
    char c = (unsigned char)128;
    char u = (unsigned char)150;
    char e = (unsigned char)136;
    char g = (unsigned char)132;
    system ("Color 70");
    for (int i = 0; i < 200; i++)
    { 
        if ((ch[i] == d) && (ch[i + 1] == u) && (ch[i + 2] == e))
        { 
            cout << (unsigned char)219;
            i + 2;
        }
        else if (ch[i] == ' ')
        {
            cout << " ";
        }
        else if (ch[i] == '|')
        {
            cout << "\n";
            cout<<"\t\t\t\t\t\t\t\t";
        }
        else if ((ch[i] == d) && (ch[i + 1] == u) && (ch[i + 2] == c))
        {
            cout << (unsigned char)223;
            i + 2;
        }
        else if ((ch[i] == d) && (ch[i + 1] == u) && (ch[i + 2] == g))
        {
            cout << (unsigned char)220;
            i + 2;
        }
    }
}

void menuimage()
{
    system("cls");
    ifstream ifs("art.txt");
    string Lines = "";

    if (ifs)
    {
        while (ifs.good())
        {
            string t;
            getline(ifs, t);
            t += "\n";
            Lines += t;
        }
        cout << Lines;
    }
    cout << "\n\t  |\t\t\t\t\t\t\t\n\n\n\n\n";
    ifs.close();
}
void ThankYou()
{
    system("cls");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    ifstream ifs("Thank You.txt");
    string Lines = "";

    if (ifs)
    {
        while (ifs.good())
        {
            string t;
            getline(ifs, t);
            t += "\n";
            Lines += t;
        }
        cout << Lines;
    }
    cout << "\n\t  |\t\t\t\t\t\t\t";
    ifs.close();
}

void QRimage()
{
    char ch[200];
    ifstream f;
    f.open("QR.txt");
    while (!f.eof())
    { f.read((char *)&ch, sizeof(ch));
        QR_printer(ch);
    }
    f.close();
}
void backadcust()
{
    int ch;
    cout << "\n\n\t\t\t\t\t\t\t1: Customer Management";
    cout << "\t2: Administrator Menu";
    cout << "\n\t\t\t\t\t\t\t\t\t  INPUT ";
    cin >> ch;
    fflush(stdin);
    if (ch == 1)
    {
        admincust();
    }
    else if (ch == 2)
    {
        admenu();
    }
}
void backadcars()
{
    int ch;
    cout << "\n\n\t\t\t\t\t\t\t1: Car Management";
    cout << "\t2: Administrator Menu";
    cout << "\n\n\t\t\t\t\t\t\t\t\tINPUT ";
    cin >> ch;
    fflush(stdin);
    if (ch == 1)
    {
        admincars();
    }
    else if (ch == 2)
    {
        admenu();
    }
}
void backadbm()
{
    int ch;
    cout << "\n\n\t\t\t\t\t\t\t1:Booking Management";
    cout << "\t2: EXIT";
    cout << "\n\t\t\t\t\t\t\t\t\tINPUT ";
    cin >> ch;
    fflush(stdin);
    if (ch == 1)
    {
        booking_menu();
    }
    else if (ch == 2)
    {
        Quit();
    }
}
void Password(char *ch)
{
    string password;
    cout << "\t\t\t\t\t\tEnter Password\t\t";
    char c;
    while (c != '\r') //Loop until 'Enter' is pressed
    {
        c = getch();
        if (c == 0)
        {
            switch (getch())
            {
            default:
                break;
            };
        }
        else if (c == '\b')
        {
            if (password.size() != 0)
            {
                cout << "\b \b";
                password.erase(password.size() - 1, 1);
            }
            continue;
        }
        else if (c <= '9' && c >= '0' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '!' || c == '@' || c == '#' || c == '$' || c == '%' || c == '*' || c == '&')
        {
            password += c;
            cout << "*";
        }
        else
            continue;
    }

    int i;
    for (i = 0; i < password.size(); i++)
    {
        ch[i] = password[i];
    }
    ch[password.size()] = '\0';
}
void login()
{
    int n;
    char ch[100];
    customer c;
    cout << "\n\n\n\t\t\t\t\t\tEnter User Id:\t\t";
    cin >> n;
    cout << "\n";
    Password(ch);
    ifstream f;
    bool found = false;
    f.open("Account.dat", ios::binary);
    while (f.read(reinterpret_cast<char *>(&c), sizeof(customer)) && found == false)
    {
        if (c.retuserid() == n)
        {
            j = n;
            int pos = (-1) * static_cast<int>(sizeof(customer));
            f.seekg(pos, ios::cur);
            if (strcmp(c.pwd, ch) == 0)
                booking_menu();
            found = true;
        }
        else if ((c.retuserid() == n) && (strcmp(c.pwd, ch) == 1))
        {
            break;
        }
    }
    f.close();
    if (found == false)
    {
        cout << "\n\n\t\t\t\t\t\tWrong User ID or Password ";
        Sleep(1000);
        customer_menu();
    }
}

void loginad()
{
    menuimage();
    char n[20];
    char ch[20];
    bool found = false;
    cout << "\n\n\t\t\t\t\t\t\t\t\tADMIN\n\n";
    strcpy(n, "Pra123@#");
    cout << "\t";
    Password(ch);
    if (strcmp(n, ch) == 0)
    {
        admenu();
        found = true;
    }
    if (found == false)
    {
        cout << "\n\n\n\t\t\t\t\t\t\t\tWrong Password ";
        Sleep(1000);
        menu();
    }
}
void admincust()
{
    menuimage();
    int ch;
    cout << "\n\n\n\n\t\t\t\t\t\t\t\tCUSTOMER MANAGEMENT\n\n";
    cout << "\t\t\t\t\t\t\t1:Display Account of Customers\n";
    cout << "\t\t\t\t\t\t\t2:Delete Account of a Customer\n";
    cout << "\t\t\t\t\t\t\t3:Display log a of Customers\n";
    cout << "\t\t\t\t\t\t\t4:Update account  of a Customer\n";
    cout << "\t\t\t\t\t\t\t5:Block a Customer\n";
    cout << "\t\t\t\t\t\t\t6:Administrator Menu\n\n";
    cout << "\t\t\t\t\t\t\t\tInput:"
         << " ";
    cin >> ch;
    switch (ch)
    {
    case 1:
        menuimage();
        display();
        backadcust();
        break;
    case 2:
        menuimage();
        display();
        int n;
        cout << "\n\n\t\t\t\t\t\t\tEnter User_ID of record to be deleted\t\t";
        cin >> n;
        cin.ignore();
        delete_record(n);
        backadcust();
        break;
    case 3:
        menuimage();
        log();
        backadcust();
        break;
    case 4:
        menuimage();
        display();
        modify();
        backadcust();
        break;
    case 5:
        menuimage();
        display();
        block();
        backadcust();
        break;
    case 6:
        admenu();
        break;
    default:
        cout << "\n\t\t\t\t\t\t\t\tWrong Choice! Try Again";
        Sleep(2000);
        admincust();
        break;
    }
}
void admincars()
{
    menuimage();
    int ch;
    cout << "\n\n\n\n\t\t\t\t\t\t\t\tCARS MANAGEMENT\n\n";
    cout << "\t\t\t\t\t\t\t1:Add a Car in the Database\n";
    cout << "\t\t\t\t\t\t\t2:Display details of all cars in the Database\n";
    cout << "\t\t\t\t\t\t\t3:Remove a car from the Database\n";
    cout << "\t\t\t\t\t\t\t4:Change details of a Car\n";
    cout << "\t\t\t\t\t\t\t5:Administrator Menu\n\n";
    cout << "\t\t\t\t\t\t\t\tInput:\t";
    cin >> ch;
    switch (ch)
    {
    case 1:
        menuimage();
        insert_car();
        backadcars();
        break;
    case 2:
        menuimage();
        display_cars();
        backadcars();
        break;
    case 3:
        menuimage();
        display_cars();
        delete_car();
        backadcars();
        break;
    case 4:
        menuimage();
        display_cars();
        modify_car();
        backadcars();
        break;
    case 5:
        admenu();
        break;
    default:
        cout << "\n\t\t\t\t\tWrong Choice";
        admincars();
        break;
    }
}
void customer_menu()
{
    menuimage();
    int ch;
    cout << "\n\n\n\n\t\t\t\t\t\t\t\tCUSTOMER\n\n";
    cout << "\t\t\t\t\t\t\t1:Create Account\n";
    cout << "\t\t\t\t\t\t\t2:Login\n";
    cout << "\t\t\t\t\t\t\t3:Main Menu\n";
    cout << "\t\t\t\t\t\t\t\tInput:"
         << " ";
    cin >> ch;
    cin.ignore();
    switch (ch)
    {
    case 1:
        menuimage();
        insert();
        break;
    case 2:
        menuimage();
        login();
        break;
    case 3:
        menu();
    default:
        cout << "wrong choice";
        Sleep(1000);
        customer_menu();
        break;
    }
}
void Quit()
{
    ThankYou();
    Sleep(1000);
    exit(0);
}
void admenu()
{
    menuimage();
    int ch;
    cout << "\t\t\t\t\t\t\t\t\tADMINISTRATOR MENU\n\n"
         << endl;
    cout << "\t\t\t\t\t\t1: MANAGE CUSTOMERS" << endl;
    cout << "\t\t\t\t\t\t2: MANAGE CARS" << endl;
    cout << "\t\t\t\t\t\t3: MAIN MENU" << endl;
    cout << "\t\t\t\t\t\t\tINPUT\t";
    cin >> ch;
    cin.ignore();
    switch (ch)
    {
    case 1:
        admincust();
        break;
    case 2:
        admincars();
        break;
    case 3:
        menu();
        break;
    default:
        cout << "Wrong Choice!" << endl;
        Sleep(1000);
        admenu();
    }
}
void menu()
{
    menuimage();
    int ch;
    cout << "\t\t\t\t\t\t\t\t\tMAIN MENU\n\n"
         << endl;
    cout << "\t\t\t\t\t\t1:ADMIN" << endl;
    cout << "\t\t\t\t\t\t2:CUSTOMER" << endl;
    cout << "\t\t\t\t\t\t3:EXIT" << endl;
    cout << "\n\t\t\t\t\t\t\tInput ";
    cin >> ch;
    cin.ignore();
    switch (ch)
    {
    case 1:
        loginad();
        break;
    case 2:
        customer_menu();

        break;
    case 3:
        Quit();
        break;
    default:
        cout << "\t\t\t\t\t\t\tWrong Choice";
        Sleep(1000);
        menu();
        break;
    }
}

int main()
{
    welcome();
    menu();
    return 0;
}