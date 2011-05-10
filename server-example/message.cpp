#include "message.h"
#include <QtCore>

Message::Message(int size){
	this->size = size;	
}

Message::~Message(){
}

Message *Message::generateMessage(QString str){
	QStringList lines = str.split("\n");	
	Message *msg = NULL;
	QString type = lines.at(0);
	msg = new Message(str.size());

	bool goodType = false;

	if (type ==  "PING"){
		msg->type = PING;
		goodType = true;
	}else if (type == "NEW_FILE"){
		msg->type = NEW_FILE;
		goodType=true;
	}

	if(goodType){
		return msg;
	}else{
		delete msg;
		return NULL;
	}
}

MessageType Message::getType(){
	return type;
}
