def doSquareAndMultiply(x, H, n):
    y = 1
    H = bin(int(str(H), base=10))[2:]
    for Hi in H:
        y = y ** 2 % n
        if Hi == '1':
            y = x * y % n
    return y

#print(doSquareAndMultiply(2, 32, 5487)) #3536