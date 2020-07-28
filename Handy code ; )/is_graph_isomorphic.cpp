#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

template <class T>
using ordered_set = tree <T,null_type,less <T>,rb_tree_tag,tree_order_statistics_node_update> ;
///find_by_order()
///order_of_key()

#define rand __rand
mt19937 generator(chrono::system_clock::now().time_since_epoch().count());
template <class T = int>
T rand(T range = numeric_limits <T> :: max()){
    return (T) (generator() % range);
}

template <class T,class U>
void maximize(T &x,U y){
    if(x < y)x = y;
}
template <class T,class U>
void minimize(T &x,U y){
    if(x > y)x = y;
}
template <class T>
T Abs(T x){
    return (x < (T)0 ? -x : x);
}

#define ll long long
#define pll pair <ll,ll>
#define pii pair <int,int>
#define MASK(i) ((1LL)<<(i))
#define BIT(x,i) (((x)>>(i))&1)
#define all(c) (c).begin(),(c).end()
#define fn "test"    ///FILE_NAME_HERE

/*------------------------------------------END_OF_TEMPLATE------------------------------------------*/

namespace task{

    const int N = 20;
    int E[2][N][N],O[2][N][N],Z[2][N][N];
    bool adj[2][N][N];
    int n,f = 0;
    bool invalid= false;


    void print(int t,const vector < vector <int> > &a){
        cout<<"  ";
        for(int i = 0;i < n;++i){
            cout<<setw(6)<<(char)(i + (t ? 'A' : 'a'));
        }
        cout<<"\n   ";
        for(int i = 1;i <= n;++i){
            cout<<setw(6)<<" ___";
        }
        cout<<"\n"<<"\n";
        for(int i = 1;i <= n;++i){
            cout<<(char)((i - 1) + (t ? 'A' : 'a'))<<"| ";
            for(int j = 1;j <= n;++j){
                if(a[i][j] == -1){
                    cout<<setw(6)<<"---";
                } else {
                    cout<<setw(6)<<a[i][j];
                }
            }
            cout<<"\n"<<"\n";
        }
        cout<<'\n';
    }

    void print(int step,const vector < vector <int> > &sG,const vector < vector <int> > &sH,vector <int> &pG,vector <int> &pH){
        cout<<"STEP : "<<' '<<step<<"\n"<<"\n";
        cout<<"S"<<step<<"(G(X,Y)) :\n";
        print(0,sG);
        cout<<'\n';
        cout<<"S"<<step<<"(H(X,Y)) :\n";
        print(1,sH);
        for(int i = 1;i <= n;++i){
            if(i == 1){
                cout<<"VERTICES:"<<setw(9)<<i;
            }
            else cout<<setw(6)<<i;
        }
        cout<<'\n';
        cout<<"LX G(X,Y) : ";
        for(int i = 1;i <= n;++i){
            cout<<setw(6)<<pG[i];
        }
        cout<<"\nLX H(X,Y) : ";
        for(int i = 1;i <= n;++i){
            cout<<setw(6)<<pH[i];
        }
        cout<<"\n"<<"\n";
        for(int i = 1;i <= 5;++i){
            cout<<"++++++++++++++++++";
        }
        cout<<"\n"<<"\n";
    }

    bool compare(vector <int> i,vector <int> j){
        sort(all(i),greater <int> ());
        sort(all(j),greater <int> ());
        while(!i.empty() and i.back() == -1){
            i.pop_back();
        }
        while(!j.empty() and j.back() == -1){
            j.pop_back();
        }
        if(i.size() != j.size()){
            return false;
        }
        for(int k = 0;k < i.size();++k){
            if(i[k] != j[k]){
                return false;
            }
        }
        return true;
    }

