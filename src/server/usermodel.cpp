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

// 查询
User UserModel::query(int id)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "select * from user where id = %d", id);

    // 执行sql语句
    MySQL mysql;
    if (mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            // 获取一行查询结果，row 相当于是字符串数组
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row != nullptr)
            {
                User user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setPwd(row[2]);
                user.setState(row[3]);
                // 释放res指针资源
                mysql_free_result(res);
                return user;
            }
        }
    }
    return User();
}

// 更新用户状态
bool UserModel::updateState(User &user)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "update user set state = '%s' where id = %d", user.getState().c_str(), user.getId());


    // 执行sql语句
    MySQL mysql;
    if (mysql.connect())
    {
        if (mysql.update(sql))
        {
            return true;
        }
    }
    return false;
}