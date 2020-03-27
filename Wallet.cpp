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

using namespace std;
class Wallet;
void printCurrentFunds(Wallet &obj);

int const MAX_PURCHASES = 20;
int const MAX = 100;
int const EMPTY = 0;
int purchaseCounter = 0;
int hashValue = 0;
int const PURCHASETYPES = 7;
int hashTable[PURCHASETYPES] = {0};
string hashTablePurchaseTypes[PURCHASETYPES] = "";

string purchaseRecords[MAX_PURCHASES] = {};
double purchasePrices[MAX_PURCHASES]  = {0};


string CurrentDate();
void setListofTypes();
void viewMostrecent(bool &continueLoop);


/*	TODO
 *
 *
 * Rewrite receipt to be of most recent purchase history
 *
 * be able to pull up the receipt from the menu
 *
 * need to disregard entries in datalog of all 0's

 Add menu to make selection:
 open wallet, reset wallet, view reciept, make wallet(?)
 *
 * Auto fill data into dat appropriate log
 * Process that data in python
 *
 * */

struct Wallet
{
	double contents;
	int date;

	Wallet()
	{
			contents = 0;
	}
};

struct Date
{
	int day;
	int month;
};

void openWallet(Wallet &obj)
{
		ifstream file;
		string garbage;
		string value;
		double funds;
		file.open("WalletLog.txt");
		if(file.is_open())
		{
			getline(file, garbage, ':');
			getline(file, value);
			funds = std::atof(value.c_str());
			obj.contents = funds;
		}
			else{cerr << "error";}
}

void reset(Wallet &obj)
{
	static int count = 0;
	char answer;
	//printCurrentFunds(obj);
	printf("Reset Weekly Funds? (y/n)\n\n" );
	cin >> answer;

if(answer == 'y')
{
	cout << "resetting wallet contents to default of $100" <<endl;
	obj.contents = 100;
}
else if(answer == 'n')
{
	openWallet(obj);
}
else
{
	printf("incorrect input, try again\n\n");
	count++;
	if(count > 4)
	{
		printf("number of permissible attempts exceeded.\nExiting program\n");
		exit(0);
	}
	reset(obj);
}
}


string listPurchasePossibilities()
{
	int selection;

	string selectionStr;
	printf("What did you purchase today\n1. Groceries\n2. Bills\n3. Transport\n4. Take Out\n5. Medical\n6. Entertainment\n7. Other\n\n");
	cin >> selection;
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
			cin >> selectionStr;  hashValue = 6; break;

			default:
			break;
			}
	}
	return selectionStr;
}

void modifyWallet(Wallet &obj)
{
string purchase;
char answer;
double spending;


int day;
int month;
bool continueLoop = true;

while(continueLoop)
{
	cout << "Record purchase? (y/n)\n" << endl;
	cin >> answer;
	if(answer == 'y')
	{
	purchase = listPurchasePossibilities();

	purchaseRecords[purchaseCounter] = purchase;
	cout << "how much did you spend today on " << purchase << "?\n$";
	cin >> spending;
	purchasePrices[purchaseCounter++] = spending;
	obj.contents = obj.contents - (spending);
	hashTable[hashValue] += spending;

printf("Remaining money for the week: $%.2f\n", obj.contents);
	}
	else if(answer == 'n')
	{
		printf("Remaining money for the week: $%.2f\n", obj.contents);
		printf("Terminating program\n");
		continueLoop = false;
	}else{ cout << "invalid input\n" << endl;}

}

}

void recordRemainingFunds(Wallet &obj,string timestamp)
{
	ofstream file;
//	string a = timestamp;
//	string descriptor = "_RemainingFunds.txt";
//	a += ".txt";

//	date.append("WalletLog.txt");
	file.open("WalletLog.txt");
	if(file.is_open())
	{
	std::ostringstream strs;
	strs << obj.contents;
	std::string line = strs.str();

	//string line = std::to_string(obj.contents);
	string text = "Remaining money for the week: ";
	text.append(line);
	file << text;
	}

	file.close();
}

