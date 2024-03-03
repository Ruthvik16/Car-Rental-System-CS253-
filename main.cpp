#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <cctype>
#include <string>
using namespace std;

vector<vector<string>> content;

namespace MyStoi{
    class NotIntegerException : public std::exception {
    public:
        const char* what() const noexcept override {
            return "Input string is not a valid integer";
        }
    };

    int stoi(const std::string& s) {
        for (char c : s) {
            if (!isdigit(c)) {
                throw NotIntegerException();
            }
        }

        try {
            return std::stoi(s);
        } catch (const std::out_of_range&) {
            throw std::out_of_range("Input string is out of range of int");
        }
    }
}

void divider(){
    cout<<"====================================================================\n";
}

std::string formatDateFromSeconds(time_t seconds) {
    std::tm* timeinfo = std::localtime(&seconds);

    if (timeinfo == nullptr) {
        return "";
    }
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << timeinfo->tm_mday << '/' << std::setw(2) << timeinfo->tm_mon + 1 << '/' << timeinfo->tm_year + 1900;

    return oss.str();
}

void readfile(string fname){
    vector<string> row;
    string line, word;

    fstream file (fname,ios::in);
    if(file.is_open()){
        while(getline(file, line)){
            row.clear();
            stringstream str(line);
            while(getline(str, word, ',')) row.push_back(word);
            content.push_back(row);
        }
        file.close();
    }
    else cout<<"Could not open the file\n";
}

void clearfile(string fname) {
    std::ofstream ofs;
    ofs.open(fname, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

void writefile(vector<vector<string>> data, string filename) {
    std::ofstream file(filename);

    for (const auto &row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i != row.size() - 1) 
                file << ",";
        }
        file << "\n";
    }

    file.close();
}

bool check(string id){
    content.clear();
    readfile("customers.csv");
    for(auto &x:content){
        if(x[1]==id) return true;
    }
    content.clear();
    readfile("employee.csv");
    for(auto &x:content){
        if(x[1]==id) return true;
    }
    content.clear();
    return false;
}

bool check_car(string id){
    content.clear();
    readfile("cars.csv");
    for(auto &x:content){
        if(x[1]==id) return true;
    }
    return false;
}

//User
class User{
    private:
        string password;
    public:
        string name;
        string id;
        int record;
        vector<string> cars_rented;
        double Fine_Due;
        void display_menu();
        void login();
        void logout();
        void see_all_available_cars_given_record(string id, string type_user); 
        void see_rented_cars(string id, string type_user); 
        void rent_car(string id, string car_id,string type_user);
        void return_car(string id,string car_id,string type_user);
        int calc_dues(string id,string type_user);
        void clear_fine_amount(string id,string type_user);
        string return_name(string id, string type_user);
};

//Customer
class Customer : public User{
    public:
        void display_customer_lookup(string id);
        void sign_up();
};
//Employee
class Employee : public User{
    public:
        void display_employee_lookup(string id);
};

//Manager
class Manager : public User{
    public:
        void display_manager_lookup(string id);
        void see_all_users();
        void see_all_cars();
        void add_user();
        void update_user();
        void delete_user();
        void add_car();
        void update_car();
        void delete_car();
        void see_rented_by_user(string id,string uid);
        void see_rented_cars_and_who_rented(string id);
        void see_due_date_of_car(string id);
};

class Car{
    public:
        string model;
        string id;
        string condition;
        int availability;
        int min_record_to_rent;
        int base_rent;
};

void User :: display_menu(){
    bool validinput= false;
    string temp;
    while(!validinput){
        divider();
        cout<<"Welcome to Ruthviks Car Rental System\n";
        cout<<"1. Press 1 to log in : \n";
        cout<<"2. Press 2 if you are a new customer"<<endl;
        cout<<"3. Press 3 to exit\n";
        divider();
        cin>>temp;
        bool a = false;
        a=false;
        while(!a){
            try{
                MyStoi::stoi(temp);
                if(temp=="1" || temp=="2" || temp=="3") a=true;
                else{
                    cout<<"Please enter a valid input between 1 and 3"<<endl;
                    cin>>temp;
                    a = false;
                }
                
            }
            catch(...){
                cout<<"Please enter a valid input between 1 and 3"<<endl;
                cin>>temp;
                a=false;
            }
        }
        validinput= true;
    }
    if(temp=="1"){
        User u;
        u.login();
    }
    else if(temp=="2"){
        Customer c;
        c.sign_up();
        User u;
        u.display_menu();
    }
    else if(temp=="3"){
        cout<<"Thanks for using my system!";
        exit(1);
    }  
}

