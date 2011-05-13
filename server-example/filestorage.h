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

	/* add a new file for this user, with name filename and contents contents
	 * filename can be a patch relative to the users main folder
	 *
	 * return true on success, false on failure
	 */
	virtual bool addFile(User user, QString filename, QString contents) =0;

	/* Delete a user's file with name filename. 
	 * filename can be a path relative to the users main folder
	 *
	 * return true on success, false on failure
	 *
	 * TODO: should this save some kind of backup info?
	 */
	virtual bool deleteFile(User user, QString filename) =0;

	/* modify a user's file with name filename, using the given patch and patching algo
	 * filename can be a patch relative to users main folder
	 *
	 * returns true on sucess, false on failure
	 */
	virtual bool modifyFile(User user, QString filename, QString patch, PatchType patchType) =0;

	/* returns a dictionary of this user's files, 
	 * with filenames as keys and md5sums as values
	 */
	virtual QHash<QString,QString> getFiles(User user) =0;

 protected:
 private:

 };

