#include "common.h"

/* Builds a scaled tile-position header on the stack from arg0's packed
 * byte/word fields, then hands it plus a computed image-data pointer
 * (arg1->unkC + arg2) to func_8004878C. */
/* Object header this function reads: same tile-dimension shape family as
 * func_8004878C / func_80047270 (a u16 tile-size word at 0x4, plus four
 * packed byte sub-fields at 0x8-0xB used to build a scaled tile-position
 * header on the stack). */
typedef struct {
    u8 pad0[4];
    u16 unk4;
    u8 pad1[2];
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
} S_80048870_hdr;

/* Second argument: a small record whose field at 0xC is a base pointer that
 * gets offset by arg2 to form the image-data pointer for the decode call. */
typedef struct {
    u8 pad0[0xC];
    void *unkC;
} S_80048870_rec;

/* Same shape as S_8004878C_hdr used by the sibling func_8004878C/func_80047270. */
typedef struct {
    s16 unk00;
    s16 unk02;
    s16 unk04;
    s16 unk06;
} S_8004878C_hdr;

extern void func_8004878C(void *a0, S_8004878C_hdr *a1);

void func_80048870(S_80048870_hdr *arg0, S_80048870_rec *arg1, s32 arg2)
{
    S_8004878C_hdr hdr;

    hdr.unk04 = (s16)((arg0->unkA + 1) >> 1);
    hdr.unk06 = (s16)(arg0->unkB + 1);
    hdr.unk00 = (s16)(((u32)arg0->unk8 >> 1) + ((arg0->unk4 << 6) & 0x3C0));
    hdr.unk02 = (s16)(arg0->unk9 + ((arg0->unk4 << 4) & 0x100));
    func_8004878C((void *)((u8 *)arg1->unkC + arg2), &hdr);
}
