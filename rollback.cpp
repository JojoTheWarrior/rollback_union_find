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
}