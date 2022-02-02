primes = []
for i in range(2, 101):
    is_prime = True
    for j in range(2, i):
        if i % j == 0:
            is_prime = False
    if is_prime:
        primes.append(i)

n = int(input())
my_num = 1
index = 0
for p in primes:
    if p * my_num <= n:
        index += 1
        my_num *= p

ep = 1
for i in range(index):
    ep *= primes[i] - 1
numerator = my_num - ep

def gcd(a, b):
    return a if b == 0 else gcd(b, a % b)

common = gcd(my_num, numerator)
print(f'{numerator//common}/{my_num//common}')
