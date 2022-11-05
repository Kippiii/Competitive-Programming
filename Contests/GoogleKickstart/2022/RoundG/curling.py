from math import sqrt

def dist(x, y):
    return sqrt(x*x + y*y)

def gen_dists(l):
    return sorted(list(filter(lambda d : d <= rs + rh, [dist(*p) for p in l])))

t = int(input())

for case_num in range(1, t+1):
    rs, rh = map(int, input().split())
    n = int(input())
    r = [map(int, input().split()) for _ in range(n)]
    m = int(input())
    y = [map(int, input().split()) for _ in range(m)]

    r_dists = gen_dists(r)
    y_dists = gen_dists(y)

    if len(r_dists) != 0 and (len(y_dists) == 0 or r_dists[0] < y_dists[0]):
        winner = r_dists
        sent = y_dists[0] if len(y_dists) > 0 else 999999999999999
        first = True
    else:
        winner = y_dists
        sent = r_dists[0] if len(r_dists) > 0 else 999999999999999
        first = False
    
    ans = 0
    for d in winner:
        if d < sent:
            ans += 1
        else:
            break
    
    print(f"Case #{case_num}: {ans if first else 0} {ans if not first else 0}")