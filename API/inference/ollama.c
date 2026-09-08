//#include "ollama.h"
#include <cjson/cJSON.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *data;
    size_t size;
} response_t;

static size_t write_callback(char *data,size_t size,size_t nmemb,void *userdata)
{
	response_t *response =  userdata;
	size_t bytes = size * nmemb ;
	
	char *tmp = realloc(response->data,response->size + bytes + 1);

	if (!tmp)
        	return 0 ;

	response->data = tmp;

	memcpy(response->data + response->size,data,bytes);

	response->size += bytes;
	response->data[response->size] = '\0';
	
	return bytes;

}


char *make_msg(char *model,char *content,bool stream_bool)
{	
	
	cJSON *root = cJSON_CreateObject();
	cJSON_AddStringToObject(root, "model", model);

	cJSON *messages = cJSON_AddArrayToObject(root, "messages");

	cJSON *message = cJSON_CreateObject();

	cJSON_AddStringToObject(message, "role", "user");
	cJSON_AddStringToObject(message, "content", content);

	cJSON_AddItemToArray(messages, message);

	cJSON_AddBoolToObject(root, "stream", stream_bool);

	char *json = cJSON_PrintUnformatted(root);

	//curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json);

	cJSON_Delete(root);

	return json;

}

char *recive_msg(void)
{

}


int main(void)
{
//					    V-- this is the msg content  
	char *json = make_msg("qwen3:8B", "hello !! how are you going ? i write you from an API over HTTP resquest", false);
	printf("%s\n", json);
	CURL *curl = curl_easy_init();

	response_t response = {
	.data = NULL,
	.size = 0
	};

	if (!curl)
		return 1;

	
	curl_easy_setopt(curl, CURLOPT_URL,"http://localhost:11434/api/chat");
	curl_easy_setopt(curl, CURLOPT_POST, 1L);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json);

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Content-Type: application/json");

	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,write_callback);
	curl_easy_setopt(curl,CURLOPT_WRITEDATA,&response);


	CURLcode result = curl_easy_perform(curl);

	free(json);
	curl_slist_free_all(headers);
	curl_easy_cleanup(curl);

	return result == CURLE_OK ? 0 : 1 ; 
}

