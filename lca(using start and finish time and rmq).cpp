#include<bits/stdc++.h>
using namespace std;
typedef  long long ll;
#define mod1 1000000007
#define inf 1000000007
//ios_base::sync_with_stdio(0);
//cin.tie(0);
#define mx 100010
vector<ll>v[mx];
ll arr1[mx];
ll arr2[mx];
ll start[mx],finish[mx],time1,level[mx];
ll tree[mx*3];
void merge(ll node)
{
    if(arr2[tree[2*node]]>arr2[tree[2*node+1]])
        tree[node]=tree[2*node+1];
    else
        tree[node]=tree[2*node];
}
void init(ll node,ll l,ll r)
{
    if(l==r)
    {
        tree[node]=l;
        return;
    }
    init(2*node,l,(l+r)/2);
    init(2*node+1,(l+r)/2+1,r);
    merge(node);
}
ll query(ll node,ll l,ll r,ll p,ll q)
{
    if(r<p||q<l)
        return 0;
    if(l>=p&&r<=q)
        return tree[node];
    ll s=query(2*node,l,(l+r)/2,p,q);
    ll t=query(2*node+1,(l+r)/2+1,r,p,q);
    if(arr2[s]>arr2[t])
        return t;
    else
        return s;
}
void dfs(ll u,ll par)
{
    arr1[time1]=u;
    arr2[time1]=level[u];
    start[u]=time1;
    finish[u]=time1;
    for(ll i=0; i<v[u].size(); i++)
    {
        ll s=v[u][i];
        if(s==par)
            continue;
        level[s]=level[u]+1;
        time1++;
        dfs(s,u);
        time1++;
        finish[u]=time1;
        arr1[time1]=u;
        arr2[time1]=level[u];
    }
}
ll lca(ll l,ll r)
{
    ll l1=min(start[l],start[r]);
    ll r1=max(finish[l],finish[r]);
    return arr1[query(1,1,time1,l1,r1)];
}
int main()
{
    time1=1;
    arr1[1]=1;
    arr2[0]=inf;
    arr2[1]=1;
    level[1]=1;
    ll total,cnt,l,r;
    scanf("%lld %lld",&total,&cnt);
    for(ll i=1; i<total; i++)
    {
        scanf("%lld %lld",&l,&r);
        v[l].push_back(r);
        v[r].push_back(l);
    }
    dfs(1,-1);
    arr1[time1]=1;
    arr2[time1]=1;
    finish[1]=time1;
    init(1,1,time1);
}
