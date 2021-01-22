//https://lightoj.com/problem/aladdin-and-the-return-journe
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
#define MX 100000
#define mod1  1000000007
#define check(n,i) n&1<<i
#define set(n,i) n|1<<i
ll cur_pos;
ll temp[MX];
vector <ll> adj[MX];
ll parent[MX], depth[MX], heavy[MX], head[MX], pos[MX];
ll arr[MX];
ll tree[100010*3];
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
    return;
}

void gen(ll n)   //Complexity: O(V+E)
{
    for(ll i = 1; i <= n; i++)
        heavy[i] = -1;
    cur_pos = 1;
    ll temp= dfs(1);
    decompose(1, 0);
}
void merge(ll node)
{
    tree[node]=(tree[2*node]+tree[2*node+1]);
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
        return 0;
    if(l>=p&&r<=q)
        return tree[node];
    return (segment_tree_query(2*node,l,(l+r)/2,p,q)+
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
        res +=  cur_heavy_path_max;
    }
    if (depth[a] > depth[b])
        swap(a, b);
    ll last_heavy_path_max = segment_tree_query(1,1,total,pos[a], pos[b]); //decrease one child pos[a]+1
    res += last_heavy_path_max;                                     //calculate from next child
    return res;
}
int main()
{
    ll ts;
    cin>>ts;
    for(ll t=1; t<=ts; t++)
    {
        ll total;
        cin>>total;
        for(ll i=1; i<=total; i++)
            cin>>arr[i];
        for(ll i=1; i<total; i++)
        {
            ll u,v;
            cin>>u>>v;
            u++;
            v++;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        gen(total);
        init(1,1,total);
        cout<<"Case "<<t<<":"<<endl;
        ll cnt;
        cin>>cnt;
        while(cnt--)
        {
            ll type;
            cin>>type;
            if(!type)
            {
                ll l,r;
                cin>>l>>r;
                l++;
                r++;
                ll temp1=query(l,r,total);
                cout<<temp1<<endl;
            }
            else
            {
                ll l,val;
                cin>>l>>val;
                l++;
                update(1,1,total,pos[l],pos[l],val);
            }
        }
        for(ll i=1; i<=total; i++)
            adj[i].clear();
    }
}
