import sys
from sys import argv

def read_key_values(filename):
    """
    Reads a key-value delimited file (separated by first =) into a dictionary

    Args:
    filename(str): name of the file to read
    
    Returns:
    dictionary of the read items
    """
    ans = {}
    f = open(filename,"r")
    for line in f:
        sep_idx = line.find("=")
        if sep_idx != -1:
            ans[line[0:sep_idx]] = line[sep_idx+1:-1]
    f.close()
    return ans
        
def create_output_filename(name):
    """
    create the output file name.  Given an input filename such as "input.txt",
    return "input.txt.counts"
    """
    suffix = ".counts"
    return name+suffix
    
    


def process_key_file(filename,key_values):
    """
    Loads in a key file and produces a dictionary of the count of the values 
    If a key is not found in key_values use "<unknown>"

    Args:
    filename(str): file containing keys to process
    key_values(dict): existing keys to load
    """
    #read lines
    lines = []
    f = open(filename,"r")
    for line in f:
        line = line.replace("\n","")
        lines.append(line)
    f.close()
    #initialize dict
    ans = {}
    for line in lines:
        if key_values.get(line) == None :
            ans["<unknown>"] = 0
        else:
            ans[key_values[line]] = 0
    #start counting
    for line in lines:
        if key_values.get(line) == None:
            ans["<unknown>"] += 1
        else:
            ans[key_values[line]] += 1
    return ans
        
        
        

def write_output(filename,counts):
    """
    Sort the output value the highest count descending. If two values are
    equal, arbitrarily choose 1
    """
    counts = sorted(counts.items(), key = lambda kv:kv[1],reverse = True)
    f = open(filename,"w")
    for i in counts:
        k = i[0]
        v = i[1]
        f.write("{}: {}\n".format(k,v))
    f.close()
    


def process(args):
    """
    Implement your algorithm in this function
    """
    # print(args)   #Uncomment if you want to validate/see the command-line arguments
    kv_fname = args[1]
    kvs = read_key_values(kv_fname)
    for i in args[2:]:
        counts = process_key_file(i,kvs)
        output_filename = create_output_filename(i)
        write_output(output_filename,counts)
        
    
    
    
    
    
    
    
 

# __name__ == "__main__" and argv explained in the "modules" notebook
if __name__ == "__main__":
    if len(argv) < 3:
        print("Usage: python3 key_value.py file1_name file2_name ...")
        sys.exit(-1)
    process(argv)
