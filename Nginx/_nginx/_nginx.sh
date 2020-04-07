CurrentDir=$0
CurrentDir="$( cd "$( dirname $CurrentDir  )" && pwd  )"
cd $CurrentDir

nohup sh $CurrentDir/_nginx_loop.sh &

mkdir -p /System/logs

nginx -c $CurrentDir/conf/nginx.conf

tail -f /System/logs/access.log