/* Message class
 * This is the message format for message sent from the client to the server
 */
#pragma once
#include <QtCore>
#include "defs.h"


class Message{

public:
	Message(int size);
	~Message();
	//parse a string into a message, returns NULL on failure
	static Message *generateMessage(QString str);
	//gets the message type
	MessageType getType();
	//the body of the message
	QStringList body;

private:
	 MessageType type;
	 //how many bytes is this message?
	 int size;
};
