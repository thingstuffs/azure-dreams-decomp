#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef void (*Callback3)(void *, void *, s32);
typedef void (*Callback1)(s32);

extern void *D_80016000[];
extern u8 D_80016148[16];
extern u8 D_80016170[16];

s32 func_806D2AB0(s32 *arg0, s32 arg1)
{
    s32 *ptr;
    s32 index;
    s32 offset;

    index = 0;
    if (FIELD(arg0, s32, 8) != 0) {
        ptr = arg0;
loop:
        offset = *ptr;
        if (offset != arg1) {
            ptr += 7;
            index++;
            if (FIELD(ptr, s32, 8) == 0) {
                offset = index * 8;
            } else {
                goto loop;
            }
        } else {
            offset = index * 8;
        }
        if (FIELD((offset - index) * 4 + (u8 *)arg0, s32, 8) == 0) {
            goto notify;
        }
        return index;
    } else {
notify:
        FIELD(FIELD(D_80016000[0], void *, 0x20), Callback3, 0x168)(
            D_80016148, D_80016170, 0x36);
        FIELD(FIELD(D_80016000[0], void *, 0x20), Callback1, 0x174)(1);
    }
    return index;
}
