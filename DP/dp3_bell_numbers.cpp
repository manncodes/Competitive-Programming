/*
    Bell numbers:
    Let S(n, k) be total number of partitions of n elements into k sets.
    The value of n’th Bell Number is sum of S(n, k) for k = 1 to n.

    Well here S(n,k) is called stirling numbers of second kind.

*/

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

ll solve(ll n){  

    ll bell[n+1][n+1];

    bell[0][0] = 1;


    for(ll i =1 ; i<=n ; i++){

        //last elem of row above is the first element of the current row
        bell[i][0] = bell[i-1][i-1];

        for(ll j=1;j<=i;j++){
            bell[i][j]=bell[i][j-1] + bell[i-1][j-1];
        }
    }
    return bell[n][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);;
	
    cout<< solve(5) <<endl;

	//cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << " secs" << endl;
	return 0;
}
