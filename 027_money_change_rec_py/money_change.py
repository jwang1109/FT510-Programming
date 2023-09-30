def make_change(amount):
    """
    for a given amount, returns a dictionary containing the smallest number of bills and
    coins that add up to that number.
    """
    deno = [100,50,20,10,5,2,1,0.25,0.1,0.05,0.01]
    if amount < 0.01:
        ans = {}
        return ans
    for i in deno:
        n = int(amount //i)
        if n != 0:
            amount = round(amount % i,2)
            ans = make_change(amount)
            ans[round(float(i),2)] = n
            break
    return ans


def print_change(change):
    """
    function print_change that prints the 
    change in order of the descending denomination and their corresponding amount.
    The parameter to this function will be the dictionary that is the result
    of make_change.
    """
    n = len(change)
    c_items = list(change.items())
    for i in range(n-1,-1,-1):
        print("${:.2f}: {:d}".format(c_items[i][0],c_items[i][1]))
    
