//
// Copyright (c) 2019-2022 yanggaofeng
//
#include <yangutil/yangtype.h>
#include <yangstream/YangStream.h>
#include <stdio.h>
#include <string.h>

#include "YangStreamRtmp.h"
#include "YangStreamRtc.h"
void yang_stream_init(YangStreamContext* context,YangStreamConfig* pconf){
		memset(&context->streamconfig,0,sizeof(YangStreamConfig));
		strcpy(context->streamconfig.remoteIp,pconf->remoteIp);

		strcpy(context->streamconfig.app,pconf->app);
		strcpy(context->streamconfig.stream,pconf->stream);

		context->streamconfig.remotePort=pconf->remotePort;
		context->streamconfig.localPort=pconf->localPort;
		context->streamconfig.uid=pconf->uid;
		context->streamconfig.streamOptType=pconf->streamOptType;
}

void yang_create_stream(int32_t mediaServer,int32_t transType,YangStreamHandle* streamHandle,int32_t puid,YangStreamConfig* streamconfig,YangAVInfo* pcontext,YangContextStream* stream,YangReceiveCallback* callback) {
	if(streamHandle==NULL) return;
	streamHandle->context=(YangStreamContext*)calloc(sizeof(YangStreamContext),1);
	YangStreamContext* context=streamHandle->context;
	yang_stream_init(context,streamconfig);
	context->avinfo=pcontext;
	context->stream=stream;
	context->data=callback;

	context->streamInit = 0;
	context->audioStream=0;
	context->videoStream=0;
	context->uid=puid;
	//context->data=NULL;
	context->netState = 1;
	//streamHandle->init=yang_stream_init;
	context->transtype=transType;
	context->mediaServer=mediaServer;
	if(transType==Yang_Webrtc){
		yang_create_stream_rtc(streamHandle);
	}else if(transType==Yang_Rtmp){
		yang_create_stream_rtmp(streamHandle);
	}
}

void yang_destroy_stream(YangStreamHandle* stream) {
	if(stream->context->transtype==Yang_Webrtc){
		yang_destroy_stream_rtc(stream);
	}else if(stream->context->transtype==Yang_Rtmp){
		yang_destroy_stream_rtmp(stream);
	}
	stream->context->data=NULL;
	stream->context->avinfo=NULL;
	yang_free(stream->context);
}
