import sys
from sys import argv
import pdb
    
def check_date(yearmonth,sig):
    """
    if sig = 1, checking the start month and end month in command line
    If sig = 2, f should be S&P data.
    If sig = 3, f should be bond data, 
    """
    try:
        ym = yearmonth.split(".")
        if len(ym) != 2:
            raise ValueError("Year formatting is incorect")
        if len(ym[0]) != 4:
            raise ValueError("Year digits is not 4")
        if len(ym[1]) != 2:
            raise ValueError("Month digits is not 2")
        y = int(ym[0])
        m = int(ym[1])
        if m < 1 or m > 12:
            raise ValueError("Month should between 01 and 12")
        if y < 0:
            raise ValueError("Year should be non-negative")
    except Exception as e:
        print(e)
        sys.exit(sig)

        
def check_input_date(sp_data,bond_data,start_month,end_month):
    check_date(start_month,1) #input check
    check_date(end_month,1) # input check
    try:
        if (start_month < sp_data[0][0] and start_month < bond_data[0][0]) or (end_month > sp_data[-1][0] and end_month > bond_data[-1][0]):
            exit_code = 1
            raise ValueError("Start month or End month exceeds data scope")
        if start_month < sp_data[0][0]:
            exit_code = 2
            raise ValueError("Start month is earlier than the start month of SP data")
        if end_month > sp_data[-1][0]:
            exit_code = 2
            raise ValueError("End month is later than the end month of SP data")
        if start_month < bond_data[0][0]:
            eixt_code = 3
            raise ValueError("Start month is earlier than the start month of Bond data")
        if end_month > bond_data[-1][0]:
            exit_code = 3
            raise ValueError("End month is later than the end month of Bond data")
    except Exception as e:
        print(e)
        sys.exit(exit_code)

        
def check_type_valuescope(data, sig):
    """
    If sig = 2, f should be S&P data.
    If sig = 3, f should be bond data, 
    """            
    if sig == 2:
        for line in data:
            if len(line) != 3:
                print("The number of elements per line in S&P data is not 3")
                sys.exit(sig)
            if line[1] < 0 or line[2] < 0:
                print("Index level and dividend should be non-negative")
                sys.exit(sig)
            check_date(line[0],sig)
    if sig == 3:
        for line in data:
            if len(line) != 2:
                print("The number of elements per line in bond data is not 2")
                sys.exit(sig)
            if line[1] < 0:
                print("Bond rate of return should be non-negative")
                sys.exit(sig)
            check_date(line[0],sig)

def check_unconsecutive(data,sig):
    """
    If sig = 2, f should be S&P data.
    If sig = 3, f should be bond data, 
    """
    last_month = float(data[0][0]) - 0.01
    for line in data:
        delta = round(float(line[0]) - last_month,2)
        if delta == 0.01 or delta == 0.89:
            pass
        else:
            print("Find unconsecutive data in {}th args".format(sig))
            sys.exit(sig)
        last_month = float(line[0])
    
def read_csv(f,sig):
    """
    If sig = 2, f should be S&P data.
    If sig = 3, f should be bond data, 
    """
    # 1.Open file
    try: # TESTCASE:failed to open file
        f = open(f,"r")
    except Exception as e:
        print(e)
        sys.exit(sig)
    # 2.Read contents into ans
    ans = []
    try:
        for line in f:
            line = line.strip()
            l = line.split(",")
            if l[0] == "Date":
                continue
            l[1] = float(l[1]) / 100
            if sig == 2:
                l[2] = float(l[2]) / 100 
            ans.append(l)
    except Exception as e:
        print(e)
        sys.exit(sig)        
    if ans == []:# TESTCASE:file is empty
        print("File is empty")
        sys.exit(sig)
    #3.check type and value scope
    check_type_valuescope(ans,sig)
    #4.check for unconsecutive month
    check_unconsecutive(ans,sig)
    f.close()
    return ans


def find_data(data, start_month,end_month):
    """
    Find data between start_month to end month from the raw data
    """
    ans = []
    for i in data:
        if start_month <= i[0] <= end_month:
            ans.append(i)
    return ans

