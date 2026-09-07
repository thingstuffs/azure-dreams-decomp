#include "common.h"

typedef struct {
    u8 pad0[0xC];
    u16 field_C;
    u16 padE;
} S_8005EB78_VoiceSlot;

typedef struct {
    S_8005EB78_VoiceSlot *ptr;
    u32 pad[2];
} S_8005EB78_79958;

extern S_8005EB78_79958 D_80079958;
extern s32 D_800794F0[3];

/* Returns the active/key-on state for the first voice selected in arg0. */
s32 func_8005EB78(s32 arg0)
{
    s32 voice;
    s32 one;
    s32 i;
    s32 ret;
    u16 value;

    voice = -1;
    i = 0;
    one = 1;
    while (i < 24) {
        if ((arg0 & (one << i)) != 0) {
            goto found;
        }
        i++;
    }

after_loop:
    ret = -1;
    if (voice != ret) {
        goto has_voice;
    }
    return ret;

found:
    voice = i;
    goto after_loop;

has_voice:
    arg0 = voice << 4;
    ret = (s32)D_80079958.ptr;
    i = D_800794F0[0];
    arg0 = arg0 + ret;
    ret = 1;
    ret = ret << voice;
    i = i & ret;
    value = *(u16 *)(arg0 + 0xC);
    if (i != 0) {
        if (value != 0) {
            return 1;
        }
        return 3;
    }

    return value != 0 ? 2 : 0;
}
