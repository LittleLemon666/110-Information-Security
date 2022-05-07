import argparse
import random
import math

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

# ref: http://www-math.ucdenver.edu/~wcherowi/courses/m5410/exeucalg.html
def getInverse(a, b):
    n = a
    qs = []
    ps = [0, 1]
    
    while a % b != 0:
        q = a // b
        qs.append(q)
        c = a % b
        a = b
        b = c
    
    for q in qs:
        p = (ps[-2] - ps[-1] * q) % n
        ps.append(p)

    return ps[-1]

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-i", "--generateKey", action="store_true",
						help="generate Keys")

    args = parser.parse_args()

    if args.generateKey:
        p = ""
        q = ""
        p_int = 0
        q_int = 0
        while True:
            p = generateRandomKey(512)
            p_int = int(str(p), base=2)
            if doMillerRabinTest(p_int):
                break
        print("p = " + str(p_int))

        while True:
            q = generateRandomKey(512)
            q_int = int(str(q), base=2)
            if doMillerRabinTest(q_int):
                break
        print("q = " + str(q_int))
        
        n_int = p_int * q_int
        print("N = " + str(n_int))

        phi_int = (p_int - 1) * (q_int - 1)
        print("phi = " + str(phi_int))

        e_int = 1
        while True:
            e_int = random.randint(1, phi_int)
            if math.gcd(e_int, phi_int) == 1:
                break
        print("e = " + str(e_int))

        d_int = getInverse(phi_int, e_int)
        # d_int = 1
        # while True:
        #     if d_int * e_int % phi_int == 1:
        #         break
        #     d_int += 1
        print("d = " + str(d_int))

        # print(getInverse(26, 15))
        # print(getInverse(17057154292874573786416137216370832878255923331568688491968777491964174606144103915357047679458790950210238970919614329338702894997332516909423004970859590851807240862604269103374016916775030818039376594405393903092084221847261549853314220796140906305077747193835363974919399761405150548055795563975638189989170509882217169787924122040213011891895521152807434869658377907113668480338312088668730021775934919592754607923764284550309240321983068475422898152688355200227878273107651514618060225413717755104819123214474289780059566912891719649461957101446015460430391312502275593040230514370293398973198471214386302067776, 13917528990396924339275411885516221120850589095229318826874277468572841645135564323661648087728970528068726771274235795173298951259615001670042166851201216988968950475364457462852066951106538142652316972641859606029653598945163239453425335313742499123321547507747806575159423391695830895204292478459766829776605923983481674155054087442337307064504519060711013877412443486192854023107508922939681888911815153122956369569077332552223316436130264991608648601387435026862852798266695189075567623374896188061162569639782345555161913659286113538291477517167337581940625366752433791414045177195358639470751840986340821954703))