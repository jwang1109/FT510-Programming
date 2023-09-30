
def compute(start_age, initial_savings, info):
    curr_age = start_age
    curr_savings = initial_savings
    for i in range(info["months"]):
        curr_age_year = curr_age // 12
        curr_age_month = curr_age % 12
        print("Age  {} month{:3} you have ${:,.2f}".format(curr_age_year,curr_age_month,curr_savings))
        curr_savings =  curr_savings * (1+info["rate_of_return"]) + info["contribution"]
        curr_age += 1
    return curr_savings


def retirement(start_age, initial_savings, working_info,retired_info):
    """
    Prints the current status of an individual's retirement account.
    The dictionaries both have these fields: 
        "months","contribution","rate_of_return"

    Args:
       start_age (int): At what age (in months) does the individual start
       initial_savings (float): initial savings in dollars
       working_info (dict): information about working
       retired_into (dict): information about retirement

    Returns:
    None
    """

    #working
    curr_savings = compute(start_age,initial_savings,working_info)
    #retiring
    retire_start_age = start_age + working_info["months"]
    curr_savings = compute(retire_start_age,curr_savings,retired_info)
    return;
    



working_info = {"months":489,"contribution":1000,"rate_of_return":0.045/12}
retired_info = {"months":384,"contribution":-4000,"rate_of_return":0.01/12}
retirement(327,21345,working_info,retired_info)
