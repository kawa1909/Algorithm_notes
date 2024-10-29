## 前缀树

前缀树是一种功能强大且灵活的字符串数据结构，适合处理大量字符串的查找、插入和前缀相关操作。

### 1. Trie 树的节点结构

```c++
const int MAXN = 150001;
int tree[MAXN][26];    
int endCount[MAXN];
int pass[MAXN];
```

- `tree[MAXN][26]`：一个二维数组，表示 Trie 树中的每个节点和它的 26 条可能分支（对应 `a-z` 这 26 个字母）。每个节点最多可以有 26 个子节点。
- `endCount[MAXN]`：用于记录以某个节点为结尾的单词数量。`endCount[i]` 表示以节点 `i` 为结尾的单词数。
- `pass[MAXN]`：记录经过某个节点的单词数量。`pass[i]` 表示有多少个单词经过节点 `i`。
- `cnt`：表示当前 Trie 树中已经使用的节点数。每当插入新单词时，`cnt` 自增来分配新的节点。

### 2. 初始化 Trie 树

```c++
void build() {
    cnt = 1;
    memset(tree, 0, sizeof(tree));
    memset(endCount, 0, sizeof(endCount));
    memset(pass, 0, sizeof(pass));
}
```

- `build()` 函数初始化 Trie 树。在这里，根节点的编号固定为 `1`，并且清空了 `tree`、`endCount` 和 `pass` 数组，确保每次操作前 Trie 树都是干净的。

### 3. 插入单词

```c++
void insert(const string& word) {
    int cur = 1; 
    pass[cur]++;
    for (int i = 0, path; i < word.length(); i++) {
        path = word[i] - 'a';
        if (tree[cur][path] == 0) {
            tree[cur][path] = ++cnt;
        }
        cur = tree[cur][path];
        pass[cur]++;
    }
    endCount[cur]++;
}
```

- ```c++
	insert()
	```

	 用于将一个单词插入到 Trie 树中。

	- 从根节点 `1` 开始，对每个字符计算其对应路径（通过减去 `'a'` 计算相对位置）。
	- 如果当前字符的路径不存在，则创建一个新节点（分配新编号 `cnt`）。
	- 每访问一个节点，都增加该节点的 `pass` 值，表示有一个单词经过此节点。
	- 最后，标记单词的结尾，通过 `endCount[cur]++` 增加当前节点的单词结束数量。

### 4. 查找单词

```c++
int search(const string& word) {
    int cur = 1;
    for (int i = 0, path; i < word.length(); i++) {
        path = word[i] - 'a';
        if (tree[cur][path] == 0) {
            return 0;
        }
        cur = tree[cur][path];
    }
    return endCount[cur];
}
```

- ```
	search()
	```

	 用于查找单词是否存在于 Trie 树中。

	- 从根节点开始，逐字符匹配，沿路径向下查找。
	- 如果途中某个字符的路径不存在，则该单词不在 Trie 树中，返回 `0`。
	- 如果查找到最后一个字符，返回 `endCount[cur]`，表示以该节点为结尾的单词数量。若大于 0，说明单词存在。

### 5. 查找前缀数量

```c++
int prefixNumber(const string& pre) {
    int cur = 1;
    for (int i = 0, path; i < pre.length(); i++) {
        path = pre[i] - 'a';
        if (tree[cur][path] == 0) {
            return 0;
        }
        cur = tree[cur][path];
    }
    return pass[cur];
}
```

- ```
	prefixNumber()
	```

	 用于查找以某个前缀开头的单词数量。

	- 类似于查找单词，但返回的是最后一个字符对应节点的 `pass` 值，表示有多少个单词经过这个前缀。

### 6. 删除单词

```c++
void deleteWord(const string& word) {
    if (search(word) > 0) {
        int cur = 1;
        for (int i = 0, path; i < word.length(); i++) {
            path = word[i] - 'a';
            if (--pass[tree[cur][path]] == 0) {
                tree[cur][path] = 0;
                return;
            }
            cur = tree[cur][path];
        }
        endCount[cur]--;
    }
}
```

- ```
	deleteWord()
	```

	 用于从 Trie 树中删除一个单词。

	- 先检查该单词是否存在。
	- 如果存在，沿着单词路径删除，更新 `pass` 值。若某个节点的 `pass` 值变为 `0`，说明没有单词再经过这个节点，可以直接删除路径。
	- 最后，减少 `endCount` 值以表示该单词被删除。

### 7. 清空 Trie 树

```c++
void clear() {
    for (int i = 1; i <= cnt; i++) {
        memset(tree[i], 0, sizeof(tree[i]));
        endCount[i] = 0;
        pass[i] = 0;
    }
}
```

- `clear()` 用于清空整个 Trie 树，将所有的节点、路径、单词结尾和路径通过次数清空，以便重新使用。

### 完整代码

#### 静态数组Trie写法：(推荐写法)

