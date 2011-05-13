/* definitions for the server
 */
#pragma once

/* The various types of messages the client can send
 */
typedef enum MessageType_t 
{
	        PING,
	        NEW_FILE
} MessageType ;

/* Different algos to use for diffing files
 */
typedef enum PatchType_t
{
	BSDIFF,
	COURGETTE,
	GOOGLE_DIFF

} PatchType;

//time for server connection to timeout
#define TIMEOUT_MILLISECONDS 5000

