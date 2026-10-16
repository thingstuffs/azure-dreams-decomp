#include "common.h"

extern s32 testResidentBitmapBit(s32);
extern void SD_Call(s32);
extern void townClearGlobal80110EC0Global80082A39(void);
extern s32 townCreateItemMenuObject(s32);

/* Runs the action sequence for the context unless flag 0xA5 is set. */
s32 townRunTheActionSequenceContextUnlessFlagHexA5Set(s32 context) {
    if (testResidentBitmapBit(0xA5) != 0) {
        return 0;
    }
    SD_Call(0x514);
    townClearGlobal80110EC0Global80082A39();
    return townCreateItemMenuObject(context);
}
