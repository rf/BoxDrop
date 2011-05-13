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

/* Server class
 * This is the server that listens for new connection
 * When it gets one, it spawns a new thread to deal with it
 * It also connects unix signals to qt signals through socketpairs and QSocketListeners
 * So it can react to unix signals. This is used so it can exit cleanly when given a signal
 *
 */

#ifndef SERVER_H
#define SERVER_H

#include <QStringList>
#include <QTcpServer>
#include <QSocketNotifier>
#include "filestorage.h"
#include <signal.h>

class Server : public QTcpServer
{
	Q_OBJECT

	public:
		Server( FileStorageManager *manager, QObject *parent = 0);
		virtual ~Server();
		// Unix signal handlers.
		static void hupSignalHandler(int unused);
		static void termSignalHandler(int unused);

	public slots:
		// Qt signal handlers.
		void handleSigHup();
		void handleSigTerm();

	protected:
		//called on new connection, spawns a thread to deal with it
		void incomingConnection(int socketDescriptor);

	private:
		//what backend will threads use?
		FileStorageManager *fileManager;

		//used for unix signals
		static int sighupFd[2];
		static int sigtermFd[2];
		//listens for signals
		QSocketNotifier *snHup;
		QSocketNotifier *snTerm;
};

//sets up the signal listeners
static int setup_unix_signal_handlers()
{
	struct sigaction hup, term;

	hup.sa_handler = Server::hupSignalHandler;
	sigemptyset(&hup.sa_mask);
	hup.sa_flags = 0;
	hup.sa_flags |= SA_RESTART;

	if (sigaction(SIGHUP, &hup, 0) > 0){
		return 1;
	}

	term.sa_handler = Server::termSignalHandler;
	sigemptyset(&term.sa_mask);
	term.sa_flags |= SA_RESTART;

	if (sigaction(SIGTERM, &term, 0) > 0){
		return 2;
	}

	return 0;
}
#endif
