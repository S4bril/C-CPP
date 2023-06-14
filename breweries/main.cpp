#include <iostream>

long long myMin(long long x, long long y){
    if(x < y) return x;
    return y;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    long long tab[n];
    long long SUM = 0;
    for(int i = 0; i < n; i++) {
        std::cin >> tab[i];
        SUM += tab[i];
    }
/* O(n^2)
    unsigned long long max_ds = 0;
    unsigned long long curr_ds;

    for (int i = 0; i < n - 1; i++){
        curr_ds = 0;
        for(int j = i + 1; j < n; j++){
            curr_ds += tab[j - 1];
            temp = myMin(curr_ds, SUM - curr_ds);
            if (temp > max_ds) max_ds = temp;
        }
    }
    std::cout << max_ds;
*/
//Gąsieniczka
    long long max = 0;
    long long head = 0;
    long long tail = 0;
    long long ds = 0; // length beetwen head and tail

    while(tail < n){
        ds += tab[head++];
        head = head % n;
        if(ds == SUM / 2) {
            max = ds;
            break;
        }
        if(ds < SUM / 2){
            if(ds > max) max = ds;
            continue;
        }
        while(tail != head && ds > SUM / 2)
            ds -= tab[tail++];

        if(ds == SUM / 2) {
            max = ds;
            break;
        }
        if(ds < SUM / 2){
            if(ds > max) max = ds;
            continue;
        }
    }
    std::cout << max << "\n";
    return 0;
}
