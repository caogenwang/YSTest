public class Solution{
    int[] vs = {0,2,4,3,7};
    int[] ws = {0,2,3,5,5};

    @Test
    public void testKnapsack1() {
        int result = ks(4,10);
        System.out.println(result);
    }

    private int ks(int i, int c){
        int result = 0;
        if (i == 0 || c == 0){
            // 初始条件
            result = 0;
        } else if(ws[i] > c){
            // 装不下该珠宝
            result = ks(i-1, c);
        } else {
            // 可以装下
            int tmp1 = ks(i-1, c);
            int tmp2 = ks(i-1, c-ws[i]) + vs[i];
            result = Math.max(tmp1, tmp2);
        }
        return result;
    }
}


public class KnapSack01{
     /**
     * 解决背包问题的递归函数
     *
     * @param w        物品的重量数组
     * @param v        物品的价值数组
     * @param index    当前待选择的物品索引
     * @param capacity 当前背包有效容量
     * @return 最大价值
     */

     private static int solveKs(int []w,int []v,int index,int capacity){
        if(index < 0 || capacity <= 0)
            return 0;
 
        //不放第index个物品所得价值
        int res = solveKS(w, v, index - 1, capacity);
        if (w[index] <= capacity){
            res = Math.max(res,v[index] + solveKs(w, v, index-1, capacity - w[index]));
        }
        return res;
     }

     public static int knapSack(int[] w, int[] v, int C) {
        int size = w.length;
        return solveKS(w, v, size - 1, C);
    }

    public static void main(String[] args){
        int[] w = {2,1,3,2};
        int[] v = {12,10,20,15};
        System.out.println(knapSack(w,v,5));
    }
}