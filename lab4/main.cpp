#include <iostream>
#include <vector>
#include <string>


void ZFunc(const std::string& text, std::vector<int>& result) {
    result[0] = text.size();
    for (int i = 1, left = 0, right = 0; i < text.size(); ++i) {
//  если смотрим на букву, которая в интервале
        if (i <= right) {
            result[i] = std::min(right - i + 1, result[i - left]);
        }
        while ((i + result[i] < text.size()) and (text[result[i]] == text[i + result[i]])) {
            ++result[i];
        }
        if (i + result[i] - 1 > right) {
            left = i;
            right = i + result[i] - 1;
        }
    }
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::string text;
    std::string pattern;
    std::cin >> text >> pattern;
    std::string concatenationTextAndPattern = pattern + "$" + text;
    std::vector<int> zFunctionResult(concatenationTextAndPattern.size());

    ZFunc(concatenationTextAndPattern, zFunctionResult);

    for (int i = pattern.size(); i < concatenationTextAndPattern.size(); ++i) {
        if (zFunctionResult[i] == pattern.size()) {
            std::cout << i - pattern.size() - 1 << '\n';
        }
    }

}
