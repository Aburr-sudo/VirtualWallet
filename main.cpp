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

//include header file
#include"header.h"


/*	TODO
 *
 * Exception checking for invalid inputs
 * Process data in python
 *
 * */

int main()
{
setListofTypes(); //initialise lists
Wallet wallet; // initialise wallet object
openWallet(wallet); // read in current funds from text file and save into wallet object
openMenu(wallet); //Main Loop
//record results
dataLog(); // populates dataOutput file with purchase data, wont run if no input was made
recordRemainingFunds(wallet); // saves current contents of wallet
return 0;
}
