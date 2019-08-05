#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <math.h>
using namespace std;
const int maxn = 10005;
const int maxm = 20005;
struct node {
    int to, next, w;
} edges[maxm];
int head[maxn], cnt, dp[maxn][15], dep[maxn], dist[maxn];
void addedge(int u, int v, int w) {
    edges[cnt].to = v;
    edges[cnt].w = w;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}
void dfs(int s, int x) {
    dep[s] = dep[x] + 1;
    dp[s][0] = x;
    int t;
    for(int i=1;(1<<i)<=dep[s];++i)
        dp[s][i] = dp[dp[s][i - 1]][i - 1];
    for(int i=head[s];i!=-1;i=edges[i].next) {
        t = edges[i].to;
        if (t == x)
            continue;
        dist[t] = dist[s] + edges[i].w;
        dfs(t, s);
    }
}
int lca(int u, int v) {
    if(dep[v]>dep[u]) swap(u,v);
    for (int i = 14; i >= 0; --i) {
        if ((1 << i) <= (dep[u] - dep[v])) {
            u = dp[u][i];
        }
    }
    if (u == v) return u;
    for(int i=14;i>=0;--i) {
        if ((1 << i) <= dep[u] && (dp[u][i] != dp[v][i])) {
            u = dp[u][i];
            v = dp[v][i];
        }
    }
    return dp[u][0];
}
int slove(int u ,int v) {
    int z = lca(u, v);
    return dist[u] - 2 * dist[z] + dist[v];
}
void init() {
    cnt=0;
    memset(head,-1,sizeof(head));
}
int main() {
    int n,m,u,v,w;
    scanf("%d %d",&n,&m);
    init();
    for(int i=1;i<n;++i) {
        scanf("%d %d %d", &u, &v, &w);
        addedge(u, v, w);
        addedge(v, u, w);
    }
    dep[1] = 0;
    dp[1][0] = 1;
    dfs(1,1);
    for(int i=1;i<=m;++i) {
        scanf("%d %d", &u, &v);
        printf("%d\n", slove(u, v));
    }
    return 0;
}