void User :: login(){
    bool validinput=false;
    string temp;
    divider();
    cout<<"Please choose your role\n";
    cout<<"1. Enter 1 if you are a Customer : \n";
    cout<<"2. Enter 2 if your are an Employee\n";
    cout<<"3. Enter 3 if your are a Manager\n";
    cout<<"4. Enter 4 if you want to exit\n";
    divider();
    cin>>temp;
    bool a = false;
    a=false;
    while(!a){
        //Write code to check if input temporary can be converted to an integer using MyStoi::stoi else ask for input again
        try{
            MyStoi::stoi(temp);
            if(temp=="1" || temp=="2" || temp=="3" || temp=="4") a=true;
            else{
                cout<<"Please enter a valid input between 1 and 4"<<endl;
                cin>>temp;
                a = false;
            }
            
        }
        catch(...){
            cout<<"Please enter a valid input between 1 and 4"<<endl;
            cin>>temp;
            a=false;
        }
    }

    if(temp=="4") return;
    else{
        string id,password;
        cout<<"Enter your id : ";
        cin>>id;
        cout<<"Enter the password : ";
        cin>>password;
        //If Customer, check if existing customer in the Customer database
        if(temp=="1"){
            vector<string> words_in_a_row;
            string line_in_csv,word;
            fstream file("customers.csv",ios::in);
            int count=0;
            if(file.is_open()){
                while(getline(file,line_in_csv)){
                    words_in_a_row.clear();
                    stringstream str(line_in_csv);
                    while(getline(str,word,',')) words_in_a_row.push_back(word);
                    if(words_in_a_row[1]==id){
                        count=1;
                        if(words_in_a_row[2]==password){
                            count++;
                            break;
                        }
                        else{
                            while(password!=words_in_a_row[2]){
                                cout<<"You entered the wrong password. Press 1 to reenter the password and 2 to exit\n";
                                char c;
                                cin>>c;
                                if(c=='1'){
                                    cout<<"Enter the password : ";
                                    cin>>password;
                                    if(password==words_in_a_row[2]) count++;
                                }
                                else if(c=='2'){
                                    cout<<"Exiting...";
                                    return;
                                }
                                else{
                                    cout<<"Please enter a valid input.\n";
                                }
                            }
                            if(count==2) break;
                        }
                    }
                    if(count==2) break;            
                }
                if(count==0){
                    cout<<"Customer not found\n";
                    User u;
                    u.display_menu();
                }
                if(count==2){
                    Customer c;
                    c.display_customer_lookup(id);
                }
            }
        }
        //If Employee, check if existing customer in the Employee database
        if(temp=="2"){
            vector<string> words_in_a_row;
            string line_in_csv,word;
            fstream file("employee.csv",ios::in);
            int count=0;
            if(file.is_open()){
                while(getline(file,line_in_csv)){
                    words_in_a_row.clear();
                    stringstream str(line_in_csv);
                    while(getline(str,word,',')) words_in_a_row.push_back(word);
                    if(words_in_a_row[1]==id && words_in_a_row[3]=="employee"){
                        count=1;
                        if(words_in_a_row[2]==password){
                            count++;
                            break;
                        }
                        else{
                            while(password!=words_in_a_row[2]){
                                cout<<"You entered the wrong password. Press 1 to reenter the password and 2 to exit\n";
                                char c;
                                cin>>c;
                                if(c=='1'){
                                    cout<<"Enter the password : ";
                                    cin>>password;
                                    if(password==words_in_a_row[2]) count++;
                                }
                                else if(c=='2'){
                                    cout<<"Exiting...";
                                    return;
                                }
                                else{
                                    cout<<"Please enter a valid input.\n";
                                }
                            }
                            if(count==2) break;
                        }
                    }
                    if(count==2) break;            
                }
                if(count==0){
                    cout<<"Employee not found\n";
                    User u;
                    u.display_menu();
                }
                if(count==2){
                    Employee e;
                    e.display_employee_lookup(id);
                }
            }
        }
        //If Manager, check if existing customer in the Employee database
        if(temp=="3"){
            vector<string> words_in_a_row;
            string line_in_csv,word;
            fstream file("employee.csv",ios::in);
            int count=0;
            if(file.is_open()){
                while(getline(file,line_in_csv)){
                    words_in_a_row.clear();
                    stringstream str(line_in_csv);
                    while(getline(str,word,',')) words_in_a_row.push_back(word);
                    if(words_in_a_row[1]==id && words_in_a_row[3]=="manager"){
                        count=1;
                        if(words_in_a_row[2]==password){
                            count++;
                            break;
                        }
                        else{
                            while(password!=words_in_a_row[2]){
                                cout<<"You entered the wrong password. Press 1 to reenter the password and 2 to exit\n";
                                char c;
                                cin>>c;
                                if(c=='1'){
                                    cout<<"Enter the password : ";
                                    cin>>password;
                                    if(password==words_in_a_row[2]) count++;
                                }
                                else if(c=='2'){
                                    cout<<"Exiting...";
                                    return;
                                }
                                else{
                                    cout<<"Please enter a valid input.\n";
                                }
                            }
                            if(count==2) break;
                        }
                    }
                    if(count==2) break;            
                }
                if(count==0){
                    cout<<"Manager not found\n";
                    User u;
                    u.display_menu();
                }
                if(count==2){
                    Manager m;
                    m.display_manager_lookup(id);
                }
            }
        }       
    }
}

void Customer :: display_customer_lookup(string id){
    divider();
    User u;
    string name = u.return_name(id,"customer");
    cout<<"Welcome "<<name<<"."<<endl;
    cout<<"\nYou have been Succesfully logged in as a Customer\n";
    //void see_all_available_cars_given_record(string id);
    cout<<"Press 1 to see all the available cars for rent\n";
    //void see_rented_cars(string id);
    cout<<"Press 2 to view cars rented by you\n";
    //void rent_car(string id, string car_id,string type_user);
    cout<<"Press 3 to rent a car\n";
    //void return_car(string id,string car_id);
    cout<<"Press 4 to return a car\n";
    //int calc_dues(string id,string type_user);
    cout<<"Press 5 to view the fine\n";
    //void clear_fine_amount(string id,string type_user);
    cout<<"Press 6 to clear your fine\n";
    cout<<"Press 7 to show due date of a particular car rented by you\n";
    cout<<"Press 8 to logout\n";
    divider();
    string temp;
    cin>>temp;
    bool a = false;
    a=false;
    while(!a){
        try{
            MyStoi::stoi(temp);
            if(temp=="1" || temp=="2" || temp=="3" || temp=="4"||temp=="5"||temp=="6"||temp=="7"||temp=="8" ) a=true;
            else{
                cout<<"Please enter a valid input between 1 and 8"<<endl;
                cin>>temp;
                a = false;
            }
            
        }
        catch(...){
            cout<<"Please enter a valid input between 1 and 8"<<endl;
            cin>>temp;
            a=false;
        }
    }
    Customer c;
    if(temp=="1"){
        c.see_all_available_cars_given_record(id,"customer");
        c.display_customer_lookup(id);
    }
    else if(temp=="2"){
        c.see_rented_cars(id,"customer");
        c.display_customer_lookup(id);
    }
    else if(temp=="3"){
        cout<<"Enter a car ID."<<endl;
        string carid;
        cin>>carid;
        c.rent_car(id,carid,"customer");
        c.display_customer_lookup(id);
    }
    else if(temp=="4"){
        cout<<"Enter a car ID."<<endl;
        string carid;
        cin>>carid;
        c.return_car(id,carid,"customer");
        c.display_customer_lookup(id);     
    }
    else if(temp=="5"){
        int temp;
        temp = c.calc_dues(id,"customer");
        cout<<"The fine owed by you is: "<<temp<<endl;
        c.display_customer_lookup(id); 
    }
    else if(temp=="6"){
        c.clear_fine_amount(id,"customer");
        c.display_customer_lookup(id);
    }
    else if(temp=="7"){
        cout<<"Enter the id of the car : \n";
        string uid;
        cin>>uid;
        content.clear();
        readfile("cars.csv");
        int count=0;
        for(auto &x:content){
            if(x[1]==uid && x[6]==id){
                cout<<"The due date of the car is: "<<formatDateFromSeconds(MyStoi::stoi(x[4])+30*86400)<<endl;
                count++;
                break;
            }
        }
        if(count==0) cout<<"You have not rented the car or the car does not exist. Please try again and provide valid details."<<endl;
        c.display_customer_lookup(id);
    }
    else if(temp=="8"){
        c.logout();
    }

}

