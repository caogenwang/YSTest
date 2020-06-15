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

Docker_name=backup
PWD=$Project/config/conf/xtrabackup

docker stop $Docker_name
docker rm $Docker_name

# docker volume create 
# --driver=convoy 


docker run -d \
--restart=always \
--ulimit core=0 \
--name=$Docker_name \
-v /$PWD/target: /backup \
--link DB_SERVER_CONTAINER:192.168.2.191 \
-e MYSQL_PORT=14444 \
-e MYSQL_USER=root \
-e MYSQL_PASSWORD='123456' \
ipunktbs/xtrabackup \