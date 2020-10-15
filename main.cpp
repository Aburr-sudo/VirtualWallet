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
#include <stdlib.h>


//include header file
#include"header.h"


/*	TODO
 *
    1. formatting and presentation
        maybe add condition to check if in terminal or executable
         in terminal it is possible to clear the screen
             printf("\033c");
    2. Redirect output files to specialised directories
 *
 * */

int main()
{
setListofTypes(); //initialise lists
Wallet wallet; // initialise wallet object
openWallet(wallet); // read in current funds from text file and save into wallet object
openMenu(wallet); //Main Loop
//#system("bash");
return 0;
}
