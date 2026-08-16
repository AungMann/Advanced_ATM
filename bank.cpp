#include <iostream>
#include <string>
#include <ctime>
#include <conio.h>
#include <fstream>
#include <limits>
#include <iomanip>

using namespace std;

class ATM
{
private:
    unsigned long long int balance = 0;
    double amount;
    char ch;
    string email;
    string password;
    string name, pass, ph, Email;
    unsigned long long int bal = 0;
    unsigned long long int Bal = 0;

    // Helper Functions
    int balance_fun();
    int withdraw_fun();
    void deposit_fun();
    void userLogin();
    void addnewuser();
    void transfer_fun();
    void showTransactions();
    void deleteUser();
    void already_user();
    bool get_otp();

public:
    // Constructor to initialize balance

    void Menu();
    void AtmManagement();
    void BankManagement();
};

void ATM::Menu()
{
    int choice;

    while (true)
    {
        system("cls");
        cout << "\n\n";
        cout << "\t\t\t\t\t\t\t+---------------------------------------------+" << endl;
        cout << "\t\t\t\t\t\t\t|                                             |" << endl;
        cout << "\t\t\t\t\t\t\t|            Welcome to our ATM               |" << endl;
        cout << "\t\t\t\t\t\t\t|             Banking System                  |" << endl;
        cout << "\t\t\t\t\t\t\t|                                             |" << endl;
        cout << "\t\t\t\t\t\t\t+---------------------------------------------+" << endl;
        cout << "\n\n";
        cout << "\n========================================\n";
        cout << "            MAIN MENU                  \n";
        cout << "========================================\n";
        cout << "1. ATM MANAGEMENT SYSTEM\n";
        cout << "2. BANK MANAGEMENT SYSTEM\n";
        cout << "3. Exit From ATM\n";
        cout << "========================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            AtmManagement();
            break;
        case 2:
            BankManagement();
            break;
        case 3:
            cout << "Thanks for using the ATM. Goodbye!" << endl;
            return;
        default:
            cout << "INVALID NUMBER! Please try again." << endl;
            break;
        }
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }
}

bool check = true;
bool userExists = false;

void ATM::AtmManagement()
{

    int choice;
    while (true)
    {
        system("cls");
        cout << "\n========================================\n";
        cout << "        ATM MANAGEMENT SYSTEM          \n";
        cout << "========================================\n";
        cout << "\t1: User Login\n";
        cout << "\t2: Check your balance\n";
        cout << "\t3: Withdraw money\n";
        cout << "\t4: Exit to Main Menu\n";
        cout << "========================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            userLogin();
            check =false;
            break;
        case 2:
            balance_fun();
            break;
        case 3:
            withdraw_fun();
            break;
        case 4:
            return;
        default:
            cout << "INVALID NUMBER! Please try again." << endl;
            break;
        }
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }
}

void ATM::BankManagement()
{
    int choice;
    while (true)
    {
        system("cls");
        cout << "\n========================================\n";
        cout << "       BANK MANAGEMENT SYSTEM          \n";
        cout << "========================================\n";
        cout << "\t1: New User\n";
        cout << "\t2: Already user\n";
        cout << "\t3: Deposit money\n";
        cout << "\t4: Transfer money\n";
        cout << "\t5: Show transaction history\n";
        cout << "\t6: Delete user record\n";
        cout << "\t7: Go Back\n";
        cout << "========================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addnewuser();
            break;
        case 2:
            already_user();
            break;
        case 3:
            deposit_fun();
            break;
        case 4:
            transfer_fun();
            break;
        case 5:
            showTransactions();
            break;
        case 6:
            deleteUser();
            break;
        case 7:
            return;
        default:
            cout << "INVALID NUMBER! Please try again." << endl;
            break;
        }
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }
}

void ATM::deleteUser()
{
    fstream file, tempFile;
    string usernameToDelete;
    bool userFound = false;

    system("cls");
    cout << "\n========================================\n";
    cout << "           DELETE USER RECORD           \n";
    cout << "========================================\n";
    cout << "Enter the Username to Delete: ";
    cin.ignore();
    getline(cin, usernameToDelete);

    file.open("bank.txt", ios::in);
    tempFile.open("temp.txt", ios::out);

    if (!file || !tempFile) {
        cerr << "Error accessing bank records." << endl;
    } else {
        string n, fn, pa, p;
        double b;

        while (file >> n >> fn >> pa >> p >> b) {
            if (n != usernameToDelete) {
                tempFile << n << " " << fn << " " << pa << " " << p << " " << b << endl;
            } else {
                userFound = true;
            }
        }

        file.close();
        tempFile.close();

        remove("bank.txt");
        rename("temp.txt", "bank.txt");

        if (userFound) {
            cout << "\nUser '" << usernameToDelete << "' has been successfully deleted." << endl;
            balance =0;
        } else {
            cout << "\nUser not found. Deletion failed." << endl;
        }
    }

}

