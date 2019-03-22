/*
 * AudioProvider.h
 *
 *  Created on: 2019年3月21日
 *      Author: robot
 */

#ifndef SRC_TEST_ALSA_AUDIOPROVIDER_H_
#define SRC_TEST_ALSA_AUDIOPROVIDER_H_

#include <alsa/asoundlib.h>
#include <assert.h>
#include <string>
#include <iostream>
using namespace std;

namespace aiui {

class AudioProvider
{
private :
	static const string TAG ;

	//		snd_pcm_t* handle;

	unsigned int retries;

	unsigned int retryDelay;

	unsigned int chanel;

	unsigned int sampleRate;

	const char* deviceName;

	typedef struct _record_data
	{
		snd_pcm_t *handle;
		char *buf;
		int size;
		snd_pcm_uframes_t frames;
	}	RecordData;

	RecordData recordData;

public:
	AudioProvider();

	const char* startRecord();

	void stopRecord();

	virtual ~AudioProvider();

	int pcm_read(snd_pcm_t *handle, char *buf);
};
}

#endif /* SRC_TEST_ALSA_AUDIOPROVIDER_H_ */
