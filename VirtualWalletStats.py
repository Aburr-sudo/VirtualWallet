# -*- coding: utf-8 -*-
"""
Created on Tue Apr  7 21:31:47 2020

@author: Allan
"""
import sys
import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from io import StringIO
#%matplotlib inline


directory = os.getcwd() 
#dir_path = os.path.dirname(os.path.realpath(__file__))
directory =  os.path.normpath(directory)
print(directory)
directory = directory + "\\outputData.csv"
directory =  os.path.normpath(directory)
print(directory)


#df = pd.read_csv('C:/Users/Allan/Documents/outputData.csv')
df = pd.read_csv(directory)
df.head()
df.plot(x = 'Date')

index = df.index
columns = df.columns
values = df.values

#To get correct column string names
columns

df.plot('Date', ' Total ', kind = 'bar')

#To get information from dataframe
sum = df[' Total '].sum()
mean = df[' Total '].mean()
median = df[' Total '].median()
cumulativeMax = df.cummax()
maximum= df[' Total '].max()
minimum = df[' Total '].min()
standardDev = df.std()

#may be changed to number of entries
numberOfDays = len(df.index)
numberOfDays

###Concatenate all this into a string then push into a file which can then 
## be read from the original application

print("Total amount spent in the period: ")
print(sum)
print("Average amount spent per day: ")
print(mean)
print("Most spent in a single day: ")
aa = df.max()
mostSpentInADay = aa['Date']
print(str(maximum) + " on " + str(mostSpentInADay))
#aa = df[' Total '].min()
minDate = df.min()
leastInADay = minDate['Date']
print("Least spent in a single day: ")
print(str(minimum) + " on " + str(leastInADay))
print("Total amount of days with no expenses: ")