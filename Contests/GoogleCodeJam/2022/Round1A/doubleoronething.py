t = int(input())
for case_num in range(1, t+1):
    s = input().strip()
    mod_s = [['a', 0]]
    for c in s:
        if mod_s[-1][0] == c:
            mod_s[-1][1] += 1
        else:
            mod_s.append([c, 1])
    new_mod_s = []
    for i in range(len(mod_s)-1):
        if ord(mod_s[i][0]) < ord(mod_s[i+1][0]):
            new_mod_s.append([mod_s[i][0], mod_s[i][1]*2])
        else:
            new_mod_s.append(mod_s[i])
    new_mod_s.append(mod_s[-1])
    ans = ''.join([a[1]*a[0] for a in new_mod_s])
    print(f'Case #{case_num}: {ans}')
