#include <iostream>
#include <fstream> // to use a file in code
#include <vector> // to use vector
#include <string>
#include <cctype> // to use is alpha and to upper.
#include <cstdlib> // to use exit() function
#ifdef _WIN32
#include <windows.h> //
#include <unistd.h>
#endif

using namespace std;

 void clear_screen() ;

//  "Base class" or "Parent class"
class Bank
{
    // Access Modifiers.
protected:
    // Single user variables in struct
    struct name_code
    {
        string user_number;
        string user_name;
        int money;
    };

public:
    // Container to save users in code
    vector<name_code> users;
    int vector_size = 0;

    Bank() // constructor to link files and code
    {
        ifstream data("Bank.txt"); // open file name is Bank

        // Default user from struct to i use in code
        name_code person;
        while (data >> person.user_name >> person.user_number >> person.money)
        {
            users.push_back(person);
        }
        vector_size = users.size();
        data.close(); // close file
    }

    ~Bank() // Destructor opening after object ended .
    {
        cout<< "\nCongratolation the operetor in done . "<< endl ;
    }

    virtual void add_to_file() = 0; // Definition a virtual function.

    virtual void admin() = 0 ;
};

//  "Derived class" or "Child class"
class User : public Bank // Single Inheritance from Bank's class
{

public:
    name_code one; // Default user from struct to i use in code

    void admin() override // Director's function.
    {
        int all_money =0; // Money counter.
        for(int i=0 ; i<vector_size ; i++)
        {
            all_money += users[i].money ; // add all money in money counter.
        }
        // admin interface.
        cout << "\n      Welcome to the official account" << endl ;
        cout << "          - All the money in the safe : "<< all_money << " $." << endl ;
        cout << "          - Number of users in the bank : "<< vector_size << " users."<< endl ;
        cout << "\n        - Statement of customer accounts :\n" ;

        if(vector_size == 0) // Check if there are any clients
        {
            cout<< "           -> There is no client in the bank.\n";
        }
         // user's list.
        for(int i=0 ; i<vector_size ; i++)
        {
            int x = users[i].user_name.size();
            if (x < 10)
            {
                int bit = 10 - x;
                for (int j = 0; j < bit; j++)
                {  // Use a different variable name for the inner loop
                    users[i].user_name += " ";  // Use the correct index
                }
            }


            cout<<"           " <<(i+1) <<".name: '"<<users[i].user_name << "' |code : "<< users[i].user_number
            << " |money in user account : " << users[i].money << " $." << endl ;
        }

        string code ;
        bool found = false;
        cout<< "\nEnter user code you wont it : " ;
        cin>> code ;

        for(int i=0 ; i<vector_size ; i++)
        {
            if(users[i].user_number == code || users[i].user_name == code) //Search for a specific user
            {
                cout<< "\n\nThe name of the account you want : " << users[i].user_name << "\nAnd code : "
                << users[i].user_number << "\nhave a money : " << users[i].money << " $."<< endl ;
                found = true ;
            }
        }
        if(found == false)
        {
               // if user not found .
            cout << "User not found, do you want to create a new account? Enter 'y' if you want: ";
            char vont;
            cin >> vont;
            if (vont == 'y') // creat a new account.
            {
                creat_acc();
            }
            else
            {
                cout << "Thank you for interacting with us." << endl;
                exit(0); // End program.
            }
        }

            char choice ;
            cout<< "Do you want any other operation ? /'y'/ :" ;
            cin>> choice ;

            if(choice == 'y')
            {
                clear_screen();// clean screen.
                admin(); // Re-calling function.
            }
            else
            {
                cout<< "Thanks for your cooperation."<< endl ;
                exit(0) ; // end program.
            }
    }

    void add_to_file() override // to add edit in money to file
    {
        ofstream data("Bank.txt"); // open file his name is Bank
        if (!data) {
            cout << "Error, in open." << endl;
            return;
        }

        // loop to add edit in user from vector to file
        for (int i = 0; i < vector_size; i++)
        {
            if (users[i].user_number == one.user_number)
            {
                users[i].money = one.money;
            }
            // add from vector to file
            data << users[i].user_name << " " << users[i].user_number << " " << users[i].money << endl;
        }
        // close file
        data.close();
    }

