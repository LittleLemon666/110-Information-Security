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
        
    for a in range(2, test_x):
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