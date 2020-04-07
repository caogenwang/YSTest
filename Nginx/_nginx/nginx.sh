CurrentDir=$0
CurrentDir="$( cd "$( dirname $CurrentDir  )" && pwd  )"
echo "CurrentDir=$CurrentDir"

Local_IP="$( /sbin/ifconfig -a|grep inet|grep -i 192.168|grep -v inet6|awk '{print $2}'|tr -d "addr:" )"
echo "Local_IP=$Local_IP"

Applications=$0
Applications="$( cd "$( dirname $Applications  )" && pwd  )"
Applications="$( cd "$( dirname $Applications  )" && pwd  )"
Applications="$( cd "$( dirname $Applications  )" && pwd  )"
Applications="$( cd "$( dirname $Applications  )" && pwd  )"
echo "AppDir=$Applications"

Docker_name="nginx"
Jenkins="$HOME/nginx"

mkdir -p $Jenkins/logs/
mkdir -p $Jenkins/conf/


docker stop $Docker_name
docker rm $Docker_name
docker run -d \
--name $Docker_name \
--restart=always \
--ulimit core=0 \
--log-driver none \
-p 1080:80 \
-v $Jenkins/conf/:/etc/nginx/ \
-v $Jenkins/logs:/var/log/nginx \
-v $Jenkins/book:/usr/share/nginx/book/ \
--env Local_IP=$Local_IP \
--env ENV_FILE=$ENV_FILE \
nginx:latest \