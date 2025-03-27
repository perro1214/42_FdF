# 42 Libft 関数リファレンス

以下では、`libft.h` で定義されている主な関数について、プロトタイプ・引数・戻り値を簡潔にまとめています。

## 目次
1. 基本的な文字列操作系
   - [ft_atoi](#ft_atoi)
   - [ft_bzero](#ft_bzero)
   - [ft_calloc](#ft_calloc)
   - [ft_isalnum](#ft_isalnum)
   - [ft_isalpha](#ft_isalpha)
   - [ft_isascii](#ft_isascii)
   - [ft_isdigit](#ft_isdigit)
   - [ft_isprint](#ft_isprint)
   - [ft_memchr](#ft_memchr)
   - [ft_memcmp](#ft_memcmp)
   - [ft_memcpy](#ft_memcpy)
   - [ft_memmove](#ft_memmove)
   - [ft_memset](#ft_memset)
   - [ft_strlen](#ft_strlen)
   - [ft_strchr](#ft_strchr)
   - [ft_strrchr](#ft_strrchr)
   - [ft_strncmp](#ft_strncmp)
   - [ft_strnstr](#ft_strnstr)
   - [ft_strlcpy](#ft_strlcpy)
   - [ft_strlcat](#ft_strlcat)
   - [ft_strdup](#ft_strdup)
   - [ft_tolower](#ft_tolower)
   - [ft_toupper](#ft_toupper)

2. 文字列生成・分割系
   - [ft_substr](#ft_substr)
   - [ft_strjoin](#ft_strjoin)
   - [ft_strtrim](#ft_strtrim)
   - [ft_split](#ft_split)
   - [ft_strmapi](#ft_strmapi)
   - [ft_itoa](#ft_itoa)

3. 文字列操作(コールバック)系
   - [ft_striteri](#ft_striteri)

4. 出力系
   - [ft_putstr_fd](#ft_putstr_fd)
   - [ft_putchar_fd](#ft_putchar_fd)
   - [ft_putendl_fd](#ft_putendl_fd)
   - [ft_putnbr_fd](#ft_putnbr_fd)

5. リスト操作系
   - [ft_lstnew](#ft_lstnew)
   - [ft_lstadd_front](#ft_lstadd_front)
   - [ft_lstsize](#ft_lstsize)
   - [ft_lstlast](#ft_lstlast)
   - [ft_lstadd_back](#ft_lstadd_back)
   - [ft_lstdelone](#ft_lstdelone)
   - [ft_lstclear](#ft_lstclear)
   - [ft_lstiter](#ft_lstiter)
   - [ft_lstmap](#ft_lstmap)

---

## 1. 基本的な文字列操作系

### ft_atoi
- プロトタイプ: `int ft_atoi(const char *string);`
- 引数:
  - `string`: 整数として解釈される文字列
- 戻り値: 引数文字列を整数に変換した値
- 概要: 文字列を整数に変換する。

### ft_bzero
- プロトタイプ: `void ft_bzero(void *b, size_t len);`
- 引数:
  - `b`: メモリ領域の先頭ポインタ
  - `len`: ゼロクリアするバイト数
- 戻り値: なし
- 概要: 指定したメモリ領域をゼロクリアする。

### ft_calloc
- プロトタイプ: `void *ft_calloc(size_t n, size_t size);`
- 引数:
  - `n`: 確保する要素数
  - `size`: 各要素のサイズ (バイト)
- 戻り値: 確保したメモリ領域の先頭ポインタ（確保失敗時は `NULL`）
- 概要: `malloc` と同様に動作し、割り当てたメモリをゼロクリアする。

### ft_isalnum
- プロトタイプ: `int ft_isalnum(int c);`
- 引数:
  - `c`: チェック対象の文字コード
- 戻り値: `c` が英数字であれば 1、そうでなければ 0
- 概要: 文字コードが英数字か判定する。

### ft_isalpha
- プロトタイプ: `int ft_isalpha(int a);`
- 引数:
  - `a`: チェック対象の文字コード
- 戻り値: `a` がアルファベット文字なら 1、そうでなければ 0
- 概要: 文字コードがアルファベットか判定する。

### ft_isascii
- プロトタイプ: `int ft_isascii(int c);`
- 引数:
  - `c`: チェック対象の文字コード
- 戻り値: `c` が ASCII 文字領域内（0〜127）なら 1、そうでなければ 0
- 概要: 文字コードが ASCII 文字範囲内か判定する。

### ft_isdigit
- プロトタイプ: `int ft_isdigit(int c);`
- 引数:
  - `c`: チェック対象の文字コード
- 戻り値: `c` が数字（0〜9）なら 1、そうでなければ 0
- 概要: 文字コードが数字か判定する。

### ft_isprint
- プロトタイプ: `int ft_isprint(int c);`
- 引数:
  - `c`: チェック対象の文字コード
- 戻り値: `c` が印字可能文字（スペース含む）なら 1、そうでなければ 0
- 概要: 文字コードが表示可能領域か判定する。

### ft_memchr
- プロトタイプ: `void *ft_memchr(const void *buf, int ch, size_t n);`
- 引数:
  - `buf`: 検索対象のメモリ領域
  - `ch`: 検索する値
  - `n`: 検索するバイト数
- 戻り値: 見つかった位置へのポインタ、見つからない場合は `NULL`
- 概要: メモリ領域内で特定のバイト値を検索する。

### ft_memcmp
- プロトタイプ: `int ft_memcmp(const void *buf1, const void *buf2, size_t n);`
- 引数:
  - `buf1`, `buf2`: 比較対象となるメモリ領域
  - `n`: 比較するバイト数
- 戻り値: 差分（0なら等しい）
- 概要: メモリ領域同士をバイト単位で比較する。

### ft_memcpy
- プロトタイプ: `void *ft_memcpy(void *dst, const void *src, size_t len);`
- 引数:
  - `dst`: コピー先メモリ
  - `src`: コピー元メモリ
  - `len`: コピーするバイト数
- 戻り値: `dst` のポインタ
- 概要: メモリ領域をコピーする（領域が重複しない場合に使用）。

### ft_memmove
- プロトタイプ: `void *ft_memmove(void *dst, const void *src, size_t len);`
- 引数:
  - `dst`: コピー先メモリ
  - `src`: コピー元メモリ
  - `len`: コピーするバイト数
- 戻り値: `dst` のポインタ
- 概要: メモリ領域が重複していても安全にコピーを行う。

### ft_memset
- プロトタイプ: `void *ft_memset(void *s, int c, size_t n);`
- 引数:
  - `s`: 対象メモリ
  - `c`: 設定する値
  - `n`: 設定するバイト数
- 戻り値: `s` のポインタ
- 概要: 指定バイト分、メモリ領域を同じ値で埋める。

### ft_strlen
- プロトタイプ: `size_t ft_strlen(const char *str);`
- 引数:
  - `str`: 対象文字列
- 戻り値: `str` の長さ（終端文字を含まない）
- 概要: C文字列の長さを計算する。

### ft_strchr
- プロトタイプ: `char *ft_strchr(const char *s, int c);`
- 引数:
  - `s`: 検索対象の文字列
  - `c`: 検索する文字 (`char` として解釈される)
- 戻り値: 最初に見つかった位置へのポインタ、見つからない場合は `NULL`
- 概要: 文字列内で最初に出現する特定文字を検索する。

### ft_strrchr
- プロトタイプ: `char *ft_strrchr(const char *s, int c);`
- 引数:
  - `s`: 検索対象の文字列
  - `c`: 検索する文字
- 戻り値: 最後に見つかった位置へのポインタ、見つからない場合は `NULL`
- 概要: 文字列内で最後に出現する特定文字を検索する。

### ft_strncmp
- プロトタイプ: `int ft_strncmp(const char *s1, const char *s2, size_t n);`
- 引数:
  - `s1`, `s2`: 比較元文字列
  - `n`: 比較する最大文字数
- 戻り値: 差分（0なら等しい）
- 概要: 2つの文字列を最大 n 文字まで比較する。

### ft_strnstr
- プロトタイプ: `char *ft_strnstr(const char *big, const char *little, size_t len);`
- 引数:
  - `big`: 検索対象の文字列
  - `little`: 検索する部分文字列
  - `len`: `big` から検索する最大長
- 戻り値: 見つかった位置へのポインタ、見つからない場合は `NULL`
- 概要: `big` 内で最大 `len` 文字分までを対象に、`little` を検索する。

### ft_strlcpy
- プロトタイプ: `size_t ft_strlcpy(char *dst, const char *src, size_t size);`
- 引数:
  - `dst`: コピー先文字列バッファ
  - `src`: コピー元文字列
  - `size`: `dst` のバッファサイズ
- 戻り値: `src` の長さ (終端文字含まず)
- 概要: `src` を `dst` にコピーし、ヌル終端を保証する安全な関数。

### ft_strlcat
- プロトタイプ: `size_t ft_strlcat(char *s1, const char *s2, size_t size);`
- 引数:
  - `s1`: 結合先文字列バッファ（元の文字列が含まれる）
  - `s2`: 結合する文字列
  - `size`: `s1` のバッファサイズ
- 戻り値: `s1` と `s2` を合計した長さ
- 概要: `s1` の末尾に `s2` を連結し、ヌル終端を保証する安全な関数。

### ft_strdup
- プロトタイプ: `char *ft_strdup(const char *s);`
- 引数:
  - `s`: 複製元の文字列
- 戻り値: 成功時は複製した文字列ポインタ、失敗時は `NULL`
- 概要: 与えられた文字列 `s` の複製を動的に確保して返す。

### ft_tolower
- プロトタイプ: `int ft_tolower(int c);`
- 引数:
  - `c`: 変換対象の文字コード
- 戻り値: `c` を小文字に変換した文字コード
- 概要: 英字を小文字に変換する。

### ft_toupper
- プロトタイプ: `int ft_toupper(int c);`
- 引数:
  - `c`: 変換対象の文字コード
- 戻り値: `c` を大文字に変換した文字コード
- 概要: 英字を大文字に変換する。

---

## 2. 文字列生成・分割系

### ft_substr
- プロトタイプ: `char *ft_substr(char const *s, unsigned int start, size_t len);`
- 引数:
  - `s`: 元の文字列
  - `start`: 切り出し開始位置
  - `len`: 切り出す長さ
- 戻り値: 切り出された新しい文字列ポインタ（失敗時は `NULL`）
- 概要: 文字列 `s` の `start` 位置から最大 `len` 文字を切り出す。

### ft_strjoin
- プロトタイプ: `char *ft_strjoin(char const *s1, char const *s2);`
- 引数:
  - `s1`, `s2`: 連結する文字列
- 戻り値: `s1` と `s2` を連結した新しい文字列ポインタ（失敗時は `NULL`）
- 概要: 2つの文字列を動的に確保した新しいバッファに連結する。

### ft_strtrim
- プロトタイプ: `char *ft_strtrim(char const *s1, char const *set);`
- 引数:
  - `s1`: トリミング対象の文字列
  - `set`: 取り除く文字が含まれるセット
- 戻り値: 先頭と末尾から `set` に含まれる文字を取り除いた新しい文字列（失敗時は `NULL`）
- 概要: `s1` の先頭と末尾から特定の文字を消去した文字列を返す。

### ft_split
- プロトタイプ: `char **ft_split(char const *str, char charset);`
- 引数:
  - `str`: 分割する元の文字列
  - `charset`: 区切り文字
- 戻り値: 分割後の文字列配列（失敗時は `NULL`）
- 概要: 文字列 `str` を `charset` に応じて分割し、各部分文字列を要素とする配列を返す。

### ft_strmapi
- プロトタイプ: `char *ft_strmapi(char const *s, char (*f)(unsigned int, char));`
- 引数:
  - `s`: 元となる文字列
  - `f`: 各文字に適用する関数ポインタ
- 戻り値: 変換後の新しい文字列ポインタ（失敗時は `NULL`）
- 概要: 文字列 `s` の各文字に関数 `f` を適用して生成した新しい文字列を返す。

### ft_itoa
- プロトタイプ: `char *ft_itoa(int n);`
- 引数:
  - `n`: 変換する整数
- 戻り値: 整数を文字列化した新しい文字列ポインタ（失敗時は `NULL`）
- 概要: 整数を文字列に変換する。

---

## 3. 文字列操作(コールバック)系

### ft_striteri
- プロトタイプ: `void ft_striteri(char *s, void (*f)(unsigned int, char *));`
- 引数:
  - `s`: 操作対象の文字列
  - `f`: 各文字に対して実行する関数
- 戻り値: なし
- 概要: 文字列 `s` の各文字に関数 `f` を適用（破壊的に書き換え）する。

---

## 4. 出力系

### ft_putstr_fd
- プロトタイプ: `void ft_putstr_fd(char *c, int fd);`
- 引数:
  - `c`: 出力対象の文字列
  - `fd`: ファイルディスクリプタ
- 戻り値: なし
- 概要: 指定したファイルディスクリプタに文字列を出力する。

### ft_putchar_fd
- プロトタイプ: `void ft_putchar_fd(char c, int fd);`
- 引数:
  - `c`: 出力する文字
  - `fd`: ファイルディスクリプタ
- 戻り値: なし
- 概要: 指定したファイルディスクリプタに1文字出力する。

### ft_putendl_fd
- プロトタイプ: `void ft_putendl_fd(char *c, int fd);`
- 引数:
  - `c`: 出力対象の文字列
  - `fd`: ファイルディスクリプタ
- 戻り値: なし
- 概要: 文字列の末尾に改行を付けて出力する。

### ft_putnbr_fd
- プロトタイプ: `void ft_putnbr_fd(int n, int fd);`
- 引数:
  - `n`: 出力する整数
  - `fd`: ファイルディスクリプタ
- 戻り値: なし
- 概要: 指定したファイルディスクリプタに整数を文字列形式で出力する。

---

## 5. リスト操作系

### ft_lstnew
- プロトタイプ: `t_list *ft_lstnew(void *content);`
- 引数:
  - `content`: 新しいノードの `content` に格納するポインタ
- 戻り値: 新規に割り当てられたノードへのポインタ
- 概要: シンプルなリストノードを作成する。

### ft_lstadd_front
- プロトタイプ: `void ft_lstadd_front(t_list **lst, t_list *new);`
- 引数:
  - `lst`: リストの先頭ポインタへのポインタ
  - `new`: 追加するノード
- 戻り値: なし
- 概要: リストの先頭にノードを追加する。

### ft_lstsize
- プロトタイプ: `int ft_lstsize(t_list *lst);`
- 引数:
  - `lst`: リストの先頭
- 戻り値: リストの要素数
- 概要: 与えられたリストのノード数を数える。

### ft_lstlast
- プロトタイプ: `t_list *ft_lstlast(t_list *lst);`
- 引数:
  - `lst`: リストの先頭
- 戻り値: リストの最後のノード
- 概要: リストの末尾ノードを取得する。

### ft_lstadd_back
- プロトタイプ: `void ft_lstadd_back(t_list **lst, t_list *new);`
- 引数:
  - `lst`: リストの先頭ポインタへのポインタ
  - `new`: 追加するノード
- 戻り値: なし
- 概要: リストの末尾にノードを追加する。

### ft_lstdelone
- プロトタイプ: `void ft_lstdelone(t_list *lst, void (*del)(void *));`
- 引数:
  - `lst`: 削除対象のノード
  - `del`: `lst->content` を解放するために使用される関数ポインタ
- 戻り値: なし
- 概要: ノードを削除し、その `content` を適切に解放する。

### ft_lstclear
- プロトタイプ: `void ft_lstclear(t_list **lst, void (*del)(void *));`
- 引数:
  - `lst`: リストの先頭ポインタへのポインタ
  - `del`: 各ノードの `content` を解放する関数ポインタ
- 戻り値: なし
- 概要: リストの全ノードを削除・解放し、リストを空にする。

### ft_lstiter
- プロトタイプ: `void ft_lstiter(t_list *lst, void (*f)(void *));`
- 引数:
  - `lst`: リストの先頭
  - `f`: 各ノードの `content` に対して実行する関数ポインタ
- 戻り値: なし
- 概要: リストの各ノードに関数 `f` を適用する。

### ft_lstmap
- プロトタイプ: 
  ```c
  t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
