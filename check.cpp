#include <stdio.h>
#include <vector>
#include <cmath>
using namespace std;

#define AC 0
#define WA 1

int main(int argc, char* argv[]) {
    FILE* fin   = fopen(argv[1], "r"); // input
    FILE* fuser = fopen(argv[2], "r"); // user output
    FILE* fans  = fopen(argv[3], "r"); // standard output

    if (!fin || !fuser || !fans) {
        printf("0\n");
        return AC;
    }

    
    int M, N;
    if (fscanf(fin, "%d%d", &M, &N) != 2) {
        printf("0\n");
        return AC;
    }

    vector<int> trace(N);
    for (int i = 0; i < N; i++) {
        if (fscanf(fin, "%d", &trace[i]) != 1) {
            printf("0\n");
            return AC;
        }
    }
    fclose(fin);

    long long std_miss;
    if (fscanf(fans, "%lld", &std_miss) != 1) {
        printf("0\n");
        return AC;
    }
    fclose(fans);

    long long user_miss;
    if (fscanf(fuser, "%lld", &user_miss) != 1) {
        printf("0\n");
        return AC;
    }
    fclose(fuser);

    if (user_miss < 0 || user_miss > N) {
        printf("0\n");
        return AC;
    }

    int score;
    if(user_miss >= std_miss){
        score = 90.0 * pow((double)std_miss / (double)user_miss , 1.5);
    }
    else{
        score = 90 + 10.0 * (1 - (double)user_miss / (double)std_miss );
    }


    
    printf("%d\n", score);


    

    return AC;
}
