
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

fig, axis = plt.subplots(4,4) # generating a 4x4 subplot

df = pd.read_csv(r'heart.csv') # loading data from csv file

column = df.columns # extracting all the columns

# extracting all the rows from python
rowList = [df.loc[:, column[0]]]
for i in range(1, len(column.to_list()) - 1):
    rowList.append(df.loc[:, column[i]])

target = df.loc[:, column[-1]] # placing the target in a seperate place

for i in range(4):
    for j in range(4):
        if (4 * i + j) < (len(column.to_list()) - 1):
            axis[i,j].scatter(rowList[4*i+j].array, target.array)
            axis[i,j].set_title(rowList[4*i+j].name)

for ax in axis.flat:
    ax.label_outer()

plt.show()
