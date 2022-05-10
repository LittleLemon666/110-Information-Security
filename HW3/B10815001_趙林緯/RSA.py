import sys
import random
import math
import base64
import binascii

def generatePrime():
    while (True):
        num = ''
        for id in range(512):
            num += random.choice(['0', '1'])
        candidate = int(num, base = 2)
        if (Miller_Rabin_Test(candidate)):
            return candidate


#referenced from https://www.geeksforgeeks.org/primality-test-set-3-miller-rabin/
def Miller_Rabin_Test(n):
    if (n <= 1):
        return False

    if n <= 3:
        return True

    if n % 2 == 0:
        return False

    d = n - 1
    while (d % 2 == 0):
        d //= 2

    for i in range(40): #cryptographically safe number = 40
        if (calculate(d, n) == False):
            return False
 
    return True


def calculate(d, n):
    # Pick a random number in [2..n-2]
    a = 2 + random.randint(1, n - 4)
 
    x = Square_and_Multiply(a, d, n)
 
    if (x == 1 or x == n - 1):
        return True

    while (d != n - 1):
        x = (x * x) % n
        d *= 2
 
        if (x == 1):
            return False
        if (x == n - 1):
            return True
 
    return False


def Square_and_Multiply(base, pow, mod):
    result = 1
    pow = bin(int(str(pow), base = 10))[1:]
    for exp in pow:
        result = (result ** 2) % mod
        if exp == '1':
            result = (base * result) % mod
    return result


def generateNumbers():
    p = generatePrime()
    print("p =", p)

    q = generatePrime()
    print("q =", q)

    n = p * q
    print("N =", n)

    phi = (p - 1) * (q - 1)
    print("phi =", phi)

    e = 1
    while True:
        e = random.randint(1, phi - 1)
        if math.gcd(e, phi) == 1:
            break
    print("e =", e)

    d = pow(e, -1, phi)
    print("d =", d)


def getNumber(msg):
    result = 0
    for letter in range(len(msg)):
        result *= 100
        if (ord(msg[letter]) >= ord('0') and ord(msg[letter]) <= ord('9')):
            result += ord(msg[letter]) - ord('0')
        elif (ord(msg[letter]) >= ord('A') and ord(msg[letter]) <= ord('Z')):
            result += 10 + (ord(msg[letter]) - ord('A'))
        elif (ord(msg[letter]) >= ord('a') and ord(msg[letter]) <= ord('z')):
            result += 36 + (ord(msg[letter]) - ord('a'))
        else: result += 63

    return result

def getString(msg):
    result = ""
    for letter in range(0, len(msg), 2):
        number = (ord(msg[letter]) - ord('0')) * 10 + ord(msg[letter + 1]) - ord('0')
        if (number >= 0 and number <= 9):
            result += chr(ord('0') + number)
        elif (number >= 10 and number <= 35):
            result += chr(ord('A') + number - 10)
        elif (number >= 36 and number <= 61):
            result += chr(ord('a') + number - 36)
        else: result += " "

    return result


def modFunction(num, mod):
    while num >= mod:
        num %= mod
    return num


if __name__ == "__main__":
    args = sys.argv[1:]
    if (args[0] == '-i'):
        generateNumbers()

    if (args[0] == '-e'):
        msg = args[1]
        N = int(args[2], base = 10)
        e = int(args[3], base = 10)
        msg = getNumber(msg)
        ciphertext = Square_and_Multiply(msg, e, N)
        base = base64.b64encode(str(ciphertext).encode('ASCII')).decode()
        print(base)

    if (args[0] == '-d'):
        msg = int(base64.b64decode(args[1]).decode('ASCII'))
        N = int(args[2], base = 10)
        d = int(args[3], base = 10)
        plaintext = Square_and_Multiply(msg, d, N)
        str_text = getString(str(plaintext))
        print(str_text)


    if (args[0] == '-CRT'):
        #referenced from https://en.wikipedia.org/wiki/RSA_(cryptosystem)
        msg = int(base64.b64decode(args[1]).decode('ASCII'))
        p = int(args[2], base = 10)
        q = int(args[3], base = 10)
        d = int(args[4], base = 10)   
        dp = modFunction(d, (p - 1))
        dq = modFunction(d, (q - 1))
        qinv = pow(q, -1, p)
        m1 = Square_and_Multiply(msg, dp, p)
        m2 = Square_and_Multiply(msg, dq, q)
        h = modFunction((qinv * (m1 - m2)), p)
        m = modFunction((m2 + h * q), (p * q))
        str_text = getString(str(m))
        print(str_text)