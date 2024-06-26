#include <bits/stdc++.h>
using namespace std;
#define ll long long
void eulertour2(vector<list<int>> &adj, int src, int parent, vector<ll> &arr)
{
    arr.push_back(src);
    for (auto ngh : adj[src])
    {
        if (ngh != parent)
            eulertour2(adj, ngh, src, arr);
    }
    arr.push_back(-src);
}
#define ll long long
class segmentTree
{

public:
    vector<ll> segTree;
    segmentTree(int n)
    {
        segTree.resize(4 * n + 10, 0);
    }
    ll merge(ll p, ll q)
    {
        return p + q;
    }
    void build(ll idx, ll l, ll r, vector<ll> &a, vector<ll> &values)
    {
        if (l == r)
        {
            segTree[idx] = (2 * (a[l] > 0) - 1) * values[abs(a[l])];
            return;
        }
        ll m = (l + r) / 2;
        build(idx * 2 + 1, l, m, a, values);
        build(idx * 2 + 2, m + 1, r, a, values);
        segTree[idx] = merge(segTree[idx * 2 + 1], segTree[idx * 2 + 2]);
    }
    void update(ll idx, ll l, ll r, ll i, ll j, ll x)
    {
        if (l > j or i > r or l > r)
            return;
        if (i == l and r == j)
        {
            segTree[idx] = x;
            return;
        }
        ll m = (l + r) / 2;
        update(idx * 2 + 1, l, m, i, j, x);
        update(idx * 2 + 2, m + 1, r, i, j, x);
        segTree[idx] = merge(segTree[idx * 2 + 1], segTree[idx * 2 + 2]);
    }

    ll query(ll idx, ll l, ll r, ll i, ll j)
    {
        if (l > j or i > r or l > r)
            return 0;
        if (i <= l and r <= j)
        {
            return segTree[idx];
        }
        ll m = (l + r) / 2;
        ll ans = merge(query(idx * 2 + 1, l, m, i, j), query(idx * 2 + 2, m + 1, r, i, j));

        return ans;
    }
};

int main()
{
    int n, q;
    cin >> n >> q;
    vector<ll> values(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> values[i];
    }
    vector<list<int>> adj(n + 1, list<int>());
    for (int i = 0; i <= n - 2; i++)
    {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<ll> arr;
    eulertour2(adj, 1, -1, arr);
    int sz = arr.size();
    vector<int> leftPtr(n + 1, -1);
    vector<int> rightPtr(n + 1, -1);
    segmentTree st(sz);
    st.build(0, 0, sz - 1, arr, values);

    for (int i = 0; i < sz; i++)
    {
        if (leftPtr[abs(arr[i])] == -1)
            leftPtr[abs(arr[i])] = i;
        rightPtr[abs(arr[i])] = i;
    }

    while (q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            ll node, x;
            cin >> node >> x;
            values[node] = x;
            st.update(0, 0, sz - 1, leftPtr[node], leftPtr[node], x);
            st.update(0, 0, sz - 1, rightPtr[node], rightPtr[node], -x);
        }
        else
        {
            int node;
            cin >> node;
            cout << st.query(0, 0, sz - 1, leftPtr[0], leftPtr[node]) << endl;
        }
    }
}