void Employee :: display_employee_lookup(string id){
    divider();
    User u;
    string name = u.return_name(id,"employee");
    cout<<"Welcome "<<name<<" . "<<endl;
    cout<<"\nYou have been Succesfully logged in as an Employee\n";
    //void see_all_available_cars_given_record(string id);
    cout<<"Press 1 to see all the available cars for rent\n";
    //void see_rented_cars(string id);
    cout<<"Press 2 to view cars rented by you\n";
    //void rent_car(string id, string car_id,string type_user);
    cout<<"Press 3 to rent a car\n";
    //void return_car(string id,string car_id);
    cout<<"Press 4 to return a car\n";
    //int calc_dues(string id,string type_user);
    cout<<"Press 5 to view the fine\n";
    //void clear_fine_amount(string id,string type_user);
    cout<<"Press 6 to clear your fine\n";
    cout<<"Press 7 to show due date of rented car\n";
    cout<<"Press 8 to logout\n";
    divider();
    string temp;
    cin>>temp;
    bool a = false;
    a=false;
    while(!a){
        try{
            MyStoi::stoi(temp);
            if(temp=="1" || temp=="2" || temp=="3" || temp=="4"||temp=="5"||temp=="6"||temp=="7"||temp=="8") a=true;
            else{
                cout<<"Please enter a valid input between 1 and 8"<<endl;
                cin>>temp;
                a = false;
            }
            
        }
        catch(...){
            cout<<"Please enter a valid input between 1 and 8"<<endl;
            cin>>temp;
            a=false;
        }
    }
    Employee e;
    if(temp=="1"){
        e.see_all_available_cars_given_record(id,"employee");
        e.display_employee_lookup(id);
    }
    else if(temp=="2"){
        e.see_rented_cars(id,"employee");
        e.display_employee_lookup(id);
    }
    else if(temp=="3"){
        cout<<"Enter a car ID."<<endl;
        string carid;
        cin>>carid;
        e.rent_car(id,carid,"employee");
        e.display_employee_lookup(id);
    }
    else if(temp=="4"){
        cout<<"Enter a car ID."<<endl;
        string carid;
        cin>>carid;
        e.return_car(id,carid,"employee");
        e.display_employee_lookup(id);
    }
    else if(temp=="5"){
        int temp;
        temp = e.calc_dues(id,"employee");;
        cout<<"The fine owed by you is: "<<temp<<endl;
        e.display_employee_lookup(id);
    }
    else if(temp=="6"){
        e.clear_fine_amount(id,"employee");
        e.display_employee_lookup(id);
    }
    else if(temp=="7"){
        cout<<"Enter the id of the car : \n";
        string uid;
        cin>>uid;
        content.clear();
        readfile("cars.csv");
        int count=0;
        for(auto &x:content){
            if(x[1]==uid && x[6]==id){
                cout<<"The due date of the car is: "<<formatDateFromSeconds(MyStoi::stoi(x[4])+30*86400)<<endl;
                count++;
                break;
            }
        }
        if(count==0) cout<<"You have not rented the car or the car does not exist. Please try again and provide valid details."<<endl;
        e.display_employee_lookup(id);
    }
    else if(temp=="8"){
        e.logout();
    }

}

