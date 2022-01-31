#include <bits/stdc++.h>

using namespace std;

int binary_search(int arr[], int goal, int low, int high) {
  while (low != high) {
    int mid = (low + high) / 2;
    if (arr[mid] <= goal) {
      high = mid;
    } else {
      low = mid+1;
    }
  }
  if (arr[low] == goal)
    return low;
  return -1;
}

int main() {
  int m, n;
  scanf("%d%d", &m, &n);
  int a[m];
  for (int i = 0; i < m; i++)
    scanf("%d", a + i);

  int left_arr[m+1];
  left_arr[0] = 0;
  for (int i = 0; i < m; i++)
    left_arr[i+1] = left_arr[i] + a[i];
  int right_arr[m+1];
  right_arr[m] = 0;
  for (int i = m - 1; i >= 0; i--)
    right_arr[i] = right_arr[i+1] + a[i];

  while (n--) {
    int q;
    scanf("%d", &q);
    bool found = false;
    for (int i = m; i >= 0; i--) {
      int find = q - right_arr[i];
      if (find < 0)
        break;
      if (find == 0) {
        found = true;
        break;
      }
      //int attempt = binary_search(right_arr, find, i+1, m-1);
      if (binary_search(left_arr, left_arr + i, find)) {
        found = true;
        break;
      }
    }

    if (found)
      printf("Yes\n");
    else
      printf("No\n");
  }
}
