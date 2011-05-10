#pragma once
#include <QtCore>


typedef enum MessageType_t 
{
	PING,
	NEW_FILE
} MessageType ;

class Message{

public:
	Message(int size);
	~Message();
	static Message *generateMessage(QString str);
	MessageType getType();

private:
	 MessageType type;
	 int size;


};
