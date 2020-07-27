#include<bits/stdc++.h>
using namespace std;

#define mms(a, b, n) memset(a, b, sizeof(*a) * (n))
#define mcp(a, b, n) memcpy(a, b, sizeof(*b) * (n))

#define N 66

int n, P;

struct rect {
    int l, r, d, u;
    rect() {}
    rect(int l, int r, int d, int u) : l(l), r(r), d(d), u(u) {}
};

struct grid {
    vector <int> X, Y;
    grid() {
        X.clear(), Y.clear();
    }
    grid(vector <int> X, vector <int> Y) : X(X), Y(Y) {}
    grid(int dx, int dy) {
        X.clear(), Y.clear();
        for (int i = 1; i <= 60; i += dx) X.push_back(i);
        for (int i = 1; i <= 60; i += dy) Y.push_back(i);
        X.push_back(60 + 1), Y.push_back(60 + 1);
    }

    bool full() {
        return X.size() > 60 && Y.size() > 60;
    }
    int xize() {return X.size();}
    int yize() {return Y.size();}

    bool inside(rect p) {
        bool flag = 0;
        for (int i = 0; i < X.size(); i ++) if (X[i] == p.l) {flag = 1; break;}
        if (!flag) return 0;
        flag = 0;
        for (int i = 0; i < X.size(); i ++) if (X[i] == p.r + 1) {flag = 1; break;}
        if (!flag) return 0;
        flag = 0;
        for (int i = 0; i < Y.size(); i ++) if (Y[i] == p.d) {flag = 1; break;}
        if (!flag) return 0;
        flag = 0;
        for (int i = 0; i < Y.size(); i ++) if (Y[i] == p.u + 1) {flag = 1; break;}
        if (!flag) return 0;
        return 1;
    }

    grid half() {
        if (X.size() < Y.size()) {
            vector <int> Z;
            for (int i = 0; i < X.size() - 1; i ++) {
                int l = X[i], r = X[i+1];
                Z.push_back(l);
                int dir = (r > 30);
                if (l < r - 1) Z.push_back(l + r + dir >> 1);
            }
            Z.push_back(X.back());
            return grid(Z, Y);
        }
        else {
            vector <int> Z;
            for (int i = 0; i < Y.size() - 1; i ++) {
                int l = Y[i], r = Y[i+1];
                Z.push_back(l);
                int dir = (r > 30);
                if (l < r - 1) Z.push_back(l + r + dir >> 1);
            }
            Z.push_back(Y.back());
            return grid(X, Z);
        }
    }
};

namespace UPDATE {
    int cnt[N][N][N][N], Ans[N][N];
    bool vis[N][N][N][N];
    bitset <N> hor[N][N][N], ver[N][N][N];

    struct Fen2 {
        int a[N][N];
        Fen2() {
            memset(a, 0, sizeof a);
        }
        void Add(int x, int y) {
            for (int i = x; i < N; i ++) for (int j = y; j < N; j ++) a[i][j] ++;
        }
        int sum(int x, int y) {
            return a[x][y];
        }
    };
    const double ep = 1e-8;
    struct doubleFen {
        double a[N][N], b[N][N];
        doubleFen() {
            for (int i = 0; i < N; i ++) for (int j = 0; j < N; j ++) a[i][j] = b[i][j] = 0;
        }
        void set(int x, int y, double v) {
            double delta = v - b[x][y];
            if (delta < ep) return;
            b[x][y] = v;
            for (int i = x; i < N; i ++) for (int j = y; j < N; j ++) a[i][j] += delta;
        }
        double sum(int l, int r, int d, int u) {
            return a[r][u] - a[r][d-1] - a[l-1][u] + a[l-1][d-1];
        }
    };

    Fen2 F1, F2;
    doubleFen DF;

    double Sum_p(int l, int r, int d, int u) {
        return DF.sum(l, r, d, u) / 1000;
    }

    bitset <N> pre[N][N][N];

    void init() {
        for (int i = 0; i < N; i ++) for (int j = 0; j < N; j ++) for (int k = 1; k < N; k ++) pre[i][j][k].reset();
        F1 = Fen2(), F2 = Fen2(), DF = doubleFen();
        for (int i = 1; i <= n; i ++) for (int j = 1; j <= n; j ++) DF.set(i, j, P * 10);
        memset(vis, 0, sizeof vis);
        for (int i = 0; i < N; i ++) for (int j = 0; j < N; j ++) for (int k = 0; k < N; k ++) {
                    hor[i][j][k].reset(); hor[i][j][k][k] = 1;
                    ver[i][j][k].reset(); ver[i][j][k][k] = 1;
                }
        memset(cnt, -1, sizeof cnt);
        for (int i = 0; i < N; i ++) for (int j = 0; j < N; j ++)
                for (int k = 0; k < N; k ++) for (int h = 0; h < N; h ++) {
                        if (i > j || k > h) cnt[i][j][k][h] = 0;
                    }
    }

