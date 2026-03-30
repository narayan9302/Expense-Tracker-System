#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Expense {
private:
    int id;
    string title;
    float amount;
    string category;

public:
    Expense(int i, string t, float a, string c) {
        id = i;
        title = t;
        amount = a;
        category = c;
    }

    string toString() {
        return to_string(id) + "|" + title + "|" + to_string(amount) + "|" + category;
    }

    static Expense fromString(string line) {
        int id;
        string title, category;
        float amount;

        int pos1 = line.find("|");
        int pos2 = line.find("|", pos1 + 1);
        int pos3 = line.find("|", pos2 + 1);

        id = stoi(line.substr(0, pos1));
        title = line.substr(pos1 + 1, pos2 - pos1 - 1);
        amount = stof(line.substr(pos2 + 1, pos3 - pos2 - 1));
        category = line.substr(pos3 + 1);

        return Expense(id, title, amount, category);
    }

    void display() {
        cout << "ID: " << id
             << " | Title: " << title
             << " | Amount: " << amount
             << " | Category: " << category << endl;
    }

    int getId() { return id; }
};

class ExpenseManager {
private:
    vector<Expense> expenses;
    string filename = "expenses.txt";

public:
    void loadFromFile() {
        ifstream file(filename);
        string line;

        while (getline(file, line)) {
            expenses.push_back(Expense::fromString(line));
        }
        file.close();
    }

    void saveToFile() {
        ofstream file(filename);
        for (auto &e : expenses) {
            file << e.toString() << endl;
        }
        file.close();
    }

    void addExpense() {
        int id;
        string title, category;
        float amount;

        cout << "Enter ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Title: ";
        getline(cin, title);

        cout << "Enter Amount: ";
        cin >> amount;
        cin.ignore();

        cout << "Enter Category: ";
        getline(cin, category);

        expenses.push_back(Expense(id, title, amount, category));
        saveToFile();
        cout << "Expense Added Successfully!\n";
    }

    void viewExpenses() {
        if (expenses.empty()) {
            cout << "No expenses found.\n";
            return;
        }

        for (auto &e : expenses) {
            e.display();
        }
    }

    void deleteExpense() {
        int id;
        cout << "Enter ID to delete: ";
        cin >> id;

        for (auto it = expenses.begin(); it != expenses.end(); ++it) {
            if (it->getId() == id) {
                expenses.erase(it);
                saveToFile();
                cout << "Deleted Successfully!\n";
                return;
            }
        }
        cout << "Expense not found.\n";
    }
};

int main() {
    ExpenseManager manager;
    manager.loadFromFile();

    int choice;

    do {
        cout << "\n===== Expense Tracker =====\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses\n";
        cout << "3. Delete Expense\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            manager.addExpense();
            break;
        case 2:
            manager.viewExpenses();
            break;
        case 3:
            manager.deleteExpense();
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 4);

    return 0;
}