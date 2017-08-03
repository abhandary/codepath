
class MatrixElement implements Comparable<MatrixElement>{

    public int val;
    public int row;
    public int col;

    public MatrixElement(int val, int row, int col){
		this.val = val;
		this.row = row;
		this.col = col;
	}
	@Override
	public int compareTo(MatrixElement o) {
		return Integer.compare(this.val, o.val);
	}
}

public class Solution {
  // ---- Trees -----
  // Inorder Traversal
	public ArrayList<Integer> inorderTraversal(TreeNode a) {
	    Deque<TreeNode> stack = new ArrayDeque<>();
	    ArrayList<Integer> result = new ArrayList<>();

	    if (a == null) { return result; }
        TreeNode current = a;

	    while (stack.size() > 0 || current != null) {

	        while (current != null) {
	            stack.push(current);
	            current = current.left;
	        }

	        if (stack.size() > 0) {
	            current = stack.pop();
	            result.add(current.val);
                current = current.right;
	        }
	    }
	    return result;
	}

  // Preorder Traversal
  public ArrayList<Integer> preorderTraversal(TreeNode a) {
	    ArrayList<Integer> result = new ArrayList<>();

	    if (a == null) { return result; }

	    Deque<TreeNode> stack = new ArrayDeque<>();

	    stack.push(a);
	    while (stack.size() > 0) {
	        TreeNode current = stack.pop();
	        result.add(current.val);

	        if (current.right != null) {
	            stack.push(current.right);
	        }
	        if (current.left != null) {
	            stack.push(current.left);
	        }
	    }
	    return result;
	}

  // Invert the Binary Tree
  public TreeNode invertTree(TreeNode root) {
        if (root == null) { return root; }

        TreeNode temp = root.left;
        root.left = root.right;
        root.right = temp;
        invertTree(root.left);
        invertTree(root.right);

        return root;
  }

  // Populate Next Right Pointers
  public void connect(TreeLinkNode root) {

        TreeLinkNode leftWall = null;
        TreeLinkNode prev = null;

        while (root != null) {
            TreeLinkNode current = root;
            while (current != null) {
                if (current.left != null) {
                    if (prev != null) {
                        prev.next = current.left;
                    } else {
                        leftWall = current.left;
                    }
                    prev = current.left;
                }
                if (current.right != null) {
                    if (prev != null) {
                        prev.next = current.right;
                    } else {
                        leftWall = current.right;
                    }
                    prev = current.right;
                }
                current = current.next;
            }
            root = leftWall;
            prev = null;
            leftWall = null;
        }
    }

    // Max Depth of Binary Tree
    public int maxDepth(TreeNode a) {
        if (a == null) {
            return 0;
        }
        return 1 + Math.max(maxDepth(a.left), maxDepth(a.right));
	  }

    // Sum Root to Leaf Numbers
    int sumNumbersHelper(TreeNode a, int numSoFar) {
        if (a == null) { return 0; }
        numSoFar *= 10;
        numSoFar  = (numSoFar + a.val) % 1003;
        if (a.left == null && a.right == null) {
            return numSoFar;
        }

        return (sumNumbersHelper(a.left, numSoFar) + sumNumbersHelper(a.right, numSoFar)) % 1003;
    }

    public int sumNumbers(TreeNode a) {
	     int sum = sumNumbersHelper(a, 0);
	      return sum % 1003;
	  }


    // --- Binary Search
    // Matrix Median
    public int findMedian(ArrayList<ArrayList<Integer>> A) {
       if (A.size() == 0) { return -1; }
       int n = A.size();
       int m = A.get(0).size();

       int k = 1 + n * m / 2;

       PriorityQueue<MatrixElement> pq = new PriorityQueue<>();

       for (int ix = 0; ix < n; ix++) {
           pq.offer(new MatrixElement(A.get(ix).get(0), ix, 0));
       }

       int count = 0;
       MatrixElement me = null;
       while (pq.size() > 0 && count < k) {
           count++;
           me = pq.poll();
           if (me.col + 1 < m) {
               pq.offer(new MatrixElement(A.get(me.row).get(me.col + 1), me.row, me.col + 1));
           }
       }
       return me.val;
   }

   //  Rotated Sorted Array Search
   public int search(final List<Integer> a, int b) {
	    int left = 0;
	    int right = a.size() - 1;


	    while (left <= right) {
	        int mid = right - ((right - left) / 2);
	        if (a.get(mid) == b) { return mid; }
	        if (a.get(left) <= a.get(mid)) {
	            if (b >= a.get(left) && b < a.get(mid)) {
	                right = mid - 1;
	            } else {
	                left = mid + 1;
	            }
	        } else {
	            if (b <= a.get(right) && b > a.get(mid)) {
	                left = mid + 1;
	            } else {
	                right = mid - 1;
	            }
	        }
	    }
	    return -1;
	}

  // Heaps and Maps
  public ListNode mergeKLists(ArrayList<ListNode> a) {

	    PriorityQueue<ListNode> pq = new PriorityQueue<>(a.size(), new Comparator<ListNode>() {
			@Override
			public int compare(ListNode x, ListNode y) {
                if (x.val < y.val)
                {
                    return -1;
                }
                if (x.val > y.val)
                {
                    return 1;
                }
                return 0;

			}
		});

	    for (int ix = 0; ix < a.size(); ix++) {
	        ListNode current = a.get(ix);
	        if (current != null) {
	            pq.offer(current);
	        }
	    }

	    ListNode dummyHead = new ListNode(0);
	    ListNode currentItr = dummyHead;

	    while (pq.size() > 0) {
	        ListNode nextSmallest = pq.poll();
	        currentItr.next = nextSmallest;
	        currentItr = nextSmallest;
	        nextSmallest = nextSmallest.next;
	        if (nextSmallest != null) {
	            pq.offer(nextSmallest);
	        }
	    }
	    return dummyHead.next;
	}
}
