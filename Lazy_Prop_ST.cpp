#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define V vector
#define pb push_back
#define pf push_front
#define qb pop_back
#define qf pop_front
#define eb emplace_back
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
#define fi first
#define se second
#define FR(i, a, b) for (int i = a; i <= b; i++)
#define FRR(i, a, b) for (int i = a; i >= b; i--)
#define _sort(x) sort((x).begin(),(x).end());
const int inf = 0x3f3f3f3f, mod = 1e9 + 7;
const ll infl = 0x3f3f3f3f3f3f3f3fll;

//update-> incr by val in range l to r 
//query-> find whats at index ind

class ST{
    vector<int>arr;
    int n;

    vector<int>lazy;

    void updateHelper(int l,int r,int si,int ei,int ind,int val){
        if(si>r||ei<l){
            return;
        }
        else if(si==ei){
            lazy[ind]+=val;
            return;
        }
        else if(si>=l&&ei<=r){
            lazy[ind]+=val;
            return;
        }
        int mid=(si+ei)>>1;
        updateHelper(l,r,si,mid,2*ind+1,val);
        updateHelper(l,r,mid+1,ei,2*ind+2,val);
    }
    void propagate(int ind,int si,int ei){
        int mid=(si+ei)>>1;
        lazy[2*ind+1]+=lazy[ind];
        lazy[2*ind+2]+=lazy[ind];
        lazy[ind]=0;
    }
    int queryHelper(int ind,int tarInd,int si,int ei){
        if(si==ei){
            return lazy[ind];
        }
        int mid=(si+ei)>>1;
        propagate(ind,si,ei);
        if(tarInd<=mid){
            return queryHelper(2*ind+1,tarInd,si,mid);
        }
        else{
            return queryHelper(2*ind+2,tarInd,mid+1,ei);
        }
        
    }
    public:
    ST(vector<int>&arr){
        this->n=arr.size();
        for(auto it:arr)this->arr.push_back(it);

        lazy.resize(4*n);
        build(0,n-1,0);
        for(auto it:lazy)cout<<it<<" ";
        cout<<endl;

    }
    void build(int si,int ei,int ind){
        if(si==ei){
            lazy[ind]=arr[si];
            return;
        }
        int mid=(si+ei)>>1;
        build(si,mid,2*ind+1);
        build(mid+1,ei,2*ind+2);
        lazy[ind]=0;
    }
    void update(int l,int r,int val){
        updateHelper(l,r,0,n-1,0,val);
    }
    int query(int ind){
        int res=queryHelper(0,ind,0,n-1);
        return res;
    }
};

int main(){
    int n,q;
    cin>>n>>q;
    V<int>arr(n);
    FR(i,0,n-1)cin>>arr[i];
    ST obj(arr);
    while(q--){
        char ch;
        cin>>ch;
        if(ch=='u'){
            int l,r,val;
            cin>>l>>r>>val;
            obj.update(l,r,val);
        }
        else{
            int ind;
            cin>>ind;
            int res=obj.query(ind);
            cout<<"val at index "<<ind<<" is: ";
            cout<<res<<endl;
        }
    }

}