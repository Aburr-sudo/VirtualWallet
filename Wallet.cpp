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

string purchaseRecords[MAX_PURCHASES] = {};
double purchasePrices[MAX_PURCHASES]  = {0};
set<string> purchaseTypesMade;

string CurrentDate();




/*	TO DO
 * 
 * 
 * Rewrite receipt to be of most recent purchase history
 * 
 * be able to pull up the receipt from the menu
 * 
 * 
 * 
 * Auto fill data into dat appropriate log
 * Process that data in python 
 * 
 * How to:
 * Read in from file, use ":" token to collect money values
 * add these to a vector
 * the last item in vector is the current value of the wallet's contents
 * 
 * grab the current date and save into variable
 * append this variable to "log" text file name for a unique file for the day's purchases
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
	purchaseTypesMade.insert(purchase);
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

void printCurrentFunds(Wallet &obj)
{
	printf("Current contents of Wallet:\n%.2f", obj.contents);
}


void dataLog()
{
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
	file << date << ", ";
	for(int i =0; i < 7; i++) // remove magic numbers
	{
		if(i == 6)
		{
			file << hashTable[i]; 
		}else{
			file << hashTable[i] << ", ";
		}
	}
	file << "\n";
	}
	
	file.close();
}

void mapToType(string input, int value)
{
	switch(value){
			case 1: input = "Groceries"; hashValue = 0; break;
			case 2: input = "Bills"; hashValue = 1; break;
			case 3: input = "Transport"; hashValue = 2; break;
			case 4: input = "Take Out";  hashValue = 3; break;
			case 5: input = "Medical"; hashValue = 4; break;
			case 6: input = "Entertainment"; hashValue = 5; break;
			case 7: printf("Type in your purchase\n");
			cin >> input;  hashValue = 6; break;
			default:
			break;
		}
}

void viewMostrecent()
{
	fstream myfile;
	myfile.open("outputData.csv");
	vector<string> lines;
	string line;
	while(getline(myfile, line))
	{
			lines.push_back(line);
	}
	cout << lines.back() << line;
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

int main()
{

Wallet wallet;

string date = CurrentDate();
cout << date <<endl;
reset(wallet);
modifyWallet(wallet);
recordRemainingFunds(wallet, date);
//purchaseLog(); // populates receipt.txt file
dataLog(); // populates dataOutput file

	for (std::set<std::string>::iterator it=purchaseTypesMade.begin(); it!=purchaseTypesMade.end(); ++it)
	    std::cout << ' ' << *it;
	std::cout<<"\n";



return 0;	
}
