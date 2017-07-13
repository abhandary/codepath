//
//  week1.cpp
//  InterviewBitPreWork
//
//  Created by Akshay Bhandary on 7/12/17.
//  Copyright © 2017 AkshayBhandary. All rights reserved.
//

#include "week1.hpp"

#include <vector>
#include <unordered_set>
#include <string>


using namespace std;

class Week1 {
    
    // --- Arrays ----
    // Spiral Order Matrix I
    vector<int> spiralOrder(const vector<vector<int> > &A);
    
    // Add One To Number
    vector<int> plusOne(vector<int> &A);
    
    // Find Duplicate in Array
    int repeatedNumber(const vector<int> &A);
    
    // Pascal Triangle RowsBookmark Suggest Edit
    vector<vector<int> > generate(int A);
    
    // Set Matrix Zeros
    void setZeroes(vector<vector<int> > &A);
    
    // --- Strings ----
    // Palindrome String
    int isPalindrome(string A);
    
    
    // Longest Common Prefix
    string longestCommonPrefix(vector<string> &A);
    
    // Count And Say
    string countAndSay(int A);

    // Length of Last Word
    int lengthOfLastWord(const string &A);
    
    // Reverse the String
    void reverseWords(string &A);
    
    // --- Two Pointers ---
    // 3 Sum
    int threeSumClosest(vector<int> &A, int B);

    // 3 Sum Zero
    vector<vector<int> > threeSum(vector<int> &A);
    
    // Remove Duplicates from Sorted Array
    int removeDuplicates(vector<int> &A);
    
    // Remove Duplicates from Sorted Array II
    int removeDuplicates2(vector<int> &A);
    
    // Remove Element from Array
    int removeElement(vector<int> &A, int B);
    
    // Sort by Color
    void sortColors(vector<int> &A);
    
    // Container With Most Water
    int maxArea(vector<int> &A);
    
};

#pragma mark - Arrays

vector<int> Week1::plusOne(vector<int> &A) {
    
    vector<int> result = A;
    if (A.size() == 0) { return result; }
    result[A.size() - 1] = result[A.size() - 1] + 1;
    int ix = 0;
    for (ix = result.size() - 1; result[ix] > 9 && ix > 0; ix--) {
        result[ix] = 0;
        result[ix - 1]++;
    }
    if (ix == 0 && result[0] > 9) {
        result[0] = 0;
        result.insert(result.begin(), 1);
    }
    while(result.size() > 0 && result.front() == 0) {
        result.erase(result.begin());
    }
    return result;
}

int Week1::repeatedNumber(const vector<int> &A) {
    
    unordered_set<int> set;
    for (int ix = 0; ix < A.size(); ix++) {
        
        if (set.count(A[ix]) > 0) {
            return A[ix];
        }
        set.emplace(A[ix]);
    }
    return -1;
}


vector<vector<int> > Week1::generate(int A) {
    vector<vector<int>> result;
    
    for (int ix = 1; ix <= A; ix++) {
        vector<int> row = vector<int>(ix, 1);
        if (ix >= 3) {
            for (int jx = 1; jx < row.size() - 1; jx++) {
                row[jx] = result[ix - 2][jx - 1] + result[ix - 2][jx];
            }
        }
        result.emplace_back(row);
    }
    return result;
}

void Week1::setZeroes(vector<vector<int> > &A) {
    
    if (A.size() == 0) { return; }
    
    vector<int> rows = vector<int>(A.size(), 0);
    vector<int> cols = vector<int>(A[0].size(), 0);
    
    for (int ix = 0; ix < A.size(); ix++) {
        for (int jx = 0; jx < A[0].size(); jx++) {
            if (A[ix][jx] == 0) {
                rows[ix] = 1;
                cols[jx] = 1;
            }
        }
    }
    
    
    for (int ix = 0; ix < A.size(); ix++) {
        for (int jx = 0; jx < A[0].size(); jx++) {
            if (rows[ix] == 1 || cols[jx] == 1) {
                A[ix][jx] = 0;
            }
        }
    }
}

vector<int> Week1::spiralOrder(const vector<vector<int> > &A) {
    vector<int> result;
    if (A.size() == 0) { return result; }
    int startRow = 0;
    int endRow = A.size() - 1;
    int startCol = 0;
    int endCol = A[0].size() - 1;
    
    while (startRow <= endRow && startCol <= endCol) {
        for (int jx = startCol; jx <= endCol; jx++) {
            result.emplace_back(A[startRow][jx]);
        }
        startRow++;
        if (startRow > endRow) { return result; }
        for (int ix = startRow; ix <= endRow; ix++) {
            result.emplace_back(A[ix][endCol]);
        }
        endCol--;
        if (startCol > endCol) { return result; }
        for (int jx = endCol; jx >= startCol; jx--) {
            result.emplace_back(A[endRow][jx]);
        }
        endRow--;
        if (startRow > endRow) { return result; }
        for (int ix = endRow; ix >= startRow; ix--) {
            result.emplace_back(A[ix][startCol]);
        }
        startCol++;
    }
    
    return result;
    
}

#pragma mark - Strings

int Week1::isPalindrome(string A) {
    int ix = 0;
    int jx = A.length() - 1;
    while (ix < jx) {
        if (!isalnum(A[ix])) { ix++; continue; }
        if (!isalnum(A[jx])) { jx--; continue; }
        if (tolower(A[ix]) != tolower(A[jx])) { return 0; }
        ix++; jx--;
    }
    return 1;
}

