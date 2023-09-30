def make_change(amount):
    """
    for a given amount, returns a dictionary containing the smallest number of bills and
    coins that add up to that number.
    """
    ans = {}
    deno = [100,50,20,10,5,2,1,0.25,0.1,0.05,0.01]
    for i in deno:
        n = int(amount // i)
        amount = round(amount % i,2)
        if n != 0:
            ans[round(float(i),2)] = n
    return ans
    

def print_change(change):
    """
    function print_change that prints the 
    change in order of the descending denomination and their corresponding amount.
    The parameter to this function will be the dictionary that is the result
    of make_change.
    """
    for (k,v) in change.items():
        print("${:.2f}: {:d}".format(k,v))
