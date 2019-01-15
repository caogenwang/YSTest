var mysql = require("mysql");
var  connection = mysql.createConnection({
host:'localhost',
user:'root',
password:'123456',
database:'test'
});
connection.connect();

connection.query('SELECT 1 + 1 AS solution', function (error, results, fields) {
    if (error) throw error;
    console.log('The solution is: ', results[0].solution);
  });
var addSql = "INSERT INTO websites(Id,name,url,alexa,country) VALUES(0,?,?,?,?)";
var addSqlParams = ['菜鸟工具','http://c.runoob.com','23453','CN'];
connection.query(addSql,addSqlParams,function(err,result){
    if(err)
    {
        
    }
});