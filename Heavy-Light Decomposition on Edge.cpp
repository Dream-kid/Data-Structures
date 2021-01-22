//https://www.spoj.com/problems/QTREE/

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MX 100005
ll cur_pos;
ll temp[MX];
vector <ll> adj[MX];
ll parent[MX], depth[MX], heavy[MX], head[MX], pos[MX];
ll arr[MX];
ll tree[100010*3];
vector<pair<ll,pair<ll,ll> > >st;
ll dfs(ll u)
{
    ll sz = 1, mx = 0;

    for (ll i = 0; i < adj[u].size(); i++)
    {
        ll v = adj[u][i];

        if (v != parent[u])
        {
            parent[v] = u, depth[v] = depth[u] + 1;

            ll subtree_sz = dfs(v);
            sz += subtree_sz;
            if (subtree_sz > mx)
            {
                mx = subtree_sz, heavy[u] = v;
            }
        }
    }

    return sz;
}
void decompose(ll u, ll h)
{
    head[u] = h, pos[u] = cur_pos,temp[cur_pos++]=u;

    if (heavy[u] != -1)
        decompose(heavy[u], h);
    for (ll i = 0; i < adj[u].size(); i++)
    {
        ll v = adj[u][i];

        if (v != parent[u] && v != heavy[u])
            decompose(v, v);
    }
}

void gen(ll n)   //Complexity: O(V+E)
{
    for(ll i = 1; i <= n; i++)
        heavy[i] = -1;
    cur_pos = 1;

    dfs(1);
    decompose(1, 0);
}
void merge(ll node)
{
    tree[node]=max(tree[2*node],tree[2*node+1]);
}
void init(ll node,ll l,ll r)
{
    if(l==r)
    {
        tree[node]=arr[temp[l]];
        return;
    }
    init(2*node,l,(l+r)/2);
    init(2*node+1,(l+r)/2+1,r);
    merge(node);
}
void update(ll node,ll l,ll r,ll p,ll q,ll val)
{
    if(r<p||q<l)
        return;
    if(l>=p&&r<=q)
    {
        tree[node]=val;
        return;
    }
    update(2*node,l,(l+r)/2,p,q,val);
    update(2*node+1,(l+r)/2+1,r,p,q,val);
    merge(node);
}
ll segment_tree_query(ll node,ll l,ll r,ll p,ll q)
{
    if(r<p||q<l)
        return -1000000000;
    if(l>=p&&r<=q)
        return tree[node];
    return max(segment_tree_query(2*node,l,(l+r)/2,p,q),
               segment_tree_query(2*node+1,(l+r)/2+1,r,p,q));
}

ll query(ll a, ll b,ll total)
{
    ll res = 0;
    for (; head[a] != head[b]; b = parent[head[b]])
    {
        if (depth[head[a]] > depth[head[b]])
            swap(a, b);
        ll cur_heavy_path_max = segment_tree_query(1,1,total,pos[head[b]], pos[b]);
        res = max(res, cur_heavy_path_max);
    }
    if (depth[a] > depth[b])
        swap(a, b);
    ll last_heavy_path_max = segment_tree_query(1,1,total,pos[a]+1, pos[b]); //decrease one child pos[a]+1
    res = max(res, last_heavy_path_max);                                     //calculate from next child
    return res;
}
int main()
{
    ll ts;
    scanf("%lld",&ts);
    for(ll t=1; t<=ts; t++)
    {
        ll total;
        scanf("%lld",&total);
        for(ll i=1; i<total; i++)
        {
            ll u,v,c;
            scanf("%lld %lld %lld",&u,&v,&c);
            adj[u].push_back(v);
            adj[v].push_back(u);
            st.push_back(make_pair(u,make_pair(v,c)));
        }
        gen(total);
        for(ll i=0; i<st.size(); i++)
        {
            ll a=st[i].first;
            ll b=st[i].second.first;
            ll c=st[i].second.second;
            if(parent[a]==b)
                arr[a]=c;
            else
                arr[b]=c;
        }
        init(1,1,total);
        char pp[100];
        while(1)
        {
            scanf("%s",&pp);
            if(pp[0]=='Q')
            {
                ll a,b;
                scanf("%lld %lld",&a,&b);
                printf("%lld\n",query(a,b,total));
            }
            else if(pp[0]=='C')
            {
                ll a1,b1;
                scanf("%lld %lld",&a1,&b1);
                ll a=st[a1-1].first;
                ll b=st[a1-1].second.first;
                if(parent[a]==b)
                    update(1,1,total,pos[a],pos[a],b1);
                else
                    update(1,1,total,pos[b],pos[b],b1);

            }
            else
                break;

        }
        for(ll i=1; i<=total; i++)
            adj[i].clear();
        st.clear();
        memset(tree,0,sizeof tree);
    }
}
