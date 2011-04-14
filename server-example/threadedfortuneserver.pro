 HEADERS 	= fortuneserver.h \
                 fortunethread.h
 SOURCES 	= fortuneserver.cpp \
                 fortunethread.cpp \
                 main.cpp
 QT           += network

 # install
 target.path = $$[QT_INSTALL_EXAMPLES]/network/threadedfortuneserver
 sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS t
