#include "billing.h"

void BillingSystem::addItem()
{
    string itemID, itemName;
    float price;

    cout << "Enter Item ID: ";
    cin >> itemID;
    cout << "Enter Item Name: ";
    cin >> itemName;
    cout << "Enter Item Price: ";
    cin >> price;

    ofstream file("items.txt", ios::app);
    if (file.is_open())
    {
        file << itemID << " " << itemName << " " << price << "\n";
        file.close();
        cout << "Item added successfully!\n";
    }
    else
    {
        cout << "Error opening file.\n";
    }
}

void BillingSystem::generateBill()
{
    string customerID, itemID, fileItemID, itemName;
    float price, amount, total = 0.0;
    int quantity;
    bool found;

    cout << "Enter Customer ID: ";
    cin >> customerID;

    ofstream billFile("bills.txt", ios::app);

    while (true)
    {
        found = false;
        cout << "Enter Item ID (or 'done' to finish): ";
        cin >> itemID;

        if (itemID == "done")
            break;

        ifstream itemFile("items.txt");
        if (itemFile.is_open())
        {
            while (itemFile >> fileItemID >> itemName >> price)
            {
                if (fileItemID == itemID)
                {
                    found = true;
                    cout << "Enter Quantity: ";
                    cin >> quantity;

                    amount = price * quantity;
                    total += amount;

                    billFile << customerID << " " << itemName << " " << quantity << " " << amount << "\n";
                    cout << "Item added to bill successfully!\n";
                    break;
                }
            }
            itemFile.close();
        }

        if (!found)
        {
            cout << "Item not found!\n";
        }
    }

    billFile << "Total: " << total << "\n";
    billFile.close();
    cout << "Total Bill Amount: " << total << " saved successfully!\n";
}

void BillingSystem::printBill()
{
    string customerID, line;
    bool found = false;

    cout << "Enter Customer ID to print bill: ";
    cin >> customerID;

    ifstream billFile("bills.txt");
    if (billFile.is_open())
    {
        cout << "\n--- Bill for Customer ID: " << customerID << " ---\n";
        while (getline(billFile, line))
        {
            if (line.find(customerID) != string::npos || line.find("Total:") != string::npos)
            {
                cout << line << endl;
                found = true;
            }
        }
        billFile.close();

        if (!found)
        {
            cout << "No bill found for this customer.\n";
        }
    }
    else
    {
        cout << "Error opening bill file.\n";
    }
}

void BillingSystem::viewAllItems()
{
    ifstream file("items.txt");
    string itemID, itemName;
    float price;

    if (file.is_open())
    {
        cout << "\n--- Available Items ---\n";
        while (file >> itemID >> itemName >> price)
        {
            cout << "ID: " << itemID << " | Name: " << itemName << " | Price: " << price << "\n";
        }
        file.close();
    }
    else
    {
        cout << "No items found.\n";
    }
}

void BillingSystem::updateItem()
{
    string itemID, fileItemID, itemName, newName;
    float price, newPrice;
    bool found = false;

    cout << "Enter Item ID to Update: ";
    cin >> itemID;

    ifstream file("items.txt");
    ofstream tempFile("temp.txt");

    if (file.is_open() && tempFile.is_open())
    {
        while (file >> fileItemID >> itemName >> price)
        {
            if (fileItemID == itemID)
            {
                found = true;
                cout << "Enter New Item Name: ";
                cin >> newName;
                cout << "Enter New Price: ";
                cin >> newPrice;

                tempFile << fileItemID << " " << newName << " " << newPrice << "\n";
                cout << "Item updated successfully!\n";
            }
            else
            {
                tempFile << fileItemID << " " << itemName << " " << price << "\n";
            }
        }
        file.close();
        tempFile.close();

        remove("items.txt");
        rename("temp.txt", "items.txt");

        if (!found)
        {
            cout << "Item not found!\n";
        }
    }
    else
    {
        cout << "Error opening files.\n";
    }
}

void BillingSystem::deleteItem()
{
    string itemID, fileItemID, itemName;
    float price;
    bool found = false;

    cout << "Enter Item ID to Delete: ";
    cin >> itemID;

    ifstream file("items.txt");
    ofstream tempFile("temp.txt");

    if (file.is_open() && tempFile.is_open())
    {
        while (file >> fileItemID >> itemName >> price)
        {
            if (fileItemID == itemID)
            {
                found = true;
                cout << "Item deleted successfully!\n";
            }
            else
            {
                tempFile << fileItemID << " " << itemName << " " << price << "\n";
            }
        }
        file.close();
        tempFile.close();

        remove("items.txt");
        rename("temp.txt", "items.txt");

        if (!found)
        {
            cout << "Item not found!\n";
        }
    }
    else
    {
        cout << "Error opening files.\n";
    }
}

int main()
{
    BillingSystem system;
    int choice;

    do
    {
        cout << "\n--- Mart Billing System ---\n";
        cout << "1. Add New Item\n";
        cout << "2. Generate Bill\n";
        cout << "3. View All Items\n";
        cout << "4. Update Item\n";
        cout << "5. Delete Item\n";
        cout << "6. Print Bill\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system.addItem();
            break;
        case 2:
            system.generateBill();
            break;
        case 3:
            system.viewAllItems();
            break;
        case 4:
            system.updateItem();
            break;
        case 5:
            system.deleteItem();
            break;
        case 6:
            system.printBill();
            break;
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
