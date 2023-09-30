def print_receipt(subtotal, tax_rate, tip_rate):
    """
    This function prints out a receipt
    """
    tax = subtotal * tax_rate
    tip = subtotal * tip_rate
    total = subtotal + tax + tip
    print("Subtotal: ${:>10.2f}".format(subtotal))
    print("     Tax: ${:>10.2f}".format(tax))
    print("     Tip: ${:>10.2f}".format(tip))
    print("           "+"="*10)
    print("   Total: ${:>10.2f}".format(total))


    
