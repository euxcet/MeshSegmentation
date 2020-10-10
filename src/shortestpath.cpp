#include "shortestpath.h"

ShortestPath::ShortestPath() {

}

void ShortestPath::dijkstra(float edgeMat[][MAXVERTEX], int n) {
    priority_queue<pair<float, int>, vector<pair<float, int> >, greater<pair<float, int> > > pqueue;
    vector<pair<int, float> > edge[MAXVERTEX];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if (i != j && edgeMat[i][j] < MAXFLOAT) {
                edge[i].push_back(make_pair(j, edgeMat[i][j]));
            }
        }
    }
    for(int start = 0; start < n; start++) {
        pqueue.clear();
        pqueue.push(make_pair(start, 0));
        for(int i = 0; i < n; i++) {
            distance[start][i] = MAXFLOAT;
        }
        distance[start][start] = 0;
        while (!pqueue.empty()) {
            pair<float, int> vx = pqueue.top();
            pqueue.pop();
            float v = vx.first;
            int x = vx.second;
            if (v > distance[x]) {
                continue;
            }
            for(int i = 0; i < edge[x].size(); i++) {
                y = edge[x][i].first;
                if (distance[start][y] > distance[start][x] + edge[x][i].second) {
                    distance[start][y] = distance[start][x] + edge[x][i].second;
                    pqueue.push(make_pair(distance[start][y], y));
                }
            }
        }
    }
}