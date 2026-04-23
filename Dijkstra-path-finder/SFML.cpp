#include <bits/stdc++.h>
using namespace std;

#define INF 1e9
typedef pair<int, pair<int,int>> Node;

int n = 10, m = 10;
vector<vector<int>> grid(n, vector<int>(m, 0));
vector<vector<int>> dist(n, vector<int>(m, INF));
vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(m, {-1,-1}));

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool isValid(int x, int y) {
    return x>=0 && y>=0 && x<n && y<m && grid[x][y] == 0;
}

void dijkstra(pair<int,int> src) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    dist[src.first][src.second] = 0;
    pq.push({0, src});

    while(!pq.empty()) {
        auto curr = pq.top(); pq.pop();
        int d = curr.first;
        int x = curr.second.first;
        int y = curr.second.second;

        for(int i=0;i<4;i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(isValid(nx, ny) && dist[nx][ny] > d + 1) {
                dist[nx][ny] = d + 1;
                parent[nx][ny] = {x, y};
                pq.push({dist[nx][ny], {nx, ny}});
            }
        }
    }
}

void printGrid(pair<int,int> src, pair<int,int> dest) {
    vector<vector<char>> display(n, vector<char>(m, '.'));

    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(grid[i][j] == 1)
                display[i][j] = '#';

    int x = dest.first, y = dest.second;
    while(parent[x][y] != make_pair(-1,-1)) {
        display[x][y] = '*';
        auto p = parent[x][y];
        x = p.first;
        y = p.second;
    }

    display[src.first][src.second] = 'S';
    display[dest.first][dest.second] = 'D';

    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++)
            cout << display[i][j] << " ";
        cout << endl;
    }
}

int main() {
    cout << "Enter number of obstacles: ";
    int k; cin >> k;

    cout << "Enter obstacle coordinates:\n";
    for(int i=0;i<k;i++) {
        int x,y; cin >> x >> y;
        grid[x][y] = 1;
    }

    pair<int,int> src, dest;
    cout << "Enter source (x y): ";
    cin >> src.first >> src.second;

    cout << "Enter destination (x y): ";
    cin >> dest.first >> dest.second;

    dijkstra(src);
    printGrid(src, dest);

    return 0;
}