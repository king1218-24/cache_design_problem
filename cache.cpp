#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <assert.h>
#include <fstream>
#include <time.h>

using namespace std;

fstream fs;


int choose_victim(const vector<int>& Cache, const vector<int>& future_access);


// 一个普通的解法
// 1.txt
// 9103
// time = 2.67871s

// 2.txt
// 7346
// time = 2.58408s

// 3.txt
// 7501
// time = 2.89075s

// 5.txt
// 66300
// time = 21.1738s

// 6.txt
// 14090
// time = 5.75894s

int choose_victim(const vector<int>& Cache,
                  const vector<int>& future_access) {
    int victim = Cache[0];
    int farthest = -1;

    for (int line : Cache) {
        int next_use = 1e9;
        for (int i = 0; i < (int)future_access.size(); i++) {
            if (future_access[i] == line) {
                next_use = i;
                break;
            }
        }
        if (next_use > farthest) {
            farthest = next_use;
            victim = line;
        }
    }
    return victim;
}



// 解法二，剪枝窗口
// 1.txt k=200
// 9107
// time = 1.89897s

// 2.txt k=200
// 7347
// time = 1.6783s

// 3.txt k=200
// 7502
// time = 1.87969s

// 4.txt k=200
// 39099
// time = 8.44107s

// 4.txt k=50
// 44006
// time = 9.44511s

// 5.txt k=1000
// 66311
// time = 18.0335s

// 6.txt k=200
// 16091
// time = 4.16347s
/*
int choose_victim(const vector<int>& cache,
                  const vector<int>& future_access) {
    const int K = 200;                 // 剪枝窗口
    int limit = min((int)future_access.size(), K);

    int victim = cache[0];
    int best_next = -1;
    int best_freq = 1e9;

    for (int page : cache) {
        int next_pos = -1;
        int freq = 0;

        for (int i = 0; i < limit; i++) {
            if (future_access[i] == page) {
                freq++;
                if (next_pos == -1)
                    next_pos = i;
            }
        }

        // 在窗口内完全不出现，直接淘汰
        if (next_pos == -1) {
            return page;
        }

        // 综合比较再次访问的时间先后与频率
        if (next_pos > best_next ||
            (next_pos == best_next && freq < best_freq)) {
            best_next = next_pos;
            best_freq = freq;
            victim = page;
        }
    }

    return victim;
}
*/




void simulate_cacheline_replacement(int M, const vector<int>& access_sequence) {
    vector<int> Cache;  // 当前Cache状态
    unordered_set<int> line_set;  // 用于快速查找
    int miss_num = 0;  // 缺失次数

    for (int i = 0; i < access_sequence.size(); i++) {
        int current_line = access_sequence[i];

        // 主存块在cache中，跳过
        
        
        if (line_set.find(current_line) != line_set.end()){ 
            continue;
        }
        

        // 主存块不在cache中，发生缺失
        miss_num++;

        if (Cache.size() < M) {
            // cache未满，直接添加

            
            Cache.push_back(current_line);
            line_set.insert(current_line);
            

        } else {
            // cache已满，调用置换策略选择要换出的cache行
            vector<int> future_access(access_sequence.begin() + i + 1, access_sequence.end());
            int victim = choose_victim(Cache, future_access);

            assert(line_set.find(victim) != line_set.end());

            // 找到要换出的cache行并进行替换
            
            
            line_set.erase(victim);
            auto it = find(Cache.begin(), Cache.end(), victim);
            *it = current_line;
            line_set.insert(current_line);
            

            assert(line_set.find(victim) == line_set.end() && line_set.find(current_line) != line_set.end());
        }
    }

    // 输出缺页次数
    cout << miss_num << endl;
}

int main() {
    int M, N;
    clock_t start, end;
    
    fs.open("5.in", ios::in);

    fs >> M >> N;
    
    vector<int> access_sequence(N);
    for (int i = 0; i < N; i++) {
        fs >> access_sequence[i];
    }
    start = clock();
    simulate_cacheline_replacement(M, access_sequence);
    end = clock();
    cout << "time = " << double(end-start)/CLOCKS_PER_SEC << "s\n"; 
    return 0;
}
