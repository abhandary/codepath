//
//  main.cpp
//  InterviewBitPreWork
//
//  Created by Akshay Bhandary on 6/27/17.
//  Copyright © 2017 AkshayBhandary. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
 };

class Solution {

    // checkpoint 2
    vector<vector<int> > prettyPrint(int A);
    
    // checkpoint 4
    ListNode* subtract(ListNode* A);
    
    // checkpoint 5
    vector<vector<int>> permute(vector<int> &A);
};


// MARK: - checkpoint 2
vector<vector<int> > Solution::prettyPrint(int A) {
    
    int len = A * 2 - 1;
    vector<vector<int>> result(len, vector<int>(len, 0));
    int srow = 0, erow = len - 1;
    int scol = 0, ecol = len - 1;
    int current = A;
    
    while (srow <= erow && scol <= ecol) {
        for (int jx = scol; jx <= ecol; jx++) {
            result[srow][jx] = current;
        }
        srow++;
        if (srow > erow) { break; }
        for (int ix = srow; ix <= erow; ix++) {
            result[ix][ecol] = current;
        }
        ecol--;
        if (ecol < scol) { break; }
        for (int jx = ecol; jx >= scol; jx--) {
            result[erow][jx] = current;
        }
        erow--;
        if (erow < srow) { break; }
        for (int ix = erow; ix >= srow; ix--) {
            result[ix][scol] = current;
        }
        scol++;
        current--;
    }
    return result;
}

// MARK: - checkpoint 4

ListNode* Solution::subtract(ListNode* A) {
    if (A == NULL || A->next == NULL) { return A; }
    int len = 0;
    ListNode* itr = A;
    while (itr) {
        len++;
        itr = itr->next;
    }
    itr = A;
    for (int ix = 0; ix < len / 2; ix++) {
        itr = itr->next;
    }
    if (len & 1) {
        itr = itr->next;
    }
    
    
    // reverse the rest of the list
    ListNode* revHead = NULL;
    ListNode* next = itr->next;
    ListNode* nextToNext = NULL;
    itr->next = NULL;
    
    if (next) { nextToNext = next->next; }
    
    while (next) {
        next->next = itr;
        itr = next;
        next = nextToNext;
        if (nextToNext) { nextToNext = nextToNext->next; }
    }
    
    revHead = itr;
    
    ListNode* itr2 = revHead;
    itr = A;
    for (int ix = 0; ix < len / 2; ix++) {
        itr->val = itr2->val - itr->val;
        itr = itr->next; itr2 = itr2->next;
    }
    
    // reverse the reversed list again
    itr = revHead;
    next = itr->next;
    itr->next = NULL;
    if (next) { nextToNext = next->next; }
    while (next) {
        next->next = itr;
        itr = next;
        next = nextToNext;
        if (nextToNext) { nextToNext = nextToNext->next; }
    }
    return A;
}

// MARK: - checkpoint 5

void permuteHelper(vector<int>& input, vector<bool>& used, vector<int> partial, vector<vector<int>>& result) {
    
    if (partial.size() == input.size()) {
        result.push_back(partial);
        return;
    }
    
    for (int ix = 0; ix < input.size(); ix++) {
        if (used[ix] == true) { continue; }
        if (ix > 0 && input[ix] == input[ix - 1] && !used[ix - 1]) { continue; }
        
        partial.push_back(input[ix]);
        used[ix] = true;
        permuteHelper(input, used, partial, result);
        used[ix] = false;
        partial.pop_back();
    }
}


vector<vector<int>> Solution::permute(vector<int> &A) {
    vector<vector<int>> result;
    vector<int> partial;
    vector<bool> used = vector<bool>(A.size(), false);
    sort(A.begin(), A.end());
    permuteHelper(A, used, partial, result);
    return result;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
