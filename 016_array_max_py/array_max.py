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
        
    """
    Finds the largest number in the list.
    Ignores elements that are not an int or a float

    Args:
        array (list): list of numbers (either float or int)

    Returns:
    Largest number in the list.  None if array is empty
    or if array is not a list.
    """

def do_test(array):
    print("{}: {}".format(array,array_max(array)))

array1 = [ 77, 33, 19, 99, 42, 6, 27, 4 ]
array2 = [ -3, -42, -99, -1000, -999, -88, -77 ]
array3 = [ 425, 59, -3, 77, 0, 36]
array4 = ["string"]
array5 = [45.2, "string", 3, 0, "test"]

do_test(array1)
do_test(array2)
do_test(array3)
do_test("string passed")
do_test([])
do_test(array4)
do_test(array5)
