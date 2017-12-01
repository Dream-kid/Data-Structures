//http://acm.hdu.edu.cn/showproblem.php?pid=3371
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
#define ssslf(a,b,c) scanf("%lf%lf%lf",&a,&b,&c)
#define ssssll(a,b,c,d) scanf("%lld%lld%lld%lld",&a,&b,&c,&d)
#define Case(no) printf("CASE# %lld:\n",++no)
#define nl puts("")
#define pll(a) printf("%lld\n",a)
#define P(a) printf("%d ",a)
#define PLL(a) printf("%lld ",a)


#define ff first
#define pb push_back
#define mp make_pair
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
#define inf 10000000000000000
#define eps 1e-9
#define mod 10007
typedef long long ll;
////=====================================////
ll par[1010];
ll rank1[1010];// for tree short
vector<pair<ll,ll> >v[1010];
ll dup_check[510][510];
ll find(ll a)
{
    return(par[a]==a)?a:(par[a]=find(par[a]));
}
int main()
{
    //input;
    ll a;
    sll(a);
    while(a--)
    {
        ll b,c,d,p,q,cost;
        sssll(b,c,d);
        cover(rank1,0);
        for(ll i=1; i<=b; i++)
        {
            par[i]=i;
            for(ll j=1; j<=b; j++) dup_check[i][j]=inf;
        }
        for(ll i=1; i<=c; i++)
        {
            sssll(p,q,cost);
            dup_check[p][q]=min( dup_check[p][q],cost);
        }

        for(ll i=1; i<=b; i++)
        {
            for(ll j=1; j<=b; j++)
            {
                if(dup_check[i][j]==inf||i==j)continue;
                v[dup_check[i][j]].pb(mp(i,j));
            }
        }
        ll o,u,v1;
        while(d--)
        {
            sll(p);
            p--;
            sll(o);
            ll s;
            while(p--)
            {
                u=find(o);
                sll(s);
                v1=find(s);
                if(u!=v1)
                {
                    if(rank1[u]>rank1[v1])
                        par[v1]=u;
                    else
                    {
                        par[u]=v1;
                        if(rank1[u]==rank1[v1]) rank1[v1]++;
                    }
                }
            }
        }
        ll sum=0;
        for(ll i=0; i<=1000; i++)
        {
            if(!v[i].size()) continue;
            for(ll k=0; k<v[i].size(); k++)
            {
                p=v[i][k].ff;
                q=v[i][k].se;
                u=find(p);
                v1=find(q);
                if(u!=v1)
                {
                    sum+=i;
                    if(rank1[u]>rank1[v1])
                        par[v1]=u;
                    else
                    {
                        par[u]=v1;
                        if(rank1[u]==rank1[v1]) rank1[v1]++;
                    }
                }
            }
                v[i].clear();
            
        }
        ll cnt=0;
        for(ll i=1; i<=b; i++)
        {
            if(par[i]==i)
                cnt++;
        }
        if(cnt<=1) pll(sum);
        else pf("-1\n");
    }
}