    void prepare(grid &to) {
        for (int i = 1; i < to.xize(); i ++) for (int j = 1; j < to.yize(); j ++) {
                int l = to.X[i-1], r = to.X[i], d = to.Y[j-1], u = to.Y[j];
                pre[l][r-1][d][u-1].flip();
            }
    }

    int count(int l, int r, int d, int u) {
        return F2.sum(r, u) + F2.sum(l - 1, d - 1) - F2.sum(l - 1, u) - F2.sum(r, d - 1);
    }
    int known_cells(int l, int r, int d, int u) {
        return F1.sum(r, u) + F1.sum(l - 1, d - 1) - F1.sum(l - 1, u) - F1.sum(r, d - 1);
    }
    int unknown_cells(int l, int r, int d, int u) {
        return (r - l + 1) * (u - d + 1) - known_cells(l, r, d, u);
    }
    int count(rect p) {return count(p.l, p.r, p.d, p.u);}
    int known_cells(rect p) {return known_cells(p.l, p.r, p.d, p.u);}
    int unknown_cells(rect p) {return unknown_cells(p.l, p.r, p.d, p.u);}

    void get_ans(int x, int y, int v) {
        F1.Add(x, y);
        if (v) F2.Add(x, y);
    }

    int update_cnt(int l, int r, int d, int u, int val) {
        if ((l == r && d == u) || pre[l][r][d][u]) {
            int un = (r - l + 1) * (u - d + 1), cn = val;
            for (int i = l; i <= r; i ++) for (int j = d; j <= u; j ++) if (Ans[i][j] != -1) {
                        un --;
                        if (Ans[i][j]) cn --;
                    }
            if (un) {
                double p = 1000.0 * cn / un;
                for (int i = l; i <= r; i ++) for (int j = d; j <= u; j ++) if (Ans[i][j] == -1) DF.set(i, j, p);
            }
        }
        if (cnt[l][r][d][u] >= 0) return val;
        if (l == r && d == u && Ans[r][u] == -1) {
            Ans[r][u] = val;
            get_ans(r, u, val);
        }
        cnt[l][r][d][u] = val;
        if ((l < r || d < u) && (val == 0 || val == (r - l + 1) * (u - d + 1)) && !vis[l][r][d][u]) {
            int x = (val > 0);
            for (int i = l; i <= r; i ++) for (int j = d; j <= u; j ++) {
                    if (cnt[i][i][j][j] < 0) update_cnt(i, i, j, j, x);
                }
            vis[l][r][d][u] = 1;
        }

        ver[d][u+1][l][r+1] = ver[d][u+1][r+1][l] = hor[l][r+1][d][u+1] = hor[l][r+1][u+1][d] = 1;
        bitset <N> bt;
        bt = ver[d][u+1][l] & (~ver[d][u+1][r+1]);
        for (int i = bt._Find_first(); i < N; i = bt._Find_next(i)) {
            if (i < l) {
                if (cnt[i][r][d][u] < 0) update_cnt(i, r, d, u, cnt[i][l-1][d][u] + val);
            }
            else if (i <= r) {
                if (cnt[i][r][d][u] < 0) update_cnt(i, r, d, u, val - cnt[l][i-1][d][u]);
            }
            else {
                if (cnt[r+1][i-1][d][u] < 0) update_cnt(r + 1, i - 1, d, u, cnt[l][i-1][d][u] - val);
            }
        }
        bt = ver[d][u+1][r+1] & (~ver[d][u+1][l]);
        for (int i = bt._Find_first(); i < N; i = bt._Find_next(i)) {
            if (i < l) {
                if (cnt[i][l-1][d][u] < 0) update_cnt(i, l - 1, d, u, cnt[i][r][d][u] - val);
            }
            else if (i <= r) {
                if (cnt[l][i-1][d][u] < 0) update_cnt(l, i - 1, d, u, val - cnt[i][r][d][u]);
            }
            else {
                if (cnt[l][i-1][d][u] < 0) update_cnt(l, i - 1, d, u, cnt[r+1][i-1][d][u] + val);
            }
        }
        bt = hor[l][r+1][d] & (~hor[l][r+1][u+1]);
        for (int i = bt._Find_first(); i < N; i = bt._Find_next(i)) {
            if (i < d) {
                if (cnt[l][r][i][u] < 0) update_cnt(l, r, i, u, cnt[l][r][i][d-1] + val);
            }
            else if (i <= u) {
                if (cnt[l][r][i][u] < 0) update_cnt(l, r, i, u, val - cnt[l][r][d][i-1]);
            }
            else {
                if (cnt[l][r][u+1][i-1] < 0) update_cnt(l, r, u + 1, i - 1, cnt[l][r][d][i-1] - val);
            }
        }
        bt = hor[l][r+1][u+1] & (~hor[l][r+1][d]);
        for (int i = bt._Find_first(); i < N; i = bt._Find_next(i)) {
            if (i < d) {
                if (cnt[l][r][i][d-1] < 0) update_cnt(l, r, i, d - 1, cnt[l][r][i][u] - val);
            }
            else if (i <= u) {
                if (cnt[l][r][d][i-1] < 0) update_cnt(l, r, d, i - 1, val - cnt[l][r][i][u]);
            }
            else {
                if (cnt[l][r][d][i-1] < 0) update_cnt(l, r, d, i - 1, cnt[l][r][u+1][i-1] + val);
            }
        }
        return val;
    }
}
using UPDATE::count;
using UPDATE::known_cells;
using UPDATE::unknown_cells;
using UPDATE::update_cnt;

