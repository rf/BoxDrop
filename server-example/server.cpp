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

 #include <stdlib.h>
#include <QtDebug>
 FortuneServer::FortuneServer(QObject *parent)
     : QTcpServer(parent)
 {
     fortunes << tr("You've been leading a dog's life. Stay off the furniture.")
              << tr("You've got to think about tomorrow.")
              << tr("You will be surprised by a loud noise.")
              << tr("You will feel hungry again in another hour.")
              << tr("You might have mail.")
              << tr("You cannot kill time without injuring eternity.")
              << tr("Computers are not intelligent. They only think they are.");
 }

 void FortuneServer::incomingConnection(int socketDescriptor)
 {
     QString fortune = fortunes.at(qrand() % fortunes.size());
     FortuneThread *thread = new FortuneThread(socketDescriptor, fortune, this);
     connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
     thread->start();
 }
