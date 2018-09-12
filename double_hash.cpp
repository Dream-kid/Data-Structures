//http://codeforces.com/contest/514/problem/C
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define mx 1000000
#define base1 1217
#define base2 1223
#define mod1 1000000007
#define mod2 1000117
map<ll,map<ll,ll> >m;
pair<ll,ll>st;
void double_hash(string str)
{
    ll sum1=0,sum2=0;
    for(ll i=0; i<str.size(); i++)
    {
        sum1=(sum1*base1+str[i])%mod1;
        sum2=(sum2*base2+str[i])%mod2;
    }
    st.first=sum1;
    st.second=sum2;
}
ll calc1[mx+10];
ll calc2[mx+10];
bool process(string str)
{
    ll sum3=0,sum4=0;
    double_hash(str);
    ll sum1=st.first;
    ll sum2=st.second;
    for(ll i=0; i<str.size(); i++)
    {
        ll temp=str[i];
        for(ll j='a'; j<='c'; j++)
        {
            if(j==temp)
                continue;
            sum3=(-(temp)*calc1[str.size()-1-i]+mod1+sum1)%mod1;
            sum3=(sum3+(j)*calc1[str.size()-1-i])%mod1;
            sum4=((-temp)*calc2[str.size()-1-i]+mod2+sum2)%mod2;
            sum4=((j)*calc2[str.size()-1-i]+sum4)%mod2;
            if(m[sum3][sum4])
                return true;
        }
    }
    return false;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    calc1[0]=1;
    calc2[0]=1;
    for(ll i=1; i<=mx; i++)
    {
        calc1[i]=(calc1[i-1]*base1)%mod1;
        calc2[i]=(calc2[i-1]*base2)%mod2;
    }
    string str;
    ll total,cnt;
    cin>>total>>cnt;
    for(ll i=1; i<=total; i++)
    {

        cin>>str;
        double_hash(str);
        m[st.first][st.second]++;
    }
    for(ll i=1; i<=cnt; i++)
    {
        cin>>str;
        ll to=process(str);
        if(to)
            cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;
    }
}
