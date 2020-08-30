#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED


struct Wallet
{
	double contents;
	std::string date;
	Wallet();
};

struct Reciept{
    std::string date;
    int groceries, bills, transport, take_out, medical, entertainment, other;
    Reciept(std::string date);
    Reciept();
    void display();
    void assignValue(int counter, int value);
    double spending_sum();
};

void openWallet(Wallet &obj);
void reset(Wallet &obj);
std::string listPurchasePossibilities();
void modifyWallet(Wallet &obj);
void recordRemainingFunds(Wallet &obj);
bool isEmpty();
void dataLog();
void setListofTypes();
void readInReceipts(bool &isEmpty);
void viewMostRecent();
std::string CurrentDate();
void openMenu(Wallet &wallet);
void displayCurrentInfo(Wallet &obj);



#endif // HEADER_H_INCLUDED
