 HEADERS 	= server.h \
                 thread.h \
		 message.h \
		 user.h \
		 usermanager.h \
		 defs.h \
		 filestorage.h \
		 storage_backends/filesystem.h

 SOURCES 	= server.cpp \
                 thread.cpp \
                 main.cpp \
		 message.cpp \
		 user.cpp \
		 usermanager.cpp \
		 storage_backends/filesystem.cpp 

 QT           += network

 # install
 target.path = $$[QT_INSTALL_EXAMPLES]/network/threadedserver
 sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS t
