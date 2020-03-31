# VirtualWallet
A CLI application to keep track of purchases. 

Keeps a running log of purchases and amount left over. Keeps persistent storage on remaining funds, a detailed human readable log of purchases and a formatted csv file containg purchase data which will be fed into python program for statistical analysis.
The data stored in the csv foldeer is not prone to error from the wallet side of the application.
What this means is that even aif a purchase is made that makes the wallet's value go negative, the correct amount of total purchase prices will be stored in the csv file, thus safe guarding the statistical analysis from improper data
Once executed the user will be given the four following options:
1. Reset current funds: this will allow the user to reset their wallet's contents by updating the corresponding file with the new value
2. Record Purchase: This allows the user to record their purchases by type, with the amount they spent on each purchase in a loop until the user has no more purchases to record.
3. View recent reciepts: This allows the user to view the data stored from previous purchase logs in a human readable format. 
4. Exit: this terminates the program and saves updates all the relevant files with the new inputs. If there have been no new inputs, no new information is writeen to the files. This is to avoid empty entries in the file that will be subject to statistical analysis as such entries would skew the data

Compilation instructions:

g++ -std=c++11 main.cpp functions.cpp -o virtualWallet

To execute:
./virtualWallet
