#include <iostream>
#include <vector>

using namespace std;


////////////////    Fibonacci Series

/// Recursion + Memoization
int fibMemo(int n,vector<int> &dp){
    if(n==0||n==1) return n;

    if(dp[n]!=-1) return dp[n];

    dp[n] = fibMemo(n-1,dp)+fibMemo(n-2,dp);

    return dp[n];
}

/// Tabulation
int fibTab(int n,vector<int> &dp){
    dp[0] = 0;
    dp[1] = 1;

    if(dp[n]!=-1) return dp[n];
    
    for(int i=2;i<=n;i++){
        dp[i] = dp[i-1]+dp[i-2];
    }

    return dp[n];
}

/// Space Optimization
int fibspace(int n){
    if(n==0||n==1) return n;
    int prev1 = 0;
    int prev2 = 1;

    int curr;
    for(int i=2;i<=n;i++){
        curr = prev1+prev2;
        prev1 = prev2;
        prev2 = curr;
    }
    return curr;
}

int main(){
    int n;
    cin>>n;

    vector<int> dp(n+1,-1);

    cout<<fibMemo(n,dp);
    return 0;
}




///////////////   Ways to reach nth stair

/// Recursion + Memoization
int solve(int n,vector<int> &dp){
    if(n==0 || n==1) return 1;

    if(dp[n]!=-1) return dp[n];

    dp[n] = solve(n-1,dp) + solve(n-2,dp);

    return dp[n];
}

/// Tabulation
int solve(int n,vector<int> &dp){
    dp[0] = 1;
    dp[1] = 1;

    if(dp[n]!=-1) return dp[n];

    for(int i=2;i<=n;i++){
        dp[i] = dp[i-1]+dp[i-2];
    }

    return dp[n];
}

/// Space Optimization
int solve(int n){
    if(n==0 || n==1) return 1;
    int prev1 = 1;
    int prev2 = 1;
    int curr;

    for(int i=2;i<=n;i++){
        curr = (prev1+prev2)%1000000007;
        prev1 = prev2;
        prev2 = curr;
    }
    return curr;
}

int countDistinctWays(int nStairs) {
    vector<int> dp(nStairs+1,-1);
    return solve(nStairs,dp);
}