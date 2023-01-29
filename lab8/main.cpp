#include <iostream>
#include <algorithm>
#include <vector>


struct Segment {
    int l;
    int r;
    int idx;

    explicit Segment(int l=0, int r=0, int idx=0): l(l), r(r), idx(idx) {}
};


bool select_segments(std::vector<Segment>& segments, std::vector<Segment>& ans, int m) {
    int need_point = 0;
    int max_point = 0;
    Segment best_segment_to_cover_need_point;
    for (Segment &segment: segments) {
        if (segment.l > need_point) {
            ans.push_back(best_segment_to_cover_need_point);
            need_point = max_point;
            if (need_point >= m)
                break;
        }
        if (segment.l <= need_point and segment.r > max_point) {
            max_point = segment.r;
            best_segment_to_cover_need_point = segment;
        }
    }
    if (need_point < m) {
        ans.push_back(best_segment_to_cover_need_point);
        need_point = max_point;
    }
    return need_point >= m;
}


int main() {
    int n, m;
    std::cin >> n;
    std::vector<Segment> segments(n);
    std::vector<Segment> ans;
    for (int i = 0; i < n; ++i) {
        int l, r;
        std::cin >> l >> r;
        segments[i] = Segment(l, r, i);
    }
    std::cin >> m;
    std::sort(segments.begin(), segments.end(), [](Segment a, Segment b) {return a.l < b.l;});
    bool solution_exist = select_segments(segments, ans, m);

    if (solution_exist) {
        std::sort(ans.begin(), ans.end(), [](Segment a, Segment b) { return a.idx < b.idx; });
        std::cout << ans.size() << '\n';
        for (Segment &seg: ans) {
            std::cout << seg.l << ' ' << seg.r << '\n';
        }
    } else {
        std::cout << 0 << '\n';
    }
}