void input() {
    scanf("%d %d", &n, &P);
}

int get_type() {
    if (P == 2) return 1;
    if (P == 5) return 2;
    if (P == 10) return 3;
    if (P == 15) return 4;
}

int query(int l, int r, int d, int u) {
    printf("1 %d %d %d %d\n", l, d, r, u);
    fflush(stdout);
    int x;
    scanf("%d", &x);
    assert(x != -1);
    return x;
}

int print() {
    puts("2");
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) printf("%d ", UPDATE::Ans[i][j]);
        puts("");
    }
    fflush(stdout);
    int x;
    scanf("%d", &x);
    return x;
}

vector <rect> vec_rect;

void make_rect() {
    vec_rect.clear();
    vector <int> V;
    vector <int> X, Y;
    int D;
    if (P == 2) D = 20;
    else if (P == 5) D = 12;
    else if (P == 10) D = 9;
    else D = 9;
    for (int i = 1; i <= D; i ++) for (int k = i; k <= 60; k += D) X.push_back(k);
    Y = X;
    for (auto i : X) for (auto j : Y) {
            if (j < 1 || j > 60) continue;
            int l = i, r = 60, d = j, u = 60;
            if (i > 30) l = 1, r = i - 1;
            if (j > 30) d = 1, u = j - 1;
            vec_rect.push_back(rect(l, r, d, u));
        }
}

void Init() {
    make_rect();
    memset(UPDATE::Ans, -1, sizeof UPDATE::Ans);
}

typedef pair <int, int> pii;
typedef long long ll;
typedef pair <rect, int> pri;
typedef vector <pri> qway;

namespace CELL {

    int st;
    bitset < (1 << 24) > vis;
    vector <int> vr;

    void init() {
        st = 0;
        vis.reset();
        vr.clear();
    }

    void push(int l, int r, int d, int u) {
        int cip = (l << 18) ^ (r << 12) ^ (d << 6)^u;
        vis[cip].flip();
        vr.push_back(cip);
    }
    void push(rect p) {push(p.l, p.r, p.d, p.u);}

    void pop() {
        vis[vr.back()].flip(), vr.pop_back();
    }

    void record() {
        st = vr.size();
    }

    void go_back() {
        while (vr.size() > st) pop();
    }

    void go_back_all() {
        for (auto i : vr) vis[i].flip();
        vr.clear();
    }

    int simple(int l, int r, int d, int u) {
        if (vis[(l << 18)^(r << 12)^(d << 6)^u] || l > r || d > u) return 0;
        if (UPDATE::cnt[l][r][d][u] != -1) return 0;
        int a = r - l + 1, b = u - d + 1;
        double x = UPDATE::Sum_p(l, r, d, u), y = x;
        return ((2 * n - a) * (2 * n - b) + x) / (1 + x);
    }

    int simple(rect R) {
        return simple(R.l, R.r, R.d, R.u);
    }