```c++
#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 150001;  // 最大节点数。Trie 树总共有 MAXN 个节点，每个节点最多有26个孩子

int tree[MAXN][26];    // Trie 树的节点，二维数组表示每个节点的 26 个英文字母分支（0-25表示a-z）
int endCount[MAXN];    // 记录某个节点是否是一个单词的结尾。endCount[i] 表示以该节点为结尾的单词数量
int pass[MAXN];        // 记录经过某个节点的次数，pass[i] 表示通过该节点的单词数
int cnt;               // 当前 Trie 树的节点计数，初始时只有根节点，编号为 1

// 初始化 Trie 树，将根节点编号设置为 1
void build() {
    cnt = 1;  // 根节点编号为 1，cnt 表示当前的节点数量
    memset(tree, 0, sizeof(tree));      // 清空 tree 数组，表示 Trie 树中没有任何连接
    memset(endCount, 0, sizeof(endCount));  // 清空 endCount 数组
    memset(pass, 0, sizeof(pass));      // 清空 pass 数组
}

// 将一个单词插入到 Trie 树中
void insert(const string& word) {
    int cur = 1;  // 当前节点，相当于node，1 表示从根节点开始
    pass[cur]++;  // 根节点被访问一次，头结点
    for (int i = 0, path; i < word.length(); i++) {
        path = word[i] - 'a';  // 计算字符的位置，'a' 对应 0，'b' 对应 1，以此类推
        //tree[cur][path]相当于node.path[]
        if (tree[cur][path] == 0) {  // 如果当前节点的该路径不存在，创建新节点
            tree[cur][path] = ++cnt;  // 分配一个新节点编号，cnt 自增
        }
        cur = tree[cur][path];  // 移动到下一个节点
        pass[cur]++;  // 更新新节点的 pass 值，表示通过该节点
    }
    endCount[cur]++;  // 该节点是单词的结尾，更新 endCount，表示这里有一个单词结束
}

// 查找某个单词是否存在于 Trie 树中
int search(const string& word) {
    int cur = 1;  // 从根节点开始搜索
    for (int i = 0, path; i < word.length(); i++) {
        path = word[i] - 'a';  // 计算当前字符对应的路径
        if (tree[cur][path] == 0) {  // 如果路径不存在，说明该单词不在 Trie 树中
            return 0;
        }
        cur = tree[cur][path];  // 继续向下搜索
    }
    return endCount[cur];  // 返回是否有单词以该节点结尾，>0 表示存在该单词
}

// 返回以某个前缀开头的单词数量
int prefixNumber(const string& pre) {
    int cur = 1;  // 从根节点开始搜索前缀
    for (int i = 0, path; i < pre.length(); i++) {
        path = pre[i] - 'a';  // 计算当前字符对应的路径
        if (tree[cur][path] == 0) {  // 如果路径不存在，说明没有单词以该前缀开头
            return 0;
        }
        cur = tree[cur][path];  // 继续向下搜索
    }
    return pass[cur];  // 返回经过该前缀节点的单词数量
}

// 删除 Trie 树中的某个单词
void deleteWord(const string& word) {
    if (search(word) > 0) {  // 先判断该单词是否存在，如果不存在，不需要删除
        int cur = 1;  // 从根节点开始删除
        for (int i = 0, path; i < word.length(); i++) {
            path = word[i] - 'a';  // 计算当前字符的路径
            if (--pass[tree[cur][path]] == 0) {  // 如果删除后路径上没有单词经过，直接删除该路径
                tree[cur][path] = 0;  // 将路径置为 0，表示该路径不再存在
                return;  // 直接退出
            }
            cur = tree[cur][path];  // 继续向下处理
        }
        endCount[cur]--;  // 减少该节点的 endCount 值，表示该单词被删除
    }
}

// 清空整个 Trie 树
void clear() {
    for (int i = 1; i <= cnt; i++) {  // 遍历所有节点
        memset(tree[i], 0, sizeof(tree[i]));  // 清空每个节点的路径
        endCount[i] = 0;  // 清空单词结束标记
        pass[i] = 0;      // 清空经过节点的单词数量
    }
}

// 主函数
int main() {
    ios::sync_with_stdio(false);  // 提高输入输出效率
    cin.tie(nullptr);  // 解除输入输出流的绑定

    int m, op;  // m 是操作数，op 是操作类型
    string line;  // 用于存储输入行
    while (getline(cin, line)) {  // 读取输入行
        build();  // 初始化 Trie 树
        m = stoi(line);  // 将字符串转换为整数，表示操作数
        for (int i = 1; i <= m; i++) {
            getline(cin, line);  // 读取操作行
            size_t space_pos = line.find(' ');  // 找到操作与单词之间的空格位置
            op = stoi(line.substr(0, space_pos));  // 解析操作类型
            string word = line.substr(space_pos + 1);  // 解析单词

            if (op == 1) {
                insert(word);  // 插入单词
            } else if (op == 2) {
                deleteWord(word);  // 删除单词
            } else if (op == 3) {
                cout << (search(word) > 0 ? "YES" : "NO") << endl;  // 判断单词是否存在
            } else if (op == 4) {
                cout << prefixNumber(word) << endl;  // 返回以该前缀开头的单词数量
            }
        }
        clear();  // 清空 Trie 树
    }
    
    return 0;  // 正常退出程序
}
```

