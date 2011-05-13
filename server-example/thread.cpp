/****************************************************************************
 **
 ** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
 ** All rights reserved.
 ** Contact: Nokia Corporation (qt-info@nokia.com)
 **
 ** This file is part of the examples of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:BSD$
 ** You may use this file under the terms of the BSD license as follows:
 **
 ** "Redistribution and use in source and binary forms, with or without
 ** modification, are permitted provided that the following conditions are
 ** met:
 **   * Redistrllowing disclaimer in
 **     the documentation and/or other materials provided with the
 **     distribution.
 **   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
 **     the names of its contributors may be used to endorse or promote
 **     products derived from this software without specific prior written
 **     permission.
 **
 ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 ** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 ** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 ** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 ** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 ** SPECIAL, EXEMPLARY, OR CONSER TORT
 ** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 ** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

#include "thread.h"
#include "message.h"
#include "usermanager.h"
#include "user.h"

#include <QtNetwork>

	Thread::Thread(int socketDescriptor, FileStorageManager *manager, QObject *parent)
: QThread(parent), socketDescriptor(socketDescriptor)
{
	fileManager = manager;
	user = UserManager::loginUser("username","password");
}

void Thread::run()
{

	tcpSocket = new QTcpSocket;
	if (!tcpSocket->setSocketDescriptor(socketDescriptor)) {
		emit error(tcpSocket->error());
		return;
	}
	QString clientAddress = tcpSocket->peerAddress().toString();
	qDebug() << "New connection from " << clientAddress;

	//wait for first line
	if(!tcpSocket->waitForReadyRead(5000)){
		qDebug() << clientAddress << " timed out before sending LENGTH";
		tcpSocket->disconnectFromHost();
		return;
	}
	//first line should be message length, see SPEC
	bool* convertedOK = new bool; 
	QString firstLine = tcpSocket->readLine().trimmed();
	int numBytes = QString(firstLine).toInt(convertedOK);
	if(! *convertedOK){
		qDebug() << clientAddress << " send a bad length: " << firstLine;
		tcpSocket->disconnectFromHost();
		delete convertedOK;
		return;
	}
	delete convertedOK;

	//now, we read the full message. We know how long it is, so we keep
	// reading until we've read that many bytes
	QByteArray packet;
	while( ( packet.size() < numBytes) && tcpSocket->waitForReadyRead(TIMEOUT_MILLISECONDS)) {
		// at most, we read in the number of bytes difference between our packet so far and what we expect
		// and a +1 for the null byte at the end
		QByteArray input = tcpSocket->readLine(numBytes - packet.size() + 1);
		packet += input;
	}

	//we now have the whole packet...
	qDebug() << "The packet was:" << packet;
	Message *msg = Message::generateMessage(packet);
	if(!msg){
		qDebug() << "Invalid packet format";	
	}else if (msg->getType() == PING){
		processPing();
	}else if (msg->getType() == NEW_FILE){
		processNewFile(msg);
	}else{
		qDebug() << "Message has unrecognized type" << msg->getType() << "but was created successfully";
	}
	delete msg;
	tcpSocket->disconnectFromHost();
	if(tcpSocket->state() != QAbstractSocket::UnconnectedState){
		tcpSocket->waitForDisconnected();
	}
	qDebug() << clientAddress << " disconnected";

}

void Thread::processPing(){
	qDebug() << "Packet was a ping";
}

void Thread::processNewFile(Message *msg){
	//first line is the filename
	QString filename = msg->body.at(0);
	qDebug() << "Packet was a new file addition, adding file"<<filename;	
	QString contents = "";
	for(int i =1; i < msg->body.size(); i++){
		contents +=  msg->body.at(i) + "\n";
	}
	fileManager->addFile(*user,filename,contents);

}

Thread::~Thread(){
	delete user;
	delete tcpSocket;
	//tcpSocket->deleteLater();

}
