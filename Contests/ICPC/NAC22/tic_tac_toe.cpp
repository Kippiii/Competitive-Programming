#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>

ii sum(ii a, ii b) {
    return ii(a.first + b.first, a.second + b.second);
}

int get_num(char c) {
    if (c == '.')
        return 0;
    if (c == 'X')
        return 1;
    if (c == 'O')
        return 2;
}

char is_won(string game) {
    // Row victory
    for (int i = 0; i < 9; i += 3) {
        if (game[i] != '.' && game[i] == game[i+1] && game[i+1] == game[i+2])
            return game[i];
    }

    // Col victory
    for (int i = 0; i < 3; i++) {
        if (game[i] != '.' && game[i] == game[i+3] && game[i+3] == game[i+6])
            return game[i];
    }

    // Diag victory
    if (game[0] != '.' && game[0] == game[4] && game[4] == game[8])
        return game[0];
    if (game[2] != '.' && game[2] == game[4] && game[4] == game[6])
        return game[2];

    return 0;
}

ii memo[3][3][3][3][3][3][3][3][3];
ii solve(string game, bool x_turn) {
    ii *m = &memo[get_num(game[0])][get_num(game[1])][get_num(game[2])][get_num(game[3])][get_num(game[4])][get_num(game[5])][get_num(game[6])][get_num(game[7])][get_num(game[8])];
    if ((*m).first != -1)
        return *m;

    char won = is_won(game);
    if (won == 'X') {
        *m = ii(1, 0);
        return *m;
    }
    if (won == 'O') {
        *m = ii(0, 1);
        return *m;
    }
    
    char move = x_turn ? 'X' : 'O';
    ii wins = ii(0, 0);
    for (int i = 0; i < 9; i++) {
        if (game[i] == '.') {
            string new_game = game.substr(0, i) + move + game.substr(i+1, 9 - i - 1);
            wins = sum(wins, solve(new_game, !x_turn));
        }
    }

    *m = wins;
    return wins;
}

int main() {
    for (int i0 = 0; i0 < 3; i0++) {
        for (int i1 = 0; i1 < 3; i1++) {
            for (int i2 = 0; i2 < 3; i2++) {
                for (int i3 = 0; i3 < 3; i3++) {
                    for (int i4 = 0; i4 < 3; i4++) {
                        for (int i5 = 0; i5 < 3; i5++) {
                            for (int i6 = 0; i6 < 3; i6++) {
                                for (int i7 = 0; i7 < 3; i7++) {
                                    for (int i8 = 0; i8 < 3; i8++){
                                        memo[i0][i1][i2][i3][i4][i5][i6][i7][i8] = ii(-1, -1);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    solve(".........", true);

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;

        ii ans = memo[get_num(s[0])][get_num(s[1])][get_num(s[2])][get_num(s[3])][get_num(s[4])][get_num(s[5])][get_num(s[6])][get_num(s[7])][get_num(s[8])];
        printf("%d %d\n", ans.first, ans.second);
    }
}