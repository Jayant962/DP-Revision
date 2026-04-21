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
        int inc = nums[i];
        if(i-2 >= 0) inc += dp[i-2];
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





//////////////   House Roberry

/// Recursion
int solve1(vector<int> & valueInHouse,int i,int n){
    if(i>=n) return 0;
    
    int inc = solve1(valueInHouse,i+2,n) + valueInHouse[i];
    int exc = solve1(valueInHouse,i+1,n);

    return max(inc,exc);
}

long long int houseRobber(vector<int>& valueInHouse)
{
    if(valueInHouse.size() == 1) return valueInHouse[0];
    int i = 0;
    int n = valueInHouse.size();

    int ans1 = solve1(valueInHouse,i,n-1);
    int ans2 = solve1(valueInHouse,i+1,n);

    return max(ans1,ans2);
}

/// Recursion + Memoization
long long solve1(vector<int> & valueInHouse,int i,int n,vector<long long> &dp){
    if(i>=n) return 0;
    
    if(dp[i]!=-1) return dp[i];
    long long inc = solve1(valueInHouse,i+2,n,dp) + valueInHouse[i];
    long long exc = solve1(valueInHouse,i+1,n,dp);

    dp[i] = max(inc,exc);
    return dp[i];
}

long long int houseRobber(vector<int>& valueInHouse)
{
    if(valueInHouse.size() == 1) return valueInHouse[0];

    int i = 0;
    int n = valueInHouse.size();

    vector<long long> dp1(n,-1);
    vector<long long> dp2(n,-1);

    long long ans1 = solve1(valueInHouse,i,n-1,dp1);
    long long ans2 = solve1(valueInHouse,i+1,n,dp2);

    return max(ans1,ans2);
}


/// Tabulation
long long solve1(vector<int> & valueInHouse,int i,int n){
    vector<long long> dp(n+1,-1);
    
    dp[i] = valueInHouse[i];

    for(int j=i+1;j<n;j++){
        long long inc = valueInHouse[j];
        if(j-2 >= i) inc += dp[j-2];
        long long exc = dp[j-1];

        dp[j] = max(inc,exc);
    }
    return dp[n-1];
}

long long int houseRobber(vector<int>& valueInHouse)
{
    if(valueInHouse.size() == 1) return valueInHouse[0];

    int i = 0;
    int n = valueInHouse.size();

    long long ans1 = solve1(valueInHouse,i,n-1);
    long long ans2 = solve1(valueInHouse,i+1,n);

    return max(ans1,ans2);
}

