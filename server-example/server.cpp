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

#include "server.h"
#include "thread.h"
#include <sys/socket.h>
#include "signal.h"
#include <stdlib.h>
#include <QtDebug>
#include <QApplication>

//needed to not get an undefined reference to static members
int Server::sighupFd[2];
int Server::sigtermFd[2];
	Server::Server( FileStorageManager *manager, QObject *parent)
: QTcpServer(parent)
{
	fileManager = manager;
	if (::socketpair(AF_UNIX, SOCK_STREAM, 0, sighupFd))
		qFatal("Couldn't create HUP socketpair");

	if (::socketpair(AF_UNIX, SOCK_STREAM, 0, sigtermFd))
		qFatal("Couldn't create TERM socketpair");
	snHup = new QSocketNotifier(sighupFd[1], QSocketNotifier::Read, this);
	connect(snHup, SIGNAL(activated(int)), this, SLOT(handleSigHup()));
	snTerm = new QSocketNotifier(sigtermFd[1], QSocketNotifier::Read, this);
	connect(snTerm, SIGNAL(activated(int)), this, SLOT(handleSigTerm()));
}


void Server::incomingConnection(int socketDescriptor)
{
	Thread *thread = new Thread(socketDescriptor, fileManager,this);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();
}

void Server::hupSignalHandler(int)
{
	char a = 1;
	::write(sighupFd[0], &a, sizeof(a));
}

void Server::termSignalHandler(int)
{
	char a = 1;
	::write(sigtermFd[0], &a, sizeof(a));
}


void Server::handleSigTerm()
{
	snTerm->setEnabled(false);
	char tmp;
	::read(sigtermFd[1], &tmp, sizeof(tmp));

	// do Qt stuff
	qDebug() << "Got SIGTERM, exiting";
	close();
	QApplication::exit();
	snTerm->setEnabled(true);
}

void Server::handleSigHup()
{
	snHup->setEnabled(false);
	char tmp;
	::read(sighupFd[1], &tmp, sizeof(tmp));

	// do Qt stuff
	qDebug() << "Got SIGHUP,exiting";
	close();
	QApplication::exit();
	snHup->setEnabled(true);
}

Server::~Server(){
	delete fileManager;
	delete snHup;
	delete snTerm;
}
