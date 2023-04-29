
"""
Rough set theory deals with the analysis of uncertainty and vagueness in data. Here is an example of sample data for rough set analysis:

Consider a data set of customer purchases from a retail store. Each customer is identified by a unique ID and their purchases are recorded in terms of product codes. The data set consists of the following attributes:

    Customer ID: A unique identifier for each customer.
    Product codes: A list of codes for the products purchased by each customer.

For instance, the following table shows a sample data set for rough set analysis:
Customer ID	Product codes
1	A, B, C
2	A, B
3	C, D, E
4	B, C, E
5	A, D

In this example, there are five customers, each of whom has purchased a different set of products. The rough set analysis can be used to identify common patterns or relationships among the products purchased by the customers.

"""


# Importing required libraries
import numpy as np
import pandas as pd

# Load the dataset
data = pd.read_csv('customer_data.csv')

# Convert the dataset to a numpy array
data = np.array(data)

# Define the universe of discourse
universe = np.unique(data[:, 1])

# Define the number of attributes
num_attributes = data.shape[1] - 1

# Define the lower and upper approximation functions
def lower_approximation(decision, data):
    subset = data[np.where(data[:, -1] == decision)]
    return np.unique(subset[:, 1])

def upper_approximation(decision, data):
    subset = data[np.where(data[:, -1] == decision)]
    attributes = []
    for i in range(num_attributes):
        values = np.unique(subset[:, i])
        if len(values) == 1:
            attributes.append(values[0])
    return attributes

# Define the main function to compute rough sets
def compute_rough_sets(data):
    decisions = np.unique(data[:, -1])
    lower_approximations = []
    upper_approximations = []
    for decision in decisions:
        lower = lower_approximation(decision, data)
        upper = upper_approximation(decision, data)
        lower_approximations.append(lower)
        upper_approximations.append(upper)
    return decisions, lower_approximations, upper_approximations

# Compute the rough sets for the dataset
decisions, lower, upper = compute_rough_sets(data)

# Print the results
print("Decisions:", decisions)
for i in range(len(decisions)):
    print("Lower approximation for decision {}: {}".format(decisions[i], lower[i]))
    print("Upper approximation for decision {}: {}".format(decisions[i], upper[i]))
