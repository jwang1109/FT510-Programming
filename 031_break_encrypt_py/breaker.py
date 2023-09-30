import sys
from sys import argv

def array_max(array):

    #check if array is empty
    if array == []:
        return None
    
    #initialize max
    max = None
    #find max
    for  i in array:
        if (type(i) == int or type(i)==float):
            if max == None:
                max = i
            if i > max:
                max = i
        else:
            continue
        
    # check if no int or float in this array
    if( (type(max) != int and type(max) != float)):
        return None
    return max
        


def breaker(f):
    alphacounts = [0 for i in range(26)]
    while True:
        c = f.read(1)
        if not c: break
        
        if c.isalpha():
            c = c.lower()
            alphacounts[ord(c)-ord("a")] += 1
    max_ele = array_max(alphacounts)
    max_idx = alphacounts.index(max_ele)%26-4
    if alphacounts == [0 for i in range(26)]:
        print("Empty File")
        sys.exit(1)
    # check if no top freq    
    count = 0
    for ele in alphacounts:
        if max_ele == ele:
            count +=1
    if count > 1:
        print("No top freq")
        sys.exit(1)
    # "f" should be assigned to the 26th idx
    if max_idx < 0:
        max_idx += 26
    return max_idx
    
    

if __name__ == "__main__":
    if len(argv)!=2:
        print("Usage:python3 breaker.py input.txt")
        sys.exit(1)
    try:
        f = open(argv[1])
        if f == None:
            print("Failure to open file")
            sys.exit(1)
        print(breaker(f))
        f.close()
    except Exception as e:
        print(e)
        sys.exit(1)
    
        