/// Space Optimization
long long solve1(vector<int> & valueInHouse,int i,int n){
    long long prev2 = 0;
    long long prev1 = valueInHouse[i];

    for(int j=i+1;j<n;j++){
        long long curr = max(prev2+valueInHouse[j],prev1);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

long long int houseRobber(vector<int>& valueInHouse)
{
    if(valueInHouse.size() == 1) return valueInHouse[0];

    int i = 0;
    int n = valueInHouse.size();

    long long ans1 = solve1(valueInHouse,i,n-1);
    long long ans2 = solve1(valueInHouse,i+1,n);

    return max(ans1,ans2);
}





/////////////////////    Cut into segments

/// Recursion
int solve(int n,int x,int y,int z){
	if(n<0) return INT_MIN;
	if(n==0) return 0;

	int a = solve(n-x,x,y,z) + 1;
	int b = solve(n-y,x,y,z) + 1;
	int c = solve(n-z,x,y,z) + 1;
	 
	return max(a,max(b,c));
}

int cutSegments(int n, int x, int y, int z) {
	int ans = solve(n,x,y,z);
	if(ans<0) return 0;
	return ans;
}

/// Recursion + Memoization
int solve(int n,int x,int y,int z,vector<int> &dp){
	if(n<0) return INT_MIN;
	if(n==0) return 0;

	if(dp[n]!=-1) return dp[n];

	int a = solve(n-x,x,y,z,dp) + 1;
	int b = solve(n-y,x,y,z,dp) + 1;
	int c = solve(n-z,x,y,z,dp) + 1;
	 
	dp[n] = max(a,max(b,c));
	return dp[n];
}

int cutSegments(int n, int x, int y, int z) {
	vector<int> dp(n+1,-1);
	int ans = solve(n,x,y,z,dp);
	if(ans<0) return 0;
	return ans;
}

/// Tabulation
int solve(int n,int x,int y,int z){
	vector<int> dp(n+1,INT_MIN);
	dp[0] = 0;

	for(int i=1;i<=n;i++){
		if(i-x >= 0) dp[i] = max(dp[i],1+dp[i-x]);
		if(i-y >= 0) dp[i] = max(dp[i],1+dp[i-y]);
		if(i-z >= 0) dp[i] = max(dp[i],1+dp[i-z]);
	}
	if(dp[n]<0) return 0;
	return dp[n];
}

int cutSegments(int n, int x, int y, int z) {
	int ans = solve(n,x,y,z);
	if(ans<0) return 0;
	return ans;
}





////////////////   Count Dearrangements

#define MOD 1000000007

/// Recursion
long long int countDerangements(int n) {
    if(n==1) return 0;
    if(n==2) return 1;
    return (n-1) * (countDerangements(n-1)%MOD + countDerangements(n-2)%MOD)%MOD;
}

/// Recursion + Memoization
long long solve(int n,vector<long long> &dp){
    if(n==1) return 0;
    if(n==2) return 1;

    if(dp[n]!=-1) return dp[n];

    dp[n] = (n-1)*(solve(n-1,dp)%MOD + solve(n-2,dp)%MOD)%MOD;

    return dp[n];
}
long long int countDerangements(int n) {
    vector<long long> dp(n+1,-1);
    return solve(n,dp);
}

/// Tabulation
long long solve(int n){
    vector<long long> dp(n+1,-1);
    dp[1] = 0;
    dp[2] = 1;

    for(int i=3;i<=n;i++){
        dp[i] = (i-1) * (dp[i-1]%MOD + dp[i-2]%MOD)%MOD;
    }

    return dp[n];
}
long long int countDerangements(int n) {
    return solve(n);
}

/// Space Optimization
long long solve(int n){
    long long prev2 = 0;
    long long prev1 = 1;
    long long curr;

    for(int i=3;i<=n;i++){
        curr = (i-1) * (prev1%MOD + prev2%MOD)%MOD;
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}
long long int countDerangements(int n) {
    return solve(n);
}






/////////////////     Painting Fence problem

/// Recursion
#define MOD 1000000007
#include <bits/stdc++.h> 
int numberOfWays(int n, int k) {
    if(n==1) return k;
    if(n==2) return k+(k*(k-1));

    long long same = (1LL * numberOfWays(n-2,k)%MOD)*((k-1)%MOD) %MOD;
    long long diff = (1LL * numberOfWays(n-1,k)%MOD)*((k-1)%MOD) %MOD;

    return (same+diff)%MOD;
}

/// Recursion+ Memoization
int solve(int n,int k,vector<int> &dp){
    if(n==1) return k;
    if(n==2) return k+(k*(k-1));

    if(dp[n]!=-1) return dp[n];

    long long same = (1LL * solve(n-2,k,dp) * (k-1)) % MOD;
    long long diff = (1LL * solve(n-1,k,dp) * (k-1)) % MOD;

    dp[n] = (same + diff) % MOD;

    return dp[n];
}

int numberOfWays(int n, int k) {
    vector<int> dp(n+1,-1);

    return solve(n,k,dp);
}

/// Tabulation
int solve(int n,int k){
    vector<int> dp(n+1,-1);
    dp[1] = k;
    dp[2] = k+(k*(k-1));

    for(int i=3;i<=n;i++){
        long long same = (1LL * dp[i-2] * (k-1)) % MOD;
        long long diff = (1LL * dp[i-1] * (k-1)) % MOD;

        dp[i] = (same+diff)%MOD;
    }
    return dp[n];
}

/// Space Optimization
int solve(int n,int k){
    int prev2 = k;
    int prev1 = k+(k*(k-1));

    int curr;

    for(int i=3;i<=n;i++){
        long long same = (1LL * prev2 * (k-1)) % MOD;
        long long diff = (1LL * prev1 * (k-1)) % MOD;

        curr = (same+diff)%MOD;
        prev2 = prev1;
        prev1 = curr;
    }

    return prev1;
}





///////////////////  Knapsack Problem

/// Recursion(shrink from left)
int solve(vector<int> &weight, vector<int> &value, int i, int n, int W){
	if(i==n) return 0;

	int inc = 0;
	if(weight[i] <= W)
		inc = value[i] + solve(weight,value,i+1,n,W-weight[i]);

	int exc = solve(weight,value,i+1,n,W);

	return max(inc,exc);
}

int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight) 
{
	return solve(weight,value,0,n,maxWeight);
}

/// Recursion shrink from right
int solve(vector<int> &weight, vector<int> &value, int n, int W){
	if(n<0) return 0;

	int inc = 0;
	if(weight[n] <= W)
		inc = value[n] + solve(weight,value,n-1,W-weight[n]);

	int exc = solve(weight,value,n-1,W);

	return max(inc,exc);
}

int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight) 
{
	return solve(weight,value,n-1,maxWeight);
}


/// Recursion + Memoization
#include <bits/stdc++.h> 
int solve(vector<int> &weight, vector<int> &value, int n, int W,vector<vector<int>> &dp){
	if(n<0) return 0;

	if(dp[n][W]!=-1) return dp[n][W];

	int inc = 0;
	if(weight[n] <= W)
		inc = value[n] + solve(weight,value,n-1,W-weight[n],dp);

	int exc = solve(weight,value,n-1,W,dp);

	dp[n][W] = max(inc,exc);
	return dp[n][W];
}

int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight) 
{
	vector<vector<int>> dp(n,vector<int>(maxWeight+1,-1));
	return solve(weight,value,n-1,maxWeight,dp);
}

