﻿//
// Copyright (c) 2019-2022 yanggaofeng
//
#ifndef YangStunPacket_H__
#define YangStunPacket_H__

#include <stdint.h>
#include <string.h>
#include <yangrtp/YangRtpConstant.h>
#include <yangutil/buffer/YangBuffer.h>
#include <yangutil/sys/YangSsrc.h>
/**

**/
// @see: https://tools.ietf.org/html/rfc5389
// The magic cookie field MUST contain the fixed value 0x2112A442 in network byte order
#define  kStunMagicCookie  (uint32_t)0x2112A442
#define YangStunTranscationIdLen 12
typedef enum YangStunMessageType
{
	// see @ https://tools.ietf.org/html/rfc3489#section-11.1	
    StunBindingRequest            = 0x0001,
	StunSharedSecretRequest       = 0x0002,
	StunAllocate              = 0x0003,
	StunRefresh               = 0x0004,
	StunSend                  = 0x0006,
	StunTData                  = 0x0007,
    StunPermission            = 0x0008,
	StunChannelBindingRequest     = 0x0009,
    StunBindingIndication 		  = 0x0011,
	StunSendIndication            = 0x0016,
    StunDataIndication            = 0x0017,
    StunBindingSuccessResponse    = 0x0101,
	StunSharedSecretResponse      = 0x0102,
	StunAllocateSuccessResponse   = 0x0103,
    StunRefreshteSuccessResponse  = 0x0104,
	StunPermissionSuccessResponse = 0x0108,
	StunChannelBindSuccessResponse = 0x0109,

    StunBindingErrorResponse      = 0x0111,
	StunSharedSecretErrorResponse = 0x0112,
	StunAllocateErrorResponse     = 0x0113,
	StunRefreshErrorResponse      = 0x0114,
	StunPermissionErrorResponse   = 0x0118,
	StunChannelBindErrorResponse  = 0x0119

}YangStunMessageType;

typedef enum
{
    // see @ https://tools.ietf.org/html/rfc3489#section-11.2
	// see @ https://tools.ietf.org/html/rfc5389#section-18.2
	StunMappedAddress     = 0x0001,
   	StunResponseAddress   = 0x0002,
   	StunChangeRequest     = 0x0003,
   	StunSourceAddress     = 0x0004,
   	StunChangedAddress    = 0x0005,
   	StunUsername          = 0x0006,
   	StunPassword          = 0x0007,
   	StunMessageIntegrity  = 0x0008,
   	StunErrorCode         = 0x0009,
   	StunUnknownAttributes = 0x000A,
	StunReflectedFrom     = 0x000B,
	StunChannelNumber     = 0x000C,
	StunLifetime          = 0x000D,

	StunXorPeerAddress    = 0x0012,
    StunRealm             = 0x0014,
    StunNonce             = 0x0015,
	StunXorRelayedAddress = 0x0016,
	StunRequestTransport  = 0x0019,

    StunXorMappedAddress  = 0x0020,
    StunSoftware          = 0x8022,
    StunAlternateServer   = 0x8023,
    StunFingerprint       = 0x8028,

    StunPriority          = 0x0024,
    StunUseCandidate      = 0x0025,
    StunIceControlled     = 0x8029,
    StunIceControlling    = 0x802A,
}YangStunMessageAttribute;

typedef struct{
	uint16_t message_type;
	uint16_t mapped_port;
	int16_t use_candidate;
	int16_t ice_controlled;
	int32_t ice_controlling;
	uint32_t mapped_address;
	char local_ufrag[16];
	char remote_ufrag[32];
	char transcation_id[13];
	char username[32];
}YangStunPacket;

typedef struct{
	YangStunPacket packet;
	int32_t (*encodeStunServer)(YangBuffer* stream,void* pudp,char* username,char* ice_pwd);
	int32_t (*decodeStunServer)(YangStunPacket* pkt,char* buf, const int32_t nb_buf);
	int32_t (*decode)(YangStunPacket* pkt, char* buf,  int32_t nb_buf);
	int32_t (*decode2)( char* buf,  int32_t nb_buf);
	int32_t (*createResponseStunPacket)(YangStunPacket* request,void* session);
	int32_t (*createRequestStunPacket)(void* psession,char* ice_pwd);
}YangRtcStun;

void yang_create_stun(YangRtcStun* stun);
void yang_destroy_stun(YangRtcStun* stun);

#endif
