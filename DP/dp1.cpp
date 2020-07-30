#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--) 
#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(x) x.begin(),x.end()
const ll mod=1000000007;
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
// head


ll dp[1000];

ll solve(ll n){  

    if(n<1)
        return 0;
    if(n==1)
        return 1;

    if(dp[n]!=-1){
        return dp[n];
    }

    return solve(n-1) + solve(n-3) + solve(n-5);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);;
	
    // // For getting input from input.txt file 
    // freopen("input.txt", "r", stdin); 
  
    // // Printing the Output to output.txt file 
    // freopen("output.txt", "w", stdout); 

    fill(dp,dp+1000,-1);

	ll res = solve(7);
    cout<<res<<endl;

	//cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << " secs" << endl;
	return 0;
}
