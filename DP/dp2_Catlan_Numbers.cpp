/*
    Use cases of catlan numbers.

    1) Count the number of expressions containing n pairs of parentheses which are correctly matched.
       For n = 3, possible expressions are ((())), ()(()), ()()(), (())(), (()()).

    2) Count the number of possible Binary Search Trees with n keys 

    3) Count the number of full binary trees (A rooted binary tree is full if every vertex has either 
       two children or no children) with n+1 leaves.

    4) Given a number n, return the number of ways you can draw n chords in a circle with 2 x n points
       such that no 2 chords intersect.

       1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, …

       recursive relation:
       C[0] = 1; c[n] = SUMMATION<i from [0,n]>(c[i]*c[n-i])  

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
    ll catalan[n+1];
    
    //base case:
    catalan[0] = 1;
    catalan[1] = 1;

    for (int i=2; i<=n; i++) 
    { 
        catalan[i] = 0; 
        for (int j=0; j<i; j++) 
            catalan[i] += catalan[j] * catalan[i-j-1]; 
    } 

    return catalan[n];

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);;
	
	cout<<solve(7)<<endl;

	//cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << " secs" << endl;
	return 0;
}
