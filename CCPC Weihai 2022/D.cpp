#include<bits/stdc++.h>
using namespace std;
int dp[1<<19],w[19],m[27],sc[27];
struct edge{
    int x,y,z;
};
edge a[27]={
    (edge){0,1,2},
    (edge){3,4,5},
    (edge){4,5,6},
    (edge){7,8,9},
    (edge){8,9,10},
    (edge){9,10,11},
    (edge){12,13,14},
    (edge){13,14,15},
    (edge){16,17,18},
    (edge){0,3,7},
    (edge){1,4,8},
    (edge){4,8,12},
    (edge){2,5,9},
    (edge){5,9,13},
    (edge){9,13,16},
    (edge){6,10,14},
    (edge){10,14,17},
    (edge){11,15,18},
    (edge){0,4,9},
    (edge){1,5,10},
    (edge){2,6,11},
    (edge){3,8,13},
    (edge){4,9,14},
    (edge){5,10,15},
    (edge){7,12,16},
    (edge){8,13,17},
    (edge){9,14,18}
};
void Max(int &x,int y){if (x<y) x=y;}
int main(){
    for (int i=0;i<19;i++) scanf("%d",&w[i]);
    for (int i=0;i<27;i++){
        m[i]=(1<<a[i].x)|(1<<a[i].y)|(1<<a[i].z);
        sc[i]=w[a[i].y];
    }
    for (int d=1;d<=19;d++)
    for (int i=1;i<(1<<19);i++) if (__builtin_popcount(i)==d){
        for (int j=0;j<19;j++) if ((i>>j)&1) Max(dp[i],dp[i^(1<<j)]);
        for (int j=0;j<27;j++){
            if (((i>>a[j].y)&1)&&(((i>>a[j].x)&1)^((i>>a[j].z)&1))){
                Max(dp[i],dp[i^m[j]]+sc[j]);
            }
        }
    }
    int T; scanf("%d",&T);
    while (T--){
        int mask=0,cur=0; char s[6];
        for (int i=0;i<5;i++){
            scanf("%s",s); int len=strlen(s);
            for (int j=0;j<len;j++){
                if (s[j]=='#') mask|=1<<cur;
                cur++;
            }
        }
        printf("%d\n",dp[mask]);
    }
    return 0;
}