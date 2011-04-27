 HEADERS 	= server.h \
                 thread.h \
		  message.h
 SOURCES 	= server.cpp \
                 thread.cpp \
                 main.cpp \
		 message.cpp
 QT           += network

 # install
 target.path = $$[QT_INSTALL_EXAMPLES]/network/threadedserver
 sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS t
