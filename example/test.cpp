
#include <iostream>
#include <fstream>
#include <curl/curl.h>

int main(int argc, char const *argv[])
{
	CURL *curl;
	CURLcode res;
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

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8501/v1/models/TinyModel:predict");
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data);

		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
		}
		curl_easy_cleanup(curl);
	}
	return 0;
}