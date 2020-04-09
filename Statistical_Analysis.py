#!/usr/bin/env python
# coding: utf-8

# In[1]:


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


# In[2]:




#
#directory = os.getcwd() 
#dir_path = os.path.dirname(os.path.realpath(__file__))
#directory =  os.path.normpath(directory)
#print(directory)
#directory = directory + "\\outputData.csv"
#directory =  os.path.normpath(directory)
#print(directory)


#df = pd.read_csv('C:/Users/Allan/Documents/outputData.csv')
df = pd.read_csv('outputData.csv')
df.head()
df.plot(x = 'Date')

index = df.index
columns = df.columns
values = df.values

#To get correct column string names
columns

df.plot('Date', 'Total', kind = 'bar')

#To get information from dataframe
sum = df['Total'].sum()
mean = df['Total'].mean()
median = df['Total'].median()
cumulativeMax = df.cummax()
maximum= df['Total'].max()
minimum = df['Total'].min()
standardDev = df.std()



# In[ ]:


###Concatenate all this into a string then push into a file which can then 
## be read from the original application
def printStats():
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


# In[ ]:


printStats()


# In[ ]:


#may be changed to number of entries
def getTotalDays():
    numberOfDays = len(df.index)
    return numberOfDays


# In[ ]:


def countValuesInColumn(colName):
    var = 0
    for x in df[colName]:
        if x != 0:
            var += 1
    stringCol = str(var)
    days = getTotalDays()
    print("In a total of " + str(days)+ " days")
    print("There were " + stringCol + " instances of " + colName)
    percent = (var/days)*100
    percent = round(percent, 2)
    print("You had a " + str(percent) + "% chance of purchasing " + colName + " per day")


# In[ ]:


countValuesInColumn('Groceries')


# In[4]:



## Change date of csv to the index of dataframe

df['Date'] = pd.to_datetime(df['Date'])
df.set_index('Date', inplace = True)
df.head()


# In[9]:


df.index


# In[10]:


df.plot(x = 'Date', y='Total')


# In[ ]:


del df['Total']
df.plot(x = 'Date')


# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:




