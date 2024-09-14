#include <iostream>
#include <string>
#include <fstream> // for file I/O
#include <cstdlib> // for rand() and srand() & system(cls) - to clear screen
#include <ctime> // for time()
using namespace std;

class Bank{
private:
    string password;
    double balance;
public:
    string name;
    int accNo;
    string type;

    // Display Account Details
    void display(){
        cout<<endl;
        cout<<"Name : "<<name<<endl;
        cout<<"Account No. : "<<accNo<<endl;
        cout<<"Type : "<<type<<endl;
    }

    // Display Remaining Balance
    void checkBalance(){
        cout<<"\nBalance : "<<balance<<" Rs"<<endl;
    }

    // Deposit Money
    void deposit(double bal){
        this->balance = this->balance + bal;
        ofstream updateBalance("bankaccountbalance.txt",ios::trunc);
        updateBalance<<balance;
        updateBalance.close();
        cout<<"Successfully Deposited "<<bal<<" Rs"<<endl;
    }

    // Withdraw Money
    void withdraw(double bal){
        if(bal > this->balance){
            cout<<"Abe Bhikari Itna Paisa Tera Baap Chhod Kar Gaya Tha Ya Teri Maa....... \nAhem I Mean Insufficient Balance!"<<endl;
            return;
        }
        this->balance = this->balance - bal;

        ofstream updateBal("bankaccountbalance.txt",ios::trunc);
        updateBal<<balance;
        updateBal.close();
        cout<<"Successfully Withdrew "<<bal<<" Rs"<<endl;
    }

    // Password Setter
    void setPass(string pass){
        password = pass;
    }

    // Password Getter
    string getPass(){
        return password;
    }

    // Login to Authenticate User
    bool login(){
        string actualPass,userPass,stringAcc,stringBal;
        ifstream read("bankaccountinfo.txt");
        getline(read,name);
        getline(read,type);
        getline(read,actualPass);
        setPass(actualPass);
        getline(read,stringAcc);
        accNo = stoi(stringAcc);
        read.close();

        ifstream readBalance("bankaccountbalance.txt");
        getline(readBalance,stringBal);
        balance = stoi(stringBal);
        readBalance.close();

        cout<<"Hello "<<name<<endl;
        cout<<"Enter Password To Login : ";
        getline(cin,userPass);

        if(userPass == actualPass) {
            cout<<"Logged in successfully.";
            return true;
        } else {
            cout<<"Incorrect Password. I Guess You Are Just A Brainless Thief!";
            return false;
        }
    }

    // Create Account for New User
    void create(){
        srand(time(0));
        cout<<"Creating Account ..."<<endl;
        ofstream write("bankaccountinfo.txt");
        cout<<"Enter Name : ";
        getline(cin,name);
        write<<name;
        write<<"\n";
        cout<<endl;

        int response_accType;
        cout<<"_ACCOUNT TYPES_\n";
        cout<<" 1. Saving\n";
        cout<<" 2. Current\n";
        cout<<"Choose Your Account Type : ";
        cin>>response_accType;

        switch(response_accType) {
            case 1 :
                type = "Saving";
                break;
            case 2 :
                type = "Current";
                break;
            default :
                cout<<"Invalid Choice! Setting Type to Saving."<<endl;
                type = "Saving";
                break;
        }
        write<<type;
        write<<"\n";
        cout<<endl;

        string response_pass;
        cin.ignore();
        cout<<"Set Password : ";
        getline(cin,response_pass);
        setPass(response_pass);
        write<<getPass();
        write<<"\n";

        accNo = rand() % 69420999 + 69420000;
        write<<accNo;
        write<<"\n";

    write.close();

        balance = rand() % 99999 + 9999;
        ofstream updateBalance("bankaccountbalance.txt",ios::app);
        updateBalance<<balance<<endl;
        updateBalance.close();
    }

    double getBal(){
        return balance;
    }

};

// Check if user already have an account or not
bool checkFile(const string& filename){
    ifstream file(filename);
    return file.is_open();
}

int main() {

    Bank acc;
    string filename = "bankaccountinfo.txt";
    int access;

    // Log In
    if(checkFile(filename)) {
        access = acc.login();
    }
    else { // Account Create
        acc.create();
        system("cls");
        cout<<endl<<"Congratulation You Got "<<acc.getBal()<<" Rs As Your Joining Bonus!"<<endl<<endl;
        access = acc.login();
    }

    if(access == 1){
        int menu;
        double amount = 0;
        char again = 'n';
        do{
            cout<<"\n\n_ACCESS MENU_"<<endl;
            cout<<" 1. Check Balance"<<endl;
            cout<<" 2. Withdraw Money"<<endl;
            cout<<" 3. Deposit Money"<<endl;
            cout<<" 4. Display Info"<<endl;
            cout<<"Choose : ";
            cin>>menu;

            switch (menu)
            {
            case 1 :
                acc.checkBalance();
                break;
            
            case 2 :
                cout<<endl<<"Enter Amount : ";
                cin>>amount;
                acc.withdraw(amount);
                break;

            case 3 :
                cout<<endl<<"Enter Amount : ";
                cin>>amount;
                acc.deposit(amount);
                break;

            case 4 :
                acc.display();
                break;

            default:
                cout<<"\nInvalid Option.\nAndha Hai Kya? Options Theek Se Enter Na Kari Ja Rahi Terese."<<endl;
                break;
            }

            cout<<"Do You Want To Continue? (y/n) : ";
            cin>>again;

            if(again == 'n'){
                cout<<"\nThanks for using the program!\n";
                cout<<"\nProgrammed By Dibya.\n";
            }
        } while (again == 'y');
    }
}