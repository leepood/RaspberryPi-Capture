/*
 * http_util.c
 *
 *  Created on: 2014-3-18
 *      Author: leepood
 */
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <sys/stat.h>
#include <fcntl.h>

signed int uploadFiles(const char* url, const char* filename, char* lat,
		char*lon) {

	int result = 0;
	CURL* curl;
	CURLcode res;
	struct stat file_info;

	FILE* fd;
	fd = fopen(filename, "rb");
	if (!fd) {
		printf("open file failed\r\n");
		return 0;
	}

	if (fstat(fileno(fd), &file_info) != 0) {
		printf("file error\r\n");
		return 0;
	}

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
		curl_easy_setopt(curl, CURLOPT_READDATA, fd);
		curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE,
				(curl_off_t)file_info.st_size);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));
		} else {
			result = 1;
		}
		/* always cleanup */
		curl_easy_cleanup(curl);
	}
	return result;
}

