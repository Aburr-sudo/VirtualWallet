#include<iostream>
#include<math.h>
#include<fstream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <time.h>
#include <vector>
#include <string>
#include<set>

#include"header.h"

using namespace std;
/*
TO DO:
Add a method so that the user can input purchases from prior dates

OO the project, allow user to add category of purchase
*/

const int  MAX_PURCHASES = 20;
int  MAX = 100;
int  EMPTY = 0;
int purchaseCounter = 0;
int hashValue = 0;
const int  PURCHASETYPES = 7;
double hashTable[PURCHASETYPES] = {0};
std::string hashTablePurchaseTypes[PURCHASETYPES] = {};

std::string purchaseRecords[MAX_PURCHASES] = {};
double purchasePrices[MAX_PURCHASES]  = {0};
std::vector<Reciept> RecieptRepository; // vector to be populated with receipt objects


//class functions
Wallet::Wallet()
{
    contents = 0;
    date = CurrentDate();
}
Reciept::Reciept()
{
        this->date = "Unassigned date";
        groceries = bills = transport = take_out = medical = entertainment = other = 0;
}

Reciept::Reciept(string date)
{
    this->date = date;
    groceries = bills = transport = take_out = medical = entertainment = other = 0;
}
void Reciept::display()
{//only display non-zero values -- done
        cout << "\n\n***** Displaying purchase *****\n" << endl;
        cout << this->date << "\n";
        if(this->groceries > 0){cout << "Groceries: $" << this->groceries << endl; }
        if(this->bills > 0){cout << "\nBills: $" << this->bills << "\n";}
        if(this->transport > 0){cout<< "\nTransport: $" << this->transport << "\n";}
        if(this->take_out > 0){cout << "\nTake Out: $" << this->take_out << "\n";}
        if(this->medical > 0){cout << "\nMedical: $" << this->medical << "\n";}
        if(this->entertainment > 0){cout << "\nEntertainment: $" << this->entertainment << "\n";}
        if(this->other > 0){cout << "\nOther: $" << this->other << endl; }
}
void Reciept::assignValue(int counter, int value)
{
            switch(counter)
        {
            case 0: this->groceries = value; break;
            case 1: this->bills = value; break;
            case 2: this->transport = value; break;
            case 3: this->take_out = value; break;
            case 4: this->medical = value; break;
            case 5: this->entertainment = value; break;
            case 6: this->other = value; break;
            case 7:  break;
        }
}

// ********FREE FUNCTIONS***********  //


void openWallet(Wallet &obj)
{
		std::ifstream file;
		std::string dateOfLastReset;
		std::string value;
		double funds;
		file.open("WalletLog.txt");
		if(file.is_open())
		{
			getline(file, dateOfLastReset);
			getline(file, value);
			obj.date = dateOfLastReset;
			funds = std::atof(value.c_str());
			obj.contents = funds;
		}
			else{std::cerr << "error";}
}

void reset(Wallet &obj)
{
	char answer;
	int value;
    std::string dateOfLastReset;
    dateOfLastReset = CurrentDate();

	std::cout << "Enter amount to reset wallet to: " <<std::endl;
	std::cin >> value;
	obj.contents = value;
	obj.date = dateOfLastReset;

}


std::string listPurchasePossibilities()
{
	int selection;

	std::string selectionStr;
	printf("What did you purchase today\n1. Groceries\n2. Bills\n3. Transport\n4. Take Out\n5. Medical\n6. Entertainment\n7. Other\n\n");
	std::cin >> selection;
	if(selection <= 0 || selection > 7)
	{
	printf("Invalid selection");
	}
	else{
		switch(selection){

			case 1: selectionStr = "Groceries"; hashValue = 0; break;
			case 2: selectionStr = "Bills"; hashValue = 1; break;
			case 3: selectionStr = "Transport"; hashValue = 2; break;
			case 4: selectionStr = "Take Out";  hashValue = 3; break;
			case 5: selectionStr = "Medical"; hashValue = 4; break;
			case 6: selectionStr = "Entertainment"; hashValue = 5; break;
			case 7: printf("Type in your purchase\n");
			std::cin >> selectionStr;  hashValue = 6; break;

			default:
			break;
			}
	}
	return selectionStr;
}

