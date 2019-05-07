//http://lightoj.com/volume_showproblem.php?problem=1348
////=====================================////
///-----SOURAV CHAKRABORTY-----///
///-----KUET CSE 2K16-----///
////=====================================////
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
#define inf 1000000010000
#define mod1 1000000007
vector<ll>v[30010];
ll parent[30010];
ll visited[30010];
ll arr[30010];
ll depth[30010];
ll sparge_table[30010][20];
ll start[30010];
ll finish[30010];
ll time11;
ll tree[100010*4];
void bfs()
{
    memset(visited,0,sizeof visited);
    memset(parent,0,sizeof parent);
    queue<ll>q;
    q.push(1);
    visited[1]=1;
    while(!q.empty())
    {
        ll u=q.front();
        q.pop();
        for(ll i=0; i<v[u].size(); i++)
        {
            ll s=v[u][i];
            if(visited[s])
                continue;
            visited[s]=1;
            q.push(s);
            depth[s]=depth[u]+1;
            parent[s]=u;
        }
    }
}
void lca_init(ll total)
{
    memset(sparge_table,-1,sizeof sparge_table);
    for(ll i=1; i<=total; i++)
        sparge_table[i][0]=parent[i];
    for(ll j=1; (1<<j)<=total; j++)
    {
        for(ll i=1; i<=total; i++)
        {
            if(sparge_table[i][j-1]!=-1)
                sparge_table[i][j]=sparge_table[sparge_table[i][j-1]][j-1];
        }
    }
}
ll lca(ll s,ll t)
{
    ll log=1;
    if(depth[s]<depth[t])
        swap(s,t);
    while(1)
    {
        ll next=log+1;
        if((1<<next) <=depth[s])
            log++;
        else
            break;
    }
    for(ll i=log; i>=0; i--)
    {
        if(depth[s]- (1<<i) >= depth[t])
        {
            s=sparge_table[s][i];
        }
    }
    if(s==t)
        return s;
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
ll dfs(ll u,ll par)
{
    start[u]=time11;
    finish[u]=time11++;
    for(ll i=0; i<v[u].size(); i++)
    {
        ll s=v[u][i];
        if(s==par)
            continue;
        dfs(s,u);
    }
    finish[u]=time11++;
}
void merge(ll node)
{
    tree[node]=(tree[2*node]+tree[2*node+1]);
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
ll query(ll node,ll l,ll r,ll p,ll q)
{
    if(r<p||q<l)
        return 0;
    if(l>=p&&r<=q)
        return tree[node];
    return (query(2*node,l,(l+r)/2,p,q)+
            query(2*node+1,(l+r)/2+1,r,p,q));
}
int main()
{
    ll ts;
    cin>>ts;
    for(ll t=1; t<=ts; t++)
    {
        printf("Case %d:\n",t);
        ll total;
        scanf("%d",&total);
        for(ll i=1; i<=total; i++)
            v[i].clear();
        memset(tree,0,sizeof tree);
        for(ll i=1; i<=total; i++)
            scanf("%d",&arr[i]);
        for(ll i=1; i<total; i++)
        {
            ll l,r;
            scanf("%d %d",&l,&r);
            l++;
            r++;
            v[l].push_back(r);
            v[r].push_back(l);
        }
        bfs();
        lca_init(total);
        time11=1;
        dfs(1,-1);
        for(ll i=1; i<=total; i++)
        {
            update(1,1,time11,start[i],start[i],arr[i]);
            update(1,1,time11,finish[i],finish[i],-arr[i]);
        }
        total=time11;
        ll cnt;
        cin>>cnt;
        for(ll i=1; i<=cnt; i++)
        {
            ll type;
            scanf("%d",&type);
            if(!type)
            {
                ll l,r;
                scanf("%d %d",&l,&r);
                l++;
                r++;
                ll temp=lca(l,r);
                ll ans=query(1,1,total,min(start[l],start[temp]),max(start[l],start[temp]))+query(1,1,total,min(start[r],start[temp]),max(start[r],start[temp]));
                ans-=arr[temp];
                printf("%d\n",ans);
            }
            else
            {
                ll pos,val;
                scanf("%d %d",&pos,&val);
                pos++;
                arr[pos]=val;
                update(1,1,time11,start[pos],start[pos],val);
                update(1,1,time11,finish[pos],finish[pos],-val);
            }
        }
    }
}
