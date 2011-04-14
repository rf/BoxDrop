 HEADERS 	= server.h \
                 thread.h 
 SOURCES 	= server.cpp \
                 thread.cpp \
                 main.cpp
 QT           += network

 # install
 target.path = $$[QT_INSTALL_EXAMPLES]/network/threadedserver
 sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS t
