#include "filesystem.h"

FileSystemBackend::FileSystemBackend(){

}

bool FileSystemBackend::addFile(User user, QString filename, QString contents){
	return false;
}

bool FileSystemBackend::deleteFile(User user, QString filename){
	return false;
}

bool FileSystemBackend::modifyFile(User user, QString filename, QString patch, PatchType patchType){
	return false;
}

QHash<QString, QString> FileSystemBackend::getFiles(User user){
	QHash<QString, QString> hash;
	return hash;	
}

QString getUserTopDirectory(User user){
	return "";
}
