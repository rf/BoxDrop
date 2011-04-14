 HEADERS 	= fortuneserver.h \
                 fortunethread.h \
		 dialog.h
 SOURCES 	= fortuneserver.cpp \
                 fortunethread.cpp \
		 dialog.cpp \
                 main.cpp
 QT           += network

 # install
 target.path = $$[QT_INSTALL_EXAMPLES]/network/threadedfortuneserver
 sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS t
