#pragma once

#include "user.h"

// user表的数据操作类
class UserModel
{
public:
    // 添加
    bool insert(User &user);
};