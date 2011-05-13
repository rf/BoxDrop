/*
 * File Storage Interface
 * This is a pure abstract class, defining the minimal interface for storing/retreiving files
 *
 */ 
#include "defs.h"
#pragma once
 class FileStorageManager
 {

 public:
	virtual ~FileStorageManager() =0;
	virtual bool addFile(QString filename, QString contents) =0;
	virtual bool deleteFile(QString filename) =0;
	virtual bool modifyFile(QString filename, QString patch, PatchType patchType) =0;
 protected:
 private:

 };

