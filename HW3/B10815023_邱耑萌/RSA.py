import argparse
import random

def doSquareAndMultiply(x, H, n):
    y = 1
    H = bin(int(str(H), base=10))[2:]
    for Hi in H:
        y = y ** 2 % n
        if Hi == '1':
            y = x * y % n
    return y

#print(doSquareAndMultiply(2, 32, 5487)) #3536

def doMillerRabinTest(x):
    if x % 2 == 0:
        return False
    
    test_x = x - 1
    m = 1
    for k in range(1, 1024):
        if test_x % (2 ** k) == 0:
            m = test_x // (2 ** k)
            break
        
    a = random.randint(2, test_x)
    b = doSquareAndMultiply(a, m, x)
    if b != 1 and b != test_x:
        i = 1
        while i < k and b != test_x:
            b = b ** 2 % x
            if b == 1:
                return False
            i += 1
        if b != test_x:
            return False
    return True

# for i in range(3, 100):
#     if doMillerRabinTest(i):
#         print(i)

def generateRandomKey(bit):
    x = ''
    for i in range(bit):
        x += random.choice(["0", "1"])
    return x

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-i", "--generateKey", action="store_true",
						help="generate Keys")

    args = parser.parse_args()

    if args.generateKey:
        p = ''
        q = ''
        p_int = 0
        q_int = 0
        while True:
            p = generateRandomKey(512)
            p_int = int(str(p), base=2)
            if doMillerRabinTest(p_int):
                break
        while True:
            q = generateRandomKey(512)
            q_int = int(str(q), base=2)
            if doMillerRabinTest(q_int):
                break
        
        n_int = p_int * q_int
        print("p = " + str(p_int))
        print("q = " + str(q_int))
        print("N = " + str(n_int))