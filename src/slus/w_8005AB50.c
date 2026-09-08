#include "common.h"

#include "common.h"

typedef struct {
    /* 0x00 */ s16 marker;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} S_80086A40;

extern S_80086A40 D_80086A40[16];
typedef struct {
    s32 value;
    s32 pad[2];
} S_8007382C;

extern S_8007382C D_8007382C;

extern s32 func_8005EC40(s32 arg0, u32 arg1);
extern void func_8005ECA0(s32 arg0);

s32 func_8005AB50(s32 arg0, u32 arg1, s16 arg2)
{
    S_80086A40 *base;
    S_80086A40 *entry;
    s16 marker;
    register u32 amount ASM_REG("$17");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    u32 remaining;

    base = D_80086A40;
    entry = &base[arg2];
    marker = entry->marker;
    amount = arg1;

    if (marker != arg2) {
        return -1;
    }

    func_8005ECA0(entry->unk10 + D_8007382C.value);

    remaining = entry->unk14 - D_8007382C.value;
    if (remaining < amount) {
        amount = remaining;
    }

    if (func_8005EC40(arg0, amount) != amount) {
        return -1;
    }

    {
        s32 new_cursor;
        s32 end;
        register s32 ret ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

        new_cursor = D_8007382C.value + amount;
        end = entry->unk14;
        D_8007382C.value = new_cursor;
        ret = marker;
        if (new_cursor < end) {
            ret = -2;
        }
        return ret;
    }
}
