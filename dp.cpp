#include <iostream>
#include <vector>

using namespace std;

int fibMemo(int n,vector<int> &dp){
    if(n==0||n==1) return n;

    if(dp[n]!=-1) return dp[n];

    dp[n] = fibMemo(n-1,dp)+fibMemo(n-2,dp);

    return dp[n];
}

int fibTab(int n,vector<int> &dp){
    dp[0] = 0;
    dp[1] = 1;

    if(dp[n]!=-1) return dp[n];
    
    for(int i=2;i<=n;i++){
        dp[i] = dp[i-1]+dp[i-2];
    }

    return dp[n];
}

int fibspace(int n){
    int prev1 = 0;
    int prev2 = 1;

    int curr = prev1+prev2;
    for(int i=2;i<=n;i++){
        prev1 = prev2;
        prev2 = curr;
        curr = prev1+prev2;
    }
}

int main(){
    int n;
    cin>>n;

    vector<int> dp(n+1,-1);

    cout<<fibMemo(n,dp);
    return 0;
}