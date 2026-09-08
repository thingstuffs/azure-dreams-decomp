#include "common.h"

extern void func_80025CD8();
extern void func_80025D28();
extern void strcpy();
extern s32 D_80025BF4[];

void func_80025FFC(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    u8 *p = arg0;
    register s32 value2 ASM_REG("$18") = arg2;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 value3 = arg3;

    func_80025CD8(*(s32 *)(p + 0x74));
    func_80025D28(*(s32 *)(p + 0x74) + 0xC);
    *(s32 *)(p + 0x14) = arg1;
    *(s32 *)(p + 0x0C) = value2;
    *(s32 *)(p + 0x18) = arg1 + 0x20;
    *(s32 *)(p + 0x88) = value3;
    strcpy(p + 0x78, value3);
    ASM_KEEP(value2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    *(s32 **)(p - 0x10) = D_80025BF4;
}

/* MECHANISM: Four call-crossing inputs produce the retail 0x28 frame and s0-s3 saves.
   Guarded arg2->$s2 holding fixes the s2/s3 coloring and exact prologue emission order.
   The natural stores then place arg3's 0x88 write in strcpy's delay slot. */
