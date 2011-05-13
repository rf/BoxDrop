/* Implementation of Message class
 * This is what the client sends to the Server
 * Eventually, this may be used to send data to client?
 *
 *
 */
#include "message.h"
#include <QtCore>

Message::Message(int size){
	this->size = size;	
}

Message::~Message(){
}

/* Parse raw text into a Message instance
 *
 * Returns pointer to Message if successfull,
 * Returns NULL on error
 */
Message *Message::generateMessage(QString str){
	//split the text into lines, the first line is the message type
	QStringList lines = str.split("\n");	
	QString type = lines.at(0);
	
	//create a new Message
	Message *msg = new Message(str.size());

	//did we succesfully parse the text?
	bool goodType = false;

	//figure out message type
	if (type ==  "PING"){
		msg->type = PING;
		goodType = true;
	}else if (type == "NEW_FILE"){
		msg->type = NEW_FILE;
		goodType=true;
	}

	//if we found a good type, add the body
	if(goodType){
		for(int i =1; i < lines.size(); i++){
			msg->body += lines.at(i);
		}
		return msg;
	//otherwise free memory and return NULL
	}else{
		delete msg;
		return NULL;
	}
}

MessageType Message::getType(){
	return type;
}
