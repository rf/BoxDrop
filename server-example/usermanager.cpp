/* Implementation of User manager class
 * 
 * Mostly a stub for now, this is what actually lets users log in
 */
#include "usermanager.h"

UserManager::UserManager(){

}

/*returns the user identified by this username and password
 * returns NULL if no user with that combo exists
 *
 * For now, just a stub
 * TODO: implement this with priv/pub keys?
 */

User *UserManager::loginUser(QString username, QString password){

	User *usr = new User("jarek");
	return usr;
}
