#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <string>


struct Node {
    int x;
    int height;
    Node(int x, int height) : x(x), height(height) {};
};


int find_max_hist(const std::vector<int>& hist) {
    std::stack<Node> s;
    s.push(Node(0, -1));
    int max_area = 0;
    int area;
    int n = int(hist.size());
    for (int i = 1; i <= n + 1; ++i) {
        int h = i <= n ? hist[i - 1] : 0;
        int x = i;
        int h_prev;
        while (h <= s.top().height) {
            x = s.top().x;
            h_prev = s.top().height;
            s.pop();
            area = h_prev * (i - x);
            max_area = std::max(area, max_area);
        }
        s.push(Node(x, h));
    }
    return max_area;
}


int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> matrix(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i) {
        std::string line;
        std::cin >> line;
        for (int j = 0; j < m; ++j) {
            int value = line[j] - 48;
            matrix[i][j] = (value + 1) % 2;
        }
    }

    int max_area = find_max_hist(matrix[0]);
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (matrix[i][j] != 0) {
                matrix[i][j] += matrix[i - 1][j];
            }
        }
        max_area = std::max(max_area, find_max_hist(matrix[i]));
    }


    std::cout << max_area << std::endl;
}
