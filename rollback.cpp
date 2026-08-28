#include <bits/stdc++.h>
using namespace std;
#define sz(x) size(x)
#define pb push_back

#pragma once

typedef pair<int, int> pi;
#define F first
#define S second

struct RollbackUF {
    vector<int> e; vector<pi> st;
    RollbackUF(int n) : e(n, -1) {}
    int size(int x){
        return -e[find(x)];
    }
    // there's no path compression
    int find(int x){
        return e[x] < 0 ? x : find(e[x]);
    }
    int time(){
        return st.size();
    }
    void rollback(int t){
        for (int i = time(); i --> t;){
            e[st[i].F] = st[i].S;
        }
        st.resize(t);
    }
    // puts the smaller one under the bigger one
    bool join(int a, int b){
        a = find(a); b = find(b);
        if (a == b) return false;
        // so a < b
        if (size(a) > size(b)) swap(a, b);
        st.pb({b, e[b]});
        st.pb({a, e[a]});
        e[b] += e[a]; e[a] = b;
        return true;
    }
};






















// this version stores distances to parents, too. from https://cp-algorithms.com/data_structures/disjoint_set_union.html
const int MM = 1e5;

pi parent[MM+1];
int rnk[MM+1];
void make_set(int v){
    parent[v] = {v, 0};
    rnk[v] = 0;
}

pi find_set(int v){
    if (v != parent[v].F){
        int len = parent[v].S;
        parent[v] = find_set(parent[v].first);
        parent[v].second += len;
    }
    return parent[v];
}

bool union_sets(int a, int b){
    a = find_set(a).first;
    b = find_set(b).first;
    if (a == b) return false;
    if (rnk[a] < rnk[b]) swap(a, b);
    parent[b] = {a, 1};
    if (rnk[a] == rnk[b]) rnk[a]++;
}