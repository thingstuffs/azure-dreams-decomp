#include "common.h"

typedef struct {
    s16 unk00;
    s16 unk02;
    s16 unk04;
    s16 unk06;
} S_80047270_hdr;

extern void func_80047270(void *a0, S_80047270_hdr *a1);
extern u16 D_80083164[8];
extern u16 D_80081520;
extern u16 D_80081522;
extern u16 D_80081524;
extern u16 D_80081526;

typedef struct {
    u8 pad00[4];
    u16 unk04;
    u8 pad06[2];
    s8 unk08;
    s8 unk09;
    u8 unk0A;
    u8 unk0B;
} S_80047468_arg0;

typedef struct {
    u8 pad00[0xC];
    u8 *unk0C;
} S_80047468_arg1;

void func_80047468(S_80047468_arg0 *arg0, S_80047468_arg1 *arg1, s32 arg2)
{
    int new_var;
    s32 a3;
    u32 a3_u;
    S_80047270_hdr hdr;

    if (D_80083164[0] != D_80081526) {
        D_80081524 = 0;
        D_80081522 = 0;
        D_80081520 = 0;
        D_80081526 = D_80083164[0];
    }
    a3 = (arg0->unk0A + 3) / 4;
    hdr.unk04 = (s16)a3;
    hdr.unk06 = arg0->unk0B + 1;
    if ((D_80081522 + hdr.unk06) >= 0x80) {
        D_80081522 = 0;
        D_80081520 += D_80081524;
    }
    a3_u = (u32)a3;
    if ((D_80081520 + a3) >= 0x20) {
        if (D_80081524) {
            D_80081524 = 0;
            D_80081522 = 0;
            D_80081520 = 0;
        } else {
            D_80081524 = 0;
            D_80081522 = 0;
            D_80081520 = 0;
        }
    }
    if (((u16)D_80081524) < a3_u) {
        D_80081524 = (u16)a3;
    }
    new_var = (D_80081520 + ((arg0->unk04 << 6) & 0x3C0)) + 0x20;
    hdr.unk00 = new_var;
    hdr.unk02 = (D_80081522 + ((arg0->unk04 * 0x10) & 0x100)) + 0x80;
    arg0->unk08 = (s8)((((u8)D_80081520) * 4) - 0x80);
    arg0->unk09 = (s8)(((u8)D_80081522) + 0x80);
    D_80081522 += hdr.unk06;
    func_80047270((void *)(arg1->unk0C + arg2), &hdr);
}
