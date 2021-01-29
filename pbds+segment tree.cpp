//https://www.codechef.com/problems/GIVEAWAY (give tle use sqrt decomposition)
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef int ll;
#define inf 1000000010000
#define mod1 1000000007

typedef tree<int, null_type, less_equal<int>, rb_tree_tag,
        tree_order_statistics_node_update>
        new_data_set;

vector<new_data_set>tree1(2000000);
ll arr[100010*5];
void merge(ll node)
{
    for(auto it=tree1[2*node].begin(); it!=tree1[2*node].end(); it++)
        tree1[node].insert(*it);
    for(auto it=tree1[2*node+1].begin(); it!=tree1[2*node+1].end(); it++)
        tree1[node].insert(*it);
}
void init(ll node,ll l,ll r)
{
    if(l==r)
    {
        tree1[node].insert(arr[l]);
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
    tree1[node].erase(tree1[node].upper_bound(arr[p]));
    tree1[node].insert(val);
    if(l>=p&&r<=q)
    {
        arr[l]=val;
        return;
    }
    update(2*node,l,(l+r)/2,p,q,val);
    update(2*node+1,(l+r)/2+1,r,p,q,val);
}
ll query(ll node,ll l,ll r,ll p,ll q,ll val)
{
    if(r<p||q<l)
        return 0;
    if(l>=p&&r<=q)
    {
        return tree1[node].size()- tree1[node].order_of_key(val);
    }
    return (query(2*node,l,(l+r)/2,p,q,val)+
            query(2*node+1,(l+r)/2+1,r,p,q,val));
}
int main()
{
    ll total,cnt;
    cin>>total;
    for(ll i=1; i<=total; i++)
        scanf("%d",&arr[i]);
    init(1,1,total);
    cin>>cnt;
    ll type,a,b,val;
    while(cnt--)
    {
        scanf("%d",&type);
        scanf("%d %d",&a,&b);
        if(!type)
        {
            scanf("%d",&val);
            printf("%d\n",query(1,1,total,a,b,val));
        }
        else
            update(1,1,total,a,a,b);
    }
}
