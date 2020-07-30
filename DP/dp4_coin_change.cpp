/*
    Given a value N, if we want to make change for N cents, 
    and we have infinite supply of each of S = { S1, S2, .. , Sm} valued coins,
    how many ways can we make the change? The order of coins doesn’t matter.

    For example, for N = 4 and S = {1,2,3}, there are four solutions: 
    {1,1,1,1},{1,1,2},{2,2},{1,3}. So output should be 4. For N = 10 
    and S = {2, 5, 3, 6}, there are five solutions: 
    {2,2,2,2,2}, {2,2,3,3}, {2,2,6}, {2,3,5} and {5,5}. So the output should be 5.

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


//normie Solution
// ll solve(ll arr[],ll size, ll change){ 

//     if(change == 0)
//         return 1;
    
//     if(change<0)
//         return 0;
    
//     if(size<=0 && change >=1)
//         return 0;

//     return solve(arr,size - 1,change) + solve(arr,size,change - arr[size -1]);
// }



ll solve(ll arr[], ll size, ll change){ 

    ll table[change+1][size];

    //base
    rep(i,0,size){
        table[0][i]=1;
    }

    //filling up table

    for(ll i=1;i<=change;i++){
        for(ll j=0;j<size;j++){

            ll x = (i-arr[j]>=0) ? table[i-arr[j]][j] : 0;
            
            ll y = (j>=1) ? table[i][j-1] : 0;

            table[i][j] = x + y;
        }
    }
    return table[change][size - 1];

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);;
	
    ll arr[] = {1,2,3};
    ll size = sizeof(arr)/sizeof(arr[0]);
    ll change = 4;
	cout<<solve(arr,size,change);

	//cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << " secs" << endl;
	return 0;
}
