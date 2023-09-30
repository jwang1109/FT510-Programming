p =float(input("How many hours did the employee work?"))
r = float(input("What is the employee's pay rate?"))
if p > 40:
    total_pay = 40*r+(p-40)*r*1.5
else:
    total_pay = p*r
tax = total_pay * 0.2
net_pay = total_pay-tax

print("Total pay:",total_pay)
print("Taxes:",tax)
print("Net pay:", net_pay)                      