    int check(qway &w) {
        record();
        int ret = 0;
        for (auto p : w) {
            ret += simple(p.first);
            push(p.first);
        }
        go_back();
        return ret;
    }
}
using CELL::simple;
using CELL::check;

namespace GET_LC {
    void find_0(vector <qway> &way, int l, int r, int d, int u) {
        if (l > r || d > u) return;
        way.push_back(qway(1, pri(rect(l, r, d, u), 1)));
    }
    void find_1(vector <qway> &way, int l, int r, int d, int u) {
        if (l > r || d > u) return;
        for (int i = 1; i <= n; i ++) if (i != l && i != r) {
                qway w(2);
                if (i < l) {
                    w[0] = pri(rect(i, r, d, u), 1);
                    w[1] = pri(rect(i, l - 1, d, u), -1);
                }
                else if (i > r) {
                    w[0] = pri(rect(l, i, d, u), 1);
                    w[1] = pri(rect(r + 1, i, d, u), -1);
                }
                else {
                    w[0] = pri(rect(l, i, d, u), 1);
                    w[1] = pri(rect(i + 1, r, d, u), 1);
                }
                way.push_back(w);
            }
        for (int i = 1; i <= n; i ++) if (i != d && i != u) {
                qway w(2);
                if (i < d) {
                    w[0] = pri(rect(l, r, i, u), 1);
                    w[1] = pri(rect(l, r, i, d - 1), -1);
                }
                else if (i > u) {
                    w[0] = pri(rect(l, r, d, i), 1);
                    w[1] = pri(rect(l, r, u + 1, i), -1);
                }
                else {
                    w[0] = pri(rect(l, r, d, i), 1);
                    w[1] = pri(rect(l, r, i + 1, u), 1);
                }
                way.push_back(w);
            }
    }
    void find_2(vector <qway> &way, int l, int r, int d, int u) {
        if (l > r || d > u) return;
        if (1 < l && 1 < d) {
            qway w(4);
            w[0] = pri(rect(1, r, 1, u), 1);
            w[1] = pri(rect(1, l - 1, 1, d - 1), 1);
            w[2] = pri(rect(1, r, 1, d - 1), -1);
            w[3] = pri(rect(1, l - 1, 1, u), -1);
            way.push_back(w);
        }
        if (1 < l && u < n) {
            qway w(4);
            w[0] = pri(rect(1, r, d, n), 1);
            w[1] = pri(rect(1, l - 1, u + 1, n), 1);
            w[2] = pri(rect(1, r, u + 1, n), -1);
            w[3] = pri(rect(1, l - 1, d, n), -1);
            way.push_back(w);
        }
        if (r < n && 1 < d) {
            qway w(4);
            w[0] = pri(rect(l, n, 1, u), 1);
            w[1] = pri(rect(r + 1, n, 1, d - 1), 1);
            w[2] = pri(rect(l, n, 1, d - 1), -1);
            w[3] = pri(rect(r + 1, n, 1, u), -1);
            way.push_back(w);
        }
        if (r < n && u < n) {
            qway w(4);
            w[0] = pri(rect(l, n, d, n), 1);
            w[1] = pri(rect(r + 1, n, u + 1, n), 1);
            w[2] = pri(rect(l, n, u + 1, n), -1);
            w[3] = pri(rect(r + 1, n, d, n), -1);
            way.push_back(w);
        }
    }
    void find_0(vector <qway> &way, rect R) {find_0(way, R.l, R.r, R.d, R.u);}
    void find_1(vector <qway> &way, rect R) {find_1(way, R.l, R.r, R.d, R.u);}
    void find_2(vector <qway> &way, rect R) {find_2(way, R.l, R.r, R.d, R.u);}

    int update_qway(qway &w) {
        qway new_w;
        int nxt = 0, prv = 0;
        for (auto p : w) {
            int pv = simple(p.first);
            if (pv == 0) {
                new_w.push_back(p);
                CELL::push(p.first);
                continue;
            }
            prv += pv;
            vector <qway> way;
            find_1(way, p.first);
            int mn = 1e9, id;
            for (int i = 0; i < way.size(); i ++) {
                int cur = check(way[i]);
                if (cur < mn) mn = cur, id = i;
                if (mn == 0) break;
            }
            if (mn >= pv) {
                nxt += pv, new_w.push_back(p);
                CELL::push(p.first);
            }
            else {
                nxt += mn;
                for (auto q : way[id]) {
                    q.second *= p.second;
                    new_w.push_back(q);
                    CELL::push(q.first);
                }
            }
        }
        CELL::go_back_all();
        w = new_w;
        return prv - nxt;
    }

