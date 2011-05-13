#pragma once
typedef enum MessageType_t 
{
	        PING,
	        NEW_FILE
} MessageType ;

typedef enum PatchType_t
{
	BSDIFF,
	COURGETTE,
	GOOGLE_DIFF

} PatchType;

#define TIMEOUT_MILLISECONDS 5000

