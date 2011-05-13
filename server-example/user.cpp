/* Implementation of User class
 *
 * For now, mostly a stub
 */
#include "user.h"

User::User(QString name){
	username = name;
}

const QString User::getName(){
	return username;
}

