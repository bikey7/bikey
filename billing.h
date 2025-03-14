#ifndef BILLING_H
#define BILLING_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class BillingSystem
{
public:
    void addItem();
    void generateBill();
    void viewAllItems();
    void updateItem();
    void deleteItem();
    void printBill();
};

#endif
