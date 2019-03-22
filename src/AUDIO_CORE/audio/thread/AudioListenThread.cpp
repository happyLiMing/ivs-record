/*
 * 、
 * AudioListenThread.cpp
 *
 *  Created on: 2019年3月21日
 *      Author: robot
 */

#include "AudioListenThread.h"

using namespace std;

AudioListenThread::AudioListenThread(string& path)
:bufferSize(1024),mAudioPath(path),mRun(true),mFileHelper(NULL),mAudioProvider(NULL),audioBuffer(new char[bufferSize]),thread_created(false)
{
	mFileHelper = new FileUtil::DataFileHelper("");
	mFileHelper->createWriteFile(mAudioPath, ".pcm", true);

	mAudioProvider = new AudioProvider();
}

AudioListenThread::~AudioListenThread( )
{
	if (NULL != mFileHelper)  {
		delete mFileHelper;
		mFileHelper = NULL;
	}
}

void AudioListenThread::stopRun()
{
	if (thread_created) {
	mRun = false;
	void* retarg;
	pthread_join(thread_id, &retarg);
	thread_created = false;
	}
}

bool AudioListenThread::run()
{
	if (thread_created == false) {
		int rc = pthread_create(&thread_id, NULL, thread_proc, this);

		if (rc != 0) {
			cout << "exit, pthread_create failed, ret =  " << rc <<endl;
			exit(-1);
		}
		thread_created = true;
		return true;
	}
	return false;
}

bool AudioListenThread::threadLoop()
{
	audioBuffer = mAudioProvider->startRecord();
	fprintf(stdout, audioBuffer);
	mFileHelper->write(audioBuffer, bufferSize, 0, bufferSize);
	return mRun;
}

void*  AudioListenThread::thread_proc(void * paramptr)
{
	AudioListenThread *  self  = (AudioListenThread *)paramptr;
	while(1) {
		bool ret = self->threadLoop();
		if (!ret) {
			cout << "exit thread_proc, ret = " << ret << endl;
			break;
		}
	}
	return NULL;
}
