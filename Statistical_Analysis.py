#!/usr/bin/env python
# coding: utf-8

# In[1]:


# -*- coding: utf-8 -*-
"""
@author: AllanBurr
"""
import sys
import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns


# In[14]:

## Change date of csv to the index of dataframe
#df['Date'] = pd.to_datetime(df['Date'])
#df.set_index('Date', inplace = True)
#df.head()

df = pd.read_csv('outputData.csv')
df.head()

index = df.index
columns = df.columns
values = df.values

#To get correct column string names
columns

plot = df.plot('Date', 'Total',  kind = 'line',marker = 'o', title ='Total Spending', legend = False)
fig = plot.get_figure()
fig.savefig("figures/TotalSpendingByDate.png")

plot = df.plot('Date', 'Groceries', kind = 'line',marker = 'o',title ='Grocery Expenses', legend = False)
fig = plot.get_figure()
fig.savefig("figures/GroceriesSpending.png")

plot = df.plot('Date', 'Transport',color='orange', kind = 'bar', title ='transport Expenses', legend = False)
fig = plot.get_figure()
fig.savefig("figures/Transport.png")

plot = df.plot('Date', 'Take_Out', kind = 'bar', color='green', title ='Take Out Expenses', legend = False)
fig = plot.get_figure()
fig.savefig("figures/Take_out.png")

plot = df.plot('Date', 'Medical', kind = 'bar', color='red',title ='Medical Expenses', legend = False)
fig = plot.get_figure()
fig.savefig("figures/Medical.png")


plot = df.plot('Date', 'Entertainment', kind = 'bar', color='yellow',title ='Entertainment Expenses', legend = False)
fig = plot.get_figure()
fig.savefig("figures/Entertainment.png")

plot = df.plot('Date', 'Other', kind = 'bar', color='black',title ='Misc. Expenses', legend = False)
fig = plot.get_figure()
fig.savefig("figures/Other.png")

 # only works without total df.plot('Date', kind='bar', stacked= True)
Total = df['Total']

def goThru():
    a = list(df)
    totals = 0
    stringText = ""
    for totals in a[1:9]:        
        stringText +=getInfo(totals)
    return stringText    
        
fileText = "Begin"
def getInfo(colName):
    #To get information from dataframe
    stri = "Begin"
    sum = df[colName].sum()
    mean = df[colName].mean()
    median = df[colName].median()
    maximum= df[colName].max()
    sum = round(sum, 2)
    mean = round(mean, 2)
    median = round(median, 2)
    stri = str("Total amount spent in the period on "  + colName+ ": $" + str(sum))
    stri2 = str("Average amount spent per day on "  + colName+ ": $" + str(mean))
    stri3 = str("Most spent in a single day on "  + colName+ ": $"+ str(maximum))   
    stri += "\n"
    stri += (stri2)
    stri += "\n"
    stri += stri3
    stri += "\n"
    stri += "\n"
    stri += "\n"
    #print(stri)
    return stri





# In[4]:
def printOnce():
    aa = df.max()
    maximum= df['Total'].max()
    minimum = df['Total'].min()
    cumulativeMax = df.cummax()
    standardDev = df['Total'].std(axis = 0)
    standardDev = round(standardDev, 2)
    mostSpentInADay = aa['Date']
    print(str(maximum) + " on " + str(mostSpentInADay))
    #aa = df[' Total '].min()
    minDate = df.min()
    leastInADay = minDate['Date']
    print("Least spent in a single day: ")
    print(str(minimum) + " on " + str(leastInADay))
    print("Total amount of days with no expenses: ")
    print("Standard deviation of total spending = " + str(standardDev))
  
    
printOnce()    
###Concatenate all this into a string then push into a file which can then 
## be read from the original application


# In[5]:
#

# In[6]:


#may be changed to number of entries
def getTotalDays():
   # numberOfDays = len(df.index)
    a = df['Date'].nunique()
    return a


# In[7]:


def getTotalEntries():
    numberOfEntries = len(df.index)
    return numberOfEntries


# In[9]:


def countValuesInColumn(colName, days):
    var = 0
    for x in df[colName]:
        if x != 0:
            var += 1
    stringCol = str(var)
    print("There were " + stringCol + " instances of " + colName)
    percent = (var/days)*100
    percent = round(percent, 2)
    print("You had a " + str(percent) + "% chance of purchasing " + colName + " per day")




file1 = open("Statistical Results.txt","w") 
firstDay = df['Date'].head(1)
firstDay = firstDay[0]
lastDay =df['Date'].iloc[-1]
#lastDay = lastDay[0]


fileText = "From " + str(firstDay) + " until " + str(lastDay)+ "\n"
fileText += "there were " + str(getTotalDays()) + " days which purchases were made\n"
fileText += goThru()
file1.write(fileText)
file1.close() 


# In[15]:


fig, ax = plt.subplots(figsize = (12,6))    
fig = sns.barplot(x = 'Date', y = 'Total', data = df)
ax.set_ylabel('Total Spent')
ax.set_xlabel('Date')
ax.set_xticklabels(ax.get_xticklabels(), rotation=75)

pic = fig.get_figure()
pic.savefig("figures/SeabornTotalByDate.png")


# In[10]:


def iterateThruByColumn():
    days = getTotalDays()
    print("In a total of " + str(days)+ " days")
    a = list(df)
    totals = 0
    for totals in a[1:8]:
        countValuesInColumn(totals, days)
iterateThruByColumn()


# In[13]:


del df['Bills']
plot = df.plot(x='Date', y=['Groceries', 'Transport', 'Take_Out', 'Medical', 'Entertainment', 'Other'], kind="bar", stacked=True)
fig = plot.get_figure()
fig.savefig("figures/Without_Total.png")
del df['Total'] 
plot = df.plot(x='Date', y=['Groceries', 'Transport', 'Take_Out', 'Medical', 'Entertainment', 'Other'], kind="line")
fig = plot.get_figure()
fig.savefig("figures/WithoutBills_Rent.png")


