
#主库的配置
docker exec -it mysql /bin/bash
mysql -u root -p
grant all privileges on *.* to root@"%" identified by "new password";#设置用户 root 可以在本地被访问：
GRANT REPLICATION SLAVE ON *.* TO 'slave'@'%' IDENTIFIED BY 'slave';#设置主从开始的账号
flush privileges;#刷新权限使得刷新

#slave:
change master to master_host='172.17.0.2', master_user='slave', master_password='123456', master_port=3306,master_log_file='log.000886', master_log_pos= 208, master_connect_retry=30;

start slave

2.从数据库只能读，不能操作表
    

#查看mysql的用户

change master to master_host='172.17.0.2', master_user='slave', master_password='123456', master_port=3306, master_log_file='mysql-bin.000001', master_log_pos= 2830, master_connect_retry=30;