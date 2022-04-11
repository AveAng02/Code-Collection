
pi = 3.1415926535897932384626433832795

length = int(input("Enter radius: "))

count = 0

for i in range(length + 1):
    for j in range(length + 1):
        if (i**2 + j**2)**0.5 <= length:
            count += 1

print(count)

print("PI = ", (count * 4) / length**2)