void Manager :: display_manager_lookup(string id){
    divider();
    User u_name;
    string name = u_name.return_name(id,"manager");
    cout<<"Welcome "<<name<<" . "<<endl;
    cout<<"You have been Succesfully logged in as a Manager\n";
    //add_user(id)
    cout<<"Press 1 to add a user\n";
    //update_user(id)
    cout<<"Press 2 to update a user\n";
    //delete_user(id)
    cout<<"Press 3 to delete a user\n";
    //add_car
    cout<<"Press 4 to add a car\n";
    //update_car
    cout<<"Press 5 to update a cars details\n";
    //delete_car
    cout<<"Press 6 to delete a car\n";
    //see_rented_by_user
    cout<<"Press 7 to see all cars issued to a particular user\n";
    //see_rented_cars_and_who_rented
    cout<<"Press 8 to see to whom each car is rented to\n";
    //see_all_users
    cout<<"Press 9 to view all users\n";
    //see_all_cars
    cout<<"Press 0 to view all cars\n";
    //Show due date of the car
    cout<<"Press d to show due date of a car\n";
    //logout()
    cout<<"Press l to logout\n";
    divider();
    char temp;
    bool validinput= false;
    while(!validinput){
        cin>>temp;
        //cin>>option;
        if ((temp>='0'&&temp<='9') || temp=='l'|| temp=='d' ) {
            validinput= true;
        } else {
            cout << "Invalid input. Please enter a valid input" <<endl;
        }
    }
    Manager m;
    User u;
    Car c;
    string isbn,uid;
    if(temp=='0'){
        m.see_all_cars();
        m.display_manager_lookup(id);
    }
    else if(temp=='1'){
        m.add_user();
        m.display_manager_lookup(id);
    }
    else if(temp=='2'){
        m.update_user();
        m.display_manager_lookup(id);
    }
    else if(temp=='3'){
        m.delete_user();
        m.display_manager_lookup(id);
    }
    else if(temp=='4'){
        m.add_car();
        m.display_manager_lookup(id);
    }
    else if(temp=='5'){
        m.update_car();
        m.display_manager_lookup(id);
    }
    else if(temp=='6'){
        m.delete_car();
        m.display_manager_lookup(id);
    }
    else if(temp=='7'){
        string uid;
        cout<<"Enter the id of the user : \n";
        cin>>uid;
        m.see_rented_by_user(id,uid);
        m.display_manager_lookup(id);
    }
    else if(temp=='8'){
        m.see_rented_cars_and_who_rented(id);
        m.display_manager_lookup(id);
    }
    else if(temp=='9'){
        m.see_all_users();
        m.display_manager_lookup(id);
    }
    else if(temp=='0'){
        m.see_all_cars();
        m.display_manager_lookup(id);
    }
    else if(temp=='d'){
        string uid;
        cout<<"Enter the id of the car : \n";
        cin>>uid;
        m.see_due_date_of_car(uid);
        m.display_manager_lookup(id);
    }
    else if(temp=='l'){
        logout();
        m.display_manager_lookup(id);
    }

}

string User::return_name(string id,string type_user){
    string name;
    if(type_user == "customer"){
        content.clear();
        readfile("customers.csv");
        for(auto &x:content){
            if(x[1]==id){
                name = x[0];
                break;
            }
        }
    }
    else if(type_user == "manager" || type_user == "employee"){
        content.clear();
        readfile("employee.csv");
        for(auto &x:content){
            if(x[1]==id){
                name = x[0];
                break;
            }
        }
    }
    return name;
}

void User::logout(){
    cout<<"Logging out of the Rental system...\n";
    User u;
    u.display_menu();
}

void User::see_all_available_cars_given_record(string id, string type_user){
    int record=0;
    content.clear();
    if(type_user == "customer"){
        readfile("customers.csv");
        for(auto &x:content){
            if(x[1]==id){
                record = MyStoi::stoi(x[3]);
                break;
            }
        }
    }
    else if(type_user == "employee"){
        readfile("employee.csv");
        for(auto &x:content){
            if(x[1]==id){
                record = MyStoi::stoi(x[4]);
                break;
            }
        }
    }
    content.clear();
    readfile("cars.csv");
    cout<<"Condition 0 implies brand new while 5 implies very damaged on the scale used."<<endl;
    int count=0;
    for(auto &x:content){
        if(MyStoi::stoi(x[7])<=record && x[3]=="0"){
            cout<<"Model: "<<x[0]<<" ID: "<<x[1]<<" Condition: "<<x[2]<<endl;
            count++;
        }
    }
    if(count==0) cout<<"No cars available to rent"<<endl;
}

void User::see_rented_cars(string id,string type_user){
    content.clear();
    readfile("cars.csv");
    int count=0;
    for(auto &x:content){
        if(x[5]==type_user && x[6]==id){
            string temp=formatDateFromSeconds(MyStoi::stoi(x[4]));
            cout<<"Model: "<<x[0]<<" ID: "<<x[1]<<" Condition: "<<x[2]<<" Issued on: "<<temp<<endl;
            count++;
        }
    }
    if(count==0) cout<<"You have not rented any car"<<endl;
}

void User::rent_car(string id,string car_id,string type_user){
    content.clear();
    readfile("cars.csv");
    int count=0;
    for(auto &x:content){
        if(x[6]==id){
            count++;
        }
    }
    if(count>=3) cout<<"You can only rent 3 cars at once"<<endl;
    else{
        int record=0;
        content.clear();
        if(type_user == "customer"){
            readfile("customers.csv");
            for(auto &x:content){
                if(x[1]==id){
                    record = MyStoi::stoi(x[3]);
                    break;
                }
            }
        }
        else if(type_user == "employee"){
            readfile("employee.csv");
            for(auto &x:content){
                if(x[1]==id){
                    record = MyStoi::stoi(x[4]);
                    break;
                }
            }
        }
        int count=0;
        content.clear();
        readfile("cars.csv");
        for(auto &x:content){
            if(x[1]==car_id && x[3]=="0" && MyStoi::stoi(x[7])<=record){
                x[3] = "1";
                x[4] = to_string(time(0));
                x[5] = type_user;
                x[6] = id;
                cout<<"Car Succesfully rented"<<endl;
                count++;
            }
        }
        if(count==0) cout<<"You cannot rent this car or the car does not exist. Please try again and provide valid details."<<endl;
        clearfile("cars.csv");
        writefile(content,"cars.csv");
        content.clear();
    }
}