    qway optimal(int l, int r, int d, int u) {
        vector <int> value;
        vector <qway> way;
        int st = way.size();
        find_0(way, l, r, d, u);
        for (int i = st; i < way.size(); i ++) {
            while (1) if (update_qway(way[i]) == 0) break;
            value.push_back(check(way[i]));
            if (value.back() == 0) return way[i];
        }
        st = way.size();
        find_2(way, l, r, d, u);
        for (int i = st; i < way.size(); i ++) {
            while (1) if (update_qway(way[i]) == 0) break;
            value.push_back(check(way[i]));
            if (value.back() == 0) return way[i];
        }

        int id = min_element(value.begin(), value.end()) - value.begin();

        while (1) {
            if (update_qway(way[id]) == 0) break;
        }
        return way[id];
    }
}
using GET_LC::optimal;

namespace GET_CNT {
    using UPDATE::cnt;

    int calc_simple(int l, int r, int d, int u) {
        if (l > r || d > u) return 0;
        if (cnt[l][r][d][u] != -1) return cnt[l][r][d][u];
        int ret = query(l, r, d, u);
        return update_cnt(l, r, d, u, ret);
    }
    int calc_simple(rect R) {
        return calc_simple(R.l, R.r, R.d, R.u);
    }

    int calc(qway &w) {
        int ret = 0;
        for (auto p : w)
            ret += calc_simple(p.first) * p.second;
        return ret;
    }

    int calc(int l, int r, int d, int u) {
        if (l > r || d > u) return 0;
        if (cnt[l][r][d][u] != -1) return cnt[l][r][d][u];
        qway w = optimal(l, r, d, u);
        int ret = calc(w);
        update_cnt(l, r, d, u, ret);
        return ret;
    }
    int calc(rect p) {return calc(p.l, p.r, p.d, p.u);}

    int press(int l, int r, int d, int u) {
        if (l > r || d > u) return 0;
        if (cnt[l][r][d][u] != -1) return 0;
        qway w = optimal(l, r, d, u);
        return check(w);
    }
    int press(rect p) {return press(p.l, p.r, p.d, p.u);}
}
using GET_CNT::press;
using GET_CNT::calc;

namespace GRID {

    grid V[30];
    int V_size;

    void get_V() {
        while (!V[V_size-1].full()) {
            V[V_size] = V[V_size-1].half();
            V_size ++;
        }
    }

    int way_size;
    pri way[22222];

    void get_way(grid &from, grid &to) {
        way_size = 0;
        for (int i = 1; i < from.xize(); i ++) for (int j = 1; j < from.yize(); j ++) {
                int l = from.X[i-1], r = from.X[i], d = from.Y[j-1], u = from.Y[j];
                if (unknown_cells(l, r - 1, d, u - 1)) way[way_size ++] = pri(rect(l, r - 1, d, u - 1), 0);
            }
        for (auto p : vec_rect) {
            if (!unknown_cells(p)) continue;
            if (!to.inside(p)) continue;
            if (from.inside(p)) continue;
            way[way_size ++] = pri(p, 1);
        }
    }

    typedef tuple <int, int, int, int, int, int> tuple6;

