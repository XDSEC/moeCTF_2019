//Decision's template
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cstdlib>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<string>
#include<cmath>
#include<map>
#include<set>
using namespace std;

#define maxn 50007
#define DP_maxn 16
#define INF 1000000007
#define mod 1000000007
#define mst(s,k) memset(s,k,sizeof(s))
#define eps 1e-12

typedef long long ll;

struct Edge{
    int from,to,dist;
    Edge(int u,int v,int d):from(u),to(v),dist(d){}
};

/*-------------------------------template End--------------------------------*/

struct Node {
    int lgss,rgss,gss,sum;

    int l,r;
}nodes[maxn * 4];

int n,tmp;
int q,l,r;

void pushup(int root) {
    nodes[root].sum = nodes[root << 1].sum + nodes[root << 1 | 1].sum;
    nodes[root].lgss = max(nodes[root << 1].lgss,nodes[root << 1].sum + nodes[root << 1 | 1].lgss);
    nodes[root].rgss = max(nodes[root << 1 | 1].rgss,nodes[root << 1 | 1].sum + nodes[root << 1].rgss);
    nodes[root].gss = max(nodes[root << 1].rgss + nodes[root << 1 | 1].lgss,max(nodes[root << 1].gss,nodes[root << 1 | 1].gss));
}

void build(int root,int l,int r) {
    nodes[root].l = l;
    nodes[root].r = r;
    if(l == r) {
        scanf("%d",&tmp);
        nodes[root].lgss = nodes[root].rgss = nodes[root].gss = nodes[root].sum = tmp;
        return ;
    }
    int mid = (l + r) >> 1;
    build(root << 1,l,mid);
    build(root << 1 | 1,mid + 1,r);
    pushup(root);
}

Node query(int root,int l,int r) {
    if(l <= nodes[root].l && nodes[root].r <= r) return nodes[root];
    int mid = (nodes[root].l + nodes[root].r) >> 1;
    if(r <= mid) return query(root << 1,l,r);
    else if(l > mid) return query(root << 1 | 1,l,r);
    else {
        Node Left,Right,res;
        Left = query(root << 1,l,mid);
        Right = query(root << 1 | 1,mid + 1,r);
        res.sum = Left.sum + Right.sum;
        res.lgss = max(Left.lgss,Left.sum + Right.lgss);
        res.rgss = max(Right.rgss,Right.sum + Left.rgss);
        res.gss = max(Left.rgss + Right.lgss,max(Left.gss,Right.gss));
        return res;
    }
}

int main() {
    scanf("%d %d",&n,&q);
    build(1,1,n);
    for(int i = 1;i <= q;i++) {
        scanf("%d %d",&l,&r);
        if(l > r) swap(l,r);
        Node ans = query(1,l,r);
        printf("%d\n",ans.gss);
    }
    return 0;
}
