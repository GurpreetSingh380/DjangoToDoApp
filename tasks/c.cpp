#include <iostream>
#include <vector>
#include<cmath>
#include <string>
using namespace std;

int pivot(int l, int h, vector<int>& nums){
        if (l<=h){
            int mid = l + (h-l)/2;
            if (mid+1<nums.size() && nums[mid+1]<nums[mid]) return mid;
            if (nums[mid]>nums[l]) return pivot(mid+1, h, nums);
            else return pivot(l, mid-1, nums);
        }
        return -1;
    }

    int bs(int l, int h, vector<int>& nums, int tar){
        if (l<=h){
            int mid = l + (h-l)/2;
            if (nums[mid]==tar) return mid;
            if (nums[mid]>tar) return bs(l, mid-1, nums, tar);
            else return bs(mid+1, h, nums, tar);
        }
        return -1;
    }

    int search(vector<int>& nums, int target) {
        int p = pivot(0, nums.size()-1, nums);
        if (p==-1) return bs(0, nums.size()-1, nums, target);
        else {
            if (nums[p]==target) return p;
            else if (nums[p]>target) return bs(0, p-1, nums, target);
            return bs(p+1, nums.size()-1, nums, target);
        }
    }

double mult(double m, int n){
    double k=m;
    for(int i=1; i<n; i++){
        k *= m;
    }
    return k;
}

double nthRoot(int x, int n){
    double l=1.0, r=(double)x, mid;
    while (r-l > 1e-6){
        mid=l+(r-l)/2.0;
        if (mult(mid, n)>x) r=mid;
        else l=mid;
    }
    return l;
}
bool canEat(vector<int> piles, int h, int k){
        int ans=0;
        for(int i: piles) ans += ceil((double)i/k);
        return ans<=h;
    }
int minEatingSpeed(vector<int>& piles, int h) {
        int l=1, r=10, mid, mini=1e9;
        while (l<r){
            mid = l + (r-l)/2;
            if (canEat(piles, h, mid)) {r=mid-1; mini=min(mini, mid);}
            else l=mid+1;
        }
        return mini;
    }
bool check(pair<int, int> p, vector<vector<bool>> kept){
        int row=p.first, col=p.second;
        int cl=col-1, cr=col+1;
        for(int r=row-1; r>=0; r--){
            if (kept[r][col]) return false;
            if (cl>=1){
                if (kept[r][cl--]) return false;
            }
            if (cr<kept.size()){
                if (kept[r][cr++]) return false;
            }
        }
        return true;
    }
    void nq(int row, vector<int> &temp, vector<vector<int>> &ans, vector<vector<bool>> &kept){
        if (row==kept.size()) {ans.push_back(temp); return;}
        for(int col=1; col<=kept.size()-1; col++){
            kept[row][col]=true; temp.push_back(col);
            if (check({row, col}, kept)) {nq(row+1, temp, ans, kept); kept[row][col]=false; temp.pop_back();}
            else {kept[row][col]=false; temp.pop_back();}
        }
    }
    vector<vector<int>> nQueen(int n) {
        vector<vector<bool>> kept(n+1, vector<bool>(n+1, false));
        vector<vector<int>> ans;
        vector<int> temp;
        nq(1, temp, ans, kept);
        return ans;
    }

void give(int row, int col, vector<int> &r, vector<int> &c, vector<vector<char>> board){
        for(int k=0; k<9; k++){
            if (k!=row && board[k][col]!='.') c[board[k][col]-'0']=1;
            if (k!=col && board[row][k]!='.') r[board[row][k]-'0']=1;
        }
    }

    void solve(pair<int, int> p, vector<vector<char>> &board, vector<vector<vector<int>>> &box){
        int row=p.first, col=p.second;
        if (row==9) return;
        if (board[row][col]!='.'){
            if (col==8) solve({row+1, 0}, board, box);
            else solve({row, col+1}, board, box);
            return;
        }
        
        vector<int> r(10, 0), c(10, 0);
        give(row, col, r, c, board); int i=0;
        for(int num=1; num<=9; num++){
            if (!r[num] && !c[num] && !box[floor(row/2.9)][floor(col/2.9)][num]){
                board[row][col]=char(num+'0'); box[floor(row/2.9)][floor(col/2.9)][num]=1;
                if (col==8) solve({row+1, 0}, board, box);
                else solve({row, col+1}, board, box);
                box[floor(row/2.9)][floor(col/2.9)][num]=0;
            }
        }
    }
    void solveSudoku(vector<vector<char>>& board) {
        vector<vector<vector<int>>> box(3, vector<vector<int>>(3, vector<int>(10, 0)));
        for(int row=0; row<9; row++){
            for(int col=0; col<9; col++){
                if (board[row][col]!='.'){
                    box[floor(row/2.9)][floor(col/2.9)][board[row][col]-'0']=1;
                }
            }
        }
         
        solve({0, 0}, board, box);
    }
int main(){
    vector<vector<char>> board = {{'5','3','.','.','7','.','.','.','.'}, {'6','.','.','1','9','5','.','.','.'}, {'.','9','8','.','.','.','.','6','.'}, {'8','.','.','.','6','.','.','.','3'}, {'4','.','.','8','.','3','.','.','1'}, {'7','.','.','.','2','.','.','.','6'}, {'.','6','.','.','.','.','2','8','.'}, {'.','.','.','4','1','9','.','.','5'}, {'.','.','.','.','8','.','.','7','9'}};
    solveSudoku(board);
    // vector<vector<vector<int>>> box(3, vector<vector<int>>(3, vector<int>(10, 0)));
    //     for(int row=0; row<9; row++){
    //         for(int col=0; col<9; col++){
    //             if (board[row][col]!='.'){
    //                 box[floor(row/2.9)][floor(col/2.9)][board[row][col]-'0']=1;
    //             }
    //         }
    //     }
    // for(auto i: box){
    //     for(auto j: i){
    //         for(auto k: j){
    //             cout << k << " ";
    //         }
    //         cout << endl;
    //     }
    //     cout << endl;
    // }

    // vector<int> r(10, 0), c(10, 0);
    // give(0, 7, r, c, board);
    // cout << "Row: "; 
    // for(auto i: r){
    //     cout << i << " "; 
    // }
    // cout << endl;
    // cout << "Col: "; 
    // for(auto i: c){
    //     cout << i << " "; 
    // }
    // cout << endl;
    for(auto i: board){
        for(auto j: i){
            cout << j << " ";
        }
        cout << endl;
    }
    // vector<int> v = {3, 6, 7, 11};
    // cout << pivot(0, v.size()-1, v);
    // int x=29, n=3;
    // double ans = nthRoot(x, n);
    // bool ans = canEat(v, 8, 3);
    // cout << ans << endl;
    // cout << minEatingSpeed(v, 8);
    // vector<vector<int>> ans = nQueen(10);
    // for(auto i: ans){
    //     for(auto j: i){
    //         cout << j << ", ";
    //     }
    //     cout << endl;
    // }
    // string s="";
    // s.append(4, 'a');
    // cout << s;
    // s[2]='r';
    // cout << s;
    // cout << 5/2.0;0
}