    queue <tuple6> tq;
    int tmp1[N], tmp2[N];
    void calc_x(int x1, int mid, int x2, vector <int> &Y) {
        vector <pii> belt;
        belt.push_back(pii(0, 0));
        mms(tmp1, 0, n + 1);
        mms(tmp2, 0, n + 1);
        for (int i = 1; i < Y.size(); i ++) {
            int d = Y[i-1], u = Y[i] - 1;
            if (UPDATE::cnt[mid][x2-1][d][u] == -1)
                belt.push_back(pii(d, u));
            else {
                tmp1[u] = UPDATE::cnt[x1][mid-1][d][u];
                tmp2[u] = UPDATE::cnt[mid][x2-1][d][u];
            }
        }
        belt.push_back(pii(n + 1, n + 1));
        for (int i = 1; i <= n; i ++) tmp1[i] += tmp1[i-1], tmp2[i] += tmp2[i-1];

        auto known1 = [&](int l, int r) {return tmp1[r] - tmp1[l-1];};
        auto known2 = [&](int l, int r) {return tmp2[r] - tmp2[l-1];};

        int tot1, tot2;

        auto func = [&]() {
            tuple6 tup = tq.front(); tq.pop();
            int l = get<0>(tup), r = get<1>(tup), L1 = get<2>(tup), L2 = get<3>(tup), R1 = get<4>(tup), R2 = get<5>(tup);
            int sum1 = tot1 - L1 - R1;
            int sum2 = tot2 - L2 - R2;
            if (sum1 == 0) {
                for (int i = l; i <= r; i ++)
                    UPDATE::update_cnt(x1, mid - 1, belt[i].first, belt[i].second, 0);
                return;
            }
            if (sum2 == 0) {
                for (int i = l; i <= r; i ++)
                    UPDATE::update_cnt(mid, x2 - 1, belt[i].first, belt[i].second, 0);
                return;
            }
            if (l == r) {
                UPDATE::update_cnt(x1, mid - 1, belt[r].first, belt[r].second, sum1);
                return;
            }
            int m = l + r >> 1;
            if ((l & 1) == (r & 1)) {
                int m1 = m - 1, m2 = m;
                int d1 = max(n - belt[m1-1].second, belt[m2].first - 1);
                int d2 = max(belt[m2+1].first - 1, n - belt[m1].second);
                if (d2 > d1) m = m2;
                else m = m1;
            }

            int uu = belt[m + 1].first - 1, dd = belt[m].second + 1;

            int sumd = UPDATE::cnt[x1][x2-1][1][uu] - known1(1, uu) - known2(1, uu) - L1 - L2;
            int sumu = UPDATE::cnt[x1][x2-1][dd][n] - known1(dd, n) - known2(dd, n) - R1 - R2;

            int p1 = simple(1, mid - 1, 1, uu), d1 = UPDATE::cnt[1][x1-1][1][uu] + known1(1, uu) + L1;
            int p2 = simple(mid, n, 1, uu), d2 = UPDATE::cnt[x2][n][1][uu] + known2(1, uu) + L2;
            int p3 = simple(1, mid - 1, dd, n), d3 = UPDATE::cnt[1][x1-1][dd][n] + known1(dd, n) + R1;
            int p4 = simple(mid, n, dd, n), d4 = UPDATE::cnt[x2][n][dd][n] + known2(dd, n) + R2;

            int sd1, sd2, su1, su2;

            int mn = min(min(p1, p2), min(p3, p4));
            if (mn == p1) {
                sd1 = calc(1, mid - 1, 1, uu) - d1;
                sd2 = sumd - sd1;
                su1 = sum1 - sd1;
                su2 = sum2 - sd2;
            }
            else if (mn == p2) {
                sd2 = calc(mid, n, 1, uu) - d2;
                sd1 = sumd - sd2;
                su1 = sum1 - sd1;
                su2 = sum2 - sd2;
            }
            else if (mn == p3) {
                su1 = calc(1, mid - 1, dd, n) - d3;
                su2 = sumu - su1;
                sd1 = sum1 - su1;
                sd2 = sum2 - su2;
            }
            else {
                su2 = calc(mid, n, dd, n) - d4;
                su1 = sumu - su2;
                sd1 = sum1 - su1;
                sd2 = sum2 - su2;
            }
            tq.push(make_tuple(l, m, L1, L2, R1 + su1, R2 + su2));
            tq.push(make_tuple(m + 1, r, L1 + sd1, L2 + sd2, R1, R2));
        };

        int p1 = press(1, mid - 1, 1, n), d1 = UPDATE::cnt[1][x1-1][1][n] + known1(1, n);
        int p2 = press(mid, n, 1, n), d2 = UPDATE::cnt[x2][n][1][n] + known2(1, n);
        int tot = UPDATE::cnt[x1][x2-1][1][n] - known1(1, n) - known2(1, n);
        if (p1 < p2) {
            tot1 = calc(1, mid - 1, 1, n) - d1;
            tot2 = tot - tot1;
        }
        else {
            tot2 = calc(mid, n, 1, n) - d2;
            tot1 = tot - tot2;
        }

        if (belt.size() > 2) tq.push(make_tuple(1, belt.size() - 2, 0, 0, 0, 0));
        while (!tq.empty()) func();
    }

