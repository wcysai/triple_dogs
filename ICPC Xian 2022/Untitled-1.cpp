#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
using namespace std;
typedef long long ll;

int V;
vector<int> G[MAXN];
int match[MAXN];
bool used[MAXN];

void add_edge(int u,int v){
    G[u].push_back(v);
    G[v].push_back(u);
}

bool dfs(int v){
    used[v]=1;
    for (int i=0;i<G[v].size();++i){
        int u=G[v][i], w=match[u];
        if (w<0||!used[w]&&dfs(w)){
            match[v]=u;
            match[i]=v;
            return 1;
        }
    }
    return 0;
}

int bipartite_matching(){
    
}