void User:: return_car(string id,string car_id,string type_user){
    int count=0;
    content.clear();
    readfile("cars.csv");
    for(auto &x:content){
        if(x[1]==car_id && x[6]==id){
            count++;
        }
    }
    if(count==0){
        cout<<"You have not rented the following car or the car does not exist. Please try again and provide valid details."<<endl;
        return;    
    }
    cout<<"You can now return a car. Please enter the condition of the car which is returned on a scale of 0-5 where 0 implies that it is returned in a good condition and 5 implying its severely damaged. You can't lie this is going to be manually checked by the manager XD"<<endl;
    string temp;
    cin>>temp;
    bool a = false;
    a=false;
    while(!a){
        try{
            MyStoi::stoi(temp);
            if(temp>="0" && temp<="5") a=true;
            else{
                cout<<"Please enter a valid input between 0 and 5"<<endl;
                cin>>temp;
                a = false;
            }
            
        }
        catch(...){
            cout<<"Please enter a valid input between 0 and 5"<<endl;
            cin>>temp;
            a=false;
        }
    }
    content.clear();
    readfile("cars.csv");
    int base_rent=0;
    int issued_date=0;
    for(auto &x:content){
        if(x[1]==car_id){
            x[2] = temp;
            x[3] = "0";
            issued_date = MyStoi::stoi(x[4]);
            x[4] = "nil";
            x[5] = "nil";
            x[6] = "nil";
            int isstime = issued_date;
            int fine=0;
            int curtime = time(0);
            if((curtime-isstime)/86400>30) fine+=50*((curtime-isstime)/86400 - 30);
            x[7] = to_string(MyStoi::stoi(x[7])-3*stoi(temp)-(fine/40));
            base_rent = MyStoi::stoi(x[8]);
            count++;
        }
    }
    clearfile("cars.csv");
    writefile(content,"cars.csv");
    content.clear();
    if(type_user == "customer"){
        readfile("customers.csv");
        for(auto &x:content){
            if(x[1]==id){
                int curtime = time(0);
                int isstime = issued_date;
                int fine=0;
                if((curtime-isstime)/86400>30) fine+=50*((curtime-isstime)/86400 - 30);
                x[3] = to_string(MyStoi::stoi(x[3])-5*stoi(temp)-fine/25);
                x[4] = to_string(MyStoi::stoi(x[4])+base_rent+fine);
            }
        }
        writefile(content,"customers.csv");
        content.clear();
    }
    if(type_user == "employee"){
        readfile("employee.csv");
        for(auto &x:content){
            if(x[1]==id){
                x[4] = to_string(MyStoi::stoi(x[4])-5*stoi(temp));
                int curtime = time(0);
                int isstime = issued_date;
                int fine=0;
                if((curtime-isstime)/86400>30) fine+=40*((curtime-isstime)/86400 - 30);
                x[5] = to_string(MyStoi::stoi(x[5])+base_rent+fine);
            }
        }
        writefile(content,"employee.csv");
        content.clear();
    }
    cout<<"Car returned Succesfully"<<endl;

}

int User::calc_dues(string id,string type_user){
    content.clear();
    int dues=0;
    if(type_user == "customer"){
        readfile("customers.csv");
        for(auto &x:content){
            if(x[1]==id){
                dues = MyStoi::stoi(x[4]);
                break;
            }
        }
    }
    else if(type_user == "employee"){
        content.clear();
        readfile("employee.csv");
        for(auto &x:content){
            if(x[1]==id){
                dues = MyStoi::stoi(x[5]);
                break;
            }
        }
    }
    content.clear();

    return dues;
}

void User:: clear_fine_amount(string id,string type_user){
    content.clear();
    cout<<"Clearing dues..."<<endl;
    if(type_user == "customer"){
        readfile("customers.csv");
        for(auto &x:content){
            if(x[1]==id){
                x[4] ="0";
                break;
            }
        }
        clearfile("customers.csv");
        writefile(content,"customers.csv");
    }
    else if(type_user == "employee"){
        content.clear();
        readfile("employee.csv");
        for(auto &x:content){
            if(x[1]==id){
                x[5] ="0";
                break;
            }
        }
        clearfile("employee.csv");
        writefile(content,"employee.csv");
    }
}

void Customer :: sign_up(){
    cout<<"Welcome new user\n"<<"Please enter your Name"<<endl;
    vector<string> temp;
    string word;
    User u;
    bool is_already_used = true;
    cin>>u.name;
    temp.push_back(u.name);
    cout<<"Enter the your id"<<endl;
    cin>>u.id;
    is_already_used = check(u.id);
    readfile("customers.csv");
    while(is_already_used){
        cout<<"This ID is used, please enter another id"<<endl;
        cin>>u.id;
        is_already_used = check(u.id);
        readfile("customers.csv");
    }
    temp.push_back(u.id);
    cout<<"Enter the password"<<endl;
    cin>>word;
    temp.push_back(word);
    temp.push_back("50");
    temp.push_back("0");
    content.clear();
    readfile("customers.csv");
    content.push_back(temp);
    clearfile("customers.csv");
    writefile(content,"customers.csv");
    cout<<"Your account has been created succesfully."<<endl;

}

void Manager:: see_all_users(){
    content.clear();
    readfile("customers.csv");
    for(auto &x:content){
        cout<<"User Name: "<<x[0]<<" User ID: "<<x[1]<<" User Role: Customer"<<" User Record: "<<x[3]<<" Fine Due: "<<x[4]<<endl;
    }
    content.clear();
    readfile("employee.csv");
    for(auto &x:content){
        cout<<"User Name: "<<x[0]<<" User ID: "<<x[1]<<" User Role: "<<x[3]<<" User Record: "<<x[4]<<" Fine Due: "<<x[5]<<endl;
    }
    content.clear();
}

void Manager:: see_all_cars(){
    content.clear();
    readfile("cars.csv");
    for(auto &x:content){
        cout<<"Car model: "<<x[0]<<" Car ID: "<<x[1]<<" Car Condition: "<<x[2]<<" Car Availability: "<<x[3]<<endl;
    }
}