#### 动态数组写法：

```c++
#include <unordered_map>
#include <string>
using namespace std;

// 数组实现的 Trie
class Trie1 {
public:
    // Trie 树的节点类
    class TrieNode {
    public:
        int pass; // 经过这个节点的单词数量
        int end;  // 以这个节点为结尾的单词数量
        TrieNode* nexts[26]; // 存储 26 个字母的子节点

        TrieNode() {
            pass = 0;
            end = 0;
            for (int i = 0; i < 26; i++) {
                nexts[i] = nullptr;
            }
        }
    };

    TrieNode* root; // Trie 树的根节点

    Trie1() {
        root = new TrieNode();
    }

    // 插入单词
    void insert(const string& word) {
        TrieNode* node = root;
        node->pass++;
        for (int i = 0; i < word.size(); i++) {
            int path = word[i] - 'a'; // 计算当前字符应该走哪条路
            if (node->nexts[path] == nullptr) {
                node->nexts[path] = new TrieNode(); // 如果路不存在，新建节点
            }
            node = node->nexts[path];
            node->pass++;
        }
        node->end++; // 最后一个字符节点的 end 加 1
    }

    // 删除单词
    void erase(const string& word) {
        if (countWordsEqualTo(word) > 0) { // 只有单词存在时才删除
            TrieNode* node = root;
            node->pass--;
            for (int i = 0; i < word.size(); i++) {
                int path = word[i] - 'a';
                if (--node->nexts[path]->pass == 0) { // 如果 pass 变为 0，直接删除
                    node->nexts[path] = nullptr;
                    return;
                }
                node = node->nexts[path];
            }
            node->end--; // 减少该单词的 end 计数
        }
    }

    // 查询单词出现次数
    int countWordsEqualTo(const string& word) {
        TrieNode* node = root;
        for (int i = 0; i < word.size(); i++) {
            int path = word[i] - 'a';
            if (node->nexts[path] == nullptr) {
                return 0; // 如果路不存在，返回 0
            }
            node = node->nexts[path];
        }
        return node->end; // 返回 end，即单词出现次数
    }

    // 查询有多少单词以 prefix 作为前缀
    int countWordsStartingWith(const string& pre) {
        TrieNode* node = root;
        for (int i = 0; i < pre.size(); i++) {
            int path = pre[i] - 'a';
            if (node->nexts[path] == nullptr) {
                return 0; // 如果路不存在，返回 0
            }
            node = node->nexts[path];
        }
        return node->pass; // 返回 pass，即以该前缀为起始的单词数量
    }
};

// 哈希表实现的 Trie
class Trie2 {
public:
    // Trie 树的节点类
    class TrieNode {
    public:
        int pass; // 经过这个节点的单词数量
        int end;  // 以这个节点为结尾的单词数量
        unordered_map<char, TrieNode*> nexts; // 存储子节点的哈希表

        TrieNode() {
            pass = 0;
            end = 0;
        }
    };

    TrieNode* root; // Trie 树的根节点

    Trie2() {
        root = new TrieNode();
    }

    // 插入单词
    void insert(const string& word) {
        TrieNode* node = root;
        node->pass++;
        for (int i = 0; i < word.size(); i++) {
            char path = word[i];
            if (node->nexts.find(path) == node->nexts.end()) {
                node->nexts[path] = new TrieNode(); // 如果路不存在，新建节点
            }
            node = node->nexts[path];
            node->pass++;
        }
        node->end++; // 最后一个字符节点的 end 加 1
    }

    // 删除单词
    void erase(const string& word) {
        if (countWordsEqualTo(word) > 0) { // 只有单词存在时才删除
            TrieNode* node = root;
            node->pass--;
            for (int i = 0; i < word.size(); i++) {
                char path = word[i];
                TrieNode* next = node->nexts[path];
                if (--next->pass == 0) { // 如果 pass 变为 0，直接删除
                    node->nexts.erase(path);
                    return;
                }
                node = next;
            }
            node->end--; // 减少该单词的 end 计数
        }
    }

    // 查询单词出现次数
    int countWordsEqualTo(const string& word) {
        TrieNode* node = root;
        for (int i = 0; i < word.size(); i++) {
            char path = word[i];
            if (node->nexts.find(path) == node->nexts.end()) {
                return 0; // 如果路不存在，返回 0
            }
            node = node->nexts[path];
        }
        return node->end; // 返回 end，即单词出现次数
    }

    // 查询有多少单词以 prefix 作为前缀
    int countWordsStartingWith(const string& pre) {
        TrieNode* node = root;
        for (int i = 0; i < pre.size(); i++) {
            char path = pre[i];
            if (node->nexts.find(path) == node->nexts.end()) {
                return 0; // 如果路不存在，返回 0
            }
            node = node->nexts[path];
        }
        return node->pass; // 返回 pass，即以该前缀为起始的单词数量
    }
};

```
