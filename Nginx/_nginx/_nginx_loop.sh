while true 
    do
    curl -X POST "http://192.168.4.39:15600/api/services" -H "accept: application/json" -H "content-type: application/json" -d "{ \"url\": \"http://192.168.4.39:17300\", \"type\": \"docxinshi_nginx\", \"name\": \"dev_docxinshi\", \"desp\": \"docxinshi_nginx 服务\"}" 
    sleep 30s
done