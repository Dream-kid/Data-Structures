
//http://www.lightoj.com/volume_showproblem.php?problem=1188
using namespace std;
 #define sf scanf
#define pf printf
#define pi 2*acos(0.0)
#define ull unsigned long long
#define all(v) v.begin(),v.end()
 
#define sii(t) scanf("%d",&t)
#define sll(t) scanf("%lld",&t)
#define sll(t) scanf("%d",&t)
#define ssll(a,b) scanf("%d%d",&a,&b)
#define ssd(a,b) scanf("%lf%lf",&a,&b)
#define sssll(a,b,c) scanf("%lld%lld%lld",&a,&b,&c)
#define ssslf(a,b,c) scanf("%lf%lf%lf",&a,&b,&c)
#define ssssll(a,b,c,d) scanf("%lld%lld%lld%lld",&a,&b,&c,&d)
#define Case(no) printf("Case %d:\n",++no)
#define nl puts("")
#define pll(a) printf("%d\n",a)
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
#define output freopen("out.txt","w",stdout)
#define input freopen("in.txt","r",stdin)
#define flop(m,n,q)             for(ll i=m;i<=n;i+=q)
#define optimize ios::sync_with_stdio(0), cin.tie(0)
////============ CONSTANT ===============////
#define mx  (100010)
#define inf 200000
#define eps 1e-9
#define mod1  1000000009
//queen moves
//int fx[]={0,0,1,-1,1,1,-1,-1};
//int fy[]={1,-1,0,0,1,-1,1,-1};
 
//knight moves
//int fx[]={-2,-2,-1,-1,1,1,2,2};
//int fy[]={-1,1,-2,2,-2,2,-1,1};
typedef int ll;
//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast,no-stack-protector")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx")
//#pragma GCC target("avx,tune=native")
//float __attribute__((aligned(32)))
 
 
////=====================================////
///-----SOURAV CHAKRABORTY-----///
////=====================================////
ll arr[100010];
ll frq[100010];
ll track[100010];
ll cnt;
struct mew
{
    ll left,right,track;
} tree[100010];
bool comp(mew left,mew right)
{
    if(left.left/cnt!=right.left/cnt) return left.left/cnt<right.left/cnt;
    else return left.right/cnt<right.right/cnt;
}
void add(ll idx)
{
    frq[arr[idx]]++;
    if(frq[arr[idx]]==1) cnt++;
}
void remove(ll idx)
{
    frq[arr[idx]]--;
    if(frq[arr[idx]]==0) cnt--;
}
int main()
{
    ll a,t=0;
    sll(a);
    while(a--)
    {
        ll c,d;
        ssll(c,d);
        cnt=sqrt(c);
        for(ll i=0; i<c; i++)sll(arr[i]);
        for(ll i=0; i<d; i++)
        {
            ssll(tree[i].left,tree[i].right);
            tree[i].track=i;
        }
        sort(tree,tree+d,comp);
        cnt=0;
        ll start,end,left_pointer=0,right_pointer=0;
        for(ll i=0; i<d; i++)
        {
            start=tree[i].left-1;
            end=tree[i].right-1;
            while(left_pointer>start)
            {
                left_pointer--;
                add(left_pointer);
            }
            while(left_pointer<start)
            {
                remove(left_pointer);
                left_pointer++;
            }
            while(right_pointer>end+1)
            {
                right_pointer--;
                remove(right_pointer);
            }
            while(right_pointer<=end)
            {
                add(right_pointer);
                right_pointer++;
            }
            track[tree[i].track]=cnt;
        }
        Case(t);
        for(ll i=0; i<d; i++)
            pll(track[i]);
        cover(frq,0);
    }
}
