c, n = map(int, input().split())
errs = list(map(int, input().split()))

is_err = [False for _ in range(c+1)]
for e in errs:
    is_err[e] = True

my_errs = []
last_err = -2
my_corr = []
last_corr = -2
for i in range(1, c+1):
    if is_err[i]:
        if last_err + 1 == i:
            my_errs[-1][1] = i
        else:
            my_errs.append([i, i])
        last_err = i
    else:
        if last_corr + 1 == i:
            my_corr[-1][1] = i
        else:
            my_corr.append([i, i])
        last_corr = i

s1 = "Errors: "
for i in range(len(my_errs)):
    err_str = ""
    if my_errs[i][0] == my_errs[i][1]:
        err_str = f'{my_errs[i][0]}'
    else:
        err_str = f'{my_errs[i][0]}-{my_errs[i][1]}'
    if i == len(my_errs) - 1:
        s1 += err_str
    elif i == len(my_errs) - 2:
        s1 += f'{err_str} and '
    else:
        s1 += f'{err_str}, '
s2 = "Correct: "
for i in range(len(my_corr)):
    err_str = ""
    if my_corr[i][0] == my_corr[i][1]:
        err_str = f'{my_corr[i][0]}'
    else:
        err_str = f'{my_corr[i][0]}-{my_corr[i][1]}'
    if i == len(my_corr) - 1:
        s2 += err_str
    elif i == len(my_corr) - 2:
        s2 += f'{err_str} and '
    else:
        s2 += f'{err_str}, '

print(s1)
print(s2)