def strategy_one(sp_pro):
    ans = []
    balance = 0
    contribution = 100
    previous_month = ["",sp_pro[0][1], None]
    
    for i in sp_pro:
        # Increase contribution by 2.5% per year
        if previous_month[0][-2:] =='12' and i[0][-2:] == '01':
            contribution *= 1.025            
        #calculate result
        sp_ror = (i[1] / previous_month[1]) -1
        div_ror = i[2] / 12 / i[1]
        portf_ror = sp_ror + div_ror
        balance = balance + portf_ror * balance + contribution
        #update return, which is "ans" and reset value for loop
        ans.append([i[0],balance])
        previous_month = i

    return ans


def strategy_two(bd_pro):    
    ans = []
    balance = 0
    contribution = 100
    previous_month = ["", bd_pro[0][1], None]
    
    for i in bd_pro:
        # Increase contribution by 2.5% per year
        if previous_month[0][-2:] == '12' and i[0][-2:] == '01':
            contribution *= 1.025
        #calculate result    
        bd_ror = i[1]/12
        balance = balance + bd_ror * balance + contribution
        #update
        ans.append([i[0],balance,2])
        previous_month = i

    return ans

def concat_data(sp_pro,bd_pro):
    """
    Combine processed S&P data and processed bond data
    Return the combined processed data.
    0:year, 1:sp_index 2:sp_dividend 3:bd_percentage
    """
    ans = []
    n = 0
    for i in sp_pro:
        if i[0] == bd_pro[n][0]:
            i.append(bd_pro[n][1])
            ans.append(i)
        n += 1
    return ans

def strategy_three(cbnd_pro):
    ans = []
    balance = 0
    contribution = 100
    allocation = 1
    previous_month = ["", cbnd_pro[0][1], None, None]
    for i in cbnd_pro:
        # 1.Increase contribution by 2.5% per year,decrease allocation by 2 percentage points
        if previous_month[0][-2:] == '12' and i[0][-2:] == '01':
            contribution *= 1.025
            allocation -= 0.02
        # 2.calculate sp and bd_ror
        sp_ror = (i[1] / previous_month[1]) -1
        div_ror = i[2] / 12 / i[1]
        portf_ror = sp_ror + div_ror    
        bd_ror = i[3]/12
        # 3.calculate balance
        balance = balance * (1+portf_ror) * allocation + balance * (1+bd_ror) *(1-allocation) + contribution         
        # 4.update
        ans.append([i[0],balance])
        previous_month = i
        
    return ans

def concat_ans(ans_one,ans_two,ans_three):
    #  Concat three answers into one list
    total_ans = []
    n = 0
    for i in ans_one:
        if i[0] == ans_two[n][0] and i[0] == ans_three[n][0]:
            i.append(ans_two[n][1])
            i.append(ans_three[n][1])
            total_ans.append(i)
        n += 1
    return total_ans

def write_output(total_ans):
    f_name = "portfolio.csv"
    f = open(f_name, "w")
    f.write("Date,StrategyOne,StrategyTwo,StrategyThree\n")# header
    for i in total_ans:
        f.write("{},{:.2f},{:.2f},{:.2f}\n".format(i[0],i[1],i[2],i[3]))
    f.close()
    

def process(args):
    # 1. read csv file; input start and end of date 
    sp_data = read_csv(args[1],sig = 2)
    bd_data = read_csv(args[2],sig = 3)
    start_month , end_month  = args[3] , args[4]
    check_input_date(sp_data,bd_data,start_month,end_month)
    # 2.process data and get answer
    sp_pro, bd_pro = find_data(sp_data,start_month,end_month), find_data(bd_data,start_month,end_month)
    cbnd_pro = concat_data(sp_pro,bd_pro)#Index of list 0:year, 1:sp_index 2:sp_dividend 3:bd_percentage    
    ans_one, ans_two, ans_three = strategy_one(sp_pro), strategy_two(bd_pro), strategy_three(cbnd_pro)
    total_ans = concat_ans(ans_one, ans_two,ans_three)
    # 3.write output
    write_output(total_ans)

    
if __name__ == '__main__':
    if len(argv) != 5:
        print("Usage: retirement.py sp_data bond_dat start_month end_month")
        sys.exit(1)

    if argv[4] <= argv[3]:
        print("End date is before or equals to start date")
        sys.exit(1)
        
    process(argv)
