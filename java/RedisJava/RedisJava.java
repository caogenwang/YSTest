package RedisJava;
import redis.clients.jedis.Jedis;
public class RedisJava {
    public void RedisConnect()
    {
        Jedis jedis = new Jedis("0.0.0.0",7001);
        jedis.auth("123456");
        System.out.println("连接成功");
        //查看服务是否运行
        System.out.println("服务正在运行: "+jedis.ping());
    }
}