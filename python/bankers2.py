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

# Write code here to read allocation matrix and total vectors.
alloc=[]
for i in range(n):
    a=[]
    for j in range(m):
        a.append(int(input()))
    alloc.append(a)

total=[]
for i in range(m):
    total.append(int(input()))

def findID(finish, id, n):
    # Write code here that could return -2, -1, and 0.
    # -2 if all the processes finished their tasks.
    # -1 if the current process id finished its task.
    # 0 if scope is there to explore the current process.
    flag=0
    for i in range(n):
        if finish[i]==False:
            flag=1
    if flag==0:
        return -2,-1
    else:
        if finish[id]==False:
            return 0,id
        else:
            return -1,-1


def computeAvail(total, alloc, n, m):
    # Write code here that could return the available vector.
    avail=[]
    sum=0
    for i in range(m):
        for j in range(n):
            sum=sum+alloc[j][i]
        avail.append(total[i]-sum)
        sum=0
    return avail
        

def printTable(maxim, alloc, need, rem):
    print('\nMax      Alloc     Need      Avail')
    # Write code to print the output table 
    # See example test case for reference.
    for i in range(n):
        for j in range(m):
            print(maxim[i][j],end=' ')
        print('   ',end='')
        for j in range(m):
            print(alloc[i][j],end=' ')
        print('    ',end='')
        for j in range(m):
            print(need[i][j],end=' ')
        print('    ',end='')
        if i==0:
            for j in range(m):
                print(rem[j],end=' ')
        print('')


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
    
    work = avail.copy()

    id = 0
    k = 0
    iter = 0
    while (True):
        if(iter>=n):
            print('The system is safe.')
            break
        status, pid = findID(finish, id, n)
        if (status == -2):
            # Write code here
            print('The system is not safe.')
            break
        elif (status == -1):
            # Write code here.
            id=(id+1)%n
            continue
        else:
            # Write code here.
            k=0
            for j in range(m):
                if need[pid][j]<=work[j]:
                    continue
                else:
                    k=1
                    break
            if k==1:
                id=(id+1)%n
            else:
                for j in range(m):
                    work[j]+=alloc[pid][j]
                finish[pid]=True
                safe[iter]=pid
                iter+=1
    return need, avail, safe


need, avail, safe = bankers(maxim, alloc, total, n, m)

printTable(maxim, alloc, need, avail)
seq = []
for i in range(0, n):
    seq.append('P'+str(safe[i]))
print('\nSafe Seequence is : ',tuple(seq))
