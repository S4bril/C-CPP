#include <iostream>
#include <algorithm>

using namespace std;

void ReadRow(long long table[], string input, int length, int powers[]){
    for(int i = 0; i<length; i++)
        table[i] = (long long)powers[(int)(input[i] - '0')];
}
long long LongMax(long long x, long long y){
    if (x > y)
        return x;
    return y;
}

int main() {
    //---------------------------prepare-data-------------------------
    int powers_of_7[10] = {1, 7,	49,	343,	2401,16807,
                           117649, 823543,	5764801, 40353607};

    int w, k;
    cin >> w >> k;

    long long rows[4][k];

    for(int i = 0; i < k; i++)
        for(int j = 0; j < 3; j++)
            rows[j][i] = 0;

    string row_in;
    int first, second, third, fourth; //indexes of rows (first -> oldest, fourth -> newest)
    int max_temp_1, max_temp_2;

    //--------------------start-dynamic-programing-----------------
    for (int i = 0; i < w; i++){
        //-----------get-indexes-in-ith-iteration-------------
        first = i % 4;
        second = (i + 1) % 4;
        third = (i + 2) % 4;
        fourth = (i + 3) % 4;
        //------------------read-new-row----------------------
        cin>>row_in;
        ReadRow(rows[fourth], row_in, k, powers_of_7);

        //---find-optimal-path-from-second-row-to-fourth-row---
        rows[fourth][0] += rows[second][1];
        rows[fourth][k - 1] += rows[second][k - 2];
        for(int j = 1; j < k - 1; j++)
            rows[fourth][j] += LongMax(rows[second][j - 1], rows[second][j + 1]);

        //--------------------fix-third-row------------------- (smth is bad)
        if (i >= 2) {

            rows[third][0] = rows[third][0] - rows[first][1] + LongMax(rows[first][1], rows[fourth][2]);
            rows[third][k - 1] =
                    rows[third][k - 1] - rows[first][k - 2] + LongMax(rows[first][k - 2], rows[fourth][k - 3]);
            if (k > 3) {
                max_temp_1 = LongMax(rows[first][0], rows[first][2]);
                rows[third][1] = rows[third][1] - max_temp_1 + LongMax(max_temp_1, rows[fourth][3]);
                max_temp_1 = LongMax(rows[first][k - 1], rows[first][k - 3]);
                rows[third][k - 2] = rows[third][k - 2] - max_temp_1 + LongMax(max_temp_1, rows[fourth][k - 4]);
            }
            for (int j = 2; j < k - 2; j++) {
                max_temp_1 = LongMax(rows[first][j - 1], rows[first][j + 1]);
                max_temp_2 = LongMax(rows[fourth][j - 2], rows[fourth][j + 2]);
                rows[third][j] = rows[third][j] - max_temp_1 + LongMax(max_temp_1, max_temp_2);
            }

        }
        for (int j = 0; j < k; j++)
            cout << rows[first][j] << " ";
        cout << "\n";

        for (int j = 0; j < k; j++)
            cout << rows[second][j] << " ";
        cout << "\n";

        for (int j = 0; j < k; j++)
            cout << rows[third][j] << " ";
        cout << "\n";

        for (int j = 0; j < k; j++)
            cout << rows[fourth][j] << " ";
        cout << "\n\n";

    }

    //---------------------------result----------------------------
    long long max_val = 0;

    for(int i = 0; i < k; i++)
        max_val = LongMax(max_val, rows[fourth][i]);

    cout << max_val << "\n";

    return 0;
}
//57
