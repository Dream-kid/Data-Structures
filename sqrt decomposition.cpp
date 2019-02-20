//http://codeforces.com/contest/551/problem/E
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define inf 1000000000000000000
#define mod1 1000000007
vector<pair<ll,ll> >v[1010];
ll track[1000];
ll ans1,ans2;
void b_s(ll pos,ll y)
{
    y-=track[pos];
    if(!v[pos].size())
        return;
    ll lo=0,hi=v[pos].size()-1;
    while(lo<=hi)
    {
        ll mid=(lo+hi)/2;
        if(v[pos][mid].first==y)
            ans2=min(ans2,v[pos][mid].second);
        if(v[pos][mid].first<y)
            lo=mid+1;
        else
            hi=mid-1;
    }
    lo=0,hi=v[pos].size()-1;
    while(lo<=hi)
    {
        ll mid=(lo+hi)/2;
        if(v[pos][mid].first==y)
            ans1=max(ans1,v[pos][mid].second);
        if(v[pos][mid].first<=y)
            lo=mid+1;
        else
            hi=mid-1;
    }
    return;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll total,cnt;
    cin>>total>>cnt;
    ll temp=sqrt(total);
    ll lol=1;
    for(ll i=1; i<=total; i++)
    {
        ll val;
        cin>>val;
        v[lol].push_back({val,i});
        if(i%temp==0)
        {
            sort(v[lol].begin(),v[lol].end());
            lol++;
        }
    }
    sort(v[lol].begin(),v[lol].end());
    for(ll i=1; i<=cnt; i++)
    {
        ll type;
        cin>>type;
        if(type==1)
        {
            ll l,r,val;
            cin>>l>>r>>val;
            ll lo=ceil(l/(1.0*temp));
            ll hi=ceil(r/(1.0*temp));
            bool mark=1;
            if(lo==hi)
                mark=0;
            for(ll j=0; j<v[lo].size(); j++)
            {
                if(v[lo][j].second>=l&&v[lo][j].second<=r)
                    v[lo][j].first+=val;
            }
            sort(v[lo].begin(),v[lo].end());
            lo++;
            if(mark)
            {
                for(ll j=0; j<v[hi].size(); j++)
                {
                    if(v[hi][j].second>=l&&v[hi][j].second<=r)
                        v[hi][j].first+=val;
                }
                sort(v[hi].begin(),v[hi].end());
            }
            hi--;
            for(ll i=lo; i<=hi; i++)
                track[i]+=val;
        }
        else
        {
            ll y;
            cin>>y;
            ans1=-1,ans2=inf;
            for(ll i=1; i<=lol; i++)
                b_s(i,y);
            if(ans1==-1)
                cout<<-1<<endl;
            else
                cout<<ans1-ans2<<endl;
        }
    }
}
