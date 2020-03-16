#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
#include <queue>
#define MAX_LEN 52

using namespace std;

struct info {
    int key;
    int x;
    int y;
    int dist;
};
int N, M;
int dx[] = {0, -1, 0, 1};
int dy[] = {-1, 0, 1, 0};
char map[MAX_LEN][MAX_LEN];
bool visited[MAX_LEN][MAX_LEN][1<<6] = {false, };
    
void bfs(info p) {

    queue<info> q;
    visited[p.x][p.y][p.key] = true;
    q.push(p);

    while(!q.empty()) {
        int x = q.front().x;
        int y = q.front().y;
        int key = q.front().key;
        int dist = q.front().dist;
        q.pop();

        if (map[x][y] == '1') {
            
            cout << dist << endl;
            return;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;   // out of range 
            if (map[nx][ny] == '#') continue;   // blocked with walls
            if (visited[nx][ny][key]) continue; // checked if it is visited or not
            if ('A' <= map[nx][ny] && map[nx][ny] <= 'F') { // blocked with doors
                if (!(key & (1<<(map[nx][ny] - 'A')))) {   // check whether it can be opened or not
                    continue;   // pass this location as there is no key
                } 
            }
            if ('a' <= map[nx][ny] && map[nx][ny] <= 'f') { // find the key
                if (!(key & (1<<(map[nx][ny] - 'a')))) {  // add additional key
                    info to;
                    to.x = nx, to.y = ny, to.key = key | (1<<(map[nx][ny] - 'a')), to.dist = dist + 1;
                    visited[to.x][to.y][to.key] = true;
                    q.push(to);
                    continue;                    
                }
            }
            
            info to;
            to.x = nx, to.y = ny, to.key = key, to.dist = dist + 1;
            visited[nx][ny][key] = true;
            q.push(to);
        } 
    }

    cout << -1 << endl;
    return;
}

int main() {

    char c;
    info f;

    cin >> N >> M;

    if (N == 1 && M == 1) {
        cout << -1 << endl;
        return 0;
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
                
            cin >> map[i][j];
            if (map[i][j] == '0') {
                f.x = i;
                f.y = j;                
                f.key = 0;
                f.dist = 0;
                map[i][j] = '.';                    
            }
        }
    }   

    // printAll();
    bfs(f);
    return 0;
}
