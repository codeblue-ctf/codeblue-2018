/*
 *  g++ watch_cats.cpp -g -m32 -o watch_cats 
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <csignal>
#include <clocale>
#include <cwchar>
#include <cassert>
#include <unistd.h>
#include <vector>
#include <queue>
using namespace std;

const int NUM_STAGE = 5;

struct joint {
  char type;
  char direction;
  int cables[4];
};

struct joint_type {
  int available[4];
  char *fonts[4];
};

int answer;
int num_cables;
int num_joints;
int num_goals;
int H;
int W;

int goals[114514];
char *fonts[100][100];
int belong[100][100];

struct joint joints[114514];
const struct joint_type joint_types[10] = {
  {{1, 1, 0, 0}, {"┗", "┛", "┓", "┏"}},
  {{0, 1, 1, 0}, {"┏", "┗", "┛", "┓"}},
  {{0, 0, 1, 1}, {"┓", "┏", "┗", "┛"}},
  {{1, 0, 0, 1}, {"┛", "┓", "┏", "┗"}},
  {{1, 0, 1, 0}, {"┃", "━", "┃", "━"}},
  {{0, 1, 0, 1}, {"━", "┃", "━", "┃"}},
  {{1, 1, 1, 0}, {"┣", "┻", "┫", "┳"}},
  {{0, 1, 1, 1}, {"┳", "┣", "┻", "┫"}},
  {{1, 0, 1, 1}, {"┫", "┳", "┣", "┻"}},
  {{1, 1, 0, 1}, {"┻", "┫", "┳", "┣"}},
};

int in_flow[114514];
int joints_in_flow[114514];
vector<int> connection[114514];

void handler(int num) {
  puts("Time is up!");
  exit(0);
}

void load_stage_information(int idx) {
  char fname[100];
  snprintf(fname, 50, "stage%02d.txt", idx);

  FILE *fp = fopen(fname, "rb");
  if (fp == NULL) {
    puts("[*] Something went wrong... Please contact the admin if you are encountring this repeatedly.");
    exit(-1);
  }

  fscanf(fp, "%d", &answer);
  fscanf(fp, "%d", &num_cables);
  for (int i=0; i<num_cables; i++) {
    connection[i].clear();
  }

  fscanf(fp, "%d", &num_joints);
  for (int i=0; i<num_joints; i++) {
    int type;
    fscanf(fp, "%d", &type);
    assert(0 <= type && type < 10);
    joints[i].type = type;
    joints[i].direction = 0;
    for (int j=0; j<4; j++) {
      int v;
      fscanf(fp, "%d", &v);
      joints[i].cables[j] = v;
      if (v != -1) {
        assert(0 <= v && v < num_cables);
        connection[v].emplace_back(i);
      }
    }
  }

  fscanf(fp, "%d", &num_goals);
  for (int i=0; i<num_goals; i++) {
    fscanf(fp, "%d", &goals[i]);
    assert(0 <= goals[i] && goals[i] < num_cables);
  }

  fscanf(fp, "%d", &H);
  fscanf(fp, "%d", &W);
  for (int i=0; i<H; i++) {
    for (int j=0; j<W; j++) {
      fscanf(fp, "%d", &belong[i][j]);
    }
  }

  char buf[100];
  fgets(buf, sizeof(buf), fp);
  for (int i=0; i<H; i++) {
    for (int j=0; j<W; j++) {
      fgets(buf, sizeof(buf), fp);
      *strchr(buf, '\n') = '\0';
      fonts[i][j] = strdup(buf);
    }
  }
}

int show_circuit(void) {
  fill(in_flow, in_flow+num_cables, 0);
  fill(joints_in_flow, joints_in_flow+num_joints, 0);
  
  queue<int> q;
  q.push(0);
  in_flow[0] = 1;
  while (!q.empty()) {
    int v = q.front(); q.pop();

    for (int idx : connection[v]) {
      struct joint &jo = joints[idx];
      const struct joint_type &ty = joint_types[jo.type];

      int k;
      for (k=0; k<4; k++) {
        if (jo.cables[k] == v) break;
      }

      jo.direction %= 4;
      char dir = jo.direction;
      if (!ty.available[(k+dir)%4]) continue;

      joints_in_flow[idx] = 1;
      for (int i=0; i<4; i++) {
        if (i == k) continue;
        if (jo.cables[i] == -1) continue;

        if (ty.available[(i+dir)%4]) {
          int u = jo.cables[i];

          if (!in_flow[u]) {
            in_flow[u] = 1;
            q.push(u);
          }
        }
      }
    }
  }
  
  puts("");
  for (int i=0; i<H; i++) {
    for (int j=0; j<W; j++) {
      int grp;
      int show_in_blue = 0;
      if (belong[i][j] > 0) {
        grp = belong[i][j]-1;
        show_in_blue = in_flow[grp];
      } else if (belong[i][j] < 0) {
        grp = -1-belong[i][j];
        show_in_blue = joints_in_flow[grp];
      }

      if (show_in_blue) printf("\e[34m");
      if (belong[i][j] >= 0) printf("%s", fonts[i][j]);
      else {
        struct joint &jo = joints[grp];
        size_t dir = jo.direction;
        printf("%s", joint_types[jo.type].fonts[dir%4]);
      }
      if (show_in_blue) printf("\e[0m");
    }
    puts("");
  }
  puts("");

  int ret = 1;
  for (int i=0; i<num_goals; i++) {
    ret &= in_flow[goals[i]];
  }
  return ret;
}

void show_banner() {
 puts("                                                                                                                        "); 
 puts("   ▄█     █▄     ▄████████     ███      ▄████████    ▄█    █▄          ▄████████    ▄████████     ███        ▄████████  "); 
 puts("   ███     ███   ███    ███ ▀█████████▄ ███    ███   ███    ███        ███    ███   ███    ███ ▀█████████▄   ███    ███ "); 
 puts("   ███     ███   ███    ███    ▀███▀▀██ ███    █▀    ███    ███        ███    █▀    ███    ███    ▀███▀▀██   ███    █▀  "); 
 puts("   ███     ███   ███    ███     ███   ▀ ███         ▄███▄▄▄▄███▄▄      ███          ███    ███     ███   ▀   ███        "); 
 puts("   ███     ███ ▀███████████     ███     ███        ▀▀███▀▀▀▀███▀       ███        ▀███████████     ███     ▀███████████ "); 
 puts("   ███     ███   ███    ███     ███     ███    █▄    ███    ███        ███    █▄    ███    ███     ███              ███ "); 
 puts("   ███ ▄█▄ ███   ███    ███     ███     ███    ███   ███    ███        ███    ███   ███    ███     ███        ▄█    ███ "); 
 puts("    ▀███▀███▀    ███    █▀     ▄████▀   ████████▀    ███    █▀         ████████▀    ███    █▀     ▄████▀    ▄████████▀  "); 
 puts("                                                                                                                        ");  
}

int main() {
  setbuf(stdout, NULL);

  if (signal(SIGALRM, handler) == SIG_ERR) {
    puts("[*] Something went wrong... Please contact the admin if you are encountring this repeatedly.");
    exit(-1);
  }

  show_banner();

  alarm(120);
  for (int stage=1; stage<=NUM_STAGE; stage++) {
    load_stage_information(stage);

    printf("=========================================== Stage %d ===========================================\n", stage);
    printf("Send the blue flow through the cables and joints until it reaches the end points by %d steps!\n", answer);
    show_circuit();

    int num_op;
    int passed = 0;
    for (num_op=0; num_op<answer; num_op++) {
      int idx;

      scanf("%d", &idx);
      if (idx < 0 || num_joints <= idx) {
        puts("Idiot");
        exit(0);
      }
      ++joints[idx].direction;
      
      if (show_circuit() == 1) {
        passed = 1;
        break;
      }
    }

    if (!passed) {
      puts("Failed...");
      exit(0);
    }
  }

  puts("Congratulations!");

  FILE *fp = fopen("./flag.txt", "rb");
  if (!fp) {
    puts("[*] Something went wrong... Please contact the admin if you are encountring this repeatedly.");
    exit(-1);
  }
  
  char flag[100];
  fgets(flag, sizeof(flag), fp);
  printf("Here is the flag: %s", flag);
  fclose(fp);
}
