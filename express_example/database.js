const mysql = require('mysql2');
const dotenv = require('dotenv');

dotenv.config();

const myConnectionString = "mysql://netuser:netpass@127.0.0.1:3306/netdb";
const connection = mysql.createPool(process.env.SQL_SERVER);

module.exports = connection;

connection.query('SHOW TABLES', function(err, result, fields){
    if (err) {
      console.error('Database connection error:', err);
    } else {
      console.log('Database connection successful', result);
    }
});