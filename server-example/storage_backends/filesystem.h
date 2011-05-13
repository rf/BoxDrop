/* filesystem backend for file storage
 * The simplest way of storing Users files: just dump them in a directory
 */

#pragma once
#include "defs.h"
#include "filestorage.h"

class FileSystemBackend : public FileStorageManager
{
	public: 
		FileSystemBackend();
		virtual ~FileSystemBackend(){};
		bool addFile(User user, QString filename, QString contents);
		bool deleteFile(User user, QString filename); 
		bool modifyFile(User user, QString filename, QString patch, PatchType patchType);
		QHash<QString,QString> getFiles(User user); 

	private:
		QString getUserTopDirectory(User user);
};