void Manager::add_user(){
    cout<<"Select 1 if the user is a customer, 2 if the user is an employee and 3 if the user is a manager"<<endl;
    string temp1;
    bool validinput= false;
    bool a = false;
    while(!a){
        cin>>temp1;
        //cin>>option;
        if (temp1=="1" || temp1=="2" || temp1=="3") {
            a= true;
        } else {
            cout << "Invalid input. Please enter a valid input" <<endl;
        }
    }
    if(temp1=="3" || temp1=="2"){
        vector<string> temp;
        string word;
        User u;
        cout<<"Enter the users name"<<endl;
        cin>>u.name;
        temp.push_back(u.name);
        cout<<"Enter the your id"<<endl;
        cin>>u.id;
        bool is_already_used = check(u.id);
        readfile("employee.csv");
        while(is_already_used){
            cout<<"This ID is used, please enter another id"<<endl;
            cin>>u.id;
            is_already_used = check(u.id);
            readfile("employee.csv");

        }
        temp.push_back(u.id);
        cout<<"Enter the users password"<<endl;
        cin>>word;
        temp.push_back(word);
        if(temp1=="2") temp.push_back("employee");
        if(temp1=="3") temp.push_back("manager");
        temp.push_back("50");
        temp.push_back("0");
        content.clear();
        readfile("employee.csv");
        content.push_back(temp);
        clearfile("employee.csv");
        writefile(content,"employee.csv");
        cout<<"User added succesfully"<<endl;
    }
    if(temp1=="1"){
        vector<string> temp;
        string word;
        User u;
        cout<<"Enter the users name"<<endl;
        cin>>u.name;
        temp.push_back(u.name);
        cout<<"Enter the users id"<<endl;
        cin>>u.id;
        bool is_already_used = check(u.id);
        readfile("customers.csv");
        while(is_already_used){
            cout<<"This ID is used, please enter another id"<<endl;
            cin>>u.id;
            is_already_used = check(u.id);
            readfile("customers.csv");
        }
        temp.push_back(u.id);
        cout<<"Enter the users password"<<endl;
        cin>>word;
        temp.push_back(word);
        temp.push_back("50");
        temp.push_back("0");
        content.clear();
        readfile("customers.csv");
        content.push_back(temp);
        clearfile("customers.csv");
        writefile(content,"customers.csv");
        cout<<"User added succesfully"<<endl;
    }
}

void Manager::update_user(){
    cout<<"Select 1 if the user is a customer, 2 if the user is an employee and 3 if the user is a manager"<<endl;
    string temp1;
    bool validinput= false;
    bool a = false;
    while(!a){
        cin>>temp1;
        //cin>>option;
        if (temp1=="1" || temp1=="2" || temp1=="3") {
            a= true;
        } else {
            cout << "Invalid input. Please enter a valid input" <<endl;
        }
    }
    if(temp1=="1"){
        cout<<"Enter id of customer to be updated"<<endl;
        string id;
        cin>>id;
        int count=0;
        content.clear();
        readfile("customers.csv");
        for(auto &x:content){
            if(x[1]==id){
                count++;
            }
        }
        if(count==0){
            cout<<"This customer does not exist."<<endl;
            return;    
        }
        content.clear();
        readfile("customers.csv");
        for(auto &x:content){
            if(x[1]==id){
                cout<<"Select 1 to update customer name, 2 to update customer id, 3 to update customer password, 4 to update customer record, 5 to update customer fine due"<<endl;
                int temp1;
                bool validinput= false;
                while(!validinput){
                    cin>>temp1;
                    //cin>>option;
                    if (temp1>=1 && temp1<=5) {
                        validinput= true;
                    } else {
                        cout << "Invalid input. Please enter a valid input" <<endl;
                    }
                }
                cout<<"Enter updated detail"<<endl;
                string update;
                cin>>update;
                bool is_already_used1 = check(update);
                readfile("customers.csv");
                bool c,d,e;
                switch(temp1){
                    case 1:
                        x[0] = update;
                        break;
                    case 2:
                        while(is_already_used1){
                            cout<<"This ID is used, please enter another id"<<endl;
                            cin>>update;
                            is_already_used1 = check(update);
                            readfile("customers.csv");
                        }
                        x[1]=update;
                        break;
                    case 3:
                        x[2]=update;
                        break;
                    case 4:
                        //Write code to check if update is an integer else ask for input again
                        c = false;
                        while(!c){
                            try{
                                MyStoi::stoi(update);
                                c = true;
                            }
                            catch(...){
                                cout<<"Please enter a valid input"<<endl;
                                cin>>update;
                            }
                        }
                        x[3]=update;
                        break;
                    case 5:
                        //Write code to check if update is a positive integer else ask for input again
                        d = false;
                        while(!d){
                            try{
                                MyStoi::stoi(update);
                                if(MyStoi::stoi(update)>=0) d = true;
                                else{
                                    cout<<"Please enter a valid input"<<endl;
                                    cin>>update;
                                }
                            }
                            catch(...){
                                cout<<"Please enter a valid input"<<endl;
                                cin>>update;
                            }
                        }
                        x[4]=update;
                        break;
                }
            }
        }
        clearfile("customers.csv");
        writefile(content,"customers.csv");
        cout<<"Update Succesful for customer"<<endl;
    }
    else if(temp1=="2" || temp1=="3"){
        cout<<"Enter id of user to be updated"<<endl;
        int count=0;
        content.clear();
        string id;
        cin>>id;
        readfile("employee.csv");
        for(auto &x:content){
            if(x[1]==id){
                count++;
            }
        }
        if(count==0){
            cout<<"This user does not exist."<<endl;
            return;    
        }
        content.clear();
        readfile("employee.csv");
        for(auto &x:content){
            if(x[1]==id){
                cout<<"Select 1 to update user name, 2 to update user id, 3 to update user password, 4 to update who user is, 5 to update user record, 6 to update users fine due"<<endl;
                int temp1;
                bool validinput= false;
                while(!validinput){
                    cin>>temp1;
                    //cin>>option;
                    if (temp1>=1 && temp1<=5) {
                        validinput= true;
                    } else {
                        cout << "Invalid input. Please enter a valid input" <<endl;
                    }
                }
                cout<<"Enter updated detail"<<endl;
                string s;
                cin>>s;
                bool is_already_used2;
                bool c,d,e;
                switch(temp1){
                    case 1:
                        x[0] = s;
                        break;
                    case 2:
                        is_already_used2 = check(s);
                        readfile("employee.csv");
                        while(is_already_used2){
                            cout<<"This ID is used, please enter another id"<<endl;
                            cin>>s;
                            is_already_used2 = check(s);
                            readfile("employee.csv");
                        }
                        x[1]=s;
                        break;
                    case 3:
                        x[2]=s;
                        break;
                    case 4:
                        //Write code to check if s is either employee or manager else ask for input again
                        e = false;
                        while(!e){
                            try{
                                //
                                if(s == "employee" || s == "manager") {
                                    e = true;
                                }
                                else{
                                    cout << "Please enter a valid input" << endl;
                                    cin >> s;
                                }
                            }
                            catch(...){
                                cout << "Please enter a valid input" << endl;
                                cin >> s;
                            }
                        }
                        x[3]=s;
                        break;
                    case 5:
                        c = false;
                        while(!c){
                            try{
                                MyStoi::stoi(s);
                                c = true;
                            }
                            catch(...){
                                cout<<"Please enter a valid input"<<endl;
                                cin>>s;
                            }
                        }
                        x[4]=s;
                        break;
                    case 6:
                        d = false;
                        while(!d){
                            try{
                                MyStoi::stoi(s);
                                if(MyStoi::stoi(s)>=0) d = true;
                                else{
                                    cout<<"Please enter a valid input"<<endl;
                                    cin>>s;
                                }
                            }
                            catch(...){
                                cout<<"Please enter a valid input"<<endl;
                                cin>>s;
                            }
                        }
                        x[5]=s;
                        break;
                }
            }
        }
        clearfile("employee.csv");
        writefile(content,"employee.csv");
        cout<<"Update Succesful for User"<<endl;
    }
}