string Week1::longestCommonPrefix(vector<string> &A) {
    
    string prefix = "";
    int currentChar = 0;
    char testChar = ' ';
    bool done = false;
    
    while (true) {
        for (int sx = 0; sx < A.size(); sx++) {
            if (currentChar >= A[sx].length()) { return prefix; }
            if (sx == 0) {
                testChar = A[sx][currentChar];
            } else {
                if (testChar != A[sx][currentChar]) {
                    return prefix;
                }
            }
        }
        prefix += testChar;
        currentChar++;
    }
    return prefix;
}


string Week1::countAndSay(int A) {
    
    string result = "1";
    for (int ix =1; ix < A; ix++) {
        string inter = "";
        int count = 1;
        int jx = 1;
        for (jx = 1; jx < result.length(); jx++) {
            if (result[jx] == result[jx - 1]) {
                count++;
            } else {
                inter += to_string(count) + result[jx - 1];
                count = 1;
            }
        }
        inter += to_string(count) + result[jx - 1];
        result = inter;
    }
    return result;
}

int Week1::lengthOfLastWord(const string &A) {
    
    if (A.length() == 0) { return 0; }
    int ix = A.length() - 1;
    // skip trailing white spaces
    while (A[ix] == ' ') { ix--; }
    int last = ix;
    // get length of last word
    while (ix >= 0 && A[ix] != ' ') {
        ix--;
    }
    return last - ix;
}

void reverseString(string &A, int ix, int jx) {
    
    while (ix < jx) {
        char c = A[ix];
        A[ix] = A[jx];
        A[jx] = c;
        ix++; jx--;
    }
}

void Week1::reverseWords(string &A) {
    reverseString(A, 0, A.length() - 1);
    int first = 0;
    int last = 0;
    while ((last = A.find_first_of(" ", first)) != string::npos) {
        reverseString(A, first, last - 1);
        first = last + 1;
    }
    last = A.length() - 1;
    reverseString(A, first, last);
}



#pragma mark - Two Pointers

int Week1::threeSumClosest(vector<int> &A, int B) {
    int sum = INT_MAX;
    int minDiffSoFar = INT_MAX;
    sort(A.begin(), A.end());
    if (A.size() < 3) { return sum; }
    
    for (int ix = 0; ix < A.size() - 2; ix++) {
        int jx = ix + 1;
        int kx = A.size() - 1;
        while (jx < kx) {
            int localSum = A[ix] + A[jx] + A[kx];
            if (localSum == B) { return localSum; }
            else if (localSum > B) {
                if (localSum - B < minDiffSoFar) {
                    minDiffSoFar = localSum - B;
                    sum = localSum;
                }
                kx--;
            } else {
                if (B - localSum < minDiffSoFar) {
                    minDiffSoFar = B - localSum;
                    sum = localSum;
                }
                jx++;
            }
        }
    }
    return sum;
}

vector<vector<int> > Week1::threeSum(vector<int> &A) {
    
    vector<vector<int>> result;
    if (A.size() <= 2) { return result; }
    sort(A.begin(), A.end());
    for (int ix = 0; ix < A.size() - 2; ix++) {
        if (ix > 0 && A[ix] == A[ix - 1]) { continue; }
        int jx = ix + 1;
        int kx = A.size() - 1;
        while (jx < kx) {
            int sum = A[ix] + A[kx] + A[jx];
            if (sum == 0) {
                vector<int> inter = {A[ix], A[jx], A[kx]};
                result.emplace_back(inter);
                
                while (jx < kx && A[jx] == A[jx + 1]) { jx++; }
                while (jx < kx && A[kx] == A[kx - 1]) { kx--; }
                jx++;  kx--;
            } else if (sum > 0) {
                kx--;
            } else {
                jx++;
            }
        }
    }
    return result;
}

int Week1::removeDuplicates(vector<int> &A) {
    
    int wx = 1;
    int rx = 1;
    while (rx < A.size()) {
        if (A[rx] == A[rx - 1]) { rx++; continue; }
        A[wx++] = A[rx];
        rx++;
    }
    return wx;
}

int Week1::removeDuplicates2(vector<int> &A) {
    if (A.size() <= 2) { return A.size(); }
    int wx = 0;
    int rx = 0;
    while (rx < A.size()) {
        if (rx < A.size() - 2 && A[rx] == A[rx + 2]) { rx++; continue; }
        A[wx++] = A[rx];
        rx++;
    }
    return wx;
}

int Week1::removeElement(vector<int> &A, int B) {
    int wx = 0;
    for (int rx = 0; rx < A.size(); rx++) {
        if (A[rx] != B) {
            A[wx++] = A[rx];
        }
    }
    return wx;
}

void Week1::sortColors(vector<int> &A) {
    vector<int> count(3, 0);
    
    for (int ix = 0; ix < A.size(); ix++) {
        count[A[ix]]++;
    }
    int ix = 0;
    for (int cx = 0; cx < 3; cx++) {
        while (count[cx] > 0) {
            A[ix++] = cx;
            count[cx]--;
        }
    }
}


int Week1::maxArea(vector<int> &A) {
    int ix = 0;
    int jx = A.size() - 1;
    
    int maxArea = 0;
    while (ix < jx) {
        int h = min(A[ix], A[jx]);
        maxArea = max(maxArea, h * (jx - ix));
        
        while (A[ix] <= h) { ix++; }
        while (A[jx] <= h) { jx--; }
    }
    return maxArea;
}


