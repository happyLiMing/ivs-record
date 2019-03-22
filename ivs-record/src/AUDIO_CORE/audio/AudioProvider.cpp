/*
 * AudioProvider.cpp
 *
 *  Created on: 2019年3月21日
 *      Author: robot
 */

#include "AudioProvider.h"

namespace aiui {

	const string AudioProvider::TAG = "AudioProvider";

	AudioProvider::AudioProvider()
	:retries(10),retryDelay(20 * 1000),chanel(1),sampleRate(16000),deviceName("default")
	{
		snd_pcm_hw_params_t* params;

		unsigned i;
		for (i = 0; i < retries; ++i)
		{
			if (snd_pcm_open(&recordData.handle,  deviceName, SND_PCM_STREAM_CAPTURE, 0) == 0)
			{
				cout << "open device success "<< recordData.handle <<endl;
				break;
			}
			usleep( retryDelay);
		}
		assert( i < retries);
		snd_pcm_hw_params_alloca(&params);
		int ret = snd_pcm_hw_params_any(recordData.handle, params);
		assert(snd_pcm_hw_params_set_access(recordData.handle, params, SND_PCM_ACCESS_RW_INTERLEAVED) == 0);
		assert(snd_pcm_hw_params_set_format(recordData.handle, params, SND_PCM_FORMAT_S16_LE) == 0);
		assert(snd_pcm_hw_params_set_channels(recordData.handle, params, chanel) == 0);
		assert(snd_pcm_hw_params_set_rate_near(recordData.handle, params, &sampleRate, 0) == 0);
		recordData.frames = 512;
		assert(snd_pcm_hw_params_set_period_size_near(recordData.handle, params, &recordData.frames, 0) ==0);
		assert(snd_pcm_hw_params(recordData.handle, params) == 0);
		snd_pcm_hw_params_get_period_size(params, &recordData.frames, 0);
		recordData.size = recordData.frames *2 *1;
		recordData.buf = (char*)malloc(recordData.size);
		if (recordData.buf == NULL)
		{
			cout << "pcm read buf failed!" <<endl;
		}
	}

	const char* AudioProvider::startRecord()
	{
		if (NULL != recordData.handle)
		{
			int ret = pcm_read(recordData.handle, recordData.buf);
			return  recordData.buf;
		}

		std::cout <<" startRecord error! "<<std::endl;
		return NULL;
	}

	void AudioProvider::stopRecord()
	{
		assert(snd_pcm_close(recordData.handle) == 0);
		recordData.handle = NULL;
	}

	AudioProvider::~AudioProvider()
	{
		if ( recordData.handle != NULL) {
			//snd_pcm_drain(handle);
			snd_pcm_close(recordData.handle);
		}
		recordData.handle = NULL;
	}

	int AudioProvider::pcm_read(snd_pcm_t *handle, char *buf)
	{
		int ret = snd_pcm_readi(handle, buf, recordData.frames);
			if(ret == -EPIPE)
			{
				printf("overrun occurred\n");
				snd_pcm_prepare(recordData.handle);
				return -1;
			}
			else if(ret < 0)
			{
				printf("error from read: %s\n",snd_strerror(ret));
				return -1;
			}
			else if(ret != (int)recordData.frames)
			{
				printf("short read, read %d frames\n", ret);
				return -1;
			}
			else
				return ret;
	}
}



