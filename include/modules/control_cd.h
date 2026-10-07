#ifndef MODULE_CONTROL_CD_H
#define MODULE_CONTROL_CD_H
#include "common.h"
/* Third register is a payload word: 0/1 flags or callback/data address bits. */
extern s32 Control_CD(s32 event_code, void *event_data, s32 payload);
extern void func_8003F320(void);
#endif
