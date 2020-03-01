
//http://www.lightoj.com/volume_showproblem.php?problem=1188
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
#define inf 1000000010000
#define mod1 1000000007
ll track[1000000];
ll arr[1000000];
ll ans[1000000];
bool mark;
vector<pair<ll,pair<ll,pair<ll,ll> > > >v;
ll cnt1;
void add(ll val)
{
    track[val]++;
    if(track[val]==1)
        cnt1++;
}
void reduce(ll val)
{
    track[val]--;
    if(!track[val])
        cnt1--;
}
int main()
{
    ll ts;
    cin>>ts;
    for(ll t=1; t<=ts; t++)
    {
        memset(track,0,sizeof track);
        ll total,cnt;
        cin>>total>>cnt;
        for(ll i=1; i<=total; i++)
            scanf("%d",&arr[i]);
        ll temp=sqrt(cnt);
        for(ll i=1; i<=cnt; i++)
        {
            ll l,r;
            scanf("%d %d",&l,&r);
            v.push_back(make_pair(l/temp,make_pair(r,make_pair(l,i))));
        }
        sort(v.begin(),v.end());
        ll left_pointer=0;
        ll right_pointer=0;
        cnt1=0;
        for(ll i=0; i<v.size(); i++)
        {
            ll l=v[i].second.second.first;
            ll pos=v[i].second.second.second;
            ll r=v[i].second.first;
            ll val;
            while(left_pointer<l)
            {
                val=arr[left_pointer];
                reduce(val);
                left_pointer++;
            }
            while(right_pointer>r+1)
            {
                right_pointer--;
                val=arr[right_pointer];
                reduce(val);
            }
            while(left_pointer>l)
            {
                left_pointer--;
                val=arr[left_pointer];
                add(val);
            }
            while(right_pointer<=r)
            {
                val=arr[right_pointer];
                right_pointer++;
                add(val);
            }
            ans[pos]=cnt1;
        }
        printf("Case %d:\n",t);
        for(ll i=1; i<=cnt; i++)
            printf("%d\n",ans[i]);
        v.clear();
    }
}
