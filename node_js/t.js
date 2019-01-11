var http = require("http");
http.createServer(function(request,response){
    //响应头部
    response.writeHead(200,{'Content-Type':'text/plain'});
    //响应正文数据
    response.end("hello world!");
}).listen(8080);
 
console.log('Server is running at https://localhost:8080/');