#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef double db;
int n,k,a[MAXN];
db p1,p2,p3;
db x,in,ch;
db cf[3][4];
const db eps=1e-6;
bool IsZero(double v) 
{
    return abs(v)<eps;
}
enum GAUSS_MODE {
  DEGREE, ABS
};
template <typename T>
void GaussianElimination(vector<vector<T>>&a, int limit, GAUSS_MODE mode=ABS) 
{
    if(a.empty()||a[0].empty()) return;
    int h=static_cast<int>(a.size());
    int w=static_cast<int>(a[0].size());
    vector<int> deg(h);
    for(int i=0;i<h;i++) 
        for(int j=0;j<w;j++) 
            deg[i]+=!IsZero(a[i][j]);
    int r=0;
    for(int c=0;c<limit;c++) 
    {
        int id=-1;
        for(int i=r;i<h;i++) 
            if(!IsZero(a[i][c])&&(id==-1||(mode==DEGREE&&deg[i]<deg[id])||(mode==ABS&&abs(a[id][c])<abs(a[i][c]))))
                id=i;
        if(id==-1) continue;
        if(id>r) 
        {
            swap(a[r],a[id]); swap(deg[r],deg[id]);
            for(int j=c;j<w;j++) a[id][j]=-a[id][j];
        }
        vector<int> nonzero;
        for(int j=c;j<w;j++) 
            if(!IsZero(a[r][j])) 
                nonzero.push_back(j);
        T inv_a=1/a[r][c];
        for(int i=r+1;i<h;i++) 
        {
            if(IsZero(a[i][c])) 
                continue;
            T coeff=-a[i][c]*inv_a;
            for (int j:nonzero) 
            {
                if (!IsZero(a[i][j])) deg[i]--;
                a[i][j] += coeff * a[r][j];
                if (!IsZero(a[i][j])) deg[i]++;
            }
        }
        ++r;
    }
    for(r=h-1;r>=0;r--) 
    {
        for(int c=0;c<limit;c++) 
        {
            if(!IsZero(a[r][c])) 
            {
                T inv_a=1/a[r][c];
                for(int i=r-1;i>=0;i--) 
                {
                  if (IsZero(a[i][c])) continue;
                  T coeff = -a[i][c] * inv_a;
                  for (int j = c; j < w; j++) {
                      a[i][j] += coeff * a[r][j];
                  }
                }
              break;
            }
        }
    }
}
 
template <typename T>
vector<T> SolveLinearSystem(vector<vector<T>> a, const vector<T>& b, int w) {
  int h = static_cast<int>(a.size());
  assert(h == static_cast<int>(b.size()));
  if (h > 0) {
    assert(w == static_cast<int>(a[0].size()));
  }
  for (int i = 0; i < h; i++) {
    a[i].push_back(b[i]);
  }
  GaussianElimination(a, w);
  vector<T> x(w, 0);
  for (int i = 0; i < h; i++) {
      bool f=false;
    for (int j = 0; j < w; j++) {
      if (!IsZero(a[i][j])) {
        x[j] = a[i][w] / a[i][j]; 
        f=true;
        break;
      }
    }
    if(!f&&!IsZero(a[i][w])) return vector<T>();
  }
  return x;
}
db solve2(db x,db y){
    vector<vector<db> > a;
    vector<db> b;
    a.resize(3);
    for(int i=0;i<3;i++) a[i].resize(3);
    b.resize(3);
    db z=1.0-x-y;
  //  cout<<"x="<<x<<" y="<<y<<" z="<<z<<endl;
    a[0][0]=ch*(y+z)*p1+(y+z)*(1-ch)-1.0;
    a[0][1]=ch*(x+z)*p2;
    a[0][2]=ch*(x+y)*p3;
    a[1][0]=ch*(y+z)*p1;
    a[1][1]=ch*(x+z)*p2+(x+z)*(1-ch)-1.0;
    a[1][2]=ch*(x+y)*p3;
    a[2][0]=ch*(y+z)*p1;
    a[2][1]=ch*(x+z)*p2;
    a[2][2]=ch*(x+y)*p3+(x+y)*(1-ch)-1.0;
    b[0]=b[1]=b[2]=-1.0;
    auto r=SolveLinearSystem(a,b,3);
    if(!r.size()) return 1e18;
    cout<<"x="<<x<<" y="<<y<<" z="<<z<<" ans="<<p1*r[0]+p2*r[1]+p3*r[2]<<endl;
    return p1*r[0]+p2*r[1]+p3*r[2];
}
int cmp(db x,db y){
    if(x==1e18) return true;
    if(y==1e18) return false;
    return x>y;
}
pair<db,db> solve1(db x){
    db l=0.0,r=1.0-x;
    for(int i=0;i<200;i++){
       db lb=l*2.0/3.0+r/3.0; db rb=l/3.0+r*2.0/3.0;
       if(cmp(solve2(x,lb),solve2(x,rb))) r=rb; else l=lb;
    }
    return make_pair(solve2(x,r),r);
}
int main()
{
    cin>>p1>>p2>>p3>>ch;
    x=0.0; db choice=0.0;
    db l=0.0,r=1.0;
    for(int i=0;i<200;i++){
       db lb=l*2.0/3.0+r/3.0; db rb=l/3.0+r*2.0/3.0;
        cout<<"lb="<<lb<<" rb="<<rb<<" lans="<<solve1(lb).F<<" rans="<<solve1(rb).F<<endl;
       if(cmp(solve1(lb).F,solve1(rb).F)) r=rb; else l=lb;
    }
    auto y=solve1(r);
    cout<<"x="<<l<<" y="<<y.S<<" ans="<<y.F<<endl;
    return 0;
}

