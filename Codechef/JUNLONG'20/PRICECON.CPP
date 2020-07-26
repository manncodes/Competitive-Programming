/*
Chef has N items in his shop (numbered 1 through N); for each valid i, the price of the i-th item is Pi. Since Chef has very loyal customers, all N items are guaranteed to be sold regardless of their price.

However, the government introduced a price ceiling K, which means that for each item i such that Pi>K, its price should be reduced from Pi to K.

Chef's revenue is the sum of prices of all the items he sells. Find the amount of revenue which Chef loses because of this price ceiling.
*/

#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define ld double
#define ll long long
#define all(x) x.begin(),x.end()
const int mod=998244353;
#define fi first
#define se second
#define BohotTez  ios_base::sync_with_stdio(false);cin.tie(NULL);
#define inf (ll)1e16

ll power(ll x,ll y,ll p){
    ll res=1;
    x = x % p;
    while (y > 0){
        if (y & 1)
        res = (res * x) % p;
        y = y >> 1; // y = y/2
        x = (x * x) % p;
    }
    return res;
}
bitset<1000005> prime;
void sieve(int n){  
    prime.flip();
    for (int p=2; p*p<=n; p++){
        // If prime[p] is not changed, then it is a prime
        if (prime[p] == 1){
            for (int i=p*p; i<=n; i += p)prime[i] = 0;
        }
    }
    prime[1]=0;
}


int main() {
	int t;
	cin>>t;
	while(t--){
		int n,k;
		cin>>n>>k;
		int ans=0;
		int x;
		for(int i=0;i<n;i++){
			cin>>x;
			if(x>k){
				ans+=(x-k);
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}