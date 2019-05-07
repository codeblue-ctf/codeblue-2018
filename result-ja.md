# 長くて読めん
この記事はCODE BLUE CTF 2018の回顧を行うものです。
運営それぞれに言いたいことがあるので少し長くなるかもしれません。興味のない人は[ここ](#result)をクリック。

続く各セクションでは1年の時系列順に振り返ります。また、何を考え何が印象に残ったかは、運営の中でも異なることもあるかもしれません。
ということで各々が書きたいことを別々に書くことにしました。

# CODE BLUE CTF 2017以後
## @hugeh0ge
CODE BLUE CTF 2017が終わった直後、メンバー達で話し合った。来年度もやるかについて。
全員がやることで合意した。これは、CBCTF 2017は非常にもったいなかったという意識の表れだったと思う。
自分が言うのもなんだが、問題のクオリティはとても高かった。その割に、平日開催でしかも決勝が存在せず、まともに楽しんでもらえたのはCykorとHITCONぐらいだった。
去年CODE BLUE CTFが開催された動機は[僕のブログの通り](http://binja.github.io/2017/11/13/Thoughts-on-CODE-BLUE-CTF-write-ups/)で、
個人的には開催が出来てちょっと既に満足していたのだが、どうせ今年度もやるのであれば、Finalsをやりたいと思った。
それも、数年前から考えていたBull’s Eye(当時は名前もなかった)で。

メンバーにこの事を話した。反応は良く割と乗り気だった。
とはいえ、当時はルールの詳細やシステムの実現方法も何も考えておらず、更にシステムを自分たちで作らないといけないこともあり机上の空論に近かった。

次に、CODE BLUEの主催者であるkanaさんに話した。kanaさんはとても優しく承諾してくれた。
CBCTFはあの人がいなければ実現していない。kanaさんはとても実行力のある人で(まあでないとカンファレンスを主催出来ないと思うが)、
CBCTFの競技内容以外については、ほとんどkanaさんのおかげで成り立っている。会場設備から参加者の宿泊まで本当に多くのことでお世話になった。
これは当然資金も含めて全てである。

我々運営は言われないと動けない性格をしている人間が多いので、こうしたkanaさんの行動力がなければ企画全体が頓挫していたと思う(この延期しまくった記事みたいにな！)。
この場を借りて感謝します。

こうして、CBCTF 2018の開催が決定した。この時点で決めなければならなかったことはBull’s Eyeのルールの詳細と、予選と本戦をどう運営していくか。
TokyoWesternsは自分たちのCTF TWCTFを開くから、そこも含めて予選をどうするかを決めなくてはならなかった。

# Quals前

## @hugeh0ge
正直な所、自分はあまり作問をしたくなかった。
今自分はほとんどCTFに出ていないから最近の問題の流行には乗れていないと思うし、正直クオリティの保証もできない。
特に、クオリティが担保されてないのは自分としては許せないことである。それに作問案もほぼないし。

しかし、TWCTFを開催することは決まっていて、CBCTF Quals側はほぼbinja側単独で運営することになったので仕方なく4問ぐらい作った。
後述するが、1問作問ミスして悲しかった。また、ボス問をちゃんと作れて良かった。

# Quals

## @hugeh0ge
Real World CTFのQualsと日程が被ったのは非常に精神的に参った。正直な所、大会規模的には向こうがこちらより上なので、多くの強豪チームが参加してくれない懸念があった。
また、当日になってnomeaningさんと連絡がつかなくなってしまったのもあって、当日の昼ぐらいまで延期するか少し揉めた。
結局、日程を被せてきたのは向こう側であること、延期できるほどメンバーの都合に余裕がないことなどから、延期しない決断を下した。
結果的にはこれは間違っていなくて、RWCTFと同時に出てくれるチームは多く、まともなチームがFinalsに選出されたので非常に安心した。

ところで、RWCTFの運営の人とはDEFCONやCBCTFで話しましたし、今は全然怒ってないです。

以下、自分の作問した問題にコメントしていきます。

### [Watch Cats](https://github.com/codeblue-ctf/codeblue-2018/tree/master/problems/Quals/Watch%20Cats)
去年の問題があまりに難しかったみたいなので、今年は簡単な問題を出そうと決めていた。そのために作ったのがこのWatch Catsである。
本当に心から初心者向けに作ったつもりだったが、結果としては壊滅した。

去年の反省点に、「動的スコアとはいえ運営の難易度予想みたいなのあって良い。難易度評価できない初心者の人たちが困る」という話があったんだけど、
結局やる暇がなく今年もやらなかった。これが原因だったのかなと思う。失敗。

とはいえ、後述するgame RevengeやEasy Exampleのことを考えると僕の難易度評価は当てにならないようなので、そもそも問題が難しすぎた説はある。

この問題についてはいくつもwriteupが上がっているので具体的には
 - http://kotarou777775.hatenablog.com/entry/2018/08/07/213911
 - https://blog.dragonsector.pl/2018/08/code-blue-ctf-2018-quals-watchcats.html

これらを見ると良いかも。
と言ってもどこにもコードが上がっていなかったので、一応以下に簡易的な解説を上げる。

この問題ではC++のコードとそのバイナリ、後はステージ情報の入ったテキストファイルが5つ渡される。
5ステージクリアできればFLAGが手に入る。ゲームはWatch Dogsのミニゲームを模したものになっている。[こんな感じ](https://youtu.be/paUctg-WWc8?t=2)。

PPC(Professional Programming and Coding、要はコーディング)要素として、最後以外の4ステージはプログラムで探索すれば簡単に答えが出せるようにしてある。
問題は最後のステージ。
最後のステージは”詰んで”いる。つまり正攻法では絶対にクリアできない。ここでpwnの出番。

```
      scanf("%d", &idx);
      if (idx < 0 || num_joints <= idx) {
        puts("Idiot");
        exit(0);
      }
      ++joints[idx].direction;
```

237行目に注目する。
これは指定されたjointの向きを左に回転させる処理なのだが、整数値オーバーフローの対策(つまりmod 4を取る)をしていない。
directionはchar型だから、128回インクリメントすれば負数になる。C言語の面倒な仕様として、負数の剰余は負数のままというものがある。
つまり、-5をmod 4したとして、他の近代的な言語のように3にはなってくれず、-1になる。これを使えば関数show_circuit内の判定中に配列外参照を起こしてくれる。
これで本来流せない場所に水を流すことが出来るので、めでたく解ける。

作る際に気をつけたこととしては、これは初心者向けに作った問題なので、脆弱性にさえ気づけば初心者でも解けるようにした。
つまり、ROPやheapテクニックといった特殊な知識無しに、C言語の基本的な要素に加えて多少のデバッガ操作さえ出来れば解けるようにしてある。
しかし、そのように簡単な問題は、必要な操作が簡単なので、無限の猿定理が如く「適当に手でタイプしてたら解けた」ということになりかねない。
それでは困るので、ただ適当に連打しただけでは中々脆弱性が発現しないようにしてあるし、その上、脆弱性が分かっても多少考えないとそれを悪用できないようにもした。

```
      struct joint &jo = joints[idx];
      const struct joint_type &ty = joint_types[jo.type];

      int k;
      for (k=0; k<4; k++) {
        if (jo.cables[k] == v) break;
      }

      jo.direction %= 4;
```

具体的には、先程は説明しなかったが、142行目でちゃんとdirectionのmod 4を取っている。
しかしこれは適切な取り方ではない。というのは、142行目は、幅優先探索の内部である。
幅優先探索は「水が流れているジョイント・ケーブルを見つけて探索する」ためのもので、水が流れていないジョイントは剰余が取られないのだ。

しかし、ステージ5ではデフォルト状態では重要なジョイントに水が流れるようにしてあるので、ただそれを回転させ続けるだけでは脆弱性は発現しない。
こうすることによって、まぐれで解けてしまう恐れを減らしている。

### [game Revenge](https://github.com/codeblue-ctf/codeblue-2018/tree/master/problems/Quals/game%20Revenge)
僕の問題を解いたことがある人は知っていると思うが、僕の問題に”Revenge”が付いている時は、過去に出題された問題を改題したものである。
元の問題であるgameは、僕が中学生の頃にひっそりとやってたtkbctfのボス問枠。
当時はただのメモリリークによるフラグリークを想定解としていて、ダミーの脆弱性としてstack canaryを(ブルートフォース以外で)突破できないやつとかが置いてあった。

しかし、実は作問者の非想定な脆弱性がある。
以下のコードを見てほしい。ファイル名には任意のパスを渡せるとしよう。何か問題はあるだろうか？

```
  FILE *fp = fopen(filename, "rb");
  long off = ftell(fp);
  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  fseek(stream, off, SEEK_SET);
  void *ptr = malloc(size + 1);
  fread(ptr, size, 1u, stream);
```

実はこの処理は脆弱である。named pipeというものをご存知だろうか。
UNIX系のOSには、名前のついた、すなわちファイルとして扱えるpipeがあるのだ。
それをこの処理に渡すとどうなるだろうか？

ftellで-1が返ってくる影響で、`malloc(-1+1)`=`malloc(0)`が走り、mallocは成功してしまう。
-1はunsignedに直せばとてつもなく大きい値なので、このまま適当な関数によってバッファに入力されると、buffer overflowが起きる。

この問題が出題された当時は、まだheapのテクニックが開拓されておらず、heap overflowするとはいっても条件的にexploitableかは怪しいと考えられていた。
自分はMaster Canary Forgingで解けなくはないことを知っていたが、2018年となっては簡単な部類のheap問となってしまっている。fastbinsなどを適当に破壊すればよい。

と思って出したらsolved 1でびっくり。えーそんなに難しくないと思うけどなあ。
30~40人ぐらいは解くと思ってた。
https://twitter.com/potetisensei/status/1024670553641107456

### [Something Revenge](https://github.com/codeblue-ctf/codeblue-2018/tree/master/problems/Quals/Something%20Revenge)
大失敗。人生で初めて大切な大会でとんでもない作問ミスをした。
普段自分は作問の際にダミーの脆弱性を入れるということはしないのだが、今回はあまりに見るべき箇所がなくてすぐに想定解法が分かってしまいそうだという懸念から
ダミーの脆弱性としてformat string bugを入れた。結果的にはそれが大失敗で、それによるメモリリークでどうにかなってしまうゴミ問題と化した。noobみたいなミスをやめろ。
この作問ミスのせいでssh環境という条件を使わなくても解けてしまった。

さて想定解法はなんだったかというと、以下の部分に注目すると解ける。

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
myprintfの数値の表示にはバグが有り、INT_MINを表示しようとすると、見ての通り無限にstackを上向きに表示してしまう。
よって、これをうまく使ってFLAGがmmapされている領域を出力するという方針が立つ。
これは実際可能なのだが、そのまま何の工夫もなしに出力しようとしても、マッピングの配置の関係で上手くいかない。

ではどうするかというと、ulimit -s unlimitedによってmmapのマッピングの順序を変更する。
このテクニックはWCTF 2018でうちのチーム(@Charo_ITさん)が出した問題の本質と同じ。
Linuxのmmapはマッピングをbottom upに行う場合とtop downに行う場合があるのだが、このアルゴリズムの切り替えを行うためにulimitを使える。
だからssh接続だったんだよね。

最終的なexploitはとても簡単で、payload中でbuffer overflowをしてINT_MINを書き込むようにした上で、以下のscriptを走らせるだけ。
```
ulimit -s unlimited 
./smth_revenge < ./payload | hexdump -C | grep -B 1 -A 1 FTCBC
```

面倒なexploit要素とかがなくて好きです。まあ非想定解の方がもっと簡単なんですけどね。
ちなみにこの問題の名前にも”Revenge”が入っているが、元ネタはMidnight Sun CTFというCTFのFinalsのgissaという問題。
まあ本質は全然違うんだけど、gissaにも似た不具合があって、どっちかというとこっちの方が作問として綺麗じゃない？ぐらいの気持ちで作った。
僕の問題を何個か解いたことがある人はわかると思うんだけど、こういう変な問題好きなんだよね。Ninja no Aikotobaとか一番変で気に入ってます。

### [Code Blue Online Judge part2](https://github.com/codeblue-ctf/codeblue-2018/tree/master/problems/Quals/CODE%20BLUE%20Online%20Judge)
ボス問枠(本番ではどのチームも解くことが出来なかった)。
いくら難しい問題を作る能力がもはやなく、簡単気味に問題を作ってるといっても、流石に沢山のチームに全完されるとコンテストとしてどうかなという感じがする。
というわけで1問ぐらい高難易度の問題が欲しい気持ちがあった。まあ結果としては他の問題も壊滅的だったので多分いらなかったんですけどね。

この問題もアイデア自体は数年前から持っていた。基本的にもうCTF引退老害勢としては過去の遺産にすがりつくしかないので。
まあアイデアの昇華の仕方としてはかなり良い方向、というかこれ以外無理そうだと思う。
その程度に、現実ではまず見れないであろう設定かなという気がする。
まあとはいっても、実は昔ある有名な言語処理系(しかもサンドボックス用途で使う)の実装でこれが出来る状況だったことはあるんですが...

どういう問題だったかというと、競技プログラミングのジャッジシステムをpwnしてくださいというもの。
競技プログラミングには、インタラクティブと呼ばれる形式の問題がある。
典型的なものとしては、「AliceとBobがいて、Bobは秘密のデータを持っている。Aliceにはある形式の質問のみが許されている。
Q回以下まで質問が出来る時、Aliceとして秘密のデータを特定してください。」という感じのものとかがそれに当たる。

普通の競技プログラミングの問題では、正解・不正解というのは提出されたコードに適当な入力を与えて、出力結果が正しいものかどうかをdiffを取って見るだけで良いが、
インタラクティブ問題では提出されたコードの出力に応じて何かしらの応答を返さないといけないため、当然正解判定側もプログラムになる。
この問題のテーマは、そういったジャッジ用プログラムに脆弱性があったらどうするか？というもの。

ここに良い例があります:
https://arc026.contest.atcoder.jp/submissions/476526

この問題は2つのpartに分かれていて、part1ではwebシステム側、part2ではジャッジプログラムを攻略することになる。
わざわざこのためにジャッジサイトを1から(icchyが)実装し、1から競プロの問題を(僕が)作った。出題した競プロの問題は具体的には以下のようなものだった。

> N人の人が1列に並ぼうとしている。
> ただし、この時M個満たさなければならない条件がある。
> i番目の条件は、「A_i番目の人はB_i番目の人よりも左に並んでいたい」。
> M個全ての条件を満たすためにはどのような並び方をするべきか答えよ。以下のフォーマットに沿って答えること:
>  Q個の質問が来る。i番目の質問では、「X_i番目の人はY_i番目の人より左に来るべきか？右に来るべきか？」を尋ねられる。
>  左に来るべきであれば-1を、右に来るべきであれば+1を出力すること。

実際の問題文は[ここ](https://github.com/codeblue-ctf/codeblue-2018/blob/master/problems/Quals/CODE%20BLUE%20Online%20Judge/statement.pdf)で見れる。 

まあ競プロをやっている人からすると自明にDirected Acyclic Graphのトポロジカルソートをするだけの問題なんですが、
答え方がかなり特殊なことに気づくと思う。実は、ジャッジプログラムは以下のような形で正解を判定している:

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

ジャッジプログラムは提出されたコードとプロセス間通信をしていて、`fs`にその入出力が入っている。
このプロセス間通信の入出力をもってqsort_rによるsortを掛けた結果、出来上がる配列が正しくsortされてるかを見ることで正解判定をしている。

さて、面白いのはここからで、実はこの実装はまずくて脆弱です。
つまり、提出コードは-1と1しか出力できないけれども、ジャッジプログラムをexploitしてジャッジ側の権限で任意のコードを走らせることが出来る。
そんなバカなと思ったあなた。一緒にglibcのコードを読んでみよう。
以下はglibcのstdlib/qsort.cの_quicksort関数。

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

さて、いくつかの箇所で
  `while ((*cmp) ((void *) left_ptr, (void *) mid, arg) < 0)`
という形の処理が見受けられる。
このcmpという関数ポインタは引数として渡される比較関数で、この問題においては提出コードの出力によって操作されているということになる。
つまり、提出コードが-1を返し続けた時、qsortは少なくとも無限ループする。

無限ループするだけならまだしも、それに応じてポインタをインクリメント・デクリメントして配列操作をするわけだから、配列外参照を起こせてしまうということになるのだ。
いやー恐ろしい。

というわけで、比較関数によって配列外参照が起こることは分かるので、後は適切に-1, 1を返して、うまく任意のコード実行に持っていけばよい
(と簡単に書いているが、これもそこまで簡単ではない。でもボス問を解くようなチームにとっては，数時間あれば出来る程度の難度になっている)。

ちなみに、実は_quicksort関数は通常呼ばれる関数ではない。今のglibcの実装では、メモリに余裕がある時はマージソートを行うことになっている(qsortという名前なのにね)。
マージソートでは、アルゴリズムを想像すれば分かると思うが、比較関数の値を元にwhileループを回すようなことはしないから、脆弱性は存在しない。

つまり、quicksortを呼ぶためにはメモリを圧迫するなどしてメモリ確保を失敗させる必要がある。しかし、これについてはジャッジプログラムは初めから条件を満たしている。
というのも、ジャッジプログラムは”””セキュア”””にプロセス間通信を行う意図でseccompによる制限をかけているのであるが、ページサイズを取得するためのsyscallが禁止されている影響で、
qsort内のメモリ確保は必ず失敗する。そのため、必ず_quicksortが呼ばれてしまっているのだ。

この問題のいやらしい部分は、qsortが怪しいと思った参加者が手元で実験用のコードを書いても、書き方が適当だとマージソートが呼ばれてしまって再現しないという所にある。
ちゃんと問題の実装を全てリバースエンジニアリングして実験コードを作成するか、glibcを読まなければ解けないように出来ている。まあボス問だしそれぐらいにはしないとね。

ところで、part1を作ってくれたTWのicchyにはかなり感謝してる。web何も分からんので。コンテストサイトも作れるわけなし。

# Finals前
## @hugeh0ge
システム開発大爆発！のせいでweb勢が全員開発に時間を取られ、作問に手が回せなくなってしまった。
また、crypto勢は全く作問をしてくれなかった。結果として問題のバランスがめちゃくちゃ悪くなった。
Bull’s Eyeをpwn以外のジャンルでも出来ると良かったが、結局pwn 6問のBull’s Eyeとcrypto 1問のJeopardyによるミックスになった。悲しい。

以下は自分の作った問題に関するコメント:

### [Fliqpy](https://github.com/codeblue-ctf/codeblue-2018/tree/master/problems/Finals/Bull's%20Eye/Fliqpy)
短いのでコードを載せる。
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

Quals向けの作問中に思いついた問題。
一言で言えば、「任意にアドレスを指定して1bitだけ反転できます。Exploitできますか？」。
着想はTWCTF 3rdのparrotとrui314さんの[この記事](https://note.mu/ruiu/n/nbb7a52c374ae)。

作問は2,3分ぐらいで終わった(!w)けど、当初の予想よりこれは解けるかかなり非自明であることに気づいた。
確率的な解法を見出すまでにすら半日を要した上、満点解法の存在に関しては疑問視するレベルであった。
結局満点解法あるか分からんなあと思ったまま放置して数ヶ月が経ったんだけど、突然チームメイトのBono_iPadさんが解けたと言ってきて無事満点解法の存在が保証された。

このように意図せずFinalsの問題にとても相応しく仕上がってしまったので、QualsよりはFinalsで出そうということでリザーブすることになった。

最終ラウンドではどのチームも良く解いていたし、作問の傾向としても非常に自分らしい問題なので良かったのではないか。
あまり、解析に時間がかかるような問題は作りたくないんですよ。exploit部分のみで時間が溶けるような問題が好き。

### [EasyExample](https://github.com/codeblue-ctf/codeblue-2018/tree/master/problems/Finals/Bull's%20Eye/Easy%20Example)
Finalsの一月前。
全く見たことのないルールで行われる大会の初回に、Sanity Check以外の練習問題がないのは、参加するチームにあまり親切でないのではないかと思った。
結果、ある種のProof of Concept程度の意味合いで、めちゃくちゃ簡単な問題を作ってやろうと思って出来たのがこの問題である。

この通り、めちゃくちゃコードは短い:
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

アイデアとしては、std::stringがアロケートされる領域はサイズによって異なるという事実に基づいている。
それぞれサイズが小さい時と大きい時でstackとheapであるから、単純なstack bofとheap bofを解法として使えば良い。

ただし、差が出なさすぎてはSanity Checkと別に出す意味もなくなってしまうので、満点解法は、少なくとも全チームが1ラウンド目から提出出来るものではない方が良いと思った。
結果、heap bof側の想定解法として、[link_map Forging](https://www.slideshare.net/ssuser726f56/wctf-2017-binja-editorial)を採用することにした。
しかしこれはあまりにも知識ゲーであり、更に当初の意図からすればかなり非本質的なことであるから、部分点解法との点数差は意図的に小さくしてある。

このプランに基づいて、適当に実装した後、どうせ簡単だからと思って、少しの間テストせず放置していた。
その後Ga_ryo_さんに指摘されて気づいたのは、socketの出力をshutdownするまでreadが打ち切られないということである。
これはROP stagerのように、一度アドレスをleakしてから再度ROP payloadを送るような手法が使えなくなっている事を意味する。
パッと見では、そのままでは作った自分ですらstack bofでは解けなくなってしまっているように見えた。
結局Ga_ryo_さんには、その場では「後で直す」と伝えた。しかし、その直後ラーメン屋でラーメンを食べながら冷静になってみると、
実は今の状態でも工夫すれば解けることに気づいたのでそのまま放置することにした。

これは今思うとあまり良くなかったかもしれない。
この部分のせいで、思っていたよりも普通に難しい問題になってしまったらしく、始め2ラウンドぐらいは提出がない状態になってしまった。
僕の予定は、1ラウンド目に全てのチームから提出があり、そのうち数チーム程度が満点解法で提出してくるというものだったが、あまりに想定が下手すぎたらしい。

## @\_N4NU\_
### [Fuzzy Fault](https://github.com/codeblue-ctf/codeblue-2018/tree/master/problems/Finals/Jeopardy/Fuzzy%20Fault)

Round8にfaultをinjectするAESのDFAを少し変えた問題． 
通常のDFAと異なるのは， Round8だけでなく同じ位置にRound9とRound10でもfaultがinjectするという点．
過去にAESに対するDFAをメインに扱ったCTFの問題が無かった事が， この問題の作成のモチベーションだった．
この問題は6月から作り始めた． 弊学の崎山先生に相談をして，崎山研究室に所属している羽田野さんと一緒に作った．
メインアイデアとドラフトを作ったのは羽田野さん． それを@_N4NU_がCTFの問題として適当なものに調整した．
この問題の想定解は追加されたfaultを無視して解くという方法で，
Round9とRound10で入ったfaultに影響されない2列分の情報を元に通常のDFAと同様に解けるという解法だった．
崎山研究室の方々の作問への多大な協力に，改めて感謝の意を表します

## @Ga_ryo_
### [OSS](https://github.com/codeblue-ctf/codeblue-2018/tree/master/problems/Finals/Bull's%20Eye/OSS)
Bull’s Eyeの形式が決まったときに初めに思いついた問題。
ソースコードが提供されている状態において、複数の環境下で動くexploitを書けますか？という問題。
OSSのコードに脆弱性が見つかったけどTargetの環境は完全には特定できていない中で失敗しないexploitが書けるか？みたいな状況を妄想していた。

用意した環境はそれぞれ当時のlatestでUbuntu16.04 + GCC, Ubuntu18.04 + GCC, Ubuntu18.04 + clang。
本当はWindowsとかもっと色々出したかった。問題としてはしょうもないStack buffer overflowなのでそれぞれROPをするだけ、と言いたいところだが、
clangのdefault以外は当然Canaryが付いている。例外をthrowするとcatchされるまでのcanary checkが呼ばれないことに気がつけば、
数値変換関数で数字以外を入れるなどして例外を出せばただのROPに出来る。
ついでに各環境で用意されるstackサイズが異なるので、ちょっとずつoverflowさせていけば環境の特定も出来る。
つまり想定解としてはUniversalなexploitというよりは環境特定 + 各環境のexploitということになる。

### [JNI](https://github.com/codeblue-ctf/codeblue-2018/tree/master/problems/Finals/Bull's%20Eye/JNI)
相変わらず問題名にセンスがない。そのまんまJNIの問題である。
解説が面倒なので、以下のWriteupスライドを貼っておく。

https://docs.google.com/presentation/d/1l77sVYlU1I6RIIg_yHSt1VDzQ_6fj4WY5ghhWOgKzy0/edit?usp=sharing

簡単に説明すると、JNIのC++側関数でUAFがある。少なくともPrimitiveの関数に関しては型のcheckが甘く、TypeConfusionが出来る。
そこで別の型のObjectとみなして関数を呼ぶ事でSize/Pointerとかを良い感じに調整出来る。
あとは任意に書き換えに持ち込めるのでshellが取れる。(IntegerのvalueはStringの文字列へのPointer及び、int[],long[]のSizeと場所が重なっている。)
GCの影響度を高めるためにもう少しランダム性(ランダムでallocate, heap sizeをランダムにする等)するとexploitの正確性が測れてもっと良いと思ったが、
作問者がその状況でも安定するexploitを書く時間がなかった。。。

## @tyage
競技システムの開発をしていました。
本番では、全スコアが今日まで発表されなかったり、本来よりも少ないラウンドで競技が終了するなど、終始トラブル続きだったと思います。
ごめんね。

開発時や競技中に何が発生していたかを詳細に説明したいのですが、長くなりすぎるので開発時に使用していたシーケンス図を貼ります。
個人的にはBullsEyeのシステムのソースコードも全部公開してしまいたいのですが、それはまた機会があれば。

![シーケンス図](https://github.com/codeblue-ctf/codeblue-2018/tree/master/sequence.jpg)

# Finals 1日目
## hugeh0ge
序盤のネットワークのトラブルに関しては、反省してもしきれない。
CTFの運営とネットワークのNOCは全くもって別の組織である。
したがって、ネットワークに何か異常が発生した場合に我々には対処する術がなく、構成には慎重を期す必要があった。

NOC側から構成について、「無線のみで良いか。有線は必要か。少なくとも端末間の通信は無線でも出来ないようにする」という問い合わせが来ていた。
我々は熟考せずOKを出してしまったが、結果として当日起きたような事故が発生した。

あれは結局、誰か(一応分からないということにしておいてやるが)がfake APを立てていたのであろうという結論に至っている。CTF参加者でない可能性は低いだろう。
苦言を呈するならば、あの行為は全くもって無駄である。理由は、このポストを読めば分かるかもしれないが、我々は各チームの公平性が担保されない限り、
競技を始めない性格である。したがって、困らせて楽しむのが目的であるならば手の施しようがないが、競技を楽しみたいのであれば全くもって逆効果である。
競技を有利に進めたいという意図においてもあまり意味がない。
脆弱性があると攻撃したくなる性格の人間ばかりが集まっていることも、脆弱性を残すような無能な運営側が悪いことも重々承知しているが、
あまり頭の悪そうに見えることはしない方が良い。益がないので。むしろ報告すればボーナスポイントを出すかもしれない話である。善意を持て。

また、Jeopardyの重みが結果としてでかくなりすぎたこともとても反省している。
Jepardyの問題の点数は、Bull’s Eyeの問題1問と同程度の価値にするつもりであった。
結果として採用されたJeopardyの点数は「Bull’s Eyeの問題の満点の半分」。
元々2日合わせて8ラウンドの提出があり、満点は1問300点だから、その半分となると1200点。
だからFuzzy Faultは1200点だったのである。

しかし、現実はというと、開始時のトラブルによる遅延で6ラウンドしか出来なかったため、これでは点数が大きすぎる。
我々はこのことに気づいて点数を修正しようとしたが、その矢先にPPPがこの問題を解いてしまった。
2チーム目の回答が夜に出たことを考えると、開始数時間で解いてしまうのは異常な速度である。
PPPが解いてしまった状態で点数を変更するのはあまりに不公平であるから、結局1200点のまま続行する羽目になってしまった。
運営は正直、これの差で勝敗が決まったりしたらどうしようとハラハラしていた。

ラウンドが少なくなったこと自体も残念である。

## @mage_1868
### 可視化
今回、新しい競技形式「Bull's Eye」を視覚的に表現する可視化システムを作成しました。
https://www.youtube.com/watch?v=1ojN39eV2_c

そもそもCTFには映画のような派手なエフェクトやUIを用いたハッキングシーンは無く、傍から見る分には地味で退屈な競技です。
そこで従来の形式のCTFはパケットの可視化や問題の攻略状況を可視化することで、観戦者の気を引く試みがよく行われています。
「Bull's Eye」もその例外ではなく、名称の由来でもあるダーツをモチーフにし、チームと問題毎のexploitの成功状況を可視化しました。

実装の大枠はthree.jsのCSS3DRendererを使用し、オブジェクトはSVGで描写、細かい動きはCSSのkeyframes,transformとJavaScriptで制御しています。
OpenGL等に比べて実装が楽になる分、パフォーマンスが気になるところですが、20万円ほどで購入できるそこそこのラップトップでも動かすことができました。

見た目に既視感を覚えるかもしれませんが、それは気の所為です。（サイバー感を出そうとするとどうしても被ってしまいますね、すいません）

# Result

## @hugeh0ge
さて、Finalsに参加した皆さんにとってはお待ちかねの結果発表です。
競技中、そしてこれまで長い間待たせてしまったことをここでお詫びしたい。

| EasyExample | 1 | 2 | 3 | 4 | 5 | 6 | total |
|:---------|:---------|:---------|:---------|:---------|:---------|:---------|:---------|
| Dragon Sector | 0(0/500) | 0(0/500) | 255(255/500) | 255(239/500) | 255(235/500) | 255(232/500) | 1020 |
| CyKOR | 0(0/500) | 240(208/500) | 210(83/500) | 297(484/500) | 285(444/500) | 285(432/500) | 1317 |
| !SpamAndHex | 0(0/500) | 0(0/500) | 0(0/500) | 0(0/500) | 0(0/500) | 0(0/500) | 0 |
| TSG | 0(0/500) | 0(0/500) | 0(0/500) | 255(213/500) | 255(237/500) | 255(242/500) | 765 |
| LeaveCat-PLUS | 0(0/500) | 0(0/500) | 0(0/500) | 255(256/500) | 255(242/500) | 240(230/500) | 750 |
| blue-lotus | 0(0/500) | 0(0/500) | 255(271/500) | 0(0/500) | 0(0/500) | 0(0/500) | 255 |
| hxp | 0(0/500) | 0(0/500) | 240(210/500) | 240(210/500) | 240(196/500) | 240(194/500) | 960 |
| LCBC | 0(0/500) | 0(0/500) | 0(0/500) | 300(500/500) | 300(500/500) | 300(500/500) | 900 |
| 0daysober | 0(0/500) | 0(0/500) | 255(268/500) | 255(247/500) | 255(262/500) | 255(264/500) | 1020 |
| PPP | 0(0/500) | 240(223/500) | 255(233/500) | 255(235/500) | 255(237/500) | 255(241/500) | 1260 |

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

まず、多くのチームが僕の問題以外に対してスコアを出せないという少々悲しい結果になった。
こうなることを懸念して、Javaの2問に関しては早く出題し、とっつきやすいFliqpyは少し後にするというの処置をしたが、効果はあまりなかったように思える。
むしろ、かなり取り組みやすい見た目をしているEasyExampleとFliqpyに時間を取られたような形にも見える。

また、Cykorの1位が絶対的であることも読み取れる。
Cykorの優勝は、インフラの不備などの不具合を全てなかったことにしてもおそらく覆ることはなく正当であり、
プライズが出る範囲ではコンテストは問題がなかったといえる。
そもそもsolutionを提出してないならインフラ不備によって結果が変わることはない
(もちろん問題が取得できていない場合にはこの限りではないが、どのチームも問題の取得は出来ていた。また、出来ていなかったとしても初めのEasy Exampleのみである)。
それにCykor自身もこれらの不具合は経験しているし、何より1番被害を受けている。
Jeopardyのスコアが取れていないという大きすぎるハンデも含めて1位を取っていることに文句はつけられない。

実は、我々は(ほとんど)全ての問題に対して満点解法を用意してあった(JNIに関しては、作者の環境で100%, 本番環境で9割であった。
また、Accountに対してはどのチームからの提出がなかったので、ここからは読み取ることができないが100%である)。しかし、競技中、我々はそのことについて保証はしなかった。
競技中にも少し説明したことであるが、これはかなり自然なことである。
A&Dにおいて、「ある問題が持つ脆弱性の個数」が参加者に知らされることはまずない。
更には、作問者の非想定な解法によって、追加の点数を得られることすら多々ある。
この事実によって、A&Dでは「いつ、ある問題をこれ以上見なくて良い、無視してよいと決断するか？」という部分にゲーム性が生じている。
この判断は大量の得点や失点に繋がるわけである。

これをBull’s Eyeに当てはめるならば、まず我々は想定解の確率を参加者に教えるべきではない。
更には、100%の解法があることも保証すべきではない。もちろん、作問者は50%が最大だと思って出題することすら出来る。
それは、「参加者がより良い解法によって50%を上回る可能性」を否定するわけではなく、その場合には適切な加点をしてやれば良いだけである。

参加者からのフィードバックで全ての問題を1日目に公開できると良かったとあったが、2日目に2問出したのは意図的なものだ。
このルールではあるチームのある問題に対する点数は、ラウンドを経るごとに単調に増加するしかないので、
1日目の序盤に最強のチームが全てに対してパーフェクトな解法を提出し決着がつき、全くもってつまらない結果になるということがあり得る。
まあこれはA&Dでも起こりうることなんだけど。

対策としては、問題の公開タイミングをずらすことで、特に2日目に問題を公開するのが1番効果があると思う。
とはいえ、そもそも1日目の点数差というのはほぼチームの実力と相関があるわけで、よっぽどのことがない限り大方1日目と同じ順位になるわけである。まあこれは仕方がない。
どちらにせよ、”詰み”は避けるべきだ。

そして、CTCとAccountが2日目に回ったのは、”真っ当”な問題と判断したからであるからである。
ここでいう”真っ当”とは、奇抜な問題ではなく、十分な時間を掛けて丁寧に詰めればどのチームも解くことが出来るであろうという意味である。
奇抜な問題や捻りが強く、解けないチームも出るだろう問題は1日目に、
時間を掛けれるならばどのチームも解けてしまうであろう問題は2日目に(2日目は十分な時間がないので、差が出る)、という方針であった。

他のフィードバックとしては、ラウンドをもっと細かくした方が良いという意見などがあったが、これに関しては *全く以って* 同意しない。
このルールのコンセプトおよび根幹にある考え方は精度や信頼性、言い換えれば”慎重さ”であって、「とりあえず出しとけ」といった姿勢を持たれては困るものである。
その上、この時間間隔は、実力はあるが、早解きが苦手なチームへの救済措置でもある。A&Dでは早解きの得意不得意が強く試合結果に反映される。
対して、Jeopardyでは、first bloodの加点を除いて、期間中に問題を解けば良く、そこに差はない。
基本的には、問題が公開されてからどのタイミングで問題を見てどのタイミングでexploitを書きどのタイミングで提出しても良い。
つまりそこに早解きの要素はあまりなく、数時間のロスは許容され、どちらかといえば高難易度の問題を解けるかの方が成績に影響する。
Bull’s Eyeはコンセプト的に、どちらかといえばJeopardyに寄せるべきものである。
したがって、ラウンド間隔が短く、提出が早い方が加点されやすい仕組みにはしたくない。

とはいえ、もちろん精度を最も重要視しているとはいっても、早く解けたチームを評価すべきというのも最もなので、
ラウンドを設け、ラウンドを跨いでしまうほどの速度の差に関しては考慮するという形を取ったのが今のルールである。
これに関しては、(2時間から1時間に変更するなどの些細な変更を除いて)抜本的に変えるつもりは全くない。

一方で、フィードバックが遅かった点については、とても良くなかったと考えている。これはシステムの不具合であり、我々の意図とは反している。
これについては出来るだけ改善するようにする。例えば、500回の実行の成否全てをリアルタイムに更新し、webインターフェース上から各1回の結果がその場で見れるぐらいにはしたいと考えている。
ただし、他チームの結果の共有に関しては今年度と同様、2ラウンド後など、少し遅らせる可能性が高い。
これは前述の通り、問題の解法の多様性について不確定要素があるべきだからである(A&Dでもパケットの公開は遅らせる事が多い)。

以上がBull’s Eyeの考案者である僕の考えである。
とはいえ、参加者に不便がかからないことも最重要事項の1つであるから、ルールにそのような部分があるならば、僕の意図に反していても取り除いたほうが良いかもしれない。
ということで意見は随時募集中です。
ところで、TokyoWesternsとbinjaは2019年度もCODE BLUE CTFを開催する意向です。来年もお楽しみに〜
