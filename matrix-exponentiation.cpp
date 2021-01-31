//https://lightoj.com/problem/summing-up-powers
#include <bits/stdc++.h>
using namespace std;
#define ll unsigned int
#define ll1 long long
#define inf 10000000
ll dp[55][55];
ll arr[55][55];
ll dup[55][55];
ll save[55][55];
ll k;
void copy1()
{
    for(ll i=1; i<=k; i++)
    {
        for(ll j=1; j<=k; j++)
            dup[i][j]=save[i][j];
    }
}
void big_mod(ll1 n)
{
    if(n==1)
    {
        for(ll i=1; i<=k; i++)
        {
            for(ll j=1; j<=k; j++)
                dup[i][j]=arr[i][j];
        }
        return;
    }
    else if(n%2==0)
    {
        big_mod(n/2);

        for(ll i=1; i<=k; i++)
        {
            for(ll j=1; j<=k; j++)
            {
                ll ans=0;
                for(ll t=1; t<=k; t++)
                {
                    ans+=dup[i][t]*dup[t][j];
                }
                save[i][j]=ans;
            }
        }
    }
    else
    {
        big_mod(n-1);
        for(ll i=1; i<=k; i++)
        {
            for(ll j=1; j<=k; j++)
            {
                ll ans=0;
                for(ll t=1; t<=k; t++)
                    ans+=arr[i][t]*dup[t][j];
                save[i][j]=ans;
            }
        }
    }
    copy1();
    return;
}
ll ncr(ll n,ll r)
{
    ll &res=dp[n][r];
    if(res!=-1)
        return res;
    if(n==r||!r)
        return res=1;
    return res=ncr(n-1,r)+ncr(n-1,r-1);
}
int main()
{
    memset(dp,-1,sizeof dp);
    ll ts;
    cin>>ts;
    for(ll t=1; t<=ts; t++)
    {
        ll1 n;
        cin>>n>>k;
        arr[1][1]=1;
        for(ll i=2; i<=k+2; i++)
            arr[1][i]=ncr(k,i-2);

        for(ll i=2,t1=k; i<=k+2; i++,t1--)
        {
            for(ll j=i,t2=0; j<=k+2; j++,t2++)
                arr[i][j]=ncr(t1,t2);
        }
        k+=2;
        if(n!=1)
            big_mod(n-1);
        else
            dup[1][1]=1;
        ll ans=0;
        for(ll i=1; i<=k; i++)
            ans+=dup[1][i];
        cout<<"Case "<<t<<": "<<ans<<endl;
    }
}
