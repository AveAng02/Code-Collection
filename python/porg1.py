n = int(input())

sum = 0

list = [int(input()) for i in range(n)]

for i in range(0, len(list)):
    sum += list[i]
    
print(sum)