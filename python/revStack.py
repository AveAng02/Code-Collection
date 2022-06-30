m = int(input("Length of stack: "))

stack = [input() for i in range(m)]
temp = []

for k in range(len(stack)):
    if(stack[k] == '+' or stack[k] == '-' or stack[k] == '*' or stack[k] == '/'):
        temp_length = len(temp)

        if(stack[k] == '+'):
            temp[temp_length - 2] += temp[temp_length - 1]
            temp.remove(temp[temp_length - 1])
        elif(stack[k] == '-'):
            temp[temp_length - 2] -= temp[temp_length - 1]
            temp.remove(temp[temp_length - 1])
        elif(stack[k] == '*'):
            temp[temp_length - 2] *= temp[temp_length - 1]
            temp.remove(temp[temp_length - 1])
        elif(stack[k] == '/'):
            temp[temp_length - 2] /= temp[temp_length - 1]
            temp.remove(temp[temp_length - 1])
    else:
        temp.append(int(stack[k]))

print(temp[0])     