    int creat_acc() // function to add user in system.
    {
        string name, code;
        string rcode;
        do
        {
           cout << "Enter your Name: ";
           cin >> name;
        }
        while (!isalpha(name[0])) ;

        if(islower(name[0])) // Leave the first letter of the user name as the capital.
        {
            name[0] = toupper(name[0]);
        }

        cout << "Enter your code: ";
        cin >> code;


        // loop to add value to others.
        for (int i = 0; i < 4 && i < code.size(); i++)
        {
            rcode += code[i] + 1;
        }

        // Check the code bit number.
        if(rcode.size()<4)
        {
            // To create a code consisting of 4 bits.
            int bits = 4-rcode.size() ;
            for(int i=0 ; i<bits ; i++)
            {
                rcode += '0' ;
                if(rcode[i]==':')
                {
                    rcode[i] = '1' ;
                }
            }
        }


        // Verify that the resulting code does not exist .
        for (const auto user : users)
        {
            if (user.user_number == rcode)
            {
                // if there is close the program
                cout << "User is unavailable. Please try again with a different code." << endl;
                creat_acc() ;
            }
        }
        cout << "\nYour user name is: " << name << endl;
            // user code
        cout << "Your code is: " << rcode << endl;

        // Assigning values ​​after creating the account and zeroing the account value .
        name_code new_user;
        new_user.user_name = name;
        new_user.user_number = rcode;
        new_user.money = 0;
        users.push_back(new_user); // add user in vector .
        vector_size = users.size();// edit vector's size .

        // add editing in file
        add_to_file();
        cout << "We are happy to add you in our system, Good Luck." << endl;
        cout<<"\nyou will login with any account ? " ;
        string x ;
        cin>> x ;
        get_user(x) ;
    }


    bool get_user(string code ) // get user's num from user .
    {
        if(code == "admin")
        {
            admin() ;
        }

        for (int i = 0; i < vector_size; i++)
        {
            // search for the user from the system
            if (users[i].user_number == code)
            {
                // Assigning values ​​to an external variable of type struct
                one.user_name = users[i].user_name;
                one.money = users[i].money;
                one.user_number = users[i].user_number;
                return true;
            }
        }
        // if user not found .
        cout << "User not found, do you want to create a new account? Enter 'y' if you want: ";
        char vont;
        cin >> vont;
        if (vont == 'y') // creat a new account .
        {
            creat_acc();
            return true;
        }
        else
        {
            cout << "Thank you for interacting with us." << endl;
            exit(0);
        }
    }


    void cash_withdrawal() // to take some money from his account .
    {
        int amount;
        int it = 0;
        do
        {
            if (it > 0)
            {
                cout << "Your account balance is insufficient." << endl; // for the first time
            }
            cout << "Enter the amount of money: "; // for the second time
            cin >> amount;
            it++; // add 1 after
        } while (one.money - amount < 0); // if his account not have enough money
        // if his account have enough money
        one.money -= amount;
    }


    int cash_transfer(string one_user) //transferring money between two accounts .
    {
         string acc_transfer;
         int it=0 ;   // Transfer to anther account.
        do
        {
            if(it > 0)
            {
                cout<< "We can't transfer to the same account.\n" ;
                cout<< "Enter a anther account : ";
                cin>> acc_transfer ;
            }
            else
            {
                cout << "Enter the account you want to transfer to: ";
                cin >> acc_transfer; // he wont to transfer to
                it++ ;
            }

        }
        while(acc_transfer == one_user);
        bool found = false;
        for (int i = 0; i < vector_size; i++)
        {
            // Search for the account in the existing accounts
            if (acc_transfer == users[i].user_number)
            {

                 int amount,it=0;
                do
                {
                if(it==0)
                {
                cout << "Enter amount of money: ";
                cin >> amount;
                it++;
                }
                else if(it > 0)
                {
                    cout<< "\nyou don't have this amount of money please try agean . "<< endl ;
                    cout << "Enter amount of money: ";
                    cin >> amount;
                }
                }
                while(amount > one.money) ;


                users[i].money += amount; // transfer a money from accounts .
                one.money -= amount; // deducting money from the first account
                add_to_file();
                found = true;
                cout << "\nOperation accomplished successfully." << endl; // done msg .
                cout<< "\nyou send : "<< amount<< " $ to "<< users[i].user_name << endl ;
                cout<< "money in your account : "<< one.money << " $.";
                break;
            }
        }

        if (!found) // If we don't have the account
        {
            char choice;
            do
            {
                cout << "Account not found, do you want to create one? (y/n): ";
                cin >> choice;
            } while (choice != 'y' && choice != 'n');

            if (choice == 'y')
            {
                creat_acc(); // create a new account
            }
            else
            {
                cout << "Thanks for your cooperation." << endl;
            }
        }
        return 0;
    }

