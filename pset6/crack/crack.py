import crypt
import itertools
import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python crack.py <hash>")
        exit()

    else:
        print("Working...")

    input_hash = sys.argv[1]
    salt = sys.argv[1][:2]

    alphabet = list(map(chr, range(97, 123))) + list(map(chr, range(65, 91)))

    for i in range(1, 6):
        for permutations in itertools.product(alphabet, repeat=i):
            unhashed = ''.join(map(str, permutations))
            check_hash = crypt.crypt(unhashed, salt)
            if input_hash == check_hash:
                print("Password:",unhashed)
                return
        print(".", end='')
    print("Not found")


if __name__ == "__main__":
    main()