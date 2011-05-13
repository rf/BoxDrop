/*
 * File Storage Interface
 * This is a pure abstract class, defining the minimal interface for storing/retreiving files
 *
 */ 
#include "defs.h"
#include "user.h"
#include <QString>
#include <QHash>
#pragma once

 class FileStorageManager
 {

 public:
	inline virtual ~FileStorageManager() {};
	virtual bool addFile(User user, QString filename, QString contents) =0;
	virtual bool deleteFile(User user, QString filename) =0;
	virtual bool modifyFile(User user, QString filename, QString patch, PatchType patchType) =0;
	virtual QHash<QString,QString> getFiles(User user) =0;

 protected:
 private:

 };

