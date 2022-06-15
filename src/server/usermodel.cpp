#include "usermodel.h"
#include "db.h"

// 添加
bool UserModel::insert(User &user)
{
    // 因为主键是自动生成的，所以user中先不给id，当user添加到数据库中会自动生成id，然后我们再为user设置这个id
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into user(name, password, state) values('%s', '%s', '%s')",
            user.getName().c_str(), user.getPwd().c_str(), user.getState().c_str());
    // 执行sql语句
    MySQL mysql;
    if (mysql.connect())
    {
        if (mysql.update(sql))
        {
            // 添加成功，为user设置id
            user.setId(mysql_insert_id(mysql.getConnection()));
            return true;
        }
    }
    return false;
}