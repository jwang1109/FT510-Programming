def compute_average(l):
    """
    Computes the average of list, ignoring any entries that 
    are not numbers (floats or ints)

    Args:
    l(list): list of items to compute the average
 
    returns:
    average of the numbers in the list
    
    raises:
    ValueError if the argument is not a list or if the list does not contain any numbers
    """
    # TODO: Implement Function
    total = 0
    n = 0
    if isinstance(l,list) != True:
        raise ValueError("Input is not a list")
    for i in l:
        if type(i) == int or type(i) == float:
            total += i
            n += 1
    if n == 0:
        raise ValueError("The list does not contain any numbers")
    return total/n
