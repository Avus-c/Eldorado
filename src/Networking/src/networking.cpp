#include <Networking/networking.hpp>

#include <Networking/discord.hpp>

#include <curl/curl.h>
#include <iostream>
#include <print>
#include <string>

#define STOP_THE_DISCORD_SPAM_DURING_DEVELOPMENT 1

// Callback function to handle the response data
size_t WriteCallback( void *contents, size_t size, size_t nmemb, void *userp )
{
	// You can handle the response data here if needed.
	// For now, we'll just discard it.
	return size * nmemb;
}

void sendMessage( const std::string &message )
{
#if STOP_THE_DISCORD_SPAM_DURING_DEVELOPMENT == 1
	std::println( "{}", message.c_str() );
#else
	CURL    *curl;
	CURLcode res;
	curl = curl_easy_init();
	if ( !curl )
	{
		return;
	}

	std::string url
	    = "https://discord.com/api/v10/channels/" + std::string( TestChannel ) + "/messages";
	std::string jsonPayload = "{\"content\":\"" + message + "\"}";

	struct curl_slist *headers = nullptr;
	headers
	    = curl_slist_append( headers, ( "Authorization: Bot " + std::string( BotToken ) ).c_str() );

	headers = curl_slist_append( headers, "Content-Type: application/json" );

	curl_easy_setopt( curl, CURLOPT_URL, url.c_str() );
	curl_easy_setopt( curl, CURLOPT_POSTFIELDS, jsonPayload.c_str() );
	curl_easy_setopt( curl, CURLOPT_HTTPHEADER, headers );

	// Set the write callback function
	curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, WriteCallback );

	res = curl_easy_perform( curl );
	if ( res != CURLE_OK )
	{
		std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror( res ) << std::endl;
	}

	curl_easy_cleanup( curl );
#endif
}
