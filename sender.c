
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include <syslog.h>

#include "session.h"

#include "sender.h"

char *fixstr(char *tmp)
{
	int i, len = strlen(tmp);
	char *dst = strdup(tmp);
	char c;

	for (i=0; i<len; i++)
	{
		c = tmp[i];
		if (c < 32 || c > 127) c = 32;
		dst[i] = c;
	}
	return dst;
}

void* sender_worker(void* data) {

	struct message_container* message = (struct message_container*) data;

	openlog (SYSLOG_NAME, LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL7);

	char *msg = (char*) malloc(sizeof(char) * 1024);

	

	if (message->body)
	{
		snprintf(msg, 1024, "MESSAGE: %s - %s", fixstr(message->mail_from), fixstr(message->body));
	}
	else
	{
		snprintf(msg, 1024, "MESSAGE: %s - Nothing received.", fixstr(message->mail_from));
	}

	syslog (LOG_INFO, "%s", msg);
	closelog();

	// cleanup
	free(msg);
	free(message->mail_from);
	free(message->rcpt_to);
	free(message->body);
	free(message);
	return NULL;

}

