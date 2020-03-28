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
class Reciept;
vector<Reciept> RecieptRepository; // vector to be populated with receipt objects


string CurrentDate();
void setListofTypes();
void viewMostrecent(bool &continueLoop);
void constructingMostRecent();


/*	TODO
 *
 *
 * Rewrite receipt to be of most recent purchase history -- needs fixing
 *
 * be able to pull up the receipt from the menu -- complete
 *
 * need to disregard entries in datalog of all 0's -- complete

 Add menu to make selection:
 open wallet, reset wallet, view reciept, make wallet(?)
 *
 * Auto fill data into appropriate log
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

struct Reciept{
    string date;
    int groceries, bills, transport, take_out, medical, entertainment, other;
    Reciept(string date)
    {
        this->date = date;
        groceries = bills = transport = take_out = medical = entertainment = other = 0;
    }
    Reciept()
    {
        this->date = "Unassigned date";
        groceries = bills = transport = take_out = medical = entertainment = other = 0;
    }

    void dispay()
    {
        cout << "Displaying purchase" << "\n" << this->date << "\n"
        << "Groceries: $" << this->groceries << "\nBills: $" << this->bills
        << "\nTransport: $" << this->transport << "\nTake Out: $" << this->take_out
        << "\nMedical: $" << this->medical << "\nEntertainment: $" << this->entertainment
        << "\nOther: $" << this->other << endl;
    }

    void assignValue(int counter, int value)
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
	int value;

	cout << "Enter amount to reset wallet to: " <<endl;
	cin >> value;
	obj.contents = value;

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
		continueLoop = false;
	}else{ cout << "invalid input\n" << endl;}

}

}

void recordRemainingFunds(Wallet &obj)
{
	ofstream file;
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
	for(int i =0; i < PURCHASETYPES; i++) // remove magic numbers
	{
		if(i == (PURCHASETYPES-1))
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
		//viewMostrecent(choice);
		constructingMostRecent();
	}
}

void readInReceipts()
{
    fstream myfile;
	myfile.open("outputData.csv");
	vector<string> lines;
	string token;
	vector<string> splitLine;
	string line;

	string toReciept;
	int recieptCounter = 0;




	int recentPurchases[PURCHASETYPES] = {};
    Reciept recieptRecord;


	while(getline(myfile, line))
	{
			lines.push_back(line);
	}
    int counter = lines.size() -1; // minus 1 as the first row is categorical data and won't make a reciept


    string delimiter = ",";
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
        cout << toReciept <<endl;

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




void constructingMostRecent()
{
    char decision;
    bool continueLoop = true;

	fstream myfile;
	myfile.open("outputData.csv");
	vector<string> lines;
	string token;
	vector<string> splitLine;
	string line;

	string toReciept;
	int recieptCounter = 0;


	vector<Reciept> RecieptRepository;

	int recentPurchases[PURCHASETYPES] = {};
    Reciept recieptRecord;


	while(getline(myfile, line))
	{
			lines.push_back(line);
	}
    int counter = lines.size() -1; // minus 1 as the first row is categorical data and won't make a reciept


    string delimiter = ",";
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
        cout << toReciept <<endl;

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

	while(continueLoop)
	{
	cout << "look at more recent reciept? (y/n)";
	cin >> decision;
	if(decision == 'y')
	{continueLoop = true;}else{continueLoop = false;}
	}
}


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


// display date, remaining funds (and wallet name)
void displayCurrentInfo(Wallet &obj)
{
	string date = CurrentDate();
 	cout << "Date: " << date << "\nCurrent funds: $" << obj.contents << endl;
}

void openMenu(Wallet &wallet)
{
    displayCurrentInfo(wallet);
	char select;
	bool continueCycle = true;

	cout << "\n\nWELCOME TO VIRTUAL WALLET\n\nPlease select an option below\n\n";
	while(continueCycle)
	{

	cout << "1. Reset remaining funds\n2. Record purchases\n3. View recent purchases\n4. Exit" << endl;
	cin >> select;
	if(select == '1')
	{
		reset(wallet);
		cout << "\n\n";
	}else if(select == '2')
	{
		modifyWallet(wallet);
        cout << "\n\n";
	}
	else if(select == '3')
	{
		chooseToView(); // this function needs fixing, only shows last purchase
		cout << "\n\n";
	}else if(select == '4')
	{
	printf("Terminating program\nWriting output to data log and saving current amount of funds\n");
	continueCycle = false;
	return;

	}
	else{
		cout << "invalid selection please try again.\n Valid inputs are '1', '2' or '3'" << endl;
        cout << "1. Reset remaining funds\n2. Record purchases\n3. View recent purchases\n4. Exit" << endl;
        cin >> select;
	}
	}
}

int main()
{
setListofTypes(); //initialise lists
Wallet wallet; // initialise wallet object
openWallet(wallet); // read in current funds from text file and save into wallet object
//Main Loop
openMenu(wallet);
//record results
dataLog(); // populates dataOutput file with purchase data
recordRemainingFunds(wallet); // saves current contents of wallet

return 0;
}