void modifyWallet(Wallet &obj)
{
std::string purchase;
char answer;
double spending;
int day;
int month;
bool continueLoop = true;

while(continueLoop)
{
	std::cout << "Record purchase? (y/n)\n" << std::endl;
	std::cin >> answer;
	if(answer == 'y')
	{
	purchase = listPurchasePossibilities();

	purchaseRecords[purchaseCounter] = purchase;
	std::cout << "how much did you spend today on " << purchase << "?\n$";
	std::cin >> spending;
	purchasePrices[purchaseCounter++] = spending;
	obj.contents = obj.contents - (spending);
	hashTable[hashValue] += spending;

printf("Remaining disposable funds: $%.2f\n", obj.contents);
	}
	else if(answer == 'n')
	{
		printf("Remaining disposable funds: $%.2f\n", obj.contents);
		continueLoop = false;
	}else{ std::cout << "invalid input\n" << std::endl;}

}

}

void recordRemainingFunds(Wallet &obj)
{
	std::ofstream file;
	file.open("WalletLog.txt");
	if(file.is_open())
	{
	std::ostringstream strs;
	strs << obj.date << "\n" << obj.contents;
	std::string line = strs.str();

	file << line;
	}

	file.close();
}

bool isEmpty()
{
    //if hashtable is empty do not open and write to file
    //linear search
    int checkIfAllEmpty = 0;
    for(int i =0; i < PURCHASETYPES; i++)
    {
        if(hashTable[i] == 0)
        {
            checkIfAllEmpty++;
        }
    }
    if(checkIfAllEmpty == PURCHASETYPES)
    {
        return true;
    }else{
    return false;
    }
}

void dataLog()
{
    //Measure to avoid empty log entries
    if(isEmpty())
    {
        return;
    }

	std::fstream file;
	std::string date = CurrentDate();
	std::string garbage;
	double total = 0;
	std::string fileName = "outputData.csv";
	file.open(fileName);
	if(file.is_open())
	{
	while(getline(file, garbage))
	{
		//nothing, just iterate through
	}
	if(file.eof()){ file.clear();} // reset flag, say end of file has not been reached, allows further input
	file << date << ",";
	for(int i = 0; i <= PURCHASETYPES; i++) // remove magic numbers
	{
		if(i == (PURCHASETYPES))
		{
			file << total;
		}else{
			file << hashTable[i] << ",";
			total += hashTable[i];
		}
	}
	file << "\n";
	}

	file.close();
}

void setListofTypes()
{
	int counter = 0;
	while(counter < PURCHASETYPES)
	{
		if(counter == 0)
		{
			hashTablePurchaseTypes[0] = "Groceries";
			counter++;
		}else if(counter == 1)
		{
			hashTablePurchaseTypes[1] = "Bills";
			counter++;
		}else if(counter == 2)
		{
			hashTablePurchaseTypes[2] = "Transport";
			counter++;
		}else if(counter == 3)
		{
			hashTablePurchaseTypes[3] = "Take Out";
			counter++;
				}else if(counter == 4)
		{
			hashTablePurchaseTypes[4] = "Medical";
			counter++;
		}else if(counter == 5)
		{
			hashTablePurchaseTypes[5] = "Entertainment";
			counter++;
		}else if(counter == 6)
		{
			hashTablePurchaseTypes[6] = "Other";
			counter++;
		}else{

        }
	}
}


