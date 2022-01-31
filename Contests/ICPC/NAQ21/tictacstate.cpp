#include <bits/stdc++.h>

using namespace std;

bool is_set(int num, int bit) {
  return num & (1 << bit);
}

int get_win(int num, int i, int j, int k) {
  if (is_set(num, i) && is_set(num, j) && is_set(num, k)) {
    if (is_set(num, i + 9) == is_set(num, j + 9) && is_set(num, j + 9) == is_set(num, k + 9)) {
      if (is_set(num, i + 9))
        return 2;
      else
        return 1;
    }
  }
  return 0;
}

void update_victor(int i, bool &someone_won, bool &x_won) {
  if (i > 0)
    someone_won = true;
  if (i == 1)
    x_won = false;
  if (i == 2)
    x_won = true;
}

int main() {
  int c;
  cin >> c;
  while (c--) {
    int num = 0;
    string s;
    cin >> s;
    for (int i = 0; i < (int) s.size(); i++) {
      num *= 8;
      num += s[i] - '0';
    }

    bool someone_won = false;
    bool x_won = false;
    // Horizontal
    int h1 = get_win(num, 0, 1, 2);
    update_victor(h1, someone_won, x_won);
    int h2 = get_win(num, 3, 4, 5);
    update_victor(h2, someone_won, x_won);
    int h3 = get_win(num, 6, 7, 8);
    update_victor(h3, someone_won, x_won);
    //Vertical
    int v1 = get_win(num, 0, 3, 6);
    update_victor(v1, someone_won, x_won);
    int v2 = get_win(num, 1, 4, 7);
    update_victor(v2, someone_won, x_won);
    int v3 = get_win(num, 2, 5, 8);
    update_victor(v3, someone_won, x_won);
    //Diagnal
    int d1 = get_win(num, 0, 4, 8);
    update_victor(d1, someone_won, x_won);
    int d2 = get_win(num, 2, 4, 6);
    update_victor(d2, someone_won, x_won);

    bool is_cat = false;
    if (!someone_won) {
      is_cat = true;
      for (int i = 0; i < 9; i++) {
        if (!is_set(num, i)) {
          is_cat = false;
        }
      }
    }

    if (someone_won) {
      if (x_won) {
        cout << "X wins" << endl;
      } else {
        cout << "O wins" << endl;
      }
    } else if (is_cat) {
      cout << "Cat's" << endl;
    } else {
      cout << "In progress" << endl;
    }
  }
}