    void calc_y(int y1, int mid, int y2, vector <int> &X) {
        vector <pii> belt;
        belt.push_back(pii(0, 0));
        mms(tmp1, 0, n + 1);
        mms(tmp2, 0, n + 1);
        for (int i = 1; i < X.size(); i ++) {
            int d = X[i-1], u = X[i] - 1;
            if (UPDATE::cnt[d][u][mid][y2-1] == -1)
                belt.push_back(pii(d, u));
            else {
                tmp1[u] = UPDATE::cnt[d][u][y1][mid-1];
                tmp2[u] = UPDATE::cnt[d][u][mid][y2-1];
            }
        }
        belt.push_back(pii(n + 1, n + 1));
        for (int i = 1; i <= n; i ++) tmp1[i] += tmp1[i-1], tmp2[i] += tmp2[i-1];

        auto known1 = [&](int l, int r) {return tmp1[r] - tmp1[l-1];};
        auto known2 = [&](int l, int r) {return tmp2[r] - tmp2[l-1];};

        int tot1, tot2;

        auto func = [&]() {
            tuple6 tup = tq.front(); tq.pop();
            int l = get<0>(tup), r = get<1>(tup), L1 = get<2>(tup), L2 = get<3>(tup), R1 = get<4>(tup), R2 = get<5>(tup);
            int sum1 = tot1 - L1 - R1;
            int sum2 = tot2 - L2 - R2;
            if (sum1 == 0) {
                for (int i = l; i <= r; i ++)
                    UPDATE::update_cnt(belt[i].first, belt[i].second, y1, mid - 1, 0);
                return;
            }
            if (sum2 == 0) {
                for (int i = l; i <= r; i ++)
                    UPDATE::update_cnt(belt[i].first, belt[i].second, mid, y2 - 1, 0);
                return;
            }
            if (l == r) {
                UPDATE::update_cnt(belt[r].first, belt[r].second, y1, mid - 1, sum1);
                return;
            }
            int m = l + r >> 1;
            if ((l & 1) == (r & 1)) {
                int m1 = m - 1, m2 = m;
                int d1 = max(n - belt[m1-1].second, belt[m2].first - 1);
                int d2 = max(belt[m2+1].first - 1, n - belt[m1].second);
                if (d2 > d1) m = m2;
                else m = m1;
            }

            int uu = belt[m + 1].first - 1, dd = belt[m].second + 1;

            int sumd = UPDATE::cnt[1][uu][y1][y2-1] - known1(1, uu) - known2(1, uu) - L1 - L2;
            int sumu = UPDATE::cnt[dd][n][y1][y2-1] - known1(dd, n) - known2(dd, n) - R1 - R2;

            int p1 = press(1, uu, 1, mid - 1), d1 = UPDATE::cnt[1][uu][1][y1-1] + known1(1, uu) + L1;
            int p2 = press(1, uu, mid, n), d2 = UPDATE::cnt[1][uu][y2][n] + known2(1, uu) + L2;
            int p3 = press(dd, n, 1, mid - 1), d3 = UPDATE::cnt[dd][n][1][y1-1] + known1(dd, n) + R1;
            int p4 = press(dd, n, mid, n), d4 = UPDATE::cnt[dd][n][y2][n] + known2(dd, n) + R2;

            int sd1, sd2, su1, su2;

            int mn = min(min(p1, p2), min(p3, p4));
            if (mn == p1) {
                sd1 = calc(1, uu, 1, mid - 1) - d1;
                sd2 = sumd - sd1;
                su1 = sum1 - sd1;
                su2 = sum2 - sd2;
            }
            else if (mn == p2) {
                sd2 = calc(1, uu, mid, n) - d2;
                sd1 = sumd - sd2;
                su1 = sum1 - sd1;
                su2 = sum2 - sd2;
            }
            else if (mn == p3) {
                su1 = calc(dd, n, 1, mid - 1) - d3;
                su2 = sumu - su1;
                sd1 = sum1 - su1;
                sd2 = sum2 - su2;
            }
            else {
                su2 = calc(dd, n, mid, n) - d4;
                su1 = sumu - su2;
                sd1 = sum1 - su1;
                sd2 = sum2 - su2;
            }
            tq.push(make_tuple(l, m, L1, L2, R1 + su1, R2 + su2));
            tq.push(make_tuple(m + 1, r, L1 + sd1, L2 + sd2, R1, R2));
        };

        int p1 = press(1, n, 1, mid - 1), d1 = UPDATE::cnt[1][n][1][y1-1] + known1(1, n);
        int p2 = press(1, n, mid, n), d2 = UPDATE::cnt[1][n][y2][n] + known2(1, n);
        int tot = UPDATE::cnt[1][n][y1][y2-1] - known1(1, n) - known2(1, n);
        if (p1 < p2) {
            tot1 = calc(1, n, 1, mid - 1) - d1;
            tot2 = tot - tot1;
        }
        else {
            tot2 = calc(1, n, mid, n) - d2;
            tot1 = tot - tot2;
        }

        if (belt.size() > 2) tq.push(make_tuple(1, belt.size() - 2, 0, 0, 0, 0));
        while (!tq.empty()) func();
    }

