* 使用说明

本工程是在PC上使用Ubuntu操作系统并通过alsa实时获取16k 16bit音频的参考示例,不保证兼容其他设备及系统。开发者可以改程序为参考，结合自有开发板/样机录音方式采集16k 1bbit音频并采用stdout做标准输出。

* 编译
* 安装alsa ``sudo apt-get install libasound2-dev`` 默认安装在/usr/lib 下，头文件位于 /usr/include/alsa 下面。头文件如果改变,CMakeList.txt请注意修改。

* 修改测试音频输出路径。修改文件 src/AUDIO_CORE/AIUITest.h 中音频保存路径 
  
 ``#define  SAVE_AUDIO_PATH "/home/earl/save.pcm"``
 
 ```
   cd /tartget/build/
   
   cmake ..
   
   make 
   
  ``` 
  
* 编译好的ivs-record位于 ``/tartget/build/bin/``下面，执行即可。
