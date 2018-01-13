#include "audioRecorder.h"
#include <string.h>
#include <unistd.h>




static int MyPaStreamCallback(const void *inputBuffer, void *outputBuffer,
                               unsigned long framesPerBuffer,
                               const PaStreamCallbackTimeInfo* timeInfo,
                               PaStreamCallbackFlags statusFlags,
                               void *userData ){

	AudioRecorder *audioRecorder = reinterpret_cast<AudioRecorder*>(userData);
	return audioRecorder->recordCallback(inputBuffer,outputBuffer, framesPerBuffer, timeInfo, statusFlags, &audioRecorder->_data);
}

AudioRecorder::AudioRecorder(std::string fileName = "recorded.wav",int numChannels = 10){
	Pa_Initialize();                                      // init port audio
	PaError _err = paNoError;                             // keeps track of port audio errors
	strcpy(_fileName, fileName.c_str());                  // copy filename into char
	_inputParameters.device = Pa_GetDefaultInputDevice(); // get default device

	// Check if there is a device
	if(_inputParameters.device == paNoDevice){
		printf("Error: No default audio input device.\n");
		_flagDevice = false;
		
	}
	else{
		_flagDevice = true;
		// get device information
		_deviceInfo = Pa_GetDeviceInfo(_inputParameters.device);
		printf("Defualt Input Device found %s\n",_deviceInfo->name);

		// ensure number of channels is supported. If not, use max number of channels
		if(numChannels > _deviceInfo->maxInputChannels){
			_data.numChannels = _deviceInfo->maxInputChannels;
		}
		else{
			_data.numChannels = numChannels;
		}

		

		// Set stream parameters
		_inputParameters.suggestedLatency = _deviceInfo->defaultLowInputLatency;
		_inputParameters.channelCount = _data.numChannels;
		_inputParameters.hostApiSpecificStreamInfo = NULL;
		_inputParameters.sampleFormat = paInt16;

		printf("Device Sample Rate %f\n",_deviceInfo->defaultSampleRate);

		
		// open audio stream
		_err = Pa_OpenStream(&_stream,
							&_inputParameters,
							NULL,             /* No output parameters */
							_deviceInfo->defaultSampleRate,
							paFramesPerBufferUnspecified,
							paNoFlag,        /* No need to clip data */
							MyPaStreamCallback,
							this);

		if(_err !=paNoError){
			printf("Error: could not open audio stream. \n");
		}

	}
}



void AudioRecorder::stopStream(){
	if(_streamOpen == true && _flagDevice){
		Pa_StopStream(_stream);
		_streamOpen = false;
	}	
}

void AudioRecorder::startStream(){
	if(_streamOpen == false && _flagDevice){
		Pa_StartStream(_stream);
		_streamOpen = true;
	}
}

void AudioRecorder::writeToFile(){
	if(_flagDevice)
	{


		stopStream(); // make sure the stream is stopped.

		
		// repackage data into an array. 
		int16_t test[_data.recordedSamples.size()];
		for(int i = 0; i < _data.recordedSamples.size(); i++)
		{
			test[i] = _data.recordedSamples[i];
		}

		FILE *fid;
		WAV_Writer_s wavWriter;
		wavWriter.fid = fid;
		wavWriter.dataSizeOffset = 0;
		wavWriter.dataSize = sizeof(int16_t);

		long temp;

		// Open file and create header
		temp = Audio_WAV_OpenWriter(&wavWriter, _fileName, _deviceInfo->defaultSampleRate,_data.numChannels);
		printf("Open Writer %ld\n", temp);
		// write data to file
		temp = Audio_WAV_WriteShorts(&wavWriter, test, _data.recordedSamples.size());
		printf("Open Writer %ld\n", temp);
		// close file
		temp = Audio_WAV_CloseWriter(&wavWriter);
	}
	else{
		printf("Error: Cannot write to file. No audio device was found\n");
	}

}

AudioRecorder::~AudioRecorder(){
	stopStream();
	Pa_CloseStream(_stream);
	Pa_Terminate();
}


int AudioRecorder::recordCallback(const void *inputBuffer, void *outputBuffer,
                               unsigned long framesPerBuffer,
                               const PaStreamCallbackTimeInfo* timeInfo,
                               PaStreamCallbackFlags statusFlags,
                               void *userData ){
	audioRecorderData* data = (audioRecorderData*)userData;
	int numChannels = data->numChannels;
	std::vector<int16_t>* samples = &data->recordedSamples;
	const int16_t *rptr = (const int16_t*) inputBuffer;
	
		

	(void) outputBuffer; /*Prevent unused variable warnings */
	(void) timeInfo;
	(void) statusFlags;
	(void) userData;	
	// if there is nothing in the input
	if(inputBuffer == NULL)	{
		for(int i = 0; i <framesPerBuffer; i++){
			for(int j = 0; j <numChannels; j++){
				samples->push_back(0.0f);
			}
			
		}
	}
	else{ // push buffer data onto recordedSamples
		for(int i = 0; i <framesPerBuffer; i++){
			for(int j = 0; j <numChannels; j++){
				
				samples->push_back(*rptr++);
				
			}
			
		}
	}


	return paContinue;

}




