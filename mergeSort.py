'''
    Syntax: merge(Merging array, Array 1, Array 2)
        
    There are 5 cases that are covered
    1. arr1 < arr2

    2. arr2 < arr1

    3. arr1 == arr2

    4. arr1 is fully scanned

    5. arr2 is fully scanned

    Case 1, 2 & 3 are covered in a while loop
    Case 4 & 5 is covered in the if else block

'''

def merge(arrMain, arr1, arr2):
    i = j = 0 # variable i is for arr1
              # variable j is for arr2

    ########### while loop ############
    while i != len(arr1) and j != len(arr2):
        if arr1[i] < arr2[j]:
            arrMain.append(arr1[i])
            i += 1
        elif arr2[j] < arr1[i]:
            arrMain.append(arr2[j])
            j += 1
        elif arr1[i] == arr2[j]:
            arrMain.append(arr1[i])
            arrMain.append(arr2[j])
            i += 1
            j += 1
        else:
            print("Erroe in Merge While Loop!!")
    
    ############ array extension if else ###############
    if i == len(arr1):
            arrMain.extend(arr2[j:])
    elif j == len(arr2):
            arrMain.extend(arr1[i:])
    else :
        print("Error in Merge array extension")

'''
    Syntax: sort(list to be sorted)

    Base Case:
    if length if sort_this == 1
    return sort_this 

    General Case:
    define new_list
    pass the new_list, send sorted first half of sort_this and sorted second half of sort_this seperately to the merge function
    return new_list 
'''
def sort(sort_this):
    if len(sort_this) == 1:
        return sort_this
    else:
        new_list = []
        merge(new_list, sort(sort_this[:len(sort_this)//2]), sort(sort_this[len(sort_this)//2:]))
        return new_list




#lst_new = []
lst = list(map(int, input("Type number with space: ").split()))

#merge(lst_new, lst[:len(lst)//2], lst[len(lst)//2:])

print(sort(lst))