void Manager::delete_user(){
    cout<<"Select 1 if the user is a customer, 2 if the user is an employee and 3 if the user is a manager"<<endl;
    string temp1;
    bool validinput= false;
    bool a = false;
    while(!a){
        cin>>temp1;
        //cin>>option;
        if (temp1=="1" || temp1=="2" || temp1=="3") {
            a= true;
        } else {
            cout << "Invalid input. Please enter a valid input" <<endl;
        }
    }
    if(temp1=="1"){
        cout<<"Enter id of customer to be removed"<<endl;
        string id;
        cin>>id;
        int count1=0;
        content.clear();
        readfile("customers.csv");
        for(auto &x:content){
            if(x[1]==id){
                count1++;
            }
        }
        if(count1==0){
            cout<<"This customer does not exist."<<endl;
            return;    
        }
        content.clear();
        readfile("customers.csv");
        for(auto &x:content){
            if(x[1]==id){
                content.erase(remove(content.begin(), content.end(), x), content.end());
                break;
            }
        }
        clearfile("customers.csv");
        writefile(content,"customers.csv");
    }
    else if(temp1=="3" || temp1=="2"){
        cout<<"Enter id of user to be removed"<<endl;
        string id;
        cin>>id;
        int count=0;
        content.clear();
        readfile("employee.csv");
        for(auto &x:content){
            if(x[1]==id){
                count++;
            }
        }
        if(count==0){
            cout<<"This user does not exist."<<endl;
            return;    
        }
        content.clear();
        readfile("employee.csv");
        for(auto &x:content){
            if(x[1]==id){
                content.erase(remove(content.begin(), content.end(), x), content.end());
                break;
            }
        }
        clearfile("employee.csv");
        writefile(content,"employee.csv");
    }
}

void Manager::add_car(){
    vector<string> temp;
    string word;
    Car u;
    cout<<"Enter the cars model"<<endl;
    cin>>u.model;
    temp.push_back(u.model);
    cout<<"Enter the cars id"<<endl;
    cin>>u.id;
    bool is_already_used2 = check_car(u.id);
    while(is_already_used2){
        cout<<"This ID is used, please enter another id"<<endl;
        cin>>u.id;
        is_already_used2 = check_car(u.id);
    }
    temp.push_back(u.id);
    cout<<"Enter the cars condition"<<endl;
    cin>>u.condition;
    //Write code to check if input is an integer between 0 and 5 else ask for input again
    bool b = false;
    while(!b){
        try{
            MyStoi::stoi(u.condition);
            if(MyStoi::stoi(u.condition)<0 || MyStoi::stoi(u.condition)>5){
            cout<<"Please enter a valid input"<<endl;
            cin>>u.condition;
            b=false;
            }
            else b=true;
        }
        catch(exception e){
            cout<<"Please enter a valid input"<<endl;
            cin>>u.condition;
        }
    }
    temp.push_back(u.condition);
    temp.push_back("0");
    temp.push_back("nil");
    temp.push_back("nil");
    temp.push_back("nil");
    cout<<"Enter the minimum record to rent"<<endl;
    string temporary;
    cin>>temporary;
    bool a=false;
    while(!a){
        //Write code to check if input temporary can be converted to an integer using MyStoi::stoi else ask for input again
        try{
            MyStoi::stoi(temporary);
            a=true;
        }
        catch(exception e){
            cout<<"Please enter a valid input"<<endl;
            cin>>temporary;
        }
    }
    temp.push_back(temporary);
    cout<<"Enter the base rent price of the car"<<endl;
    cin>>temporary;
    a=false;
    while(!a){
        try{
            MyStoi::stoi(temporary);
            a=true;
        }
        catch(exception e){
            cout<<"Please enter a valid input"<<endl;
            cin>>temporary;
        }
    }
    temp.push_back(temporary);
    content.clear();
    readfile("cars.csv");
    content.push_back(temp);
    clearfile("cars.csv");
    writefile(content,"cars.csv");
}

