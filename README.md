# VirtualWallet
This project has two main parts, "Wallet Log" and "Data Analysis". The first is a c++ command line interface which allows the user to keep a log of their spending habits and keep track of how much money they have left.
The second part is a python program that takes the data generated from the first program and subjects it to statistical analaysis.

Wallet Log:

Once executed the program will display the remaining amount of funds and the last date that this amount was reset.
Then the user will be given the five following options:

1. Record Purchase: This allows the user to record their purchases by type, with the amount they spent on each purchase in a loop until the user has no more purchases to record. 
2. Reset current funds: this will allow the user to reset their wallet's contents by updating the corresponding file with the new value
3. View recent reciepts: This allows the user to view the data stored from previous purchase logs in a human readable format. 
4. Clear purchase history: this will erase all the data in the logged from the record purchase option. The CSV file will be wiped.
5. Update statistics and data visualisations (execute python file)
6. Exit: this terminates the program and saves updates all the relevant files with the new inputs. If there have been no new inputs, no new information is written to the files. This is to avoid empty entries in the file that will be subject to statistical analysis as such entries would skew the data


Data Analysis:
This extracts the relevant statistical information from the data, plots some graphs with the data and then saves these graphs to images in the figures folder.

Note: to run option from within the command line interface, an appropriate python enviornment must be activated with the following libraries installed:
nummpy, pandas and matplotlib. An exception handling measure has been put in place in case this is not so. The python file can be executed seperately but these libraries must be installed. 

For information on how to activate a virtual enviornment from git bash see the following link: https://medium.com/@presh_onyee/activating-virtualenv-on-windows-using-git-bash-python-3-7-1-6b4b21640368




