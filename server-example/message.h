#pragma once
#include <QtCore>
#include "defs.h"


class Message{

public:
	Message(int size);
	~Message();
	static Message *generateMessage(QString str);
	MessageType getType();
	QStringList body;

private:
	 MessageType type;
	 int size;
};
