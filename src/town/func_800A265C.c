#include "common.h"

extern u32 func_800B28A0(void);
extern void func_8009FD68(void *arg0);
extern void func_80033AA8(s32 arg0);
extern s32 D_800D0728[];
extern s16 D_800D253C[];

void func_8009FDBC(void) {
    s32 count;
    s32 i;
    s16 *sound;
    u8 *entry;
    u8 state;

    count = D_800D0728[func_800B28A0()];
    do { i = 0; } while (0);
    if (count > 0) {
        sound = D_800D253C;
        entry = (u8 *)0x80010000;
loop:
        state = entry[0x981];
        if (state != 0) {
            if (state == 19) {
                func_8009FD68((void *)(0x80010A80 + ((entry[0x983] & 0x3F) * 84)));
                func_80033AA8(*sound);
            }
        }
        sound++;
        i++;
        entry += 4;
        if (i < count) {
            goto loop;
        }
    }
}

/* MECHANISM: A literal 0x80010000 loop base emits retail's single lui $s0 instead of
   the symbolic zero-offset alias's lui/addiu pair, removing the extra word and
   collapsing the downstream blez displacement while preserving the seed's frame and CFG. */
