#include <iostream>
#include <climits>
#include <vector>

const long long INF = LONG_MAX;

struct Edge{
    long long start, end;
    long long weight;
    Edge(long long start, long long end, long long weight): start(start), end(end), weight(weight) {}
};

struct Graph {
    std::vector<Edge> edges;
    long long vertices;

    explicit Graph(long long vertices) : vertices(vertices + 1) {}

    void input(long long m) {
        for (long long i = 0; i < m; ++i) {
            int v1;
            int v2;
            int w;
            std::cin >> v1 >> v2 >> w;
            this->edges.emplace_back(v1 - 1, v2 - 1, w);
        }
        for (long long i = 0; i < this->vertices; ++i) {
            this->edges.emplace_back(this->vertices, i, 0);
        }
    }
};

bool BellmanFord(Graph* graph, std::vector<long long>& distances) {
    for (int i = 0; i < graph->vertices - 1; ++i) {
        distances[i] = INF;
    }
    for (int i = 0; i < graph->vertices - 1; ++i) { // расстояния
        for (auto &edge: graph->edges) {
            if (distances[edge.start] < INF) {
                distances[edge.end] = std::min(distances[edge.start] + edge.weight, distances[edge.end]);
            }
        }
    }

    for (auto &edge: graph->edges) { // ищем цикл
        if (distances[edge.start] < INF) {
            if (distances[edge.start] + edge.weight < distances[edge.end]) {
                return true;
            }
        }
    }
    for (auto &edge: graph->edges) {
        edge.weight = edge.weight + distances[edge.start] - distances[edge.end];
    }
    return false;
}

void DijkstraAlgorithm(Graph* graph, std::vector<long long>& distances) {
    for (long long vertice = 0; vertice < graph->vertices - 1; ++vertice) {
        std::vector<long long> distances_from_vertice(graph->vertices - 1, INF);
        distances_from_vertice[vertice] = 0;

        std::vector<bool> completed(graph->vertices - 1, false);

        for (long long i = 0; i < graph->vertices - 1; ++i) {
            long long start = -1;

            for (long long j = 0; j < graph->vertices - 1; ++j) { // поиск минимума
                if ((start == -1 or distances_from_vertice[j] < distances_from_vertice[start]) and !completed[j]) {
                    start = j;
                }
            }

            if (distances_from_vertice[start] == INF) break;
            completed[start] = true;

            for (auto &edge: graph->edges) {
                if (edge.start == start) {
                    distances_from_vertice[edge.end] = std::min(distances_from_vertice[edge.end],
                                                                distances_from_vertice[edge.start] + edge.weight);
                }
            }
        }

        for (long long i = 0; i < graph->vertices - 1; ++i) {
            if (distances_from_vertice[i] == INF) {
                std::cout << "inf";
            } else {
                std::cout << distances_from_vertice[i] - distances[vertice] + distances[i];
            }
            std::cout << ' ';
        }

        std::cout << std::endl;
    }
}

int main() {
    long long n;
    long long m;
    std::cin >> n >> m;
    auto *graph = new Graph(n);
    graph->input(m);
    std::vector<long long> distances(graph->vertices);
    bool negative_cycle = BellmanFord(graph, distances);
    if (negative_cycle) {
        std::cout << "Negative cycle";
    } else {
        DijkstraAlgorithm(graph, distances);
    }
}