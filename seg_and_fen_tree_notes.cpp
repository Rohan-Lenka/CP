// 1) SEGMENT TREE FOR CP
/*
 *                         1
 *                       /    \
 *                     2        3
 *                   /   \    /    \
 *                 4      5  6      7
 *                / \   / \  / \    / \
 *               8   9 10 11 12 13 14 15

    1) The seg tree is stored as an array (always make it 1 indexed)
    2) Children of node i are -> 2i and 2i + 1
    3) Parent of node i is -> i / 2
    4) Neighbor of node i is -> i ^ 1  

 */