void readInReceipts()
{
  std::fstream myfile;
	myfile.open("outputData.csv");
	std::vector<std::string> lines;
	std::string token;
	std::vector<std::string> splitLine;
	std::string line;
  //std::cout<< "trigger"<<endl;
	std::string toReciept;
	int recieptCounter = 0;

	int recentPurchases[PURCHASETYPES] = {};
    Reciept recieptRecord;

	while(getline(myfile, line))
	{
			lines.push_back(line);
	}
    int counter = lines.size() -1; // minus 1 as the first row is categorical data and won't make a reciept


    std::string delimiter = ",";
    size_t pos = 0;

    int flipSwitch = 0;
    int value = 0;

    while(counter > 0)
    {
        toReciept = lines.at(counter);
        pos = toReciept.find(delimiter);
        token = toReciept.substr(0, pos);
        recieptRecord.date = token;
        toReciept.erase(0, pos + delimiter.length());

        while ((pos = toReciept.find(delimiter)) != std::string::npos)
        {
        if(flipSwitch == PURCHASETYPES)
        {
            flipSwitch = 0;
        }

        token = toReciept.substr(0, pos);
        value = stoi(token);

        recieptRecord.assignValue(flipSwitch, value);
        flipSwitch++;

        toReciept.erase(0, pos + delimiter.length());
        }

    RecieptRepository.push_back(recieptRecord);
    counter--;
    }
}




void viewMostRecent()
{
    std::cout << "Your receipts will be listed from most to least recent" <<std::endl;
    readInReceipts();
    char decision;
    bool continueLoop = true;
    int len = RecieptRepository.size();
    if(len == 0)
    {
      std::cout << "No available receipts\n\n";
      return;
    }
    int counter=0;
	while(continueLoop)
	{
	if(decision == 'y' || counter == 0) // the counter is included for the first case
	{
	    if(counter == len)
        {
        std::cout << "no more receipts left" << std::endl;
        continueLoop = false; // prevents out of bounds error
        }
	    RecieptRepository[counter].display();
        counter++;
       std:: cout << "View next reciept? (y/n)";
        std::cin >> decision;
    }
    else{continueLoop = false;}
	}
}


// provided by Timmmm on stackoverflow
// https://stackoverflow.com/questions/34963738/c11-get-current-date-and-time-as-string
std::string CurrentDate()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    char buf[100] = {0};
    std::strftime(buf, sizeof(buf), "%d/%m/%Y", std::localtime(&now));
    return buf;
}


// display date, remaining funds (and wallet name)
void displayCurrentInfo(Wallet &obj)
{
	std::string date = CurrentDate();
 	std::cout << "Date: " << date << "\nCurrent funds: $" << obj.contents << "\t\tDate of last reset: " << obj.date << std::endl;
}

void clearData()
{
    //std::fstream myfile;
    //myfile.open("outputData.csv");
    printf("Are you sure you want to clear all purchase history? (y/n)");
    char toClear;
    cin >> toClear;
    if(toClear == 'y')
    {
    printf("Clearing all purchase data from output file\n\n");
    std::string firstLine = "Date,Groceries,Bills,Transport,Take_Out,Medical,Entertainment,Other,Total";
    std::ofstream file("outputData.csv"); // Without append
    std::ofstream fileNew("outputData.csv", ios::app); // with append
    fileNew << firstLine << endl;

    }else if(toClear == 'n')
    {
    return;
    }else{printf("invalid selection\n\n"); return;}



}

void openMenu(Wallet &wallet)
{
    displayCurrentInfo(wallet);
	char select;
    char toClear;
	bool continueCycle = true;

	std::cout << "\n\nWELCOME TO VIRTUAL WALLET\n\nPlease select an option below\n\n";
	while(continueCycle)
	{

	std::cout << "1. Reset remaining funds\n2. Record purchases\n3. View recent purchases\n4. Clear Purchase Data\n5. Exit" << std::endl;
	std::cin >> select;
	if(select == '1')
	{
		reset(wallet);
		std::cout << "\n\n";
	}else if(select == '2')
	{
		modifyWallet(wallet);
        std::cout << "\n\n";
	}
	else if(select == '3')
	{
		viewMostRecent();
		std::cout << "\n\n";
	}else if(select == '4')
	{
    clearData();
    }
    else if(select == '5')
    {
    printf("Writing output to data log and saving current amount of funds\nTerminating program\n");
	continueCycle = false;
	return;
    }
	else{
		std::cout << "invalid selection please try again.\n Valid inputs are '1', '2', '3', '4' or '5'" << std::endl;
        std::cout << "1. Reset remaining funds\n2. Record purchases\n3. View recent purchases\n4. Clear Purchase Data\n5. Exit" << std::endl;
        std::cin >> select;
	}
	}
}