    typedef tuple<int, int, int> tuple3;

    void last(grid &from, grid &to) {
        if (from.xize() == to.xize()) {
            ll mask = 0;
            for (auto y : from.Y) mask ^= 1ll << y;
            vector <tuple3> qu;
            for (int i = 0; i < to.yize(); i ++) {
                if (mask >> to.Y[i] & 1) continue;
                qu.push_back(make_tuple(to.Y[i-1], to.Y[i], to.Y[i+1]));
            }
            sort(qu.begin(), qu.end(), [&](tuple3 a, tuple3 b) {
                return abs(30 - get<1>(a)) < abs(30 - get<1>(b));
            });
            for (auto tup : qu) calc_y(get<0>(tup), get<1>(tup), get<2>(tup), to.X);
        }
        else {
            ll mask = 0;
            for (auto x : from.X) mask ^= 1ll << x;
            vector <tuple3> qu;
            for (int i = 0; i < to.xize(); i ++) {
                if (mask >> to.X[i] & 1) continue;
                qu.push_back(make_tuple(to.X[i-1], to.X[i], to.X[i+1]));
            }
            sort(qu.begin(), qu.end(), [&](tuple3 a, tuple3 b) {
                return abs(30 - get<1>(a)) > abs(30 - get<1>(b));
            });
            for (auto tup : qu) calc_x(get<0>(tup), get<1>(tup), get<2>(tup), to.Y);
        }
    }

    int tmp[3601];
    void brute(grid &from, grid &to) {
        if (from.xize() == to.xize() && from.yize() == to.yize()) return;

        get_way(from, to);

        UPDATE::prepare(to);

        for (int i = 0; i < way_size; i ++) {
            rect p = way[i].first;
            int l = p.l, r = p.r, d = p.d, u = p.u;
            calc(l, r, d, u);
        }

        UPDATE::prepare(to);
    }

    void get_V1() {
        V_size = 1;
        V[0] = grid(n, n);
        get_V();
    }

    void get_V2() {
        V_size = 2;
        V[0] = grid(n, n);
        V[1] = grid(20, 20);
        get_V();
    }

    void get_V3() {
        V_size = 3;
        V[0] = grid(n, n);
        V[1] = grid(20, 20);
        V[2] = grid(4, 4);
        get_V();
    }

    void get_V8() {
        vector <int> v1 = {1, 21, 41, 61};
        vector <int> v2 = {1, 9, 21, 29, 41, 49, 61};
        vector <int> v3 = {1, 9, 17, 21, 29, 37, 41, 49, 57, 61};
        vector <int> v4;
        for (int i = 1; i < 64; i += 4) v4.push_back(i);
        V_size = 8;
        V[0] = grid(n, n);
        V[1] = grid(v1, v1);
        V[2] = grid(v1, v2);
        V[3] = grid(v2, v2);
        V[4] = grid(v2, v3);
        V[5] = grid(v3, v3);
        V[6] = grid(v3, v4);
        V[7] = grid(v4, v4);
        get_V();
    }

    void solve() {
        if (P == 2) {
            get_V2();
            for (int i = 1; i < V_size; i ++) {
                if (i < V_size - 4) brute(V[i-1], V[i]);
                else last(V[i-1], V[i]);
            }
        }
        if (P == 5) {
            get_V8();
            for (int i = 1; i < V_size; i ++) {
                if (i < V_size - 3) brute(V[i-1], V[i]);
                else last(V[i-1], V[i]);
            }
        }
        if (P == 10) {
            get_V8();
            for (int i = 1; i < V_size; i ++) {
                if (i < V_size - 4) brute(V[i-1], V[i]);
                else last(V[i-1], V[i]);
            }
        }
        if (P == 15) {
            get_V8();
            for (int i = 1; i < V_size; i ++) {
                if (i < V_size - 3) brute(V[i-1], V[i]);
                else last(V[i-1], V[i]);
            }
        }
    }
}

void SOLVE() {
    CELL::init();
    UPDATE::init();
    GRID::solve();
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test_id = 1; test_id <= T; test_id ++) {
        input();
        Init();
        SOLVE();
        assert(print() == 1);
    }
}
