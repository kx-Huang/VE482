#include <iostream>
using namespace std;

#define PROCESS_CNT 5  // Number of processes
#define RESOURCE_CNT 3 // Number of resources

int alloced[PROCESS_CNT][RESOURCE_CNT] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

int maximum[PROCESS_CNT][RESOURCE_CNT] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

int available[RESOURCE_CNT] = {3, 3, 2};

int main() {
  int i, j, k, l;
  bool safe = false;
  int finish[PROCESS_CNT], ans[PROCESS_CNT], ind = 0;
  for (k = 0; k < PROCESS_CNT; k++) {
    finish[k] = 0;
  }
  int request[PROCESS_CNT][RESOURCE_CNT];
  for (i = 0; i < PROCESS_CNT; i++) {
    for (j = 0; j < RESOURCE_CNT; j++)
      request[i][j] = maximum[i][j] - alloced[i][j];
  }
  for (k = 0; k < PROCESS_CNT; k++) {
    safe = false;
    for (i = 0; i < PROCESS_CNT; i++) {
      if (finish[i] == 0) {
        bool found = true;
        for (j = 0; j < RESOURCE_CNT; j++) {
          if (request[i][j] > available[j]) {
            found = false;
            break;
          }
        }
        if (found) {
          safe = true;
          ans[ind++] = i;
          for (l = 0; l < RESOURCE_CNT; l++)
            available[l] += alloced[i][l];
          finish[i] = 1;
          break;
        }
      }
    }
    if (safe == false) break;
  }
  if (safe == false)
    cout<<"The system is unsafe."<<endl;
  else {
    cout << "The system is safe." << endl;
    for (i = 0; i < PROCESS_CNT - 1; i++)
      cout << " P" << ans[i] + 1 << " ->";
    cout << " P" << ans[PROCESS_CNT - 1] + 1 << endl;
  }
  return 0;
}