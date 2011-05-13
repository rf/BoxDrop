/*
 * User class
 */ 

#pragma once
#include <QString>
 class User
 {


 public:
   User(QString name);
   const QString getName();

 protected:
 private:
	QString username;	
 };

