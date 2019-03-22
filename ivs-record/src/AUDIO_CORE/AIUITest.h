/*
 * AIUIAgentTest.h
 *
 *  Created on: 2019年3月21日
 *      Author: robot
 */

#ifndef AIUIAGENTTEST_H_
#define AIUIAGENTTEST_H_


#include "utils/file/FileUtil.h"
#include "audio/thread/AudioListenThread.h"
#include <string>
#include <iostream>


#define  SAVE_AUDIO_PATH "/home/earl/AIUI/save"
using namespace std;

class AIUITester
{
public:
	AIUITester() ;

	~AIUITester();

public:
	void readCmd();
	void test();
	void alsaStart();
	void alsaStop();
	AudioListenThread * audioListeningThread;
};

#endif /* AIUIAGENTTEST_H_ */
