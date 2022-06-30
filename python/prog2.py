n = int(input("Number of Students:"))
m = int(input("Number of fields:"))

student = []
S1 = []

for i in range(0, n):
        S1 = [input() for i in range(m)]
        student.append(S1)
 
        
primary = int(input("Enter primary Key"))

value = input("Enter the value in the primary key:")

for i in range(0, n):
    if(student[i][primary] == value):
        print(student[i])
        