void ATM::showTransactions()
{
    system("cls");
    fstream transactionFile("transactions.txt", ios::in);
    string line;

    cout << "\n========================================\n";
    cout << "           TRANSACTION HISTORY          \n";
    cout << "========================================\n";

    if (!transactionFile) {
        cout << "No transactions found." << endl;
    } else {
        cout << "Recent Transactions:\n" << endl;
        while (getline(transactionFile, line)) {
            cout << line << endl;
        }
        transactionFile.close();
    }

}

void ATM::transfer_fun()
{
    fstream file, tempFile;
    string recipientName;
    bool recipientFound = false;

    system("cls");
    cout << "\n========================================\n";
    cout << "           TRANSFER MONEY               \n";
    cout << "========================================\n";
    if (check) {
        cout << "Please Login and Add user first" << endl;
        return;
    }
    cout << "Enter the Recipient's Name: ";
    cin.ignore();
    getline(cin, recipientName);
    cout << "Enter Amount to Transfer: ";
    cin >> amount;
    bool receive1 =get_otp();
    if (receive1){
        if (amount > balance) {
        cout << "\nInsufficient balance for the transfer." << endl;
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
        return;
    }
    }else {
        return;
    }
    
    file.open("bank.txt", ios::in);
    tempFile.open("temp.txt", ios::out);

    if (file && tempFile) {
        string n, em, pa, p;
        double b;

        while (file >> n >> em >> pa >> p >> b) {
            if (n == recipientName) {
                recipientFound = true;
                b += amount; // Add the transfer amount to the recipient's balance
                tempFile << n << " " << em << " " << pa << " " << p << " " << b << endl;
            } else if (n == name) {
                balance -= amount; // Deduct the transfer amount from the sender's balance
                tempFile << n << " " << em << " " << pa << " " << p << " " << balance << endl;
            } else {
                tempFile << n << " " << em << " " << pa << " " << p << " " << b << endl;
            }
        }

        file.close();
        tempFile.close();

        remove("bank.txt");
        rename("temp.txt", "bank.txt");

        if (recipientFound) {
            cout << "\nTransfer successful! $" << amount << " has been transferred to " << recipientName << "." << endl;
            balance -= amount;
            fstream transactionFile("transactions.txt", ios::app);
            if (transactionFile) {
                time_t now = time(0);
                char *dt = ctime(&now);
                transactionFile << dt << ": Transferred $" << amount << " to " << recipientName << endl;
                transactionFile.close();
            }
        } else {
            cout << "\nRecipient not found. Transfer failed." << endl;
        }
    } else {
        cerr << "\nError accessing bank records." << endl;
    }

}


void ATM::userLogin()
{
    fstream file;
    string n, em, pa, p;
    unsigned long long int b;

        system("cls");
        cout << "\n========================================\n";
        cout << "              LOGIN ACCOUNT             \n";
        cout << "========================================\n";
        cout << "Enter your Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter your Email: ";
        getline(cin, email);
        cout << "Enter your Password: ";
        getline(cin, password);
        
        // Generate OTP (ideally this would be sent to the user's email)
        srand(time(0));
        int otp = rand() % 10000;
        cout << "Your OTP is: " << otp << endl;  // For testing, remove this in a real scenario
        
        int OTP;
        cout << "Enter the OTP sent to your email: ";
        cin >> OTP;

        if (OTP == otp) {
            cout << "\nOTP verified successfully!" << endl;

            // Open the file to verify the user and get the balance
            file.open("bank.txt", ios::in);
            if (!file) {
                cout << "Error accessing bank records. Please try again later." << endl;
            }

            bool userFound = false;
            while (file >> n >> em >> pa >> p >> b) {
                if (n == name && em == email && pa == password) {
                    balance = b;  // Retrieve the balance from the file
                    cout << "\nLogin successful!" << endl;
                    cout << "Your current balance is $" << balance << endl;
                    userFound = true;
                    break;
                }
            }
            file.close();

            if (userFound) {
                cout << "\nUser not found or credentials incorrect. Please try again." << endl;
            }
        }else {
            cout << "\nINVALID OTP! Please try again." << endl;
           
        }

    }





void ATM::addnewuser()
{
    fstream file;
    string n, fn, pa, p;
    float b;

    system("cls");
    cout << "\n========================================\n";
    cout << "              ADD NEW USER              \n";
    cout << "========================================\n";
    cin.ignore(); // Clear the newline left in the input buffer

    cout << "Enter User Name: ";
    getline(cin, name);

    cout << "Enter your Email: ";
    getline(cin, Email);
    bool receive =get_otp();
    if (receive){
        password.clear();  // Clear the password string to avoid appending
        cout << "Create 4-digit Password: ";
    for (int i = 1; i < 5; i++) {
        ch = getch();
        password += ch;
        cout << "*";
    }
    cout << endl;

    cout << "Enter Phone Number: ";
    cin.ignore();
    getline(cin, ph);
    cout << "Enter your Current Balance: ";
    while (!(cin >> bal) && bal < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a positive numeric balance: ";
    }
    cin.ignore(); // Clear the newline left in the input buffer

    file.open("bank.txt", ios::in);
    bool userExists = false;

    if (file) {
        while (file >> n >> fn >> pa >> p >> b) {
            if (n == name) {
                cout << "User already exists." << endl;
                userExists = true;
                break;
            }
        }
        file.close();
    }

    if (!userExists) {
        file.open("bank.txt", ios::app | ios::out);
        if (file) {
            file << name << " " << Email << " " << password << " " << ph << " " << bal << endl;
            file.close();
            balance = bal;
            cout << "\nAdded new user successfully!" << endl;
            check = false;
        } else {
            cerr << "Error opening file for writing." << endl;
        }
    } else {
        cout << "Please try again with a different username." << endl;
    }
    }
    
}

