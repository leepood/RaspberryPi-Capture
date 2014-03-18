/*
 * jobs.c
 *
 *  Created on: 2014-3-18
 *      Author: leepood
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <time.h>
#include <err.h>
#include <errno.h>
#include <curl/curl.h>
#include <curl/easy.h>

#include "../header/http_util.h"

#define UPLOAD_URL "http://up.qiniu.com"
#define FIELD_GPS_LON "lon"
#define FIELD_GPS_LAT "lat"

int main(int argc, char **argv) {
	const char* fileName = "capture.jpg";
	CvCapture* pCapture = NULL;
	if (!(pCapture = cvCreateCameraCapture(0))) {
		perror("open camera failed\r\n");
		return -1;
	}

	IplImage* pFrame = NULL;
	while ((pFrame = cvQueryFrame(pCapture))) {
		cvSaveImage(fileName, pFrame, 0);
		break;
	}

	//cvRelease(&pFrame);
	cvReleaseCapture(&pCapture);

	//curl upload
	uploadFiles(UPLOAD_URL,fileName,"","");
}

