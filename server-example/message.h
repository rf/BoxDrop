#pragma once
#include <QtCore>


typedef enum MessageType_t 
{
	PING
} MessageType ;

class Message{

public:
	Message();
	~Message();
	static Message *generateMessage(QString str);
	MessageType getType();
private:
	 MessageType type;


};
