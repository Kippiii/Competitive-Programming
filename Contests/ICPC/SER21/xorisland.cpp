#include <bits/stdc++.h>

using namespace std;

#define vi vector<int>
#define vl vector<long long>

#define max_mask 600

#define vm vector<bitset<max_mask>>

int min_set_cover(vm &groups, int index, bitset<max_mask> mask, int group_num);

int num_groups;
bitset<max_mask> best_mask;

int main() {
   int n;
   scanf("%d", &n);
   int a[n];
   for (int i = 0; i < n; i++)
      scanf("%d", a + i);

   vi groups;
   for (int i = 0; i < n; i++)
      for (int j = i+1; j < n; j++)
         for (int k = j+1; k < n; k++)
            if ((a[i] ^ a[j]) == a[k])
               groups.push_back((1 << i) | (1 << j) | (1 << k));
   num_groups = (int) groups.size();

   assert(num_groups <= max_mask);

   for (int i = 0 ; i < num_groups; i++) {
      best_mask.set(i);
   }

   vm sets;
   for (int i = 0; i < n; i++) {
      bitset<max_mask> cur_mask;
      for (int j = 0; j < num_groups; j++) {
         int group = groups[j];
         if (group & (1 << i))
            cur_mask.set(j);
      }
      sets.push_back(cur_mask);
   }

   bitset<max_mask> empty_mask;
   int ans = min_set_cover(sets, 0, empty_mask, 0);

   printf("%d\n", ans);
}

int min_set_cover(vm &sets, int index, bitset<max_mask> mask, int num_sets) {
   if (index >= (int) sets.size()) {
      if (mask == best_mask)
         return num_sets;
      return 9999999;
   }

   int ans = min(min_set_cover(sets, index+1, mask | sets[index], num_sets+1), min_set_cover(sets, index+1, mask, num_sets));
   return ans;
}
