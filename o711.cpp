#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/**
 * 根據當前累積體積與杯子參數計算水位高度
 */
int calculate_height(int current_v, int w1, int w2, int h1, int v1_limit) {
    if (current_v <= v1_limit) {
        // 水位在底層長方體
        return current_v / (w1 * w1);
    } else {
        // 水位已進入頂層長方體
        int remaining_v = current_v - v1_limit;
        return h1 + (remaining_v / (w2 * w2));
    }
}

int main() {
    // 優化輸入輸出速度
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    int w1, w2, h1, h2;
    cin >> w1 >> w2 >> h1 >> h2;

    // 預先計算底層容量與總容量
    int v1_limit = w1 * w1 * h1;
    int v_total_max = v1_limit + (w2 * w2 * h2);

    int current_volume = 0;
    int current_height = 0;
    int max_increase = 0;

    for (int i = 0; i < n; ++i) {
        int v_input;
        cin >> v_input;

        int old_height = current_height;

        // 更新總體積，且不能超過杯子上限 [1]
        current_volume = min(current_volume + v_input, v_total_max);

        // 計算新高度
        current_height = calculate_height(current_volume, w1, w2, h1, v1_limit);

        // 計算本次上升高度並更新最大值 [2]
        int increase = current_height - old_height;
        if (increase > max_increase) {
            max_increase = increase;
        }
    }

    // 輸出最終的最大上升量 [2]
    cout << max_increase << endl;

    return 0;
}