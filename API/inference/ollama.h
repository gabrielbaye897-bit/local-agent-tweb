#ifndef OLLAMA_H
#define OLLAMA_H

typedef struct {
	char *data;
	size_t size ;
	size_t capacity;
} response_buffer_t;

int ollama_chat(const char *model,const ollama_message_t *request,size_t message_count);

size_t write_callback(char *incoming,size_t size, size_t nmemb,void *userdata);

#endif
