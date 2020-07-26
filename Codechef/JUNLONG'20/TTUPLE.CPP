/*
Consider the following operations on a triple of integers. In one operation, you should:

Choose an integer d and an arithmetic operation ― either addition or multiplication.
Choose a subset of elements of the triple.
Apply the arithmetic operation to each of the chosen elements, i.e.
either add d to each of them or multiply each of them by d.
For example, if we have a triple (3,5,7), we may choose to add 3 to
the first and third element, and we get (6,5,10) using one operation.

You are given an initial triple (p,q,r) and a target triple (a,b,c).
Find the minimum number of operations needed to transform (p,q,r) into (a,b,c).
*/

#pragma GCC optimize("O3")
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
    ll t; 
    cin >> t;
    while(t--) {

        ll p, q, r, a, b, c; 
        ll fac = 0;
        cin >> p >> q >> r;
        cin >> a >> b >> c;
        
        //conditions of 0
        if(p == a && q == b && r == c) cout << 0;

        //conditions of any one pairwise equal.
        else if((p == a && q == b) || (q == b && r == c) || (p == a && r == c)) cout << 1;
        
        //p  + diff(pairwise equal)--->1
        //els3 2 optrns to perform
        else if(p == a) {
            if((!q || !r) && q - b == r - c) cout << 1;
            else if(q && r && (q - b == r - c || (b / q == c / r && b % q == 0 && c % r == 0))) cout << 1;
            else cout << 2;
        }

        //q  + diff(pairwise equal)--->1
        //els3 2 optrns to perform
        else if(q == b) {
            if((!p || !r) && p - a == r - c) cout << 1;
            else if(p && r && (p - a == r - c || (a / p == c / r && a % p == 0 && c % r == 0))) cout << 1;
            else cout << 2;
        }

        //r  + diff(pairwise equal)--->1
        //els3 2 optrns to perform
        else if(r == c) {
            if((!p || !q) && p - a == q - b) cout << 1;
            else if(p && q && (p - a == q - b || (b / q == a / p && b % q == 0 && a % p == 0))) cout << 1;
            else cout << 2;
        }

        //main goal is to check for every diff and ratio that is available and predetermine the oprtn that 
        //keeps up with the line that approaches our a,b,c.

        else if((p - a == q - b) && (q - b == r - c) && (r - c == p - a)) cout << 1;
        else if(p && q && r && b / q == c / r && a / p == c / r && b / q == a / p && a % p == 0 && b % q == 0 && c % r == 0) cout << 1;
        else if((p - a == q - b) || (q - b == r - c) || (r - c == p - a)) cout << 2;
        else if(q && p && b / q == a / p && b % q == 0 && a % p == 0) cout << 2;
        else if(q && r && b / q == c / r && b % q == 0 && c % r == 0) cout << 2;
        else if(p && r && a / p == c / r && a % p == 0 && c % r == 0) cout << 2;
        else if(p - a == q - b + r - c || q - b == p - a + r - c || r - c == p - a + q - b) cout << 2;
        else if((p && q && r && a % p == 0 && b % q == 0 && c % r == 0) && (a / p * b / q == c / r || b / q * c / r == a / p || c / r * a / p == b / q)) cout << 2;
        else {
            if(p && a % p == 0) {
                ll k = a / p;
                if(q * k - b == r - c || r * k - c == q - b) fac = 1, cout << 2;
                else if(k && ((c % k == 0 && q - b == r - c / k) || (b % k == 0 && r - c == q - b / k))) fac = 1, cout << 2;
            }
            if(!fac && q && b % q == 0) {
                ll k = b / q;
                if(p * k - a == r - c || r * k - c == p - a) fac = 1, cout << 2;
                else if(k && ((a % k == 0 && r - c == p - a / k) || (c % k == 0 && p - a == r - c / k))) fac = 1, cout << 2;
            }
            if(!fac && r && c % r == 0) {
                ll k = c / r;
                if(p * k - a == q - b || q * k - b == p - a) fac = 1, cout << 2;
                else if(k && ((b % k == 0 && p - a == q - b / k) || (a % k == 0 && q - b == p - a / k))) fac = 1, cout << 2;
            }
            if(!fac && (p != q) && (a - b) % (p - q) == 0) {
                ll k =  (a - b) / (p - q);
                if(p * k - a == r * k - c) fac = 1, cout << 2;
                else if(p * k - a == r - c) fac = 1, cout << 2;
                else if(r * k == c) fac = 1, cout << 2;
                else if(k && a % k == 0 && b % k == 0 && c - r == a / k - p && c - r == b / k - q) fac = 1, cout << 2;
            }
            if(!fac && (q != r) && (b - c) % (q - r) == 0) {
                ll k =  (b - c) / (q - r);
                if(q * k - b == p * k - a) fac = 1, cout << 2;
                else if(q * k - b == p - a) fac = 1, cout << 2;
                else if(p * k == a) fac = 1, cout << 2;
                else if(k && c % k == 0 && b % k == 0 && a - p == b / k - q && a - p == c / k - r) fac = 1, cout << 2;
            }
            if(!fac && (r != p) && (c - a) % (r - p) == 0) {
                ll k =  (c - a) / (r - p);
                if(r * k - c == q * k - b) fac = 1, cout << 2;
                else if(r * k - c == q - b) fac = 1, cout << 2;
                else if(q * k == b) fac = 1, cout << 2;
                else if(k && a % k == 0 && c % k == 0 && b - q == a / k - p && b - q == c / k - r) fac = 1, cout << 2;
            }
            if(!fac) cout << 3;
        }
        cout <<endl;
    }
}


