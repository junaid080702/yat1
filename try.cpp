#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Customer {
    string name;
    string id;
    string address;
    string contact;
    double balance;

    void display() const {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Address: " << address << endl;
        cout << "Contact: " << contact << endl;
        cout << "Balance: " << balance << endl;
    }
};

class Bank {
private:
    vector<Customer> customers;

    Customer* findCustomerById(const string& id);
    const Customer* findCustomerById(const string& id) const;

public:
    void createAccount();
    void viewAllAccounts() const;
    void updateAccount();
    void searchAccount() const;
    void performTransaction();
    void deleteAccount();
    void menu();
};

Customer* Bank::findCustomerById(const string& id) {
    for (auto& customer : customers) {
        if (customer.id == id) {
            return &customer;
        }
    }
    return nullptr;
}

// Const findCustomerById for read-only operations
const Customer* Bank::findCustomerById(const string& id) const {
    for (const auto& customer : customers) {
        if (customer.id == id) {
            return &customer;
        }
    }
    return nullptr;
}

void Bank::createAccount() {
    Customer customer;
    cout << "\n--- Create New Account ---\n";
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, customer.name);
    cout << "Enter ID: ";
    cin >> customer.id;
    cout << "Enter Address: ";
    cin.ignore();
    getline(cin, customer.address);
    cout << "Enter Contact: ";
    cin >> customer.contact;
    cout << "Enter Initial Balance: ";
    cin >> customer.balance;

    customers.push_back(customer);
    cout << "Account created successfully!\n";
}

void Bank::viewAllAccounts() const {
    if (customers.empty()) {
        cout << "\nNo accounts found.\n";
        return;
    }
    cout << "\n--- Customer List ---\n";
    for (const auto& customer : customers) {
        customer.display();
        cout << "---------------------\n";
    }
}

void Bank::updateAccount() {
    string id;
    cout << "\n--- Update Account ---\n";
    cout << "Enter Customer ID: ";
    cin >> id;

    Customer* customer = findCustomerById(id);
    if (customer) {
        cout << "Enter New Address: ";
        cin.ignore();
        getline(cin, customer->address);
        cout << "Enter New Contact: ";
        cin >> customer->contact;
        cout << "Details updated successfully!\n";
    } else {
        cout << "No account found with ID: " << id << endl;
    }
}

void Bank::searchAccount() const {
    string id;
    cout << "\n--- Search Account ---\n";
    cout << "Enter Customer ID: ";
    cin >> id;

    const Customer* customer = findCustomerById(id);
    if (customer) {
        customer->display();
    } else {
        cout << "No account found with ID: " << id << endl;
    }
}

void Bank::performTransaction() {
    string id;
    cout << "\n--- Perform Transaction ---\n";
    cout << "Enter Customer ID: ";
    cin >> id;

    Customer* customer = findCustomerById(id);
    if (customer) {
        cout << "1. Deposit\n2. Withdraw\nChoose an option: ";
        int option;
        cin >> option;
        double amount;
        if (option == 1) {
            cout << "Enter deposit amount: ";
            cin >> amount;
            customer->balance += amount;
            cout << "Deposit successful. New balance: " << customer->balance << endl;
        } else if (option == 2) {
            cout << "Enter withdrawal amount: ";
            cin >> amount;
            if (amount > customer->balance) {
                cout << "Insufficient balance. Current balance: " << customer->balance << endl;
            } else {
                customer->balance -= amount;
                cout << "Withdrawal successful. New balance: " << customer->balance << endl;
            }
        } else {
            cout << "Invalid option.\n";
        }
    } else {
        cout << "No account found with ID: " << id << endl;
    }
}

void Bank::deleteAccount() {
    string id;
    cout << "\n--- Delete Account ---\n";
    cout << "Enter Customer ID: ";
    cin >> id;

    auto it = remove_if(customers.begin(), customers.end(), [&](const Customer& customer) {
        return customer.id == id;
    });

    if (it != customers.end()) {
        customers.erase(it, customers.end());
        cout << "Account deleted successfully!\n";
    } else {
        cout << "No account found with ID: " << id << endl;
    }
}

void Bank::menu() {
    while (true) {
        cout << "\n--- Bank Management System ---\n";
        cout << "1. Create Account\n";
        cout << "2. View All Accounts\n";
        cout << "3. Update Account\n";
        cout << "4. Search Account\n";
        cout << "5. Perform Transaction\n";
        cout << "6. Delete Account\n";
        cout << "7. Exit\n";
        cout << "Choose an option: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            createAccount();
            break;
        case 2:
            viewAllAccounts();
            break;
        case 3:
            updateAccount();
            break;
        case 4:
            searchAccount();
            break;
        case 5:
            performTransaction();
            break;
        case 6:
            deleteAccount();
            break;
        case 7:
            cout << "Exiting system. Goodbye!\n";
            return;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}

int main() {
    Bank bank;
    bank.menu();
    return 0;
}
