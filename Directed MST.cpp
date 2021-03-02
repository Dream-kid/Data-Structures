//https://lightoj.com/problem/teleport
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
const ll N = 1001;
const ll MAX_E = 100001;
const ll INF = 100000000;
ll in[N], pre[N], id[N],vis[N] ;
struct Edge
{
    int u,v,w;
};
Edge e[MAX_E];

ll DMST(ll root,ll nv,ll ne)
{
    int res = 0;
    while(true)
    {
        for(int i= 0; i < nv; i++ )
            in[i] = INF,id[i] = -1, vis[i] = -1;
        for(int i = 0; i < ne; i++)
        {
            int u = e[i].u, v = e[i].v;
            if(u != v && e[i].w < in[v])
            {
                in[v] = e[i].w;
                pre[v] = u;
            }
        }
        for(int i = 0; i < nv; i++)
        {
            if(i == root)
                continue;
            if(in[i] == INF)
                return -1;
        }

        in[root] = 0;
        pre[root] = root;
        int cntnode = 0;
        for(int i = 0; i < nv; i++)
        {
            res += in[i];
            if(vis[i] ==-1 )
            {
                int v = i;
                while(vis[v]==-1)
                {
                    vis[v] = i, v = pre[v];
                }
                if(v==root || vis[v] != i )
                    continue;
                id[v] = cntnode;
                for(int u= pre[v] ; u != v; u = pre[u] )
                    id[u] = cntnode;
                cntnode++;
            }
        }

        if(cntnode == 0)
            break;

        for(int i = 0; i < nv; i++)
            if(id[i] == -1)
                id[i] = cntnode++;


        for(int i = 0; i < ne; i++)
        {
            int temp = e[i].v;
            e[i].u = id[e[i].u];
            e[i].v = id[e[i].v];
            if(e[i].u != e[i].v)
                e[i].w -= in[temp];
        }
        nv = cntnode;
        root = id[root];
    }
    return res;
}
int main()
{
    ll ts;
    scanf("%d",&ts);
    for(ll t=1; t<=ts; t++)
    {
        ll total,cnt,root;
        cin>>total>>cnt>>root;
        for(ll i=0; i<cnt; i++)
            scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
        ll temp= DMST(root,total,cnt);
        cout<<"Case "<<t<<": ";
        if(temp==-1)
            cout<<"impossible"<<endl;
        else
            cout<<temp<<endl;
    }
}
