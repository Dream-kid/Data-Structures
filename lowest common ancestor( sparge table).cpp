//https://uva.onlinejudge.org/external/122/12238.pdf
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
vector<pair<ll,ll> >v[100010];
ll parent[100010];
ll visited[100010];
ll distance1[100010];
ll depth[100010];
ll sparge_table[100010][20];
void bfs()
{
    cover(visited,0);
    cover(parent,0);
    queue<ll>q;
    q.push(0);
    visited[0]=1;
    while(!q.empty())
    {
        ll u=q.front();
        q.pop();
        for(ll i=0; i<v[u].size(); i++)
        {
            ll s=v[u][i].ff;
            ll cost=v[u][i].se;
            if(visited[s]) continue;
            visited[s]=1;
            q.push(s);
            distance1[s]=cost+distance1[u];
            depth[s]=depth[u]+1;
            parent[s]=u;
        }
    }
}
void lca_init(ll a)
{
    cover(sparge_table,-1);
    for(ll i=0; i<a; i++)
    {
        sparge_table[i][0]=parent[i];
    }
    for(ll j=1; (1<<j)<a; j++)
    {
        for(ll i=0; i<a; i++)
        {
            if(sparge_table[i][j-1]!=-1)
                sparge_table[i][j]=sparge_table[sparge_table[i][j-1]][j-1];
        }
    }
}
ll lca(ll s,ll t,ll a)
{
    if(depth[t]>depth[s]) swap(s,t);
    ll log=1;
    while(1)
    {
        ll next=log+1;
        if((1<<next) <=depth[s]) log++;
        else break;
    }
    for(ll i=log; i>=0; i--)
    {
        if(depth[s]- (1<<i) >= depth[t])
        {
            s=sparge_table[s][i];
        }
    }
    if(s==t) return s;
    for(ll i=log; i>=0; i--)
    {
        if(sparge_table[s][i]!=sparge_table[t][i]&&sparge_table[s][i]!=-1)
        {
            s=sparge_table[s][i];
            t=sparge_table[t][i];
        }
    }
    return parent[t];
}
int main()
{
   // input;
    ll a,b;
    while(sll(a)==1)
    {
        if(a==0) return 0;
        for(ll i=1; i<a; i++)
        {
            ll p,cost;
            ssll(p,cost);
            v[i].pb(make_pair(p,cost));
            v[p].pb(make_pair(i,cost));
        }
        bfs();
        a++;
        lca_init(a);
        ll o,l1=0;
        sll(o);
        while(o--)
        {
            ll p,q,a;
            ssll(p,q);
           // if(depth[q]>depth[p]) swap(p,q);
            ll s=lca(p,q,a);
            ll l=distance1[p]+distance1[q]-2*distance1[s];
            if(l1) pf(" ");
            l1++;
            pf("%lld",l);
        }
        pf("\n");
        for(ll i=0; i<=a; i++)
        {
            v[i].clear();
        }
    }
}
