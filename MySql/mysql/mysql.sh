Local_IP="$( /sbin/ifconfig -a|grep inet|grep -i 192.168|grep -v inet6|awk '{print $2}'|tr -d "addr:" )"
echo $Local_IP

Project=$0
Project="$( cd "$( dirname $Project  )" && pwd  )"
Project="$( cd "$( dirname $Project  )" && pwd  )"
Project="$( cd "$( dirname $Project  )" && pwd  )"
echo "Project=$Project"

AppDir=$0
AppDir="$( cd "$( dirname $AppDir  )" && pwd  )"
AppDir="$( cd "$( dirname $AppDir  )" && pwd  )"
AppDir="$( cd "$( dirname $AppDir  )" && pwd  )"
AppDir="$( cd "$( dirname $AppDir  )" && pwd  )"
AppDir="$( cd "$( dirname $AppDir  )" && pwd  )"
echo "AppDir=$AppDir"

Docker_name=dfs_mysql_master
PWD=$Project/config/conf/master

docker stop $Docker_name
docker rm $Docker_name
docker run -d \
--restart=always \
--ulimit core=0 \
-p 14454:3306 \
--name $Docker_name \
-v $PWD/conf:/etc/mysql/conf.d \
-v $PWD/logs:/logs \
-v $PWD/data:/var/lib/mysql \
-e MYSQL_ROOT_PASSWORD=123456 \
mysql:5.6 \
--character_set_server=utf8 \
--character_set_client=utf-8 \
--collation_server=utf8_general_ci 
