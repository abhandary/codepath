public class Solution {
    
    
    // ---- Hashing -----
    // Colorful Number
    public int colorful(int a) {
        ArrayList<Integer> al = new ArrayList<>();
        while (a != 0) {
            al.add(a % 10);
            a /= 10;
        }
        HashSet<Integer> hset = new HashSet<>();
        for (int ix = 0; ix < al.size(); ix++) {
            int product = al.get(ix);
            if (hset.contains(product) == true) { return 0; }
            hset.add(product);
            for (int jx = ix + 1; jx < al.size(); jx++) {
                product *= al.get(jx);
                if (hset.contains(product) == true) { return 0; }
                hset.add(product);
            }
        }
        return 1;
    }
    
    // 2 Sum
    public ArrayList<Integer> twoSum(final List<Integer> a, int b) {
        ArrayList<Integer> result = new ArrayList<>();
        
        HashMap<Integer, Integer> hmap = new HashMap<Integer, Integer>();
        for (int ix = 0; ix < a.size(); ix++) {
            Integer val = hmap.get(b - a.get(ix));
            if (val != null) {
                result.add(val + 1);
                result.add(ix + 1);
                break;
            }
            if (hmap.get(a.get(ix)) == null) {
                hmap.put(a.get(ix), ix);
            }
        }
        
        return result;
    }
    
    // Valid SudokuBookmark Suggest Edit

    
        boolean isValid(ArrayList<ArrayList<Character>> matrix, int rowStart, int rowEnd, int colStart, int colEnd) {
            HashSet<Character> hset = new HashSet<>();
            
            for (int ix = rowStart; ix < rowEnd; ix++) {
                for (int jx = colStart; jx < colEnd; jx++) {
                    char c = matrix.get(ix).get(jx);
                    if (c == '.') { continue; }
                    if (hset.contains(c) == true) {
                        return false;
                    }
                    hset.add(c);
                }
            }
            return true;
        }
        
        public int isValidSudoku(final List<String> a) {
            ArrayList<ArrayList<Character>> matrix = new ArrayList<>();
            for (String s : a) {
                char[] chars = s.toCharArray();
                ArrayList<Character> cl = new ArrayList<>();
                for (char c : chars) {
                    cl.add(c);
                }
                matrix.add(cl);
            }
            
            // validate rows
            for (int ix = 0; ix < matrix.size(); ix++) {
                if (!isValid(matrix, ix, ix + 1, 0, matrix.size())) {
                    return 0;
                }
            }
            
            // validate columns
            for (int jx = 0; jx < matrix.size(); jx++) {
                if (!isValid(matrix, 0, matrix.size(), jx, jx + 1)) {
                    return 0;
                }
            }
            
            // validate quadrants
            for (int ix = 0; ix < 3; ix++) {
                for (int jx = 0; jx < 3; jx++) {
                    if (!isValid(matrix, ix*3, (ix + 1)*3, jx*3, (jx + 1)*3)) {
                        return 0;
                    }
                }
            }
            return 1;
        }

    // Anagrams
    public ArrayList<ArrayList<Integer>> anagrams(final List<String> a) {
        
        
        HashMap<String, ArrayList<Integer>> hmap = new HashMap<>();
        
        for (int ix = 0; ix < a.size(); ix++) {
            char[] chars = a.get(ix).toCharArray();
            Arrays.sort(chars);
            String sorted = new String(chars);
            if (hmap.get(sorted) == null) {
                ArrayList<Integer> al = new ArrayList<>();
                al.add(ix + 1);
                hmap.put(sorted, al);
            } else {
                hmap.get(sorted).add(ix + 1);
            }
        }
        ArrayList<ArrayList<Integer>> result = new ArrayList<>(hmap.values());
        return result;
    }
    
    
    // ---- Linked Lists
    
    // Palindrome List
    public int lPalin(ListNode A) {
        int len = 0;
        if (A == null) { return 0; }
        ListNode itr = A;
        while (itr != null) {
            len++; itr = itr.next;
        }
        if (len == 1) { return 1; }
        itr = A;
        for (int ix = 0; ix < Math.ceil(len / 2.0); ix++) {
            itr = itr.next;
        }
        ListNode prev = null;
        ListNode next = itr.next;
        while (itr != null) {
            itr.next = prev;
            prev = itr;
            itr = next;
            if (itr != null) { next = itr.next; }
        }
        ListNode rev = prev;
        itr = A;
        while (rev != null) {
            if (rev.val != itr.val) { return 0; }
            rev = rev.next;
            itr = itr.next;
        }
        return 1;
    }
    
    // Remove Duplicates from Sorted List
    public ListNode deleteDuplicates(ListNode a) {
        if (a == null) { return null; }
        ListNode itr = a;
        while (itr != null) {
            if (itr.next != null) {
                if (itr.next.val == itr.val) {
                    ListNode temp = itr.next;
                    itr.next = temp.next;
                    temp.next = null;
                } else {
                    itr = itr.next;
                }
            } else {
                itr = itr.next;
            }
        }
        return a;
    }
    
    // Partition List
    public ListNode partition(ListNode a, int b) {
        if (a == null) { return null; }
        ListNode l1Head = new ListNode(0);
        ListNode l2Head = new ListNode(0);
        ListNode l1itr = l1Head;
        ListNode l2itr = l2Head;
        
        while (a != null) {
            if (a.val < b) {
                l1itr.next = a;
                l1itr = a;
            } else {
                l2itr.next = a;
                l2itr = a;
            }
            a = a.next;
        }
        l2itr.next = null;
        l1itr.next = l2Head.next;
        return l1Head.next;
    }
    
    // Merge Two Sorted Lists
    public ListNode mergeTwoLists(ListNode a, ListNode b) {
        ListNode result = new ListNode(0);
        ListNode itr = result;
        while (a != null || b != null) {
            if (a != null && b != null) {
                if (a.val < b.val) {
                    itr.next = a; a = a.next;
                } else {
                    itr.next = b; b = b.next;
                }
            } else if (a != null) {
                itr.next = a; a = a.next;
            } else {
                itr.next = b; b = b.next;
            }
            itr = itr.next;
        }
        itr.next = null;
        return result.next;
    }
}
