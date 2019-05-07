# TL; DR
This post is the retrospect of CODE BLUE CTF 2018.
Each of us has something to say.
Therefore this post would be too long, and we know some of you are not interested in it.
So, for the final score, click [here](#result).

In the following sections, we look back 1 year in chronological order.
Also what we think or what we feel strongly about, may be different, so 
we decided to write as we like, separately.

# After CODE BLUE CTF 2017
## @hugeh0ge
Just after CODE BLUE CTF 2017, we talked together, about what and how we shall do next year.
We have reached a consensus to hold this CTF again. 
To me this seems to show our regret for wasting CBCTF 2017. 
I don’t mean to brag, but last year’s problems were very good in quality. 
For all their quality, however, it was held as a weekday CTF, which has no Finals. 
Maybe we entertained only Cykor and HITCON.
Why and how CODE BLUE CTF was organized last year is [shown in my blog](http://binja.github.io/2017/11/13/Thoughts-on-CODE-BLUE-CTF-write-ups/),
and at that time I already satisfied to some extent to have realized my wish,
but if we are going to the trouble of organizing a CTF, I want it to have the Finals,
which is run in Bull’s Eye(it has no name then), I came up with a few years ago.

I told this to the other organizers. 
They showed positive responses, and their eagerness to accomplish the goal. 
Nevertheless, we didn’t give much thought yet to the details of Bull’s Eye and how we can realize its system. 
Moreover, we have to implement the whole system even if we could hammer out them. It was just an armchair plan at that time.

During the networking party, we talked about it to Kana-san, the organizer of CODE BLUE. 
Kana-san really kindly accepted our proposal. We owe the realization of CBCTF to her. 
She is absolutely a person of action(well, that should be why she can organize a large conference), 
and kind enough to have taken charge of everything except the contents of the competition, 
from site management to accommodations. Of course that includes financing. 

Without her activeness, we all, who tend to procrastinate, must have failed in our duties(like this blog post!). 
We would like to take this opportunity to express our appreciation to her.

Thus we have decided to hold CBCTF 2018. 
At this point, two things are left to be determined: the detailed rule of Bull’s Eye and how we organize Quals and Finals. 
Especially, Quals is a trouble because TokyoWesterns wants to hold their TWCTF.

# Before Quals

## @hugeh0ge
To be honest, I didn’t want to create problems.
Now that I rarely participate in CTFs, I cannot follow the trend of recent problems,
and cannot guarantee the quality of my problems. Especially I can’t stand setting low-quality problems. 
Also I consumed most of ideas in the past problem-settings and only few left in my stock.

However, as TWCTF would be held and binja was in charge of CBCTF Quals, I ended up in creating 4 problems. 
I’ll talk about it later, but I feel sad making a mistake in one problem. 
In contrast it was good to succeeded in creating the “boss” problem.

# Quals

## @hugeh0ge
The schedule conflict with Real World CTF was very unbearable to me. 
Honestly speaking, I was worried that many strong teams may not participate in our CTF because their CTF takes place on a larger scale than ours.
After all I have made the decision not to postpone our CTF, considering the fact that it was RWCTF who made the schedules overlap and that we had no other day off to hold the Quals. 
In the end this worked out. I felt relieved to see many teams taking part in both CTFs at the same time and proper teams qualified for the Finals.

By the way I talked with the admins of RWCTF in DEF CON and CODE BLUE. I never got angry about it. 

Let me leave some comments for my problems.

### [Watch Cats](https://github.com/codeblue-ctf/codeblue-2018/tree/master/problems/Quals/Watch%20Cats)
Because last year’s problems seemed too difficult for most of participants, I made up my mind to set an easy problem. For this purpose, I prepared Watch Cats.

I heartily made this problem for beginners, but the result was devastating.
Last year we regretted that we didn’t show our prediction about the difficulty of the problems to participants. We adopt dynamic scoring in CBCTF Quals for the sake of fairness, but this scoring is not beginner-friendly for they are likely not to be able to estimate difficulties. 
In such a situation, the prediction would help them, so we would like to implement it. 
Still and all we couldn’t make the prediction available this year due to lack of time. 
This may be why Watch Cats was not solved by so many players. Pity. 

Well, but considering game Revenge and Easy Example, which are described later, my difficulty prediction tends to be broken. Therefore I cannot deny the possibility of it being too hard.

You can see some write-ups of this problem uploaded:
 - http://kotarou777775.hatenablog.com/entry/2018/08/07/213911
 - https://blog.dragonsector.pl/2018/08/code-blue-ctf-2018-quals-watchcats.html
 
Nonetheless the source code was not uploaded anywhere, so I would like to give a short commentary.
In this problem, you are given a source code written in C++, its resultant binary, and 5 text files which include the stage information. You can get the flag just going clear all of the 5 stages. The game is the imitation of a minigame in Watch Dogs. [Like this](https://youtu.be/paUctg-WWc8?t=2).

As a factor of PPC, the problem requires simple brute-forcing in the first 4 stages. The challenge lies in the last stage.
The last stage is “checkmated”. I mean there is no regular way to solve this stage. Here’s pwn’s turn.

```
      scanf("%d", &idx);
      if (idx < 0 || num_joints <= idx) {
        puts("Idiot");
        exit(0);
      }
      ++joints[idx].direction;
```

Let’s focus on line 237. 
This line turns the specified joint counterclockwise, but it doesn’t take measures against integer overflow(i.e. mod 4). 
Because the type of direction is char, the value of it becomes negative when we increment it 128 times.
As a bothersome specification of C language, the modulo operator turns negative numbers into negative numbers. 
That means -5 % 4 equals -1, not 3. With this behavior, one can cause out-of-bounds read in show_circuit, which results in sending the flow to areas which are originally unreachable.
Thus one can solve this problem.

During the setting, I was careful not to make the problem require any expertise because this problem is for beginners. 
That is, this problem should be solvable only with a basic understanding of C and debugger, without ROP or heap techniques.
Easy problems, however, require only easy operations of course. 
It is possible that someone “inadvertently” solves this problem just typing random words like infinite monkey theorem. 
I didn’t want this to happen, so I elaborated the problem so that the vulnerability would rarely come out when you type randomly by hands. 
Moreover because of the same intention, I made the phases of the exploitation a bit complicated. 
Hence it may take time even after you find the vulnerability.

```
      struct joint &jo = joints[idx];
      const struct joint_type &ty = joint_types[jo.type];

      int k;
      for (k=0; k<4; k++) {
        if (jo.cables[k] == v) break;
      }

      jo.direction %= 4;
```

To be specific, the program actually does ‘direction %= 4’ in line 142. 
However this modulo operation is not appropriate, for line 142 is inside the procedure of a breadth first search. 
The BFS searches for and visits joints or cables through which the blue flow is running. 
That means the program doesn’t perform modulo operations for any joints isolated from the blue flow.

In stage 5, however, the important joint lies in the flow at the initial phase, 
so you can’t utilize the vulnerability no matter how many times you rotate only that joint, 
unless you separate it from the blue flow. This way I reduced the possibility of “inadvertence”.

### [game Revenge](https://github.com/codeblue-ctf/codeblue-2018/tree/master/problems/Quals/game%20Revenge)
As those who have solved my problems may know, the problems named “.* Revenge” are the remakes of past challenges.
The original “game” was the “boss” problem of tkbctf, held when I was a junior high school student. 
Its intended solution was just leaking the flag from the heap. Also as a dummy vulnerability, there was a stack bof, 
unusable due to stack canary.

Importantly, the problem has an extra vulnerability.
Take a look at the below snippet. Assume we can give an arbitrary path as ‘filename’. Is there any problem?

```
  FILE *fp = fopen(filename, "rb");
  long off = ftell(fp);
  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  fseek(stream, off, SEEK_SET);
  void *ptr = malloc(size + 1);
  fread(ptr, size, 1u, stream);
```

Actually this is a vulnerable procedure. Do you know named pipe?
UNIX-like operating systems have pipe named, i.e. treated as a file.
What happens if we pass it to this process?
 
Actually, ftell returns -1, and `malloc(-1+1)`=`malloc(0)` runs. Therefore malloc succeeds. fread takes its arguments as unsigned, so eventually buffer overflow occurs.

At that time almost nobody knows heap techniques, and everyone doubts whether that problem is exploitable although one can abuse heap bof. I knew it was actually possible with Master Canary Forging, but now that many other heap techniques have been explored, we can take easier approaches. For example fastbins corruption would be enough.

Thinking this way, I set this problem and got surprised to see “solved by 1”. Umm… I think this is not so difficult.
I thought 30~40 teams would solve it.

### [Something Revenge](https://github.com/codeblue-ctf/codeblue-2018/tree/master/problems/Quals/Something%20Revenge)
I just blundered. It was the first time for me to make a mistake in large contests. 
Usually I don’t insert dummy vulnerabilities in my problems, but this time I did it with fsb, 
for fear that this problem may be too easy because there was nowhere else interesting to see other than the intended vulnerability.  
The result was a catastrophe. The problem can be brought to an end just leaking the memory with fsb. 
How could you make such a mistake like noobs do?? Learn a lesson.

Then, what was the intended solution? 
Let’s take a look at the following part:

```
void myprintf(char *frmt, ...) {
  char *format = frmt;
  int i;
  int n;
  int out;
  va_list ap;
  va_start(ap, frmt);

  n = strlen(format);
  out = 0;
  for (i=0; i<n; ) {
    if (format[i] != '%') {
      write(STDOUT_FILENO, format+i, 1);
      ++i;
      ++out;
      continue;
    }

    ++i;
    if (i >= n) break;

    char c = format[i++];

    int val;
    int *ref;
    char cval;
    char digits[10];
    char *p = digits;
    switch (c) {
...
    case 'd':
      val = va_arg(ap, int);
      if (val == 0) {
        write(STDOUT_FILENO, "0", 1);
        ++out;
        break;
      }

      if (val < 0) {
        write(STDOUT_FILENO, "-", 1);
        ++out;
        val = ((unsigned int)val) ^ 0x80000000u;
      }

      while (val > 0) {
        *p = '0' + (val%10);
        val /= 10;
        ++p;
      }

      --p;
      while (1) {
        write(1, p, 1);
        ++out;
        if (p == digits) break;
        --p;
      }
      break;   
```

The process of printing numbers in myprintf has a bug: when it attempts to show INT_MIN, it infinitely prints the contents of the stack upward, as you can see from the above code.
Hence, you would like to output the memory region where the flag is mapped applying that vulnerability well.
This is really possible, but still requires some ingenious application because otherwise it doesn’t work well due to the arrangement of mappings.

Then, what we should do is to change that arrangement using ‘ulimit -s unlimited’. This technique is the same as the one needed in our problem in WCTF 2018(set by @Charo_IT).

In Linux, mmap adopts either bottom-up or top-down order to map regions. We can switch this ordering with ulimit. That is why we provided a ssh environment.

The resultant exploit is extremely simple. You only have to create a payload which causes bof and writes INT_MIN in the stack, and to run the following script:

```
ulimit -s unlimited 
./smth_revenge < ./payload | hexdump -C | grep -B 1 -A 1 FTCBC
```

This is one of my favorite problems because it doesn't require any complicated operations in an exploit
and one can easily write a simple exploit (the unintended solution is simpler though...). 

Also, the name of this problem includes “Revenge”. 
This is actually inspired by gissa, a problem of Midnight Sun CTF Finals. 
The original problem requires a totally different solution(ROP), but it has the same flaw and I thought it might be more elegant to use this flaw. 
As you may know, I like these kinds of strange problems. My strangest and most favorite one is Ninja no Aikotoba.

### [Code Blue Online Judge part2](https://github.com/codeblue-ctf/codeblue-2018/tree/master/problems/Quals/CODE%20BLUE%20Online%20Judge)
This is the boss(no one solved this problem during the contest). As much as I can’t create difficult problems anymore and would not like to do that, I was not sure whether it was no problem even if a lot of teams completed all the challenges. This is why I wanted one hard challenge at least. Well, consequently it was all in my mind, just a imaginary fear because few teams solved other problems.
 
I already came up with the idea of this problem a few years ago. Basically, retired fogy has no choice but to lean on relics of the past.
I think the idea cannot be sublimated into a problem in a better way. In fact it is probably impossible otherwise.
To such an extent, the setting is so weird. Nevertheless I saw this configuration in some language processor(besides it is used as a sandbox)....

The subject of the problem was to exploit a competitive programming system.
In competitive programming, there is a type of problems called interactive. 
One typical example is “There are Alice and Bob. Bob has some secret data. Alice is allowed to ask Bob some predefined questions. As alice, specify the secret data with Q questions”.

Usually in competitive programming, the correctness of the submission is tested by executing the submitted code with certain input data, 
and just comparing its output with the answers. 
However when it comes to interactive problems, the judge needs to implement a judge program because it has to send a response to questions posed by the submitted program. 
The theme of this problem is “what if the judge program has a vulnerability?”.

Here is a good example:
https://arc026.contest.atcoder.jp/submissions/476526

This problem has two parts: you need to exploit the web system in part 1, and the judge program in part 2. For this purpose, we(rather icchy) implemented the judge system from scratch, and (I) created a problem of competitive programming.
The problem was something just like this:

> N persons want to line up in a row. There are M constraints to be met: the i-th constraint is “the A_i-th person must be to the left of the B_i-th person”. In order to fulfill all of the M conditions, how should they line up? Answer it in the following format: 
>   There will be Q questions. The i-th question asks you “should the X_i-th person be to the left of the Y_i-th person or not?”.  If he should, then print -1. If not, then print +1.

The actual problem statement is [here](https://github.com/codeblue-ctf/codeblue-2018-problems/blob/master/Quals/CODE%20BLUE%20Online%20Judge/statement.pdf).

Competitive programmers would immediately notice this problem is just about topological sorting of a directed acyclic graph, and that the format of answering is really weird. Actually the judge program returns a verdict with the following routine:


```
int cmp(const void *ap, const void *bp, void *fp) {
  int r;
  short a = *(short *)ap;
  short b = *(short *)bp;
  struct io *iop = (struct io *)fp;

  fprintf(iop->wfp, "%hd %hd\n", a, b);
  fscanf(iop->rfp, "%d", &r);
  if (r != -1 && r != 1) exit(-1);
  
  return r;
}

int do_check(char *path, int rfd, int wfd) {
...
  for (i=0; i<N; i++) A[i] = i;
  qsort_r(A, N, sizeof(short), cmp, &fs);
  for (i=0; i<N; i++) B[A[i]] = i;
```

The judge program communicates with the submitted program using IPC, and ‘fs’ is its I/O stream. 
The judge program renders a verdict, based on the array sorted by qsort_r, which uses the output of the submitted program as the order of the elements.

Here, this is the interesting part: actually the above implementation is vulnerable.
That means the submitted program can exploit the judge program only with -1 and 1.

Ridiculous? Let’s read the source code of glibc. 
The following is _quicksort in stdlib/qsort.c:

```
void
_quicksort (void *const pbase, size_t total_elems, size_t size,
	    __compar_d_fn_t cmp, void *arg)
{
  char *base_ptr = (char *) pbase;

  const size_t max_thresh = MAX_THRESH * size;

  if (total_elems == 0)
    /* Avoid lossage with unsigned arithmetic below.  */
    return;

  if (total_elems > MAX_THRESH)
    {
      char *lo = base_ptr;
      char *hi = &lo[size * (total_elems - 1)];
      stack_node stack[STACK_SIZE];
      stack_node *top = stack;

      PUSH (NULL, NULL);

      while (STACK_NOT_EMPTY)
        {
          char *left_ptr;
          char *right_ptr;

	  /* Select median value from among LO, MID, and HI. Rearrange
	     LO and HI so the three values are sorted. This lowers the
	     probability of picking a pathological pivot value and
	     skips a comparison for both the LEFT_PTR and RIGHT_PTR in
	     the while loops. */

	  char *mid = lo + size * ((hi - lo) / size >> 1);

	  if ((*cmp) ((void *) mid, (void *) lo, arg) < 0)
	    SWAP (mid, lo, size);
	  if ((*cmp) ((void *) hi, (void *) mid, arg) < 0)
	    SWAP (mid, hi, size);
	  else
	    goto jump_over;
	  if ((*cmp) ((void *) mid, (void *) lo, arg) < 0)
	    SWAP (mid, lo, size);
	jump_over:;

	  left_ptr  = lo + size;
	  right_ptr = hi - size;

	  /* Here's the famous ``collapse the walls'' section of quicksort.
	     Gotta like those tight inner loops!  They are the main reason
	     that this algorithm runs much faster than others. */
	  do
	    {
	      while ((*cmp) ((void *) left_ptr, (void *) mid, arg) < 0)
		left_ptr += size;

	      while ((*cmp) ((void *) mid, (void *) right_ptr, arg) < 0)
		right_ptr -= size;

	      if (left_ptr < right_ptr)
		{
		  SWAP (left_ptr, right_ptr, size);
		  if (mid == left_ptr)
		    mid = right_ptr;
		  else if (mid == right_ptr)
		    mid = left_ptr;
		  left_ptr += size;
		  right_ptr -= size;
		}
	      else if (left_ptr == right_ptr)
		{
		  left_ptr += size;
		  right_ptr -= size;
		  break;
		}
	    }
	  while (left_ptr <= right_ptr);

          /* Set up pointers for next iteration.  First determine whether
             left and right partitions are below the threshold size.  If so,
             ignore one or both.  Otherwise, push the larger partition's
             bounds on the stack and continue sorting the smaller one. */

          if ((size_t) (right_ptr - lo) <= max_thresh)
            {
              if ((size_t) (hi - left_ptr) <= max_thresh)
		/* Ignore both small partitions. */
                POP (lo, hi);
              else
		/* Ignore small left partition. */
                lo = left_ptr;
            }
          else if ((size_t) (hi - left_ptr) <= max_thresh)
	    /* Ignore small right partition. */
            hi = right_ptr;
          else if ((right_ptr - lo) > (hi - left_ptr))
            {
	      /* Push larger left partition indices. */
              PUSH (lo, right_ptr);
              lo = left_ptr;
            }
          else
            {
	      /* Push larger right partition indices. */
              PUSH (left_ptr, hi);
              hi = right_ptr;
            }
        }
    }

  /* Once the BASE_PTR array is partially sorted by quicksort the rest
     is completely sorted using insertion sort, since this is efficient
     for partitions below MAX_THRESH size. BASE_PTR points to the beginning
     of the array to sort, and END_PTR points at the very last element in
     the array (*not* one beyond it!). */

#define min(x, y) ((x) < (y) ? (x) : (y))

  {
    char *const end_ptr = &base_ptr[size * (total_elems - 1)];
    char *tmp_ptr = base_ptr;
    char *thresh = min(end_ptr, base_ptr + max_thresh);
    char *run_ptr;

    /* Find smallest element in first threshold and place it at the
       array's beginning.  This is the smallest array element,
       and the operation speeds up insertion sort's inner loop. */

    for (run_ptr = tmp_ptr + size; run_ptr <= thresh; run_ptr += size)
      if ((*cmp) ((void *) run_ptr, (void *) tmp_ptr, arg) < 0)
        tmp_ptr = run_ptr;

    if (tmp_ptr != base_ptr)
      SWAP (tmp_ptr, base_ptr, size);

    /* Insertion sort, running from left-hand-side up to right-hand-side.  */

    run_ptr = base_ptr + size;
    while ((run_ptr += size) <= end_ptr)
      {
	tmp_ptr = run_ptr - size;
	while ((*cmp) ((void *) run_ptr, (void *) tmp_ptr, arg) < 0)
	  tmp_ptr -= size;

	tmp_ptr += size;
        if (tmp_ptr != run_ptr)
          {
            char *trav;

	    trav = run_ptr + size;
	    while (--trav >= run_ptr)
              {
                char c = *trav;
                char *hi, *lo;

                for (hi = lo = trav; (lo -= size) >= tmp_ptr; hi = lo)
                  *hi = *lo;
                *hi = c;
              }
          }
      }
  }
}
```

You can see the procedure like
  `while ((*cmp) ((void *) left_ptr, (void *) mid, arg) < 0)`
in some places. `cmp` is a function pointer to the comparison function, given as an argument, which means it is controlled by the output of the submitted code.
Thus, if the submitted code continue outputting -1, qsort will be at least stuck in an infinite loop. 

That is not all. Using the output as a reference, `qsort` increments/decrements pointers and manipulates the array. This shows there will be out-of-bounds read/write. Horrible!

This way, after realizing this vulnerability, you can just get RCE returning -1 and 1 appropriately(this is not so easy though I say as if everyone can do that. But if you are so strong that you can realize this fact, then you will have little difficulty in the exploitation part).

For your information, qsort_r usually doesn’t call _quicksort inside. The current implementation of glibc adopts merge sort when it can spend enough memory(though its name is “qsort”). If you imagine the algorithm of merge sort, you can see the above vulnerability cannot exist in this sorting because it doesn’t have any loops depending on the return values of the comparison function.

This means you need to cause allocations to fail in order to call _quicksort. However, this condition is actually met from the beginning.
For, the judge program uses seccomp to “securely” conduct IPC, and this makes every memory allocation in qsort considered as failed because qsort can’t retrieve the page size due to system calls prohibited . Thus qsort always uses _quicksort in this setting.

This problem is wicked in the point that inappropriate tests or fuzzings won’t reveal the vulnerability even if you suspect qsort and run experiments with a snippet. To find the vulnerability, you need to read glibc or completely imitate the judge program by reverse engineering. Well, slipshod attacks cuts no ice with the boss.

By the way, I want to say thanks to icchy of TokyoWesterns, who made CODE BLUE Online Judge part 1. I don’t know anything about web. Of course I can’t launch a contest site.


# Finals前
## @hugeh0ge
BOOM! The system development exploded! That took web guys the whole time, which led to “no web challenge”. Also, somehow crypto guys run away from their problem-setting. As a result we sent a very unbalanced problem set. It would have been better if we could prepare Bull’s Eye problems in other genres than pwn. However after all the Finals took place with 6 pwn problems(Bull’s Eye) and 1 crypto problem(Jeopardy). Bummer.

The following are the comments for my problems:

### [Fliqpy](https://github.com/codeblue-ctf/codeblue-2018/tree/master/problems/Finals/Bull's%20Eye/Fliqpy)
The source code of the problem is extremely tiny as you can see:
```
/*
 *  gcc fliqpy.c -o fliqpy 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

__attribute__((constructor))
void set_timeout(void) {
  alarm(150);
}

int main(void) {
  unsigned char *addr;
  unsigned long long int ord;

  puts("You know, actually soft error is a common phenomenon.");
  puts("It occurs with non-negligible probability, not astronomical odds.");
  puts("So this time let's see if you can exploit this only with one bit flip!");

  printf("Enter the address you want to flip: ");
  scanf("%p", &addr);
  printf("Which bit do you want to flip?: ");
  scanf("%llu", &ord);
  if (ord >= 8) {
    puts("Idiot");
    exit(0);
  }
 
  *addr ^= 1 << ord;
  exit(0);
}
```

I came up with this problem in preparation for Quals.
In a word, the summary of this problem is “You can designate one address and flip one bit. Can you exploit this?”.
The idea came from parrot, the problem of TWCTF 3rd and [rui314’s article](https://note.mu/ruiu/n/nbb7a52c374ae).

It took only 2 or 3 minutes for me to create the problem(lol), but solving this problem was more nontrivial than I had expected.
I spent half a day even to find a probabilistic solution. I was doubting if there was the perfect solution. 
In the end I left the problem unsolved, but a few months later, suddenly my teammate Bono_iPad proved that it is fully solvable. Thus the completeness was ensured. 

This way unintentionally I made a problem very suitable for the Finals, and we decided to reserve this problem.

It was good that most of the participants finally succeeded in submitting a solution. I feel like this problem shows my style of problem-setting. I don’t like problems consuming lots of time in analysis. I prefer ones time-consuming to exploit like this problem.

### [EasyExample](https://github.com/codeblue-ctf/codeblue-2018/tree/master/problems/Finals/Bull's%20Eye/Easy%20Example)
It was a month before Finals.
Suddenly I thought it might be unhelpful to prepare no exercises but Sanity Check, considering the fact that no one had ever tried Bull’s Eye.
Therefore I made up my mind to create, as a kind of Proof of Concept, a very simple and easy problem. 

As you can see, the source code is really small:
```
/*
 *  g++ easy_example.cpp -o easy_example -fstack-protector-all
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <vector>
#include <string>
#include <unistd.h>
#include <errno.h>
using namespace std;

__attribute__((constructor))
void set_timeout(void) {
  alarm(30);
  setbuf(stdout, NULL);
}

void myread(char *buf) {
  while (1) {
    int ret = read(STDIN_FILENO, buf, 1);
    if (ret == -1) {
      if (errno == EAGAIN || errno == EINTR) continue;
      return;
    }

    if (ret == 0) return;
    ++buf;
  }
}

int main(void) {
  puts("You know, buffer overflow is famous as a basic vulnerability.");
  puts("In CTFs, we often see problems covering it as their subject.");
  puts("So this time let's warm up with a really simple baby buffer overflow!");

  string buf;
  uint32_t sz; 
  printf("Size: ");
  scanf("%u", &sz);
  buf.resize(sz);

  printf("And here's a hint! cookie: %llx, buf: %p\n", *(unsigned long long int*)(((char*)(&sz))+44) & ~(1LL << 16), buf.c_str());
  
  printf("Input: ");
  myread((char*)buf.c_str());

  write(STDOUT_FILENO, "Output: ", 8);
  write(STDOUT_FILENO, buf.c_str(), strlen(buf.c_str()));
  write(STDOUT_FILENO, "\n", 1);
}
```

The idea is on the basis of the fact that std::string allocates its buffer in different regions depending on allocation size. Stack and heap will be used when the size is small and large respectively, so I could employ both of stack bof and heap bof as solutions.

However, it is meaningless to have this problem besides Sanity Check if it makes no difference to the scores, so I thought the perfect solution should be difficult to achieve enough that most of the teams cannot submit the full solution in the first round. Hence I adopted  [link_map Forging](https://www.slideshare.net/ssuser726f56/wctf-2017-binja-editorial) as the solution for heap bof.
Nonetheless, whether you can submit the perfect solution is totally dependent on whether you know this technique and it digresses from what I meant initially, so I intentionally made small the difference between the scores you earn with the partial solution and the perfect one. 

Following this plan, I sloppily implemented the problem, and left it untested for a while because I thought it could be easily verified.

After a while Ga_ryo_ pointed out to me that ‘myread’ would not return unless users shut down a half of the connection, for example using `socket.shutdown(SHUT_WR)`.
This means you cannot resend a ROP payload after leaking some address(this is called ROP stager).
Seemingly the problem seemed unsolvable even to me.
Finally I told Ga_ryo_ that I would fix it later. However, just after that, while I was eating ramen, I realized that this problem still remained solvable with a little twist. Therefore I just left it as it is.

In hindsight, this handling might be a failure. That tricky part made the problem a little bit harder, and as a result no teams submitted a solution in the first 2 rounds.
In my plan, every team would have made a submission in the 1st round and some of them would be the perfect solution, which revealed that I’m really not good at speculating difficulty. 

## @\_N4NU\_
### [Fuzzy Fault](https://github.com/codeblue-ctf/codeblue-2018/tree/master/problems/Finals/Jeopardy/Fuzzy%20Fault)

"Fuzzy Fault" is a task that slightly changed DFA of AES which inject fault into Round 8.
What's different from a typical DFA is that faults are injected into Round 9 and Round 10 in the same position of Round 8.
The motivation to create this task is that there has been no task that deals mainly with DFA for AES in the past CTF.
We started making this task in June.
I consulted with prof. Sakiyama of The University of Electro-Communications and make it with Mr. Hatano who belongs to the Sakiyama laboratory.
It was Mr. Hatano who made the main idea and draft, and @_N4NU_ adjusted it as suitable for CTF task.
The intended solution is to ignore the effect of appended fault.
This task can be solved in the same way as a typical DFA by leveraging information of two rows that are not affected by fault in Round 9 and Round 10.
I would like to express my deep appreciation for the support provided by Sakiyama laboratory.


## @Ga_ryo_
### [OSS](https://github.com/codeblue-ctf/codeblue-2018/tree/master/problems/Finals/Bull's%20Eye/OSS)
OSS is a challenge that came up to my mind first when Bull's Eye format was decided. 
The challenge is that if you can write an exploit that runs under multiple circumstances when source code given? 
I assumed the situation that you found a bug in OSS but you don't know the target's info(distro/compiler).

Ubuntu 16.04 + GCC, Ubuntu 18.04 + GCC, Ubuntu 18.04 + Clang are the prepared environments at the time. Actually I wanted to do with Windows and more.
Cuz the bug is just a stack bof, I'd just like to say that you only need to do ROP:) But of course there is a Canary other than the default configuration for clang. 
If you notice that no canary check exists between throw~catch exception, you can make it just ROP challenge.
In addition, the stack sizes prepared in each environment are different, so you can specify the environment by overflowing it a bit at a time. 
An assumed solution is identifying environment then exploit  each one, rather than writing a universal exploit.

### [JNI](https://github.com/codeblue-ctf/codeblue-2018/tree/master/problems/Finals/Bull's%20Eye/JNI)
As usual the challenge’s name has no sense X(
Because it’s tiresome to commentary, copy-pasted the writeup’s URL.

https://docs.google.com/presentation/d/1l77sVYlU1I6RIIg_yHSt1VDzQ_6fj4WY5ghhWOgKzy0/edit?usp=sharing

Briefly, the bug is UAF in C++ function. At least, functions for primitive type doesn't check types strictly. So TypeConfusion can be done. Then, by considering it as an object of another type, you can adjust Size/Pointer and other things to feel good by calling the prepared JNI function. After that you can get arbitrarily read/write, and can get a shell. (The value of `Integer` is overlapped with the size of Pointer to the string of `String` and size of `int[]`, `long[]`.)
In order to increase the influence of GC, I was thinking about adding a little more randomity (random allocate, randomize the heap size etc.). ( The players become to have to write more stable exploit. )
But I did not have time to write such stable exploit (TT) ...

## @tyage
I have developed the bullseye system.
There were so many troubles during the contest, so I apology to the participants.
(For example, almost all scores are hidden during the contest and the contest finished with less round than we had told you.)

I want to describe what kind of trouble happened, but it will take too much times.
So I will show you the sequence diagram, which we had used to develop bullseye system.
I also want to make the bullseye’s source code public when it is possible.

![シーケンス図](https://github.com/codeblue-ctf/codeblue-2018/raw/master/sequence.png)

# Finals 1日目
## hugeh0ge
I cannot feel apologetic enough for the network issues in the beginning.
The admins of the CTF and the NOC of CODE BLUE are completely different organizations, so even if the issues occurred, we had no way to cope with them. This means we should have taken the utmost care for the configuration of the network.

The NOC asked us whether we had any problem if they provided us only with wireless connections. We gave approval without much consideration since they assured us that they would prohibit any communications between terminals even with wireless configurations.
As a result, the serious accident happened as you experienced.

We came to conclusion that someone built a fake AP, and that “someone” is likely to be a CTF participant.
Let me give you a piece of candid advice. That action was totally meaningless, for as you can see from this post, we never start competitions unless we can level the playing field. Therefore, the act was counterproductive if you would like to enjoy the CTF(though, it can’t be helped if you don’t want to proactively participate in the CTF and would like to trouble us. But even if so, do you want to be confined in a dark room doing nothing??? Maybe you are foolish).
Also, for the same reason, it was worthless even if you meant to take advantages in the game.
We are fully aware and acknowledge that competitors of CTFs are crazy people who immediately try to exploit something when they find its vulnerability, and that incompetent admins who left such vulnerabilities are to blame. Nevertheless you should not take such actions unreasonably if you don’t want to look an idiot. Conversely it was possible that we gave some extra points if you reported us vulnerabilities without exploiting them.  

We also need to feel deeply sorry about Jeopardy’s weight.
We wanted the value of Jeopardy problems to be the same as one Bull’s problem. Therefore we adopted “half of the perfect score of Bull’s Eye problems” as its (perfect) score.
Originally there intended to be 8 rounds and the perfect score is 300, so by simple arithmetic it is 1200.
That is why the score of Fuzzy Fault was set as 1200pts.

In reality, however, we had only 6 rounds due to the delay caused by the network issue. This made Fuzzy Fault overpriced.
At the very moment when we noticed this matter and tried to adjust the score, PPP solved the problem. Considering that the second correct flag submission was sent at night, we cannot help admitting they has insane speed.
Once a team solved the problem, we had no choice but to keep going without changing the score for the sake of justice.
Actually the organizers were afraid of the result being decided only by this excessive scoring.

Of course it was disappointing to have only 6 rounds in itself.

## @mage_1868
### 可視化
This time I developed the visualization system for Bull’s Eye.
https://www.youtube.com/watch?v=1ojN39eV2_c

In the first place, unlike in movies CTF has no hacking scenes where hackers displays showy effects or UI in their laptops. CTF is a really quiet and boring competition for spectators. Therefore organizers of CTF often try to attract their attentions visualizing network packets or participants’ status. Bull’s Eye is no exception. We visualized the results of exploits of each team for each problem taking as a motif darts, which is also the origin of the name “Bull’s Eye”.

I adopted CSS3DRenderer of three.js as the general framework, drew objects with SVG, and controlled delicate movements of them using Javascript and keyframes,transform from CSS.
Compared to pompous tools like OpenGL, those tools make it easier to implement the visualization, so one may wonder if they would sacrifice performance instead. The visualization, however, works fine in just a laptop which costs about 200,000 yen. 

Maybe you thought you already saw a similar design somewhere else, but it’s deja vu, your imagination(I think this matching inevitably occurs when people want the system to be “cyberwise”. I’m sorry though).

# Result

## @hugeh0ge
And now, we are ready to announce the final result.
We want to say sorry for keeping you waiting during the competition, and for this very long time.

| EasyExample | 1 | 2 | 3 | 4 | 5 | 6 | total |
|:---------|:---------|:---------|:---------|:---------|:---------|:---------|:---------|
| Dragon Sector | N/A | 0(0/500) | 255(255/500) | 255(239/500) | 255(235/500) | 255(232/500) | 1020 |
| CyKOR | N/A | 240(208/500) | 210(83/500) | 297(484/500) | 285(444/500) | 285(432/500) | 1317 |
| !SpamAndHex | 0(0/500) | 0(0/500) | 0(0/500) | 0(0/500) | 0(0/500) | 0(0/500) | 0 |
| TSG | 0(0/500) | 0(0/500) | 0(0/500) | 255(213/500) | 255(237/500) | 255(242/500) | 765 |
| LeaveCat-PLUS | 0(0/500) | 0(0/500) | 0(0/500) | 255(256/500) | 255(242/500) | 240(230/500) | 750 |
| blue-lotus | 0(0/500) | 0(0/500) | 255(271/500) | 0(0/500) | 0(0/500) | 0(0/500) | 255 |
| hxp | 0(0/500) | 0(0/500) | 240(210/500) | 240(210/500) | 240(196/500) | 240(194/500) | 960 |
| LCBC | 0(0/500) | 0(0/500) | 0(0/500) | 300(500/500) | 300(500/500) | 300(500/500) | 900 |
| 0daysober | 0(0/500) | 0(0/500) | 255(268/500) | 255(247/500) | 255(262/500) | 255(264/500) | 1020 |
| PPP | N/A | 240(223/500) | 255(233/500) | 255(235/500) | 255(237/500) | 255(241/500) | 1260 |

| CTC | 1 | 2 | 3 | 4 | 5 | 6 | total |
|:---------|:---------|:---------|:---------|:---------|:---------|:---------|:---------|
| Dragon Sector | N/A | N/A | N/A | N/A | N/A | N/A | 0 |
| CyKOR | N/A | N/A | N/A | 297(496/500) | 297(495/500) | 297(498/500) | 891 |
| !SpamAndHex | N/A | N/A | N/A | N/A | N/A | N/A | 0 |
| TSG | N/A | N/A | N/A | N/A | N/A | N/A | 0 |
| LeaveCat-PLUS | N/A | N/A | N/A | N/A | N/A | N/A | 0 |
| blue-lotus | N/A | N/A | N/A | N/A | N/A | N/A | 0 |
| hxp | N/A | N/A | N/A | N/A | N/A | N/A | 0 |
| LCBC | N/A | N/A | N/A | 207(387/500) | 207(363/500) | 207(361/500) | 621 |
| 0daysober | N/A | N/A | N/A | N/A | N/A | N/A | 0 |
| PPP | N/A | N/A | N/A | N/A | N/A | N/A | 0 |

| JNI | 1 | 2 | 3 | 4 | 5 | 6 | total |
|:---------|:---------|:---------|:---------|:---------|:---------|:---------|:---------|
| Dragon Sector | N/A | N/A | N/A | N/A | N/A | N/A | 0 |
| CyKOR | 0(0/500) | 195(62/500) | 297(499/500) | 297(495/500) | 297(494/500) | 297(497/500) | 1383 |
| !SpamAndHex | N/A | N/A | N/A | N/A | N/A | N/A | 0 |
| TSG | N/A | N/A | N/A | N/A | N/A | N/A | 0 |
| LeaveCat-PLUS | N/A | N/A | N/A | N/A | N/A | N/A | 0 |
| blue-lotus | N/A | N/A | N/A | N/A | N/A | N/A | 0 |
| hxp | N/A | N/A | N/A | N/A | N/A | N/A | 0 |
| LCBC | N/A | N/A | N/A | N/A | N/A | N/A | 0 |
| 0daysober | N/A | N/A | N/A | 0(0/500) | 0(0/500) | 0(0/500) | 0 |
| PPP | N/A | N/A | N/A | 240(224/500) | 240(209/500) | 240(196/500) | 720 |

| OSS | OSS(1) 5 | OSS(2) 5 | OSS(3) 5 | OSS(1) 6 | OSS(2) 6 | OSS(3) 6 | total |
|:---------|:---------|:---------|:---------|:---------|:---------|:---------|:---------|
| Dragon Sector | 0(0/166) | 0(0/167) | 168(152/167) | 0(0/166) | 0(0/167) | 184(156/167) | 352 |
| CyKOR | 0(0/166) | 0(0/167) | 198(163/167) | 184(160/166) | 168(152/167) | 168(153/167) | 718 |
| !SpamAndHex | N/A | N/A | N/A | N/A | N/A | N/A | 0 |
| TSG | N/A | N/A | N/A | N/A | N/A | N/A | 0 |
| LeaveCat-PLUS | N/A | N/A | N/A | N/A | N/A | N/A | 0 |
| blue-lotus | N/A | N/A | N/A | N/A | N/A | N/A | 0 |
| hxp | N/A | N/A | N/A | N/A | N/A | N/A | 0 |
| LCBC | N/A | N/A | N/A | N/A | N/A | N/A | 0 |
| 0daysober | N/A | N/A | N/A | N/A | N/A | N/A | 0 |
| PPP | N/A | N/A | N/A | 0(0/166) | 0(0/167) | 198(165/167) | 198 |

| Fliqpy | 3 | 4 | 5 | 6 | total |
|:---------|:---------|:---------|:---------|:---------|:---------|
| Dragon Sector | N/A | 240(221/500) | 255(243/500) | 255(242/500) | 750 |
| CyKOR | 165(13/500) | 285(449/500) | 297(461/500) | 297(456/500) | 1044 |
| !SpamAndHex | N/A | 0(0/500) | 0(0/500) | 0(0/500) | 0 |
| TSG | N/A | 240(211/500) | 240(224/500) | 240(210/500) | 720 |
| LeaveCat-PLUS | N/A | 240(227/500) | 255(234/500) | 255(235/500) | 750 |
| blue-lotus | N/A | 0(0/500) | 0(0/500) | 0(0/500) | 0 |
| hxp | N/A | N/A | N/A | 297(456/500) | 297 |
| LCBC | N/A | N/A | N/A | N/A | 0 |
| 0daysober | N/A | N/A | N/A | 0(0/500) | 0 |
| PPP | N/A | 297(477/500) | 297(482/500) | 297(483/500) | 891 |

| Sum | Easy Example | CTC | JNI | OSS | Fliqpy | FuzzyFault | total | rank |
|:---------|:---------|:---------|:---------|:---------|:---------|:---------|:---------|:---------|
| Dragon Sector | 1020 | 0 | 0 | 352 | 750 | 1200 | 3322 | 3 |
| CyKOR | 1317 | 891 | 1383 | 718 | 1044 | 0 | 5353 | 1 |
| !SpamAndHex | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 10 |
| TSG | 765 | 0 | 0 | 0 | 720 | 1200 | 2685 | 6 |
| LeaveCat-PLUS | 750 | 0 | 0 | 0 | 750 | 1200 | 2700 | 5 |
| blue-lotus | 255 | 0 | 0 | 0 | 0 | 0 | 255 | 9 |
| hxp | 960 | 0 | 0 | 0 | 297 | 1200 | 2457 | 7 |
| LCBC | 900 | 621 | 0 | 0 | 0 | 1200 | 2721 | 4 |
| 0daysober | 1020 | 0 | 0 | 0 | 0 | 1200 | 2220 | 8 |
| PPP | 1260 | 0 | 720 | 198 | 891 | 1200 | 4269 | 2 |

At first sight, you can see that many teams could not earn points in the other problems than mine.
Of course I imagined and was afraid of this situation, and made Java problems opened early and Fliqpy a little later because Fliqpy appears easier than its actual difficulty. However, it had no effect as far as I see this result. Rather, this action seems to have made teams enter into EasyExample and Fliqpy.

We can also see Cykor’s win was a “solid” one.
Even if there had been no troubles, their winning might not have been overturned, so I claim the result is a just one, at least in the part affecting “which team gets the prize”.

At the first place if you didn't submit solutions, then failures of the infrastructure didn’t affect your scores(though it can do if you couldn't even download the problems, but all the teams successfully downloaded them(except only Easy Example, if any)).
Moreover, the team which suffered from the failures most was Cykor, because they submitted solutions most. We cannot complain about the winner, in addition considering the fact that they were very handicapped failing to solve the “sweet” Jeopardy problem.

Actually we prepared the perfect solutions for almost all the problems(about JNI, the prepared solution gives 100% accuracy in the author’s environment and 90% in the actual environment. about Account, we cannot confirm this fact because no one solved it, but we actually did).
As I explained during the contest, this is a very natural handling.
In A&D, participants are never told “how many vulnerabilities each problem has”.
Furthermore it is highly possible that they can earn extra points finding unintended solutions.
This fact makes A&D more exciting, for participants need to find out “when they should stop inspecting, and start ignoring some problem”. This crucial decision can lead to large scores or “going down in flames”.

Applying this playability to our rule, first we should not tell the challengers the success rates of our solutions.
Moreover we should not guarantee the problems to have perfect solutions. Of course authors can even set problems whose solutions seem to have 50% accuracy at most.
It does not necessarily mean participants could not achieve more than 50%, so such settings have no problem. We can just give appropriate additional points for unintended solutions(and it retains fairness even if there don’t exist such solutions, of course).

As a feedback, we were told it would be better if we could open all the problems on day 1.
We dared, however, to open two problems on day 2 intentionally.
In this rule, the score of a team would monotonously increase as rounds go on.
This means it is possible that the strongest team submit perfect solutions to all the problems on day 1, putting an end to the game, which is boring to all of us
(well, this can happen also in A&D though).

Delaying the release of some problems, especially till the beginning of day 2, would be the most effective as a countermeasure.
Nevertheless the ranking in the end of day 1 must have a high correlation with capabilities of teams, so the final ranks would not change unless in extreme circumstances. 
Well, this is inevitable.
Anyway we need to avoid “checkmate”.

That’s why we made CTC and Account opened on day 2. Then, why did we choose them for day 2? It was because we considered them “honest” problems. Here “honest” means “not strange, and would be solvable for all the teams if given plenty of time”.
We have planned to open on day 1, strange or twisted problems which some teams would fail to solve, and on day 2 “honest” problems which all the teams could solve if they would have enough time(because actually they don’t on day 2, scores they get will differ).

Another feedback claims it would be better if the interval of each round becomes shorter, which I completely disagree with. The concept or underlying thinking of this rule  is accuracy, or reliability, in other words, “prudence”. We would not like to accept attitudes like “submit anyway”.
Moreover, this interval is a kind of relief measure for capable teams which cannot solve problems fast. In A&D, the speed of solving problems strongly affects results. In contrast, in Jeopardy, the speed makes little difference, except for first blood because teams are allowed to solve problems at any time taking as much time as they like. 
That means, “fast solving” is not regarded as important, and losing a couple of hours is tolerated. Rather, the result is swayed by whether you can solve challenging problems.
Thinking about the concept of Bull’s Eye, we should make it similar to Jeopardy rather than A&D. Therefore, we don’t want to admit the mechanism of adding more points for teams submitting solutions faster.

Nonetheless, we should of course recognize fast solving to some extent even though we place the highest importance on accuracy. This is why we set rounds and considered some differences of speeds which are so obvious that we can notice them from the rounds in which each team submitted a solution. We are not going to make changes to this part(except for tiny changes like changing the interval from 2 hours to 1 hour).

Whereas, it was extremely regrettable that we could not immediately provide the results of exploits as feedbacks. This was completely due to some error in the system, and not what we meant. We will struggle to improve this situation as much as possible. For example, we will probably update the results of 500 trials in real time and make it possible for teams to see every one of them via browser.
However we are very likely to delay 1 or 2 rounds releasing the results of the other teams to each team. This is a natural measure to keep solutions diverse and a game interesting(like network packets in A & D).

The above is my thought for Bull’s Eye as the inventor. I explained almost all the parts are intentionally designed and we are not going to change some of them, but participants’ comfort is one of the most important things. Thus there may be some parts which should be removed even if they go against our intention, so we are looking for opinions.
By the way, TokyoWesterns and binja are going to hold CODE BLUE CTF this year too. Look forward.
