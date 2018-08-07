//http://codeforces.com/contest/342/problem/E
#include<bits/stdc++.h>
using namespace std;
typedef  long long ll;
#define mod1 1000000007
#define inf 1000000007
#define mx 1000100
vector<ll>v[mx];
ll arr1[mx];
ll arr2[mx];
ll colour[mx];
bool vis[mx];
ll start[mx],finish[mx],time1,level[mx],depth[mx];
ll tree[mx*3];
ll par1[mx];
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
void dfs_rank(ll u,ll par)
{
    level[u]=1;
    for(ll i=0; i<v[u].size(); i++)
    {
        ll s=v[u][i];
        if(vis[s]||s==par)
            continue;
        depth[s]=depth[u]+1;
        dfs_rank(s,u);
        level[u]+=level[s];
    }
}
ll get_centroid(ll u,ll par,ll n)
{
    ll temp=u;
    for(ll i=0; i<v[u].size(); i++)
    {
        ll s=v[u][i];
        if(par==s||vis[s])
            continue;
        if(level[s]>(n/2))
        {
            temp=get_centroid(s,u,n);
            break;
        }
    }
    return temp;
}
void decompose(ll u,ll par)
{
    dfs_rank(u,-1);
    ll centroid=get_centroid(u,-1,level[u]);
    vis[centroid]=1;
    par1[centroid]=par;
    for(ll i=0; i<v[centroid].size(); i++)
    {
        ll s=v[centroid][i];
        if(vis[s])
            continue;
        decompose(s,centroid);
    }
}
ll dis(ll s,ll t)
{
    ll val=lca(s,t);
    ll temp=depth[s]+depth[t]-2*depth[val];
    return temp;
}
void update(ll u)
{
    colour[u]=0;
    ll x=u;
    u=par1[u];
    while(u!=-1)
    {
        colour[u]=min(colour[u],dis(x,u));
        u=par1[u];
    }
}
void ans(ll u)
{
    ll x=u;
    u=par1[u];
    ll temp=colour[x];
    while(u!=-1)
    {
        temp=min(temp,colour[u]+dis(x,u));
        u=par1[u];
    }
    printf("%lld\n",temp);
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
    for(ll i=1; i<=total; i++)
        colour[i]=inf;
    for(ll i=1; i<total; i++)
    {
        scanf("%lld %lld",&l,&r);
        v[l].push_back(r);
        v[r].push_back(l);
    }
    decompose(1,-1);
    level[1]=1;
    time1=1;
    dfs(1,-1);
    arr1[time1]=1;
    arr2[time1]=1;
    finish[1]=time1;
    init(1,1,time1);
    ll type,val;
    depth[1]=1;
    memset(vis,0,sizeof vis);
    dfs_rank(1,-1);
    update(1);
    for(ll i=1; i<=cnt; i++)
    {
        scanf("%lld %lld",&type,&val);
        if(type==1)
            update(val);
        else
            ans(val);
    }
}
