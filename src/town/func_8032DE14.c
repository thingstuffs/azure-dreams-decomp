#include "common.h"

typedef struct Copy4 {
    u8 bytes[4];
} Copy4;

extern void townAppendShopEntry(const Copy4 *);
extern s32 townGetFreeShopSlotCount(void);
extern void townSetScriptFlagBit(s32);
extern s32 townGetScriptFlagMask(s32);
extern Copy4 D_8001BE5C;
extern s32 D_8001EACC;
extern s32 D_8001EBCA;

/* Select the response and set flag 0xD80 when its prerequisite passes. */
s32 *townSelectResponseAndSetD80(void) {
    if (townGetScriptFlagMask(0xD80) == 0) {
        if (townGetFreeShopSlotCount() != 0) {
            townSetScriptFlagBit(0xD80);
            townAppendShopEntry(&D_8001BE5C);
            return &D_8001EACC;
        }
    }
    return &D_8001EBCA;
}
