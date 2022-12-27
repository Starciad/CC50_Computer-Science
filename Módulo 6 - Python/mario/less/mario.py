from cs50 import get_int

while True:
    size = get_int("Height: ")
    if 0 < size < 9:
        break

for i in range(size):
    air = size - i - 1

    for j in range(air):
        print(" ", end="")

    for k in range(i + 1):
        print("#", end="")

    print()