//
//  week1_post.cpp
//  InterviewBitPreWork
//
//  Created by Akshay Bhandary on 7/20/17.
//  Copyright © 2017 AkshayBhandary. All rights reserved.
//

#include "week1_post.hpp"

#include <vector>
#include <unordered_set>
#include <string>
#include <unordered_map>

using namespace std;

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};



class Week1Post {
    
    // -- Arrays ---
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval);
    
    vector<Interval> merge(vector<Interval> &A);

    vector<vector<int> > generateMatrix(int A);
    
    int firstMissingPositive(vector<int> &A);
    
    // --- Strings ----
    int romanToInt(string A);
};

vector<Interval> Week1Post::insert(vector<Interval> &intervals, Interval newInterval) {
    Interval intervalToMerge = newInterval;
    
    vector<Interval> result;
    int ix = 0;
    while (ix < intervals.size() && intervals[ix].end < intervalToMerge.start) {
        result.emplace_back(intervals[ix++]);
    }
    while (ix < intervals.size() && intervals[ix].start <= intervalToMerge.end) {
        intervalToMerge.start = min(intervalToMerge.start, intervals[ix].start);
        intervalToMerge.end   = max(intervalToMerge.end, intervals[ix].end);
        ix++;
    }
    result.emplace_back(intervalToMerge);
    while (ix < intervals.size()) {
        result.emplace_back(intervals[ix++]);
    }
    return result;
}


bool sortFunction (Interval i,Interval j) { return (i.start<j.start); }
vector<Interval> Week1Post::merge(vector<Interval> &A) {
    vector<Interval> result;
    if (A.size() == 0) { return result; }
    
    sort(A.begin(), A.end(), sortFunction);
    
    int start = A[0].start;
    int end   = A[0].end;
    
    
    for (int ix = 1; ix < A.size(); ix++) {
        if (A[ix].start <= end) {
            end   = max(end, A[ix].end);
        } else {
            result.emplace_back(Interval(start, end));
            start = A[ix].start;
            end = A[ix].end;
        }
    }
    result.emplace_back(Interval(start, end));
    return result;
}

vector<vector<int> > Week1Post::generateMatrix(int A) {
    
    vector<vector<int>> matrix = vector<vector<int>>(A, vector<int>(A, 0));
    
    int colStart = 0, colEnd = A - 1;
    int rowStart = 0, rowEnd = A - 1;
    
    int n = 1;
    while (colStart <= colEnd && rowStart <= rowEnd) {
        for (int jx = colStart; jx <= colEnd; jx++) {
            matrix[rowStart][jx] = n++;
        }
        rowStart++;
        if (rowStart > rowEnd) { break; }
        for (int ix = rowStart; ix <= rowEnd; ix++) {
            matrix[ix][colEnd] = n++;
        }
        colEnd--;
        if (colStart > colEnd) { break; }
        for (int jx = colEnd; jx >= colStart; jx--) {
            matrix[rowEnd][jx] = n++;
        }
        rowEnd--;
        if (rowStart > rowEnd) { break; }
        for (int ix = rowEnd; ix >= rowStart; ix--) {
            matrix[ix][colStart] = n++;
        }
        colStart++;
    }
    return matrix;
}


int Week1Post::firstMissingPositive(vector<int> &A) {
    for (int ix = 0; ix < A.size(); ix++) {
        while (A[ix] >= 1 && A[ix] <= A.size() && A[ix] != A[A[ix] - 1]) {
            swap(A[ix], A[A[ix] - 1]);
        }
    }
    for (int ix = 0; ix < A.size(); ix++) {
        if (A[ix] != ix + 1) {
            return ix + 1;
        }
    }
    return A.size() + 1;
}

int Week1Post::romanToInt(string A) {
    unordered_map<char, int> hmap;
    hmap['M'] = 1000;
    hmap['D'] = 500;
    hmap['C'] = 100;
    hmap['L'] = 50;
    hmap['X'] = 10;
    hmap['V'] = 5;
    hmap['I'] = 1;
    
    int sum = 0;
    if (A.length() == 0) { return sum; }
    int ix = A.length() - 1;
    int maxSeen = hmap[A[ix--]];
    sum = maxSeen;
    while (ix >= 0)  {
        int val = hmap[A[ix]];
        if (val >= maxSeen) {
            sum += val;
            maxSeen = val;
        } else {
            sum -= val;
        }
        ix--;
    }
    return sum;
}
