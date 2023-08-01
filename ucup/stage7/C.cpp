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
int n,k,a[MAXN];
double x,in,ch;
double cf[2][3];
const double eps=1e-6;
int main()
{
    cin>>in>>ch;
    x=0.0; double choice=0.0;
    double ans=1e9;
    for(int i=0;i<=100000;i++){
        x+=0.00001;
        double n1=(1-x)*ch*in+(1-x)*(1-ch);
        double n2=x*ch*(1-in);
        double n3=1.0;
        double m1=(1-x)*ch*in;
        double m2=x*ch*(1-in)+x*(1-ch);
        double m3=1.0;
        double c=(n2*m1)/(1-m2)+n1;
        double d=n2*m3/(1-m2)+n3;
        c=1.0-c;
        if(c<eps||c>1-eps) continue; 
    //    cout<<c<<endl;
        double a=d/c;
        double b=m1/(1-m2)*a+m3/(1-m2);
        double z=in*a+(1-in)*b;
        if(z<ans){
            ans=z;
            choice=x;
        //    cout<<"a="<<a<<" b="<<b<<" z="<<z<<endl;
        }
    }
    cout<<choice<<" "<<ans<<endl;
    return 0;
}

