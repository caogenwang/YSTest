/**
 * Hello
 */
import redis.clients.jedis.Jedis;
import redis.clients.jedis.Transaction;

import java.util.Set;
public class Redis {
    public static void main(String[] args) {
        Jedis jedis = new Jedis("0.0.0.0",7001);
        jedis.auth("123456");
        System.out.println("连接成功");
        //查看服务是否运行
        System.out.println("服务正在运行: "+jedis.ping());
        
        Transaction transaction = jedis.multi();
        transaction.set("k4", "v6");
        transaction.set("k5", "v6");

        // transaction.exec();
        transaction.discard();

        // jedis.set("k1", "v1");
        // jedis.set("k2", "v2");
        // jedis.set("k3", "v3");
        // Set<String> sets = jedis.keys("*");
        // System.out.println(sets);
        jedis.close();
    }
}