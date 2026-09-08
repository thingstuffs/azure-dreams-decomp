#include "common.h"

typedef struct {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    u16 field_A;
    s32 field_C;
    s32 field_10;
    u8 pad14[2];
    s16 field_16;
} UnkStack;

s32 func_800644B8(s32);
s32 func_80064584(s32);
s32 rand(void);
void func_800ABC00(UnkStack *, s16);

void func_80097844(void *arg0, s32 arg1)
{
    UnkStack sp10;
    s32 current;
    s32 count;
    s32 step;
    register s32 dividend ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    if (arg1 != 0) {
        dividend = 0x1000;
        step = dividend / arg1;
        count = 0;
        current = rand();
        sp10.field_16 = -4;
        sp10.field_A = *(u16 *)((u8 *)arg0 + 0xA);
        if (arg1 > 0) {
            do {
                count++;
                sp10.x = (*(u16 *)((u8 *)arg0 + 2) +
                          (rand() & 0x1F)) - 0x10;
                sp10.y = (*(u16 *)((u8 *)arg0 + 6) +
                          (rand() & 0x1F)) - 0x10;
                sp10.field_C = func_80064584(current) << 5;
                sp10.field_10 = func_800644B8(current) << 5;
                func_800ABC00(&sp10, (s16)current);
                current += step;
            } while (count < arg1);
        }
    }
}

/* MECHANISM: A 24-byte record at sp+0x10 forces the 0x40 frame and preserves
   the field stores observed by func_800ABC00; long-lived values yield s3/s2/s4/s1/s0.
   A guarded v0 dividend pin closes the final li/div register pair. */
