#include<bits/stdc++.h>
using namespace std;


class SegmentTree{
  vector<int>sg;
  vector<int>arr;
  int n;
  int findMinHelper(int l,int r,int si,int ei,int ind){
    int mid=(si+ei)>>1;
    if(si>=l&&ei<=r){
      return sg[ind];
    }
    else if(si>r||ei<l)return INT_MAX;
    else{
      int leftRes=findMinHelper(l,r,si,mid,2*ind+1);
      int rightRes=findMinHelper(l,r,mid+1,ei,2*ind+2);
      return min(leftRes,rightRes);
    }
  }
  void updateHelper(int si,int ei,int ind,int tarInd,int ele){
    if(si==ei){
      arr[tarInd]=ele;
      sg[ind]=ele;
      return;
    }
    int mid=(si+ei)>>1;
    if(tarInd>=si&&tarInd<=mid){
      updateHelper(si,mid,2*ind+1,tarInd,ele);
      sg[ind]=min(sg[2*ind+2],sg[2*ind+1]);
    }
    else{
      updateHelper(mid+1,ei,2*ind+2,tarInd,ele);
      sg[ind]=min(sg[2*ind+2],sg[2*ind+1]);
    }
  }
  public:
    SegmentTree(vector<int>&arr){
      n=arr.size();
      for(auto it:arr){
        this->arr.push_back(it);
      }
      sg.resize(4*n);
      build(0,0,n-1);

    } 
    void build(int ind,int si,int ei){
      if(si==ei){
        sg[ind]=arr[si];
        return;
      }
      int mid=(si+ei)>>1;
      build(2*ind+1,si,mid);
      build(2*ind+2,mid+1,ei);
      int left=sg[2*ind+1];
      int right=sg[2*ind+2];
      sg[ind]=min(left,right);

    }
    int findMin(int l,int r){
      int res=findMinHelper(l,r,0,n-1,0);
      return res;
    }
    void update(int ele,int ind){
      updateHelper(0,n-1,0,ind,ele);
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    int q;
    cin>>n>>q;
    vector<int>arr(n);
    for(int i=0;i<n;i++){cin>>arr[i];}
    SegmentTree obj(arr);
    while(q--){
      char qr;
      cin>>qr;
      if(qr=='u'){
        int ind,ele;
        cin>>ind>>ele;
        obj.update(ele,ind-1);
      }
      else{
        int l,r;
        cin>>l>>r;
        int res=obj.findMin(l-1,r-1);
        cout<<res<<endl;
      }
    }
    return 0;
}