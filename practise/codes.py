def Encrypted(num:int):
    #Put you anwser here
    # Extract every digit
    d1 = num // 1000
    d2 = (num // 100) % 10
    d3 = (num // 10) % 10
    d4 = num % 10

    # Transform each digit by adding 3 and mod 9
    new_d1 = (d1 + 3) % 9
    new_d2 = (d2 + 3) % 9
    new_d3 = (d3 + 3) % 9
    new_d4 = (d4 + 3) % 9

    # Swap the digits according to the specified pattern
    cracked = f"{new_d3}{new_d4}{new_d1}{new_d2}"

    return cracked
num = int(input("Enter the encrypted number: "))
print(Encrypted(num))