void ATM::deposit_fun()
{
    if (check) {
        cout << "Please Login and Add user first" << endl;
        return;
    }
    int amount;
    system("cls");
    cout << "\n========================================\n";
    cout << "           DEPOSIT MONEY                \n";
    cout << "========================================\n";
    cout << "Enter Amount to Deposit: ";
    cin >> amount;
    bool receive = get_otp();

    if (amount > 0 && receive) {
        balance += amount;

        // Update the balance in the file
        fstream file("bank.txt", ios::in | ios::out);
        fstream tempFile("temp.txt", ios::out);
        if (!file || !tempFile) {
            cerr << "\nError accessing bank records." << endl;
        } else {
            string n, em, pa, p;
            unsigned long long int b;

            while (file >> n >> em >> pa >> p >> b) {
                if (n == name) {
                    tempFile << n << " " << em << " " << pa << " " << p << " " << balance << endl;  // Update the balance
                } else {
                    tempFile << n << " " << em << " " << pa << " " << p << " " << b << endl;
                }
            }

            file.close();
            tempFile.close();

            remove("bank.txt");
            rename("temp.txt", "bank.txt");

            cout << "\nYour balance is now $" << balance << " after depositing." << endl;
        }
    } else {
        cout << "\nInvalid deposit amount." << endl;
    }
}

void ATM::already_user()
{
    system("cls");
    fstream file("bank.txt", ios::in);
    string name1;
    int found = 0;

    cout << "\n========================================\n";
    cout << "          ALREADY USER ACCOUNT          \n";
    cout << "========================================\n";
    
    if (!file) {
        cout << "File opening Error..." << endl;
    } else {
        cout << "User Name: ";
        cin.ignore();
        getline(cin, name1);

        while (file >> name>> email >> password  >> ph >> Bal) {
            if (name == name1) {
                system("cls");
                cout << "\n========================================\n";
                cout << "          ALREADY USER ACCOUNT          \n";
                cout << "========================================\n";
                cout << "User already exists"<<endl;
                cout << "\nUser Name: " << name <<"\nEmail :"<<email<<"\nPassword: "<<password<<"\nYour balance :"<<Bal<< "\nPhone: " << ph;
                found++;
                break;
            }
        }
        file.close();

        if (found == 0) {
            cout << "User Name not found..." << endl;
        }
    }

}

int ATM::withdraw_fun()
{
    if (check) {
        cout << "Please Login and Add user first" << endl;
        return 0;
    }

    if (get_otp()) {
        int amount;
        system("cls");
        cout << "\n========================================\n";
        cout << "           WITHDRAW MONEY               \n";
        cout << "========================================\n";
        cout << "Enter Amount to Withdraw: ";
        cin >> amount;

        if (amount > balance) {
            cout << "\nYour balance of $" << balance << " is not enough to withdraw $" << amount << "." << endl;
        } else {
            balance -= amount;

            // Update the balance in the file
            fstream file("bank.txt", ios::in | ios::out);
            fstream tempFile("temp.txt", ios::out);
            if (!file || !tempFile) {
                cerr << "\nError accessing bank records." << endl;
            } else {
                string n, em, pa, p;
                unsigned long long int b;

                while (file >> n >> em >> pa >> p >> b) {
                    if (n == name) {
                        tempFile << n << " " << em << " " << pa << " " << p << " " << balance << endl;  // Update the balance
                    } else {
                        tempFile << n << " " << em << " " << pa << " " << p << " " << b << endl;
                    }
                }

                file.close();
                tempFile.close();

                remove("bank.txt");
                rename("temp.txt", "bank.txt");

                cout << "\nYour balance is now $" << balance << " after withdrawing." << endl;
            }
        }

        return 0;
    }
    return 0;
}

int ATM::balance_fun()
{
    system("cls");
    cout << "\n========================================\n";
    cout << "           ACCOUNT BALANCE              \n";
    cout << "========================================\n";
    cout << "Your balance is $" << balance << endl;
    return 0;
}

bool ATM::get_otp()
{
    int otp;
    int OTP;
    srand(time(0));
    otp = rand() % 10000;
    cout << "Your OTP is: " << otp << endl;
    cout << "Enter OTP sent to your email: ";
    cin >> OTP;
    if (OTP == otp)
    {
        cout << "OTP verified successfully!" << endl;
        return true;
    }
    else
    {
        cout << "INVALID OTP!" << endl;
        cout <<"Retype OTP sent to your email!"<<endl;
        return false;
    }
}


int main()
{


    ATM atmbank;
    atmbank.Menu();

    return 0;