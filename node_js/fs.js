var fs = require("fs");

fs.readFile('./test.txt',function(err,data){//异步读取
    if(err)
    {
        console.error(err);
    }
    console.log("async:"+data.toString());
});

var data = fs.readFileSync('./test.txt');//同步读取
console.log("sync:"+data);
console.log("process finish!");