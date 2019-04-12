//LightOj/1132 - Summing up Powers

#include<bits/stdc++.h>
using namespace std;
typedef unsigned int ll;
typedef long long ll1;
#define inf 1000000010000
ll mat[55][55];
ll st[55][55];
ll dup[55][55];
ll dp[55][55];
ll ncr(ll n,ll r)
{
    if(n==r || !r)
        return 1;
    ll &res=dp[n][r];
    if(res!=-1)
        return res;
    return res=(ncr(n-1,r)+ncr(n-1,r-1));
}
ll dim;
void big_mod(ll1 a)
{
    if(a==1)
    {
        for(ll i=1; i<=dim; i++)
        {
            for(ll j=1; j<=dim; j++)
            {
                dup[i][j]=mat[i][j];
            }
        }
        return ;
    }
    if(a%2==0)
    {
        big_mod(a/2);
        for(ll i=1; i<=dim; i++)
        {
            ll temp=dim;
            ll j1=1;
            while(temp--)
            {
                ll ans=0;
                for(ll j=1; j<=dim; j++)
                {
                    ans+=dup[i][j]*dup[j][j1];
                }
                st[i][j1]=ans;
                j1++;
            }
        }
        for(ll i=1; i<=dim; i++)
        {
            for(ll j=1; j<=dim; j++)
            {
                dup[i][j]=st[i][j];
            }
        }
    }
    else
    {
        big_mod(a-1);
        for(ll i=1; i<=dim; i++)
        {
            ll temp=dim;
            ll j1=1;
            while(temp--)
            {
                ll ans=0;
                for(ll j=1; j<=dim; j++)
                {
                    ans+=dup[i][j]*mat[j][j1];
                }
                st[i][j1]=ans;
                j1++;
            }
        }
        for(ll i=1; i<=dim; i++)
        {
            for(ll j=1; j<=dim; j++)
            {
                dup[i][j]=st[i][j];
            }
        }
    }
    return ;
}
int main()
{
    memset(dp,-1,sizeof dp);
    ll ts;
    cin>>ts;
    for(ll t=1; t<=ts; t++)
    {
        ll1 n,k;
        cin>>n>>k;
        memset(mat,0,sizeof mat);
        memset(dup,0,sizeof dup);
        mat[1][1]=1;
        for(ll i=0; i<=k; i++)
        {
            mat[1][i+2]=ncr(k,i);
        }
        for(ll j=2; j<=k+2; j++)
        {
            for(ll i=0; i<=k-j+2; i++)
            {
                mat[j][j+i]=ncr(k-j+2,i);
            }
        }
        dim=k+2;
        dup[1][1]=1;
        if(n!=1)
            big_mod(n-1);
        ll ans=0;
        for(ll i=1; i<=k+2; i++)
        {
            ans+=dup[1][i];
        }
        cout<<"Case "<<t<<": "<<ans<<endl;
    }
}