bool isEmpty()
{
    //if hashtable is empty do not open and write to file
    int checkIfAllEmpty = 0;
    for(int i =0; i < PURCHASETYPES; i++)
    {
        if(hashTable[i] == 0)
        {
            checkIfAllEmpty++;
        }
    }
    if(checkIfAllEmpty == 7)
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

	fstream file;
	string date = CurrentDate();
	string garbage;
	string fileName = "outputData.csv";
	file.open(fileName);
	if(file.is_open())
	{
	while(getline(file, garbage))
	{
		//nothing, just iterate through
	}
	if(file.eof()){ file.clear();} // reset flag, say end of file has not been reached, allows further input
	file << date << ",";
	for(int i =0; i < 7; i++) // remove magic numbers
	{
		if(i == 6)
		{
			file << hashTable[i];
		}else{
			file << hashTable[i] << ",";
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
		}else{}
	}
}

void chooseToView()
{
	bool choice;
	char decision;
	cout << "Would you like to look at your recent reciepts? (y/n)" << endl;
	cin >> decision;
	if(decision == 'y')
	{choice = true;}else{choice = false;}

	if(choice)
	{
		viewMostrecent(choice);
	}


}

void viewMostrecent(bool &continueLoop)
{
	fstream myfile;
	myfile.open("outputData.csv");
	vector<string> lines;
	string token;
	vector<string> splitLine;
	string line;
	int recentPurchases[PURCHASETYPES] = {};
	int counter = 1;
	char decision;

	while(getline(myfile, line))
	{
			lines.push_back(line);
	}
	while(continueLoop)
	{
	cout << "looper" << endl;
	stringstream ss(lines.back());
	while(getline(ss, token, ','))
	{
			splitLine.push_back(token);
	}
	cout << "MOST RECENT RECEIPT\n";
	for(int i =0; i < 7; i++)
	{
			if(i == 0)
			{
			cout << "Date : " << splitLine.at(i) << "\n****EXPENSES****\n";
			}else
			{
				cout << hashTablePurchaseTypes[i] << " : " << splitLine.at(i)  << endl;
			}
	}
	counter++;
	lines.pop_back();
	cout << "look at more recent reciept? (y/n)";
	cin >> decision;
	if(decision == 'y')
	{continueLoop = true;}else{continueLoop = false;}
	}

}
// make persistent
/*void purchaseLog()
{

	fstream file;
	string date = CurrentDate();
	string garbage;
	string fileName = "mostRecentPurchase.txt";
	file.open(fileName);
	if(file.is_open())
	{
	while(getline(file, garbage))
	{
		//nothing, just iterate through

	}
	if(file.eof()){ file.clear();} // reset flag, say end of file has not been reached, allows further input

	file << date << "\n";
	for(int i =0; i < purchaseCounter; i++)
	{
			file << purchaseRecords[i] << " : $" << purchasePrices[i] << "\n";
	}
	}else{
		cerr << "Error opening file" <<endl;
		}

	file.close();
}
* */

// provided by Timmmm on stackoverflow
// https://stackoverflow.com/questions/34963738/c11-get-current-date-and-time-as-string
//edited ".txt" to end of string
string CurrentDate()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    char buf[100] = {0};
    std::strftime(buf, sizeof(buf), "%d/%m/%Y", std::localtime(&now));
    return buf;
}

void viewPurchaseHistory()
{
	ofstream viewFile;
	viewFile.open("Receipt.txt");

}

// display date, remaining funds (and wallet name)
void displayCurrentInfo(Wallet &obj)
{
	string date = CurrentDate();
 	//cout << date <<endl;
 	printf("%S\nCurrent contents of Wallet:\n%.2f", date, obj.contents);
}

void openMenu()
{
	char select;
	cout << "Hello, please select an option below\n";
	cout << "1. Reset remaining funds\n2. Record purchases\n3. View recent purchases" << endl;

	cin >> select;
	bool continueCycle = true;
	while(continueCycle)
	{
	if(select == '1')
	{
		//
		continueCycle = false;
	}else if(select == '2')
	{
		//
		continueCycle = false;
	}
	else if(select == '3')
	{
		//
		continueCycle = false;
	}else{
		cout << "invalid selection please try again.\n Valid inputs are '1', '2' or '3'" << endl;
	}
	}



}

int main()
{
setListofTypes();
Wallet wallet;
//chooseToView(); // add this as option in menu
string date = CurrentDate();
//cout << date <<endl;
openMenu();


reset(wallet);
modifyWallet(wallet);
recordRemainingFunds(wallet, date);
dataLog(); // populates dataOutput file

return 0;
}
