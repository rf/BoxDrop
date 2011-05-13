#include "usermanager.h"

UserManager::UserManager(){

}

User *UserManager::loginUser(QString username, QString password){

	User *usr = new User("jarek");
	return usr;
}
