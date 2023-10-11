n = int(input())
m = int(input())

# Reading maximum matrix of size nxm
maxim = []
for i in range(n):        
    a =[]
    for j in range(m):    
         a.append(int(input()))
    maxim.append(a)

maxim = ((maxim))

# reading allocation matrix of size nxm
alloc = []
for i in range(n):
    a = []
    for j in range(m):
        a.append(int(input()))
    alloc.append(a)

# reading total vector of size m
total = []
for i in range(m):
    total.append(int(input()))
# Write code here to read allocation matrix and total vectors.

def findID(finish, id, n):
    if not finish[id]:
        return -1
    
    alprs = True # variable to record if all the processes are 
                 # true or not
    for j in range(n):
        alprs &= finish[j]
        
    if alprs:
        return -2
        
    return 0
            
    # Write code here that could return -2, -1, and 0.
    # -2 if all the processes finished their tasks.
    # -1 if the current process id finished its task.
    # 0 if scope is there to explore the current process.

def computeAvail(total, alloc, n, m):
    avail = [] 
    for i in range(m):
        sum = total[i]
        for j in range(n):
            sum -= alloc[j][i]
        avail.append(sum)
    return avail
    # Write code here that could return the available vector.

def printTable(maxim, alloc, need, rem):
    print('\nMax      Alloc     Need      Avail')
    
    for i in range(n):
        for j in range(m):
            print(maxim[i][j] + " ")
        print("\t") 
        for j in range(m):
            print(alloc[i][j] + " ")
        print("\t") 
        for j in range(m):
            print(need[i][j] + " ")
            
        if i == 0:
            print("\t") 
            for j in range(m):
                print(rem[j] + " ")
    # Write code to print the output table 
    # See example test case for reference.

def bankers(maxim, alloc, total, n, m):
    finish = [False]*n
    safe = [-1]*n
    need = []
    for i in range(n):        
        a =[]
        for j in range(m):    
            a.append(maxim[i][j]-alloc[i][j])
        need.append(a)
    
    avail = computeAvail(total, alloc, n, m)
    
    # work = [row.copy() for row in avail]
    for i in range(m):
        print("avail = ", avail[i])
        
    id = 0
    k = 0
    iter = 0;
    while (True):
        status = findID(finish, id, n)
        if (status == -2):
            break
            # Write code here
        elif (status == -1):
            for i in range(m):
                avail[i] += alloc[id][i]
            # safe[k] = id
            k += 1
            # Write code here.
        else:
            if id != iter:
                temp = [True] * m
                for j in range(m):
                    if need[id][j] > avail[j]:
                        temp = [False] * m
                        break
                if True in temp:
                    id = iter
                    continue
            iter += 1
            # Write code here.
    return need, avail, safe

need, avail, safe = bankers(maxim, alloc, total, n, m)

printTable(maxim, alloc, need, avail)
seq = [];
for i in range(0, n):
    seq.append('P'+str(safe[i]))
print('\nSafe Seequence is : ',tuple(seq))