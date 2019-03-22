#include "AIUITest.h"
#include <string.h>

AIUITester::AIUITester() :audioListeningThread(NULL)
{
}

AIUITester::~AIUITester()
{
}

void AIUITester::readCmd()
{
	cout << "input cmd:" << endl;

	string cmd;
	while (true)
	{
		cin >> cmd;
		 if (cmd == "l") {
			alsaStart();
		}
		else if (cmd == "s") {
			alsaStop();
		}
		else {
			cout << "invalid cmd, input again." << endl;
		}
	}
}

void AIUITester::alsaStart()
{
	if (audioListeningThread == NULL)
	{
		string savePath(SAVE_AUDIO_PATH);
		audioListeningThread = new AudioListenThread(savePath);
		audioListeningThread->run();
	} else {
		cout << " audioListeningThread not NULL " <<endl;
	}
}

void AIUITester::alsaStop()
{
	if (audioListeningThread != NULL)
	{
		audioListeningThread->stopRun();
		audioListeningThread = NULL;
	}
}

void AIUITester::test()
{
	// readCmd();
	alsaStart();
	while (60) {
		sleep(1);
	}
}