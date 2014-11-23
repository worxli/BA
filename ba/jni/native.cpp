#include "native.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <vector>
#include <OpenNI.h>

using namespace cv;
using namespace openni;
using namespace std;


#define LOG_TAG "nativeOpenNI_debug"
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)


#define SAMPLE_READ_WAIT_TIMEOUT 2000 //2000ms

Status rc;
Array<openni::DeviceInfo> deviceList;
Device device;
VideoStream depth;

bool streaming;


int init() {
	//initialize OpenNI
	rc = OpenNI::initialize();
	if (rc != STATUS_OK)
	{
		LOGW("Initialize failed\n%s\n", OpenNI::getExtendedError());
		return 1;
	} else {
		LOGW("Initialize successful\n");
		return 0;
	}
}

int connectDevice() {
	//get device list
	OpenNI::enumerateDevices(&deviceList);

	//check if any devices found
	if(deviceList.getSize()!=0) {
		LOGW("devices found");
	} else {
		LOGW("no devices found");
	}

	//open first device
	rc = device.open(ANY_DEVICE);
	if (rc != STATUS_OK)
	{
		LOGW("Couldn't open device\n%s\n", OpenNI::getExtendedError());
		return 1;
	} else {
		LOGW("Open device\n");
		return 1;
	}
}

int startDepthStream() {

	if (device.getSensorInfo(SENSOR_DEPTH) != NULL)
	{
		rc = depth.create(device, SENSOR_DEPTH);
		if (rc != STATUS_OK)
		{
			//printf("Couldn't create depth stream\n%s\n", OpenNI::getExtendedError());
			return 3;
		}
	}

	rc = depth.start();
	if (rc != STATUS_OK)
	{
		//printf("Couldn't start the depth stream\n%s\n", OpenNI::getExtendedError());
		return 4;
	}

	VideoFrameRef frame;

	streaming = true;
	while (streaming)
	{
		int changedStreamDummy;
		VideoStream* pStream = &depth;
		rc = OpenNI::waitForAnyStream(&pStream, 1, &changedStreamDummy, SAMPLE_READ_WAIT_TIMEOUT);
		if (rc != STATUS_OK)
		{
			//printf("Wait failed! (timeout is %d ms)\n%s\n", SAMPLE_READ_WAIT_TIMEOUT, OpenNI::getExtendedError());
			continue;
		}

		rc = depth.readFrame(&frame);
		if (rc != STATUS_OK)
		{
			//printf("Read failed!\n%s\n", OpenNI::getExtendedError());
			continue;
		}

		if (frame.getVideoMode().getPixelFormat() != PIXEL_FORMAT_DEPTH_1_MM && frame.getVideoMode().getPixelFormat() != PIXEL_FORMAT_DEPTH_100_UM)
		{
			//printf("Unexpected frame format\n");
			continue;
		}

		DepthPixel* pDepth = (DepthPixel*)frame.getData();

		int middleIndex = (frame.getHeight()+1)*frame.getWidth()/2;

		//printf("[%08llu] %8d\n", (long long)frame.getTimestamp(), pDepth[middleIndex]);
	}

	return 0;
}

int calibrateRGB(Mat addrRgba) {



	return 1;
}

bool runCalibrationAndSave(Settings& s, Size imageSize, Mat&  cameraMatrix, Mat& distCoeffs, vector<vector<Point2f> > imagePoints )
{
 vector<Mat> rvecs, tvecs;
 vector<float> reprojErrs;
 double totalAvgErr = 0;

 bool ok = runCalibration(s,imageSize, cameraMatrix, distCoeffs, imagePoints, rvecs, tvecs,
                          reprojErrs, totalAvgErr);


 if( ok )   // save only if the calibration was done with success
     saveCameraParams( s, imageSize, cameraMatrix, distCoeffs, rvecs ,tvecs, reprojErrs,
                         imagePoints, totalAvgErr);
 return ok;
}


void saveCameraParams(Settings& s, Size imageSize, Mat& cameraMatrix, Mat& distCoeffs, vector<Mat> rvecs , vector<Mat> tvecs, vector<float> reprojErrs,
		vector<vector<Point2f> > imagePoints, double totalAvgErr){

}

void runCalibration(Settings& s, Size imageSize, Mat& cameraMatrix, Mat& distCoeffs, vector<vector<Point2f> > imagePoints, vector<Mat> rvecs, vector<Mat> tvecs,
		vector<float> reprojErrs, double totalAvgErr) {

}

int calibrateD() {

	return 1;
}

int findExtrinsics() {

	return 1;
}

//initialize openni and sensor
JNIEXPORT jint JNICALL Java_com_example_nativeopenni_MainActivity_init(JNIEnv*, jobject)
{
	init();
	connectDevice();
	startDepthStream();
}

//calibrate model
JNIEXPORT jint JNICALL Java_com_example_nativeopenni_MainActivity_calibrate(JNIEnv*, jobject, jlong addrRgba)
{
	Mat& mRgb = *(Mat*)addrRgba;

	calibrateRGB(mRgb);
	calibrateD();
	findExtrinsics();

}

//start recording the model
JNIEXPORT jint JNICALL Java_com_example_nativeopenni_MainActivity_recordModel(JNIEnv*, jobject)
{

}

//stop the depth stream and close openni
JNIEXPORT jint JNICALL Java_com_example_nativeopenni_MainActivity_stop(JNIEnv*, jobject)
{
	//do everything to eit gracefully
	streaming = false;

	depth.stop();
	depth.destroy();
	device.close();
	OpenNI::shutdown();
}


