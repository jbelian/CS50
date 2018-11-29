import cs50

while True:
    h = cs50.get_int("Height: ")
    if h >= 0 and h <= 23:
        break
for x in range(h):
    print(" " * (h - x - 1), end="")
    print("#" * (x + 1), end="")
    print("  ", end="")
    print("#" * (x + 1))