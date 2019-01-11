var fs = require("fs");
var data = '';

// 创建可读流
var readerStream = fs.createReadStream('test.txt');
console.log("step 1 " + readerStream);

// 设置编码为 utf8。
readerStream.setEncoding('UTF8');
console.log("step 2 " + readerStream);

// 处理流事件 --> data, end, and error
readerStream.on('data', function(chunk) {
   data += chunk;
});
console.log("step 3 " + readerStream);

readerStream.on('end',function(){
   console.log(data);
});
console.log("step 4 " + readerStream);

readerStream.on('error', function(err){
   console.log(err.stack);
});
console.log("step 5 " + readerStream);

console.log("程序执行完毕");