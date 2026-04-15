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





/////////////////  nth element (min. no. of coins)

/// Recursion
int solve(vector<int> num,int x){
    if(x==0) return 0;
    if(x<0) return INT_MAX;

    int mini = INT_MAX;
    for(int i=0;i<num.size();i++){
        int ans = solve(num,x-num[i]);
        if(ans!=INT_MAX){
            mini = min(mini,1+ans);
        }
    }
    return mini;
}

/// Recursion+Memoization
int solve1(vector<int> num,int x,vector<int>& dp){
    if(x==0) return 0;
    if(x<0) return INT_MAX;

    if(dp[x]!=-1) return dp[x];

    int mini = INT_MAX;
    for(int i=0;i<num.size();i++){
        int ans = solve(num,x-num[i]);
        if(ans!=INT_MAX){
            mini = min(mini,1+ans);
        }
    }
    dp[x] = mini;
    return mini;
}

/// Tabulation
int solve2(vector<int> num,int x){
    vector<int> dp(x+1,INT_MAX);
    dp[0] = 0;

    for(int i=1;i<=x;i++){
        for(int j=0;j<num.size();j++){
            if(i-num[j] >= 0 && dp[i-num[j]]!=INT_MAX){
                dp[i] = min(dp[i],1+dp[i-num[j]]); 
            }
        }
    }

    if(dp[x] == INT_MAX) return -1;
    return dp[x];

}





////////////////  Maximum Sum of non adjacent element

/// Recursion + Memoization
int solve(vector<int> &nums,int i,vector<int> &dp){
    if(i>=nums.size()){
        return 0;
    }

    if(dp[i]!=-1) return dp[i];

    int inc = solve(nums,i+2,dp) + nums[i];
    int exc = solve(nums,i+1,dp);

    dp[i] = max(inc,exc);
    return dp[i];
}


/// Tabulation
int solve(vector<int> &nums){
    vector<int> dp(nums.size(),-1);
    dp[0] = nums[0];


    for(int i=1;i<nums.size();i++){
        int inc = dp[i-2] + nums[i];
        int exc = dp[i-1];

        dp[i] = max(inc,exc);
    }
    return dp[nums.size()-1];
}

/// Space Optimization
int solve(vector<int> &nums){
    int prev1 = nums[0];
    int prev2 = 0;

    for(int i=1;i<nums.size();i++){
        int curr = max(prev2+nums[i],prev1);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}