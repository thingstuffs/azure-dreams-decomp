#include "common.h"

/* --- gcc 2.7.2 -O2 -fno-schedule-insns -fno-schedule-insns2 translation unit --- */

typedef struct {
    /* 0x0 */ u8 pad[8];
    /* 0x8 */ s32 unk8;
} UnkStruct491CC;

/* Stores arg1 into offset 0x8 of each struct pointed to by arg0[0..arg2-1]; arg0 is walked as a raw pointer (not indexed), incrementing by one 4-byte slot per iteration. */
void func_800491CC(UnkStruct491CC **arg0, s32 arg1, s32 arg2)
{
    s32 i;
    UnkStruct491CC **p;

    p = arg0;
    i = 0;
    if (arg2 > 0) {
        do {
            UnkStruct491CC *cur = *p;
            i++;
            cur->unk8 = arg1;
            p++;
        } while (i < arg2);
    }
}
