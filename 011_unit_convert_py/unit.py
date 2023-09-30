def convert_mass(weight,fro,to):
    """
    a dictionary where you store different units
    """
    dic_1 = {"Kilogram":1
            ,"Pound":0.453592
            ,"Stone":6.35029
            ,"Jin":0.5
            ,"Seer":1.25
            ,"Gram":0.001
            ,"Oka":1.2829
            }
    '''convert'''
    return dic_1[fro]*weight/dic_1[to]
    