    void compute(const vector < vector <int> > &sG,const vector < vector <int> > &sH,vector <int> &pG,vector <int> &pH){
        vector <int> x,y;
        x.resize(n + 2,0);
        y.resize(n + 2,0);
        int cur = 1;
        for(int i = 1;i <= n;++i){
            if(!x[i]){
                for(int j = 1;j <= n;++j){
                    if(!x[j] and compare(sG[i],sG[j])){
                        x[j] = cur;
                    }
                    if(!y[j] and compare(sG[i],sH[j])){
                        y[j] = cur;
                    }
                }
                ++cur;
            }
        }
        for(int i = 1;i <= n;++i){
            if(!y[i]){
                for(int j = 1;j <= n;++j){
                    if(!y[j] and compare(sH[i],sH[j])){
                        y[j] = cur;
                    }
                }
                ++cur;
            }
        }
        pG = x,pH = y;
        for(int i = 1;i <= n;++i){
            if(y[i] > n){
                invalid = true;
                break;
            }
        }
    }

    bool chk(const vector <int> &pG,const vector <int> &pH){
        set <int> h_G,h_H;
        for(int i = 1;i <= n;++i){
            h_G.insert(pG[i]);
            h_H.insert(pH[i]);
        }
        return (h_G.size() == n and h_H.size() == n);
    }

    vector <vector <int> > build(int k,const vector < vector <int> > &base,const vector <int> &p){
        vector <vector <int> > ret;
        ret.resize(n + 2,vector <int> (n + 2,-1));
        for(int i = 1;i <= n;++i){
            for(int j = 1;j <= n;++j){
                if(!adj[k][i][j]){
                    continue;
                }
                ret[i][j] = base[i][j] * 100 + p[i] * 10 + p[j];
            }
        }
        return  ret;
    }

    void solve(){
        cin>>n;
        /*
         * type == 0 U V: arcs
         * type == 1 U V: incident edge
         * type == 2 U U : loop
         * type == 3 U U: no edges
         */
        for(int i = 0;i < 2;++i){
            int type;
            while(cin>>type){
                if(type == -1){
                    break;
                }
                char u,v;
                cin>>u>>v;
                int a = u - (i ? 'A' : 'a') + 1;
                int b = v - (i ? 'A' : 'a') + 1;
                if(type == 0){
                    ++E[i][a][b];
                    adj[i][a][b] = true;
                } else if(type == 1){
                    ++O[i][a][b];
                    adj[i][a][b] = adj[i][b][a] = true;
                } else if(type == 2){
                    ++Z[i][a][b];
                    adj[i][a][b] = true;
                } else {
                    adj[i][a][b] = true;
                }
            }
        }
        vector < vector <int> > s_0[2];
        s_0[0].resize(n + 2,vector <int> (n + 2,-1));
        s_0[1].resize(n + 2,vector <int> (n + 2,-1));
        for(int k = 0;k < 2;++k) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    if(!adj[k][i][j]){
                        continue;
                    }
                    s_0[k][i][j] = (i ^ j ? E[k][i][j] * 10 + O[k][i][j] : Z[k][i][j]);
                }
            }
        }
        vector <int> pG,pH;
        vector < vector <int> > sG,sH;
        compute(s_0[0],s_0[1],pG,pH);
        sG.resize(n + 2,vector <int> (n + 2,-1));
        sH.resize(n + 2,vector <int> (n + 2,-1));
        print(0,s_0[0],s_0[1],pG,pH);
        ++f;
        while(!chk(pG,pH)){
            sG = build(0,s_0[0],pG);
            sH = build(1,s_0[1],pH);
            compute(sG,sH,pG,pH);
            print(f++,sG,sH,pG,pH);
            if(invalid){
                cout<<"TWO GRAPH ARE NOT ISOMORPHISM\n\n";
                exit(0);
            }
        }
        cout<<"TWO GRAPH ARE ISOMORPHISM\n\n";
        vector <pair <char,char> > res;
        for(int i = 1;i <= n;++i){
            int c = pH[i];
            --c;
            res.emplace_back(make_pair((char)(c + 'a'),(char)((i - 1) + 'A')));
        }
        sort(all(res));
        for(pair <char,char> p : res){
            cout<<p.first<<" --- "<<p.second<<'\n';
        }
    }
}

int main(void){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    task::solve();
}