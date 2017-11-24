# http://codeforces.com/contest/869/problem/E
#include <list>

#include <set>
#include <map>
#include <ctime>
#include <stack>
#include <queue>
#include <cmath>
#include <deque>
#include <limits>
#include <string>
#include <cctype>
#include <cstdio>
#include <vector>
#include <bitset>
#include <numeric>
#include <cassert>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <complex>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <algorithm>
using namespace std;

#define sf scanf
#define pf printf
#define pi 2*acos(0.0)
#define ull unsigned long long
#define all(v) v.begin(),v.end()

#define sii(t) scanf("%d",&t)
#define sll(t) scanf("%lld",&t)
#define sll(t) scanf("%lld",&t)
#define ssll(a,b) scanf("%lld%lld",&a,&b)
#define ssd(a,b) scanf("%lf%lf",&a,&b)
#define sssll(a,b,c) scanf("%lld%lld%lld",&a,&b,&c)
#define sssld(a,b,c) scanf("%lf%lf%lf",&a,&b,&c)
#define ssssll(a,b,c,d) scanf("%lld%lld%lld%lld",&a,&b,&c,&d)
#define Case(no) printf("Case %lld: ",++no)
#define nl puts("")
#define p(a) printf("%d\n",a)
#define pll(a) printf("%lld\n",a)
#define P(a) printf("%d ",a)
#define PLL(a) printf("%lld ",a)


#define ff first
#define se second
#define pb push_back
#define ST(v) sort(all(v))
#define gcd(a,b) __gcd(a,b)
#define lcm(a,b) (a*(b/gcd(a,b)))
#define max3(a,b,c) max(a,max(b,c))
#define min3(a,b,c) min(a,min(b,c))
#define maxall(v) *max_element(all(v))
#define minall(v) *min_element(all(v))
#define cover(a,d) memset(a,d,sizeof(a))
#define popcount(i) __builtin_popcount(i)                       //count one
#define output freopen("out.txt","w",stdout)
#define input freopen("in.txt","r",stdin)
#define un(v) ST(v), (v).earse(unique(all(v)),v.end())
#define common(a,b) ST(a), ST(b), a.erase(set_intersection(all(a),all(b),a.begin()),a.end())
#define uncommon(a,b) ST(a), ST(b), a.erase(set_symmetric_difference(all(a),all(b),a.begin()),a.end())
#define flop(m,n,q)             for(ll i=m;i<=n;i+=q)
////============ CONSTANT ===============////
#define mx  (100010)
//#define inf 1000000000000000000
#define eps 1e-9
#define mod1 1000000007

//----------------------Graph Moves----------------
//const int fx[]={+1,-1,+0,+0};
//const int fy[]={+0,+0,+1,-1};
//const int fx[]={+0,+0,+1,-1,-1,+1,-1,+1};   // Kings Move
//const int fy[]={-1,+1,+0,+0,+1,+1,-1,-1};  // Kings Move
//const int fx[]={-2, -2, -1, -1,  1,  1,  2,  2};  // Knights Move
//const int fy[]={-1,  1, -2,  2, -2,  2, -1,  1}; // Knights Move
//------------------------------------------------
using namespace std;
#define inf 3200000
typedef  long long ll;
////=====================================////
ll tree[2510][2510];
void update(ll r,ll c,ll a,ll b,ll x)
{
    ll s=c;
    while(r<=a)
    {
        c=s;
        while(c<=b)
        {
            tree[r][c]+=x;
            c += c & (-c);
        }
        r += r & (-r);
    }
}
ll query(ll a,ll b)
{
    ll sum=0;
    ll s=b;
    while(a)
    {
        b=s;
        while(b)
        {
            sum+=tree[a][b];
            b-= b & (-b);
        }
        a-= a & (-a);
    }
    return sum;
}
int main()
{
    //input;
    ll a,b,c;
    sssll(a,b,c);
    while(c--)
    {
        ll t,r1,c1,r2,c2;
        sll(t);

        ssssll(r1,c1,r2,c2);
        if(t<=2)
        {
            ll ans=1;
            if(t==2) ans*=-1;
            ans*=(r1*2);
            ans*=(c1*3);
            ans*=(r2*4);
            ans*=(c2*5);
            update(r1,c1,a,b,ans);
            update(r2+1,c2+1,a,b,ans);
            update(r1,c2+1,a,b,-ans);
            update(r2+1,c1,a,b,-ans);

        }
        else query(r1,c1)==query(r2,c2) ? pf("Yes\n"):pf("No\n");
    }
}
