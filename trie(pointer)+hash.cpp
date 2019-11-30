#include<bits/stdc++.h>
using namespace std;
#define ll long long int
ll base=17269199;
ll M=17271739;
map<int,int>mp;
ll B[100009];
class node
{
public:
    ll cnt;
    node* next[26];
    node()
    {
        cnt=0;
        for(ll i=0;i<26;i++)
        {
            next[i]=NULL;
        }
    }
}*root,*ana[100009];
ll A;
char st[200009],st2[200009];
void insert_(node* curr)
{
    ll i,l=strlen(st),a;
    curr->cnt=max(A,curr->cnt);
    for(i=0;i<l;i++)
    {
       a=st[i]-'a';
       if(curr->next[a]==NULL)
       {
           curr->next[a]=new node();
       }
       curr=curr->next[a];
       curr->cnt=max(curr->cnt,A);
    }
}
ll search_(node* curr)
{
    ll a,i,l,mx;
    l=strlen(st);
    mx=0;
    for(i=0;i<l;i++)
    {
        a=st[i]-'a';
        if(curr->next[a]==NULL)
        {
            return mx;
        }
        curr=curr->next[a];
        mx++;
    }
    return mx;
}
ll search_ana(node* curr)
{
    ll a,i,l,mx;
    l=strlen(st);
    mx=curr->cnt;
    ll c=0;
    for(i=0;i<l;i++)
    {
        a=st[i]-'a';
        if(curr->next[a]==NULL)
        {
            return mx;
        }
        curr=curr->next[a];
        c++;
        mx=max(mx,c+curr->cnt);
    }
    return mx;
}
void del(node* curr)
{
    for(ll i=0;i<26;i++)
    {
        if(curr->next[i]!=NULL)del(curr->next[i]);
    }
    delete(curr);
}
int main()
{
    ll p,t;
    scanf("%lld",&t);
    for(p=1;p<=t;p++)
    {
        mp.clear();
        ll n,i,c,idx;
        scanf("%lld",&n);
        for(i=1;i<=n;i++)
        {
            scanf("%lld",&B[i]);
        }
        c=1;
        root=new node();
        for(idx=1;idx<=n;idx++)
        {
            ll x,l;
            scanf("%s",st);
            strcpy(st2,st);
            l=strlen(st);
            sort(st2,st2+l);
            x=0;
            for(i=0;i<l;i++)
            {
                x=(x*base)%M;
                ll a=st2[i]-'a';
                x=(x+a)%M;
            }
            //out<<x<<endl;
            if(mp[x]==0)
            {
                mp[x]=c;
                ana[c]=new node();
                c++;
            }
            A=B[idx];
            ll j=mp[x];
            insert_(root);
            insert_(ana[j]);
        }
        ll q;
        scanf("%lld",&q);
        for(idx=0;idx<q;idx++)
        {
            ll x,l;
            scanf("%s",st);
            strcpy(st2,st);
            l=strlen(st);
            sort(st2,st2+l);
            x=0;
            for(i=0;i<l;i++)
            {
                x=(x*base)%M;
                ll a=st2[i]-'a';
                x=(x+a)%M;
            }
            //cout<<x<<endl;
            ll temp1=0,temp2=0;
            temp1=search_(root);
            if(mp[x]!=0)
            {
                ll j=mp[x];
                temp2=search_ana(ana[j]);
            }
            //cout<<temp1<<"    "<<temp2<<endl;
            temp1=max(temp1,temp2);
            printf("%lld\n",temp1);
        }
        del(root);
        for(i=1;i<c;i++)
        {
            del(ana[i]);
        }
    }
}