void Manager::delete_car(){
    cout<<"Enter id of car to be removed"<<endl;
    string id;
    cin>>id;
    content.clear();
    int count=0;
    readfile("cars.csv");
    for(auto &x:content){
        if(x[1]==id){
            count++;
        }
    }
    if(count==0){
        cout<<"This car does not exist."<<endl;
        return;    
    }
    content.clear();
    readfile("cars.csv");
    for(auto &x:content){
        if(x[1]==id){
            content.erase(remove(content.begin(), content.end(), x), content.end());
            break;
        }
    }
    clearfile("cars.csv");
    writefile(content,"cars.csv");
}

void Manager::update_car(){
    cout<<"Enter id of car to be updated"<<endl;
    string id;
    cin>>id;
    content.clear();
    int count=0;
    readfile("cars.csv");
    for(auto &x:content){
        if(x[1]==id){
            count++;
        }
    }
    if(count==0){
        cout<<"This car does not exist."<<endl;
        return;    
    }
    content.clear();
    readfile("cars.csv");
    for(auto &x:content){
        if(x[1]==id){
            cout<<"Select 1 to update car model, 2 to update car id, 3 to update car condition, 4 to update date of rent of car, 5 to update who issued,6 to update id of issuer, 7 to update minimum record for rent and 8 to update the base price."<<endl;
            int temp1;
            bool validinput= false;
            while(!validinput){
                cin>>temp1;
                if (temp1>=1 && temp1<=9) {
                    validinput= true;
                } else {
                    cout << "Invalid input. Please enter a valid input" <<endl;
                }
            }
            cout<<"Enter updated detail"<<endl;
            string s;
            cin>>s;
            bool is_already_used2;
            bool a,b,e;
            bool isValidId;
            switch(temp1){
                case 1:
                    x[0] = s;
                    break;
                case 2:
                    is_already_used2 = check_car(s);
                    while(is_already_used2){
                        cout<<"This ID is used, please enter another id"<<endl;
                        cin>>s;
                        is_already_used2 = check_car(s);
                    }
                    x[1]=s;
                    break;
                case 3:
                    b = false;
                    while(!b){
                        try{
                            MyStoi::stoi(s);
                            if(MyStoi::stoi(s)<0 || MyStoi::stoi(s)>5){
                            cout<<"Please enter a valid input between 0 and 5"<<endl;
                            cin>>s;
                            b=false;
                            }
                            else b=true;
                        }
                        catch(exception e){
                            cout<<"Please enter a valid input between 0 and 5"<<endl;
                            cin>>s;
                        }
                    }
                    x[2]=s;
                    break;
                case 4:
                    //Thoda hard, have to look into data wala bs
                    x[4]=s;
                    break;
                case 5:
                    e = false;
                    while(!e){
                        try{
                            transform(s.begin(), s.end(), s.begin(),[](unsigned char c){ return tolower(c); });
                            if(s == "employee" || s == "manager" || s== "customer") {
                                e = true;
                            }
                            else{
                                cout << "Please enter a valid input" << endl;
                                cin >> s;
                            }
                        }
                        catch(...){
                            cout << "Please enter a valid input" << endl;
                            cin >> s;
                        }
                    }
                    x[5]=s;
                    break;
                case 6:
                    isValidId = check(s);
                    if (isValidId) {
                        x[6]=s;
                    } else {
                        cout << "Please enter a valid input who is a user prior." << endl;
                        cin >> s;
                    }
                    break;
                case 7:
                    a=false;
                    while(!a){
                        try{
                            MyStoi::stoi(s);
                            a=true;
                        }
                        catch(exception e){
                            cout<<"Please enter a valid input"<<endl;
                            cin>>s;
                        }
                    }
                    x[7]=s;
                    break;
                case 8:
                    a=false;
                    while(!a){
                        //Write code to check if input temporary can be converted to an integer using MyStoi::stoi else ask for input again
                        try{
                            MyStoi::stoi(s);
                            a=true;
                        }
                        catch(exception e){
                            cout<<"Please enter a valid input"<<endl;
                            cin>>s;
                        }
                    }
                    x[8]=s;
                    break;
            }
        }
    }
    clearfile("cars.csv");
    writefile(content,"cars.csv");
}

void Manager:: see_rented_by_user(string id,string uid){
    int count=0;
    content.clear();
    readfile("cars.csv");
    for(auto &x:content){
        if(x[6]==uid){
            string temp=formatDateFromSeconds(MyStoi::stoi(x[4]));
            cout<<"Model: "<<x[0]<<" ID: "<<x[1]<<" Condition: "<<x[2]<<" Issued on: "<<temp<<" Rented by ID no.: "<<x[6]<<endl;
        }
    }
    if(count==0) cout<<"No cars have been rented by any user"<<endl;
    content.clear();
}

void Manager:: see_rented_cars_and_who_rented(string id){
    content.clear();
    readfile("cars.csv");
    int count=0;
    for(auto &x:content){
        if(x[3]=="1"){
            string temp=formatDateFromSeconds(MyStoi::stoi(x[4]));
            cout<<"Model: "<<x[0]<<" ID: "<<x[1]<<" Condition: "<<x[2]<<" Issued on: "<<temp<<" Rented by ID no.: "<<x[6]<<endl;
            count++;
        }
    }
    content.clear();
    if(count==0) cout<<"No cars have been rented by this user"<<endl;
}

void Manager::see_due_date_of_car(string id){
    content.clear();
    string s=id;
    bool is_already_used = check_car(id);
    while(!is_already_used){
        cout<<"This Car does not exist. Please enter a valid ID"<<endl;
        cin>>s;
        is_already_used = check_car(s);
    }
    content.clear();
    readfile("cars.csv");
    int count=0;
    for(auto &x:content){
        if(x[1]==s && x[3]=="1"){
            string due_date;
            due_date = formatDateFromSeconds(MyStoi::stoi(x[4]) + 30*86400);
            cout<<"The due date is: "<<due_date<<endl;
            count++;
        }
    }
    if(count==0) cout<<"This car is not currently rented"<<endl;
}
int main(){
    User temp;
    temp.display_menu();
    return 0;
}
