#include "common.h"

#include "common.h"

#ifndef NULL
#define NULL 0
#endif

extern s32 DrawSync(s32);
extern s32 Control_CD();
extern s32 drainCdCommandQueue(void);
extern s32 func_80041344();
extern u8 D_80080B9C[];
extern u8 D_80080BAC[];
extern s32 D_80081480;
extern void setByteOne();

/* Runs two callback sequences, resetting their shared status byte before each. */
void sceneLoadTextureAndDataPair(s8 *status) {
    *status = 0;
    Control_CD(6, D_80080BAC, NULL);
    Control_CD(0xFF, setByteOne, status);
    drainCdCommandQueue();
    func_80041344(0x80020000, D_80081480);
    DrawSync(0);
    *status = 0;
    Control_CD(6, D_80080B9C, NULL);
    Control_CD(0xFF, setByteOne, status);
    drainCdCommandQueue();
}