     int delete_acc() // delete an account from program
    {
        char choice;
        cout << "\nAre you sure? 'y' or 'n'" << endl;
        do
        {
            cin >> choice;
        } while (choice != 'y' && choice != 'n'); // if user enter anther choice .

        if (choice == 'y')
        {
            char choice ;
            while(one.money > 0)
            {
                cout<< "\nsorr we can't delete your account becose it have a money ."<< endl;

                do{
                    cout<< "you wont transfer /'t'/ or withdrawal money /'w'/ ? \n" ;
                    cin>> choice ;
                }
                while(choice != 't' && choice != 'w') ;
                if(choice == 't')
                {
                    cash_transfer(one.user_number) ;

                }
                else if(choice == 'w')
                {
                    cash_withdrawal();
                    delete_acc() ;

                }
            }
            for (int i = 0; i < vector_size; i++)
            {
                if (one.user_number == users[i].user_number)
                {
                    users.erase(users.begin() + i); // delete user from vector .
                    vector_size = users.size(); // edit vector size .
                    add_to_file(); // add edit in file .
                    cout<< "your account was deleted .\n" ;
                    return 0;
                }
            }
        }
        else if (choice == 'n') // if user not wont delete his account .
        {
            cout << "Ok, " << one.user_name << endl;
        }
        return 0;
    }


  void edit_acc() // To edit account's name.
   {
    char choice;
    while (true)
    {
        cout << "Do you want to edit your name? (y/n): ";
        cin >> choice;

        if (choice == 'y')
        {
            string name;
            cout << "Enter new name: ";
            cin >> name;

            one.user_name = name;
            for (int i = 0; i < vector_size; i++)
            {
                if (one.user_number == users[i].user_number)
                {
                    users[i].user_name = one.user_name;
                }
            }
            add_to_file();
            cout << "\nOperation accomplished successfully." << endl;
            break;
        }
        else if (choice == 'n')
        {
            cout << "No changes made." << endl;
            break;
        }
        else
        {
            cout << "Error in input. Please enter 'y' or 'n'." << endl;
        }
    }
}

    string view_name() // return name .
    {
        return one.user_name;
    }

    int view_money() // return money .
    {
        return one.money;
    }

    friend void account_inquiry(const User &); // Definition a friend function.

    void cash_deposit(int amount) ; // to add some money in his account.
};



 // Definition of the friend function outside the class.
void account_inquiry(const User &user)
{
    cout << "\n------------------------------------------\n";
    cout << "   Account Information : "<< endl ;
    cout << "   User name: " << user.one.user_name << "\n";
    cout << "   User number: " << user.one.user_number << "\n";
    cout << "   Account balance: " << user.one.money << " $\n";
    char choice ;
    do
        {
        cout << "\n-> You wont do any thing ? /'y'/ or /'n'/ : " ;
        cin >> choice ;
        }
    while(choice != 'n' && choice != 'y') ;

    if(choice == 'n')
        {
            cout<< "Thanks for your cooperation"<< endl ;
            exit(0);
        }


}

// Definition of the regular function outside the class.
void User ::cash_deposit(int amount)
{
    one.money += amount; // Add money in account.
    add_to_file(); // add to file.
    // display money in account.
    cout<< "your money in account is : "<< one.money << " $" << endl;
}

 void clear_screen() // Clear screen.
    {
            #ifdef _WIN32
                    system("cls");
            #else
                    // Assume POSIX
                    system("clear");
            #endif
    }


int main() // main function.
{
    User one; // The first object .
    // user code
    string user_one;

    //---> Announcing the primary user,"to go enter "admin"" .
    cout<< "If you are admin we have admin account."<< endl ;

    cout << "Enter user code: ";
    cin >> user_one;

    // Enter the user into the system .
    one.get_user(user_one);

    int choice;
    do
    {
        // The primary interface .
        cout << "\n\n->   WELCOME, "<<one.view_name()<<" IN OUR BANK" << endl;
        cout << "         1. Create new account" << endl;
        cout << "         2. Account inquiry" << endl;
        cout << "         3. Cash deposit" << endl;
        cout << "         4. Cash withdrawal" << endl;
        cout << "         5. Cash transfer" << endl;
        cout << "         6. Delete account" << endl;
        cout << "         7. Edit account" << endl;
        cout << "         8. Exit" << endl;
        cout << "\nPlease choose the operation you want to perform: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            // add a new account
            one.creat_acc();
            break;
        }
        case 2:
        {
           // Account information.
            account_inquiry(one);
            break;
        }
        case 3:
        {
            int amount;
            cout << "Enter the amount: ";
            cin >> amount;

            one.cash_deposit(amount);
            one.add_to_file();
            break;
        }
        case 4:
        {
            one.cash_withdrawal();
            cout << "Your money is: " << one.view_money() << " $." << endl;
            one.add_to_file();
            break;
        }
        case 5:
        {
             // transfer money
            one.cash_transfer(user_one);
            break;
        }
        case 6:
        {

         // delete a account
            one.delete_acc();
            return 0;
        }
        case 7:
        {
                //Edit account
            one.edit_acc() ;
            return 0;

        }
        case 8:
        {
            // Exit the program.
            cout << "Exiting program, Thank you." << endl;
            one.add_to_file();
            return 0;
        }
        default:
            // Enter num anther (1 to 8 ).
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
        while (choice != 8);

    return 0;
}
