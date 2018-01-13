#include "portaudio.h"
#include <string>
#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <write_wav.h>




class AudioRecorder {


private:
	PaStreamParameters _inputParameters;  /*PaDeviceIndex  device
											int            channelCount
											PaSampleFormat sampleFormat
											PaTime         suggestedLatency
											void*          hostApiSpecificStreamInfo*/
	PaStream* _stream;  				  //handle for audio stream          
	const PaDeviceInfo *_deviceInfo;	 /* Holds the following device info: 
											int            structVersion
											const char*    name
											PaHostApiIndex hostApi
											int            maxInputChannels,
											int            maxOutputChannels,
											PaTime         defaultLowInputLatency,
											PaTime         defaultLowOutputLatency,
											PaTime         defaultHighInputLatency,
											PaTime         defaultHighOutputLatency,
											double         defaultSampleRate*/
	bool _streamOpen;       // keeps track if the stream is open
	bool _flagDevice;       // keeps track if a valid device was found.
	char _fileName[1024];   // file name of wav file

	// holds the number of channels of the recording device and 
	// recorded samples. 
	typedef struct 
	{
			int numChannels;
			std::vector<int16_t> recordedSamples;
	}audioRecorderData;

	







public:
	audioRecorderData _data;

	/* */
	AudioRecorder(std::string fileName,int numChannels);

	/*Stops and closes stream. Also terminates PA */
	~AudioRecorder();
	void stopStream();   // Stops stream callback
	void startStream();  // starts stream callback
	void writeToFile();  // Stops stream and write wav file. 

	/* audio callback */
	int recordCallback(const void *inputBuffer, void *outputBuffer, unsigned long 
		framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData);

	


};
