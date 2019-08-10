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
#include<numeric>
using namespace std;

#define maxn 1000007
#define DP_maxn 16
#define INF 1000000007
#define mod 1000000007
#define mst(s,k) memset(s,k,sizeof(s))
#define eps 1e-12
#define f_read freopen("std.in","r",stdin);
#define f_witten freopen("std.out","w",stdout);

typedef long long ll;

struct Edge{
    int from,to,dist;
    Edge(int u,int v,int d):from(u),to(v),dist(d){}
};

/*-------------------------------template End--------------------------------*/
char s1[1000007],s2[1000007]; 
int nxt[1000007];

void KMP(char *s){
    nxt[0] = 0;
    nxt[1] = 0;
    int j;
    int len = strlen(s);
    for(int i = 1;i<len;i++)
    {
        j = nxt[i];
        while(s[i]!=s[j]&&j) j = nxt[j];
        nxt[i+1] = s[i]==s[j]?j+1:0; 
    }
}

void solve(){
    int n = strlen(s1),m = strlen(s2);
    int j=0;
    for(int i = 0;i<n;i++)
    { 
        while(s1[i]!=s2[j]&&j) j = nxt[j];
        if(s1[i]==s2[j]) j++;
        if(j==m){cout<<i-j+2<<" ";}
    }
}

int main(){
    cin>>s1>>s2;
    KMP(s2);
    solve();
    return 0;
}
