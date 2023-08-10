#include <iostream>
#include <string>
#include <list>
#include <stdexcept>

using namespace std;

// Base class for different types of items
class Item {
public:
    string name;
    int id;
    float price;

    Item() : id(0), price(0.0) {}
};

// Derived class for stocks, inherits from Item
class Stock : public Item {
public:
    int quantity;

    Stock() : quantity(0) {}
};

// Derived class for clients
class Client {
public:
    string name;
    int id;
    string address;
    string dob;

    Client() : id(0) {}
};

// LinkedList template class
template <typename T>
class LinkedList {
public:
    list<T> data;

    void addNode(const T& item) {
        data.push_back(item);
    }

    void printClients() const {
        for (const auto& item : data) {
            const Client* clientPtr = dynamic_cast<const Client*>(&item);
            if (clientPtr) {
                cout << "Client Name: " << clientPtr->name << endl;
                cout << "Client ID: " << clientPtr->id << endl;
                cout << "Address: " << clientPtr->address << endl;
                cout << "DOB: " << clientPtr->dob << endl << endl;
            }
        }
    }

    void printStocks() const {
        for (const auto& item : data) {
            const Stock* stockPtr = dynamic_cast<const Stock*>(&item);
            if (stockPtr) {
                cout << "Stock Name: " << stockPtr->name << endl;
                cout << "Stock ID: " << stockPtr->id << endl;
                cout << "Price: " << stockPtr->price << endl;
                cout << "Quantity: " << stockPtr->quantity << endl << endl;
            }
        }
    }

    void removeStock(int stockId, int quantity) {
        for (auto& item : data) {
            Stock* stockPtr = dynamic_cast<Stock*>(&item);
            if (stockPtr && stockPtr->id == stockId) {
                if (stockPtr->quantity >= quantity) {
                    stockPtr->quantity -= quantity;
                    cout << quantity << " units of stock removed." << endl;
                }
                else {
                    cout << "Insufficient stock quantity." << endl;
                }
                return;
            }
        }
        cout << "Stock with ID " << stockId << " not found." << endl;
    }

    void deleteClient(int clientId) {
        data.remove_if([clientId](const T& item) {
            const Client* clientPtr = dynamic_cast<const Client*>(&item);
            return clientPtr && clientPtr->id == clientId;
            });
    }

    void updateClient(int clientId, const string& name, const string& address) {
        for (auto& item : data) {
            Client* clientPtr = dynamic_cast<Client*>(&item);
            if (clientPtr && clientPtr->id == clientId) {
                clientPtr->name = name;
                clientPtr->address = address;
                cout << "Client details updated." << endl;
                return;
            }
        }
        cout << "Client with ID " << clientId << " not found." << endl;
    }
};

int main() {
    try {
        LinkedList<Client> clientList;
        LinkedList<Stock> stockList;

        int select;
        string check;
        bool continueLoop = true;

        while (continueLoop) {
            cout << "1) Add Client\n";
            cout << "2) Add Stock\n";
            cout << "3) View Client Details\n";
            cout << "4) View Stock Details\n";
            cout << "5) Remove Stock\n";
            cout << "6) Delete Client\n";
            cout << "7) Update Client Details\n";
            cout << "8) Exit\n";

            cout << "Choose an option: ";
            cin >> select;

            switch (select) {
            case 1: {
                Client client;
                cout << "Enter username: ";
                cin >> client.name;
                cout << "Enter ID: ";
                cin >> client.id;
                cout << "Enter address: ";
                cin >> client.address;
                cout << "Enter date of birth: ";
                cin >> client.dob;
                clientList.addNode(client);
                break;
            }
            case 2: {
                Stock stock;
                cout << "Enter stock name: ";
                cin >> stock.name;
                cout << "Enter stock ID: ";
                cin >> stock.id;
                cout << "Enter price: ";
                cin >> stock.price;
                cout << "Enter quantity: ";
                cin >> stock.quantity;
                stockList.addNode(stock);
                break;
            }
            case 3:
                cout << "Client Details:\n";
                clientList.printClients();
                break;
            case 4:
                cout << "Stock Details:\n";
                stockList.printStocks();
                break;
            case 5: {
                int stockId, quantity;
                cout << "Enter stock ID to remove: ";
                cin >> stockId;
                cout << "Enter quantity to remove: ";
                cin >> quantity;
                stockList.removeStock(stockId, quantity);
                break;
            }
            case 6: {
                int clientId;
                cout << "Enter client ID to delete: ";
                cin >> clientId;
                clientList.deleteClient(clientId);
                break;
            }
            case 7: {
                int clientId;
                string name, address;
                cout << "Enter client ID to update: ";
                cin >> clientId;
                cout << "Enter updated name: ";
                cin >> name;
                cout << "Enter updated address: ";
                cin >> address;
                clientList.updateClient(clientId, name, address);
                break;
            }
            case 8:
                continueLoop = false;
                break;
            default:
                cout << "Invalid option. Please try again.\n";
            }

            cout << "Enter 'Y' to continue, 'N' to exit: ";
            cin >> check;
            if (check != "Y" && check != "y") {
                continueLoop = false;
            }
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
