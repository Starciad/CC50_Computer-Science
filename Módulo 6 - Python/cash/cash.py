from cs50 import get_float

cashTarget = 0
coinsUsedTotal = 0

while True:
    cashTarget = get_float("Enter the monetary amount: ")
    if cashTarget > 0:
        break;

cashTarget = round(cashTarget * 100)

while cashTarget > 0:
    if cashTarget >= 25:
        cashTarget -= 25

    elif cashTarget >= 10:
        cashTarget -= 10

    elif cashTarget >= 5:
        cashTarget -= 5

    else:
        cashTarget -= 1

    coinsUsedTotal += 1

print(f"{coinsUsedTotal}\n")