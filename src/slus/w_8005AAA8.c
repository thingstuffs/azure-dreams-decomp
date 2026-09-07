#include "common.h"

#include "common.h"

typedef struct {
    s16 marker;
    u8 pad02[0x0A];
    s32 owner;
    s32 unk10;
    s32 unk14;
    u8 pad18[4];
} S_80086A40; /* size 0x1C */

extern s32 func_8005ECA0(s32 arg0);
extern s32 func_8005EC40(s32 arg0, s32 arg1);
extern S_80086A40 D_80086A40[];

s16 func_8005AAA8(s32 arg0, s16 arg1)
{
    s32 value;
    s16 marker;
    S_80086A40 *base;
    S_80086A40 *entry;

    base = D_80086A40;
    entry = &base[arg1];
    marker = entry->marker;
    if (marker == arg1) {
        value = func_8005ECA0(entry->unk10);
        if (func_8005EC40(arg0, entry->unk14) == entry->unk14) {
            entry->owner = arg0;
            entry->unk10 = value;
            return marker;
        }
        return -1;
    }
    return -1;
}
