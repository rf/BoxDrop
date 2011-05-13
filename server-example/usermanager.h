/*
 * User class
 */ 

#pragma once
#include <QString>
#include "user.h"
 class UserManager
 {

 public:
	UserManager();
	static 	User loginUser(QString username, QString password);
 protected:
 private:

 };

