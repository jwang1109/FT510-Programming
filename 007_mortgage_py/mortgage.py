p = float(input("What is the amount borrowed?"))
r = float(input("What is the annual interest rate - express this as a decimal such as 0.07 for 7%?"))
r = r/12
n = 360
A = (p*r*(1+r)**n)/((1+r)**n - 1)
payment_amount = int(A*100)/100
print(payment_amount)
