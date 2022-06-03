#include "list_graph.h"

int getNumShortestPaths(const IGraph& graph, const int& from, const int& to) {
    vector<int> cnt(graph.verticesCount(), 0);

    vector<int> cnt_btw_points(graph.verticesCount(), INT16_MAX);
    cnt[from] = 1;
	cnt_btw_points[from] = 0;

    queue<int> q;
    q.push(from);


    while (!q.empty()) {
        int vertex = q.front();
        q.pop();

		for (auto child : graph.getNextVertices(vertex)) {
			if (cnt_btw_points[child] > cnt_btw_points[vertex] + 1) {
				cnt_btw_points[child] = cnt_btw_points[vertex] + 1;
				cnt[child] = cnt[vertex];
				q.push(child);
			} else if (cnt_btw_points[child] == cnt_btw_points[vertex] + 1) {
				cnt[child] += cnt[vertex];
			}
		}
    }

    return cnt[to];
}
