def main():
    n = int(input("Credit card number: "))
    digits = get_digits(n)
    cardtype = get_type(n, digits)
    if checkLuhn(n, digits) == True:
        print(f"{cardtype}")
    else:
        print("ERROR")
        exit(0)


# Check for positive number of 13, 15, or 16 digits
def get_digits(n):
    d = 0
    while n > 1:
        d = d + 1
        n = n / 10
    if d == 13 or d == 15 or d == 16:
        return d
    else:
        print("INVALID")
        exit(0)


# Checks which issuer card may belong to
def get_type(n, d):
    if d == 13:
        n = n // 10**(d - 1)
        if n == 4:
            return "VISA"
    elif d == 15:
        n = n // 10**(d - 2)
        if n == 34 or n == 37:
            return "AMEX"
    elif d == 16:
        n = n // 10**(d - 2)
        if n > 50 and n < 56:
            return "MASTERCARD"
        else:
            n = n // 10
            if n == 4:
                return "VISA"
    else:
        print("INVALID")
        exit(0)


# Use Luhn's algorithm to check if this is a valid number
def checkLuhn(n, d):
    even = 0
    odd = 0
    Luhn = 0
    while n != 0:
        even = n % 10

        n = n // 10

        odd = n % 10
        odd = odd * 2
        if odd > 9:
            odd = 1 + odd % 10

        n = n // 10

        Luhn += even + odd

    if Luhn % 10 == 0:
        return True
    else:
        print("INVALID")
        exit(0)


if __name__ == "__main__":
    main()