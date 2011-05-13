#include "filesystem.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>

FileSystemBackend::FileSystemBackend(){

}

bool FileSystemBackend::addFile(User user, QString filename, QString contents){
	QString path = getUserTopDirectory(user);
	if (! QDir(path).exists()){
		QDir().mkdir(path);
		qDebug() << "Creating directory" << path;
	}
	QString fullName = path + "/" + filename;
	QFile file(fullName);
	if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
		QTextStream out(&file);
		out << contents;
		file.close();
		qDebug() << "Created file" << fullName;
		return true;
	}else{
		qDebug() << "Could not create file" << fullName;
		qDebug() << file.error();
		return false;
	}

}

/* Delete a file from the server
 *
 * TODO: should we store a backup of it somewhere, or is it gone for good?
 * 	 This is relevant for all storage backends, not just this one...
 */
bool FileSystemBackend::deleteFile(User user, QString filename){
	return false;
}

/* modify a file on the server
 */
bool FileSystemBackend::modifyFile(User user, QString filename, QString patch, PatchType patchType){
	return false;
}

/*
 * Returns all files this user has
 *
 * The returned hash has the form <filename, md5sum of file>
 *
 */
QHash<QString, QString> FileSystemBackend::getFiles(User user){
	QHash<QString, QString> hash;
	return hash;	
}

/* Get the top level directory for this user in our storage tree
 */
QString FileSystemBackend::getUserTopDirectory(User user){
	return user.getName();
}
