# VirtualWallet
This project has two main parts, "Wallet Log" and "Data Analysis". The first is a c++ command line interface which allows the user to keep a log of their spending habits and keep track of how much money they have left.
The second part is a python program that takes the data generated from the first program and subjects it to statistical analaysis.


Wallet Log:

Once executed the program will display the remaining amount of funds and the last date that this amount was reset.
Then the user will be given the four following options:
1. Reset current funds: this will allow the user to reset their wallet's contents by updating the corresponding file with the new value
2. Record Purchase: This allows the user to record their purchases by type, with the amount they spent on each purchase in a loop until the user has no more purchases to record.
3. View recent reciepts: This allows the user to view the data stored from previous purchase logs in a human readable format. 
4. Exit: this terminates the program and saves updates all the relevant files with the new inputs. If there have been no new inputs, no new information is writeen to the files. This is to avoid empty entries in the file that will be subject to statistical analysis as such entries would skew the data



Compilation notes
This application uses features from c++11 so make sure you use a compatible compiler.

Data Analysis: