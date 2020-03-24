# VirtualWallet
A console application to keep track of purchases. 

Keeps a running log of purchases and amount left over. Keeps persistent storage on remaining funds, a detailed human readable log of purchases and a formatted csv file containg purchase data which will be fed into python program for statistical analysis.
The data stored in the csv foldeer is not prone to error from the wallet side of the application.
What this means is that even aif a purchase is made that makes the wallet's value go negative, the correct amount of total purchase prices will be stored in the csv file, thus safe guarding the statistical analysis from improper data
Data Structures used:
Hashtable
