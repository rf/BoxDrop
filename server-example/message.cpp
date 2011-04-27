#include "message.h"
#include <QtCore>

Message::Message(){
	

}

Message::~Message(){
}

Message *Message::generateMessage(QString str){
	QStringList lines = str.split("\n");	
	Message *msg = NULL;
	QString type = lines.at(0);
	if (type ==  "PING"){
		msg = new Message();
		msg->type = PING;
	}
	return msg;
}

MessageType Message::getType(){
	return type;
}
