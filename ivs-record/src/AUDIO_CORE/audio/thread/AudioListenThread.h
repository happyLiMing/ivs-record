/*
 * AudioProvider.h
 *
 *  Created on: 2017年6月23日
 *      Author: robot
 */

#ifndef SRC_TEST_ALSA_AUDIOLISTENTHREAD_H_
#define SRC_TEST_ALSA_AUDIOLISTENTHREAD

#include <string>
#include <iostream>
#include "../../utils/file/FileUtil.h"
#include "../AudioProvider.h"
#include <pthread.h>

using namespace std;
using namespace aiui;

class AudioListenThread
{

private:

	FileUtil::DataFileHelper* mFileHelper;
	AudioProvider* mAudioProvider;

	bool mRun;
	string mAudioPath;
	const  int bufferSize;
	const char * audioBuffer;

	pthread_t thread_id;
	bool thread_created;
	
private:

	bool threadLoop();
	
	static void* thread_proc(void * paramptr);

public:
	AudioListenThread( string &path);

	~AudioListenThread();

	void stopRun();
	
	bool run();
};

#endif
