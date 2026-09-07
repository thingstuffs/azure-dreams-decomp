#include "common.h"

typedef struct {
    s16 unk0;
    s16 unk2;
} S_80013564;

extern S_80013564 D_80013564[];
extern int func_8004A6C0(void);
extern void bzero(void *ptr, int len);

/* Look up an index via func_8004A6C0(); if it's within range (<20), bzero
 * the 19-byte record at fixed address 0x800133E8 + i*19, then zero the
 * two-short D_80013564[i] entry. */
void func_8004A7D8(void)
{
    s32 i = func_8004A6C0();

    if (i < 0x14) {
        bzero((void *)(0x800133E8 + i * 19), 0x13);
        D_80013564[i].unk0 = 0;
        D_80013564[i].unk2 = 0;
    }
}