/// Tabulation
int solve(vector<int> &weight, vector<int> &value, int n, int W){
	vector<vector<int>> dp(n,vector<int>(W+1,0));
	for(int i=0;i<=W;i++){
		if(weight[0] <= i)
			dp[0][i] = value[0];
		else 
			dp[0][i] = 0;
	}

	for(int i=1;i<n;i++){
		for(int j=0;j<=W;j++){
			int inc = 0;
			if(weight[i] <= j)
				inc = value[i] + dp[i-1][j-weight[i]];

			int exc = dp[i-1][j];

			dp[i][j] = max(inc,exc);
		}
	}
	return dp[n-1][W];
}

int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight) 
{
	return solve(weight,value,n,maxWeight);
}

/// Space Optimization
int solve(vector<int> &weight, vector<int> &value, int n, int W){
	vector<int> prev(W+1,0);
	vector<int> curr(W+1,0);

	for(int i=0;i<=W;i++){
		if(weight[0] <= i)
			prev[i] = value[0];
		else 
			prev[i] = 0;
	}

	for(int i=1;i<n;i++){
		for(int j=0;j<=W;j++){
			int inc = 0;
			if(weight[i] <= j)
				inc = value[i] + prev[j-weight[i]];

			int exc = prev[j];

			curr[j] = max(inc,exc);
		}
		prev = curr;
	}
	return prev[W];
}

int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight) 
{
	return solve(weight,value,n,maxWeight);
}




/////////////////   Perfect Squares problem

class Solution {
  public:
    int solve(int n){
        if(n==0) return 0;
        int ans = n;
        for(int i=1;i*i<=n;i++){
            int temp = i*i;
            ans = min(ans,solve(n-temp)+1);
        }
        return ans;
    }
    
    int solveMem(int n,vector<int> &dp){
        if(n==0) return 0;
        if(dp[n]!=-1) return dp[n];
        int ans = n;
        for(int i=1;i*i<=n;i++){
            int temp = i*i;
            ans = min(ans,solveMem(n-temp,dp)+1);
        }
        dp[n] = ans;
        return dp[n];
    }
    
    int solveTab(int n){
        vector<int> dp(n+1,INT_MAX);
        dp[0] = 0;

        for(int i=1;i<=n;i++){
            for(int j=1;j*j<=n;j++){
                int temp = j*j;
                if(i-temp>=0) dp[i] = min(dp[i],dp[i-temp]+1);
            }
        }
        return dp[n];
    }
    
    int minSquares(int n) {
        // Code here
        return solve(n);
        
        vector<int> dp(n+1,-1);
        return solveMem(n,dp);
        
        return solveTab(n);
    }
};