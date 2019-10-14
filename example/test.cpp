#include <cstring>
#include <iostream>
#include <fstream>
#include <curl/curl.h>

// This struct will store the server results
struct MemoryStruct {
	char *memory;
	size_t size;
};

// This function gets called whenever data is received and logically updates the buffer
// 		contents points at the received data
// 		size is always 1 (according to docs)
// 		nmemb is the size of the contents
// 		userdata points to the struct that the contents can be written to
//
//	This example uses C style memory allocation, but can be implemented with C++ vectors too
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userdata) {
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)userdata;

	char *ptr = (char *)realloc(mem->memory, mem->size + realsize + 1);
	if (ptr == NULL) {
		/* out of memory */
		std::cerr << "Not enough memory (realloc returned NULL)\n";
		return 0;
	}

	// C style buffer update
	mem->memory = ptr;
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}

int main(int argc, char const *argv[])
{
	CURL *curl;
	CURLcode res;

	// test data is read into json_data
	char *json_data;
	std::ifstream json_file;
	json_file.open("test.json");
	if (json_file.is_open()) {
		json_file.seekg(0, json_file.end);
		int length = json_file.tellg();
		json_file.seekg(0, json_file.beg);

		json_data = new char[length];
		json_file.read(json_data, length);
		json_file.close();
	}

	// C style initialization of a memory buffer
	struct MemoryStruct chunk;
	chunk.memory = (char *)malloc(1);
	chunk.size = 0;

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8501/v1/models/TinyModel:predict");
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk); // this is how chunk gets passed to our callback

		// send the request!
		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
		}
		else {
			/* Do something with the results here */
			std::cout << (unsigned long)chunk.size << " bytes retrieved\n";
			printf("Here is the JSON results:\n%s", chunk.memory);
		}
		curl_easy_cleanup(curl);
	}
	return 0;
}