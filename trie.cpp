//http://codeforces.com/problemset/problem/514/C
#include <bits/stdc++.h>
typedef int ll;
using namespace std;
#define mod1 1000000007
struct node
{
    bool is_end;
    ll arr[4];
} tree[600002];
ll depth;
ll lol;
void trie(string str)
{
    ll root=1;
    for(ll i=0; i<lol; i++)
    {

        ll temp=str[i]-'a';
        if(!tree[root].arr[temp])
            tree[root].arr[temp]=++depth;
        root=tree[root].arr[temp];
    }
    tree[root].is_end=1;
}

string str;
bool word(ll pos,bool is_differ,ll depth)
{

    ll temp=str[pos]-'a';
    bool temp1=0;
    if(pos==lol)
    {
        ll temp=tree[depth].is_end;
        if(is_differ&&temp)
            return 1;
        return 0;
    }
    if(tree[depth].arr[temp])
    {
        ll depth1=tree[depth].arr[temp];
        temp1=word(pos+1,is_differ,depth1);
        if(temp1)
            return 1;
    }
    if(!is_differ)
    {
        for(ll i=0; i<3; i++)
        {
            ll depth1=tree[depth].arr[i];
            if(!depth1||i==temp)
                continue;
            temp1=word(pos+1,1,depth1);
            if(temp1)
                return 1;
        }
    }
    return 0;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll total,cnt;
    cin>>total>>cnt;
    for(ll i=1; i<=total; i++)
    {
        string str;
        cin>>str;
        lol=str.size();
        trie(str);
    }
    for(ll i=1; i<=cnt; i++)
    {
        cin>>str;
        lol=str.size();
        bool temp=word(0,0,1);
        if(temp)
            cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;
    }
}
