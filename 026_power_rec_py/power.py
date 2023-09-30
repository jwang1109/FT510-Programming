def power(x,y):
    if y < 0:
        print("y should be a positive integrer")
        return
    if y==0:
        return 1
    return x*power(x,y-1)
