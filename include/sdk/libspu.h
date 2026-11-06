/* Stand-in declarations for the Psy-Q SDK library libspu. */
#ifndef SDK_LIBSPU_H
#define SDK_LIBSPU_H

#include "common.h"

void SpuSetKey(s32 key_on, u32 voices);

#include "shared/spu_voice.h"

struct S_800799BC;
struct SoundReverbParameters;

void SpuQuit(void);
s32 SpuInitMalloc(s32 count, struct S_800799BC *record);
s32 _SpuIsInAllocateArea(u32 address);
s32 _SpuIsInAllocateArea_(u32 value);
s32 _spu_FsetRXXa(s32 index, u32 value);
s32 SpuSetTransferStartAddr(s32 address);
s32 SpuIsTransferCompleted(s32 wait_for_completion);
s32 SpuGetKeyStatus(s32 voice_mask);
void SpuGetVoiceAttr(SpuVoiceAttr_ *voice_attr);
void SpuStart(void);
void func_8005D550(s32 index, u32 value, s32 apply_shift);
void _spu_FsetRXX(s32 index, u32 value, s32 apply_shift);
s32 _spu_FgetRXXa(s32 index, s32 shift_mode);
void _spu_FsetPCR(s32 use_status_3);
void _SpuInit(s32 channel);
s32 SpuReserveReverbWorkArea(s32 enabled);
void _spu_setReverbAttr(struct SoundReverbParameters *source);
s32 SpuSetReverb(s32 enable);
s32 _spu_Fw(s32 channel, s32 playback_param);
s32 _spu_Fr(s32 buffer_addr, s32 size);

#endif
