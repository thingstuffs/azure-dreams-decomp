#include "common.h"

#include "common.h"

typedef struct MainMemoryPage {
    u8 pad_0000[0x20A];
    u16 status_020A;
    u8 pad_020C[0x2D5C - 0x20C];
    s32 word_2D5C;
    u8 pad_2D60[0x2D6C - 0x2D60];
    u8 red_collar_status;
    u8 pad_2D6D[0x3714 - 0x2D6D];
    u16 flags_3714;
} MainMemoryPage;

typedef struct RuntimeFlags {
    u8 pad_00[0x16];
    u16 flags;
} RuntimeFlags;

extern void func_8003AF8C(void *arg0);
extern void func_8008EF58(void);
extern void func_8008FCE0(void);
extern void func_800A03DC(void);
extern void func_80033D44(s32 arg0);
extern void func_8003B42C(s32 arg0);
extern void func_8003B988(void);
extern void func_8003B92C(void);
extern s32 func_80033B2C(s32 arg0);
extern void func_8003BA60(void);
extern void func_8003BA9C(void);
extern void func_8003B9B8(void);
extern void func_8003B9E8(void);
extern void func_8003BA24(void);
extern void func_8008B408(s32 arg0);
extern void func_8008B550(s32 arg0);
extern void func_80041284(void *arg0);
extern void func_800434E4(void);
extern void func_800B9830(void);
extern void func_8003BAF8(void *arg0);
extern void func_8009FF28(void);
extern void func_800B9890(void);
extern void func_800B98B4(void);
extern void func_800C0FA4(void);

extern u8 D_800717D0[0x18];
extern u8 D_800717E8[0x18];
extern s32 D_8006ADBC[3];
extern u8 D_8006AEC4[12];
extern u32 D_80080EA0;
extern RuntimeFlags D_80082E60;

void func_8003B470(void)
{
    u16 flags;
    MainMemoryPage *page;

    func_8003AF8C(D_800717D0);
    func_8003AF8C(D_800717E8);
    func_8008EF58();
    func_8008FCE0();
    func_800A03DC();
    D_8006ADBC[0] = 0;
    func_80033D44(0);

    flags = D_80082E60.flags;
    if (flags & 0x4000) {
        func_8003B42C(0);
        func_8003B988();
        goto block_12;
    }
    if (flags & 0x8000) {
        func_8003B42C(1);
        func_8003B92C();
        if ((func_80033B2C(0x1391) == 0) ||
            (func_80033B2C(0xA2) != 0)) {
            func_8003BA60();
        } else if (func_80033B2C(0xA3) == 0) {
            func_8003BA9C();
        } else {
            goto block_12;
        }
        goto block_14;
    }
    if (flags & 4) {
        goto block_12;
    }
    page = (MainMemoryPage *)0x80010000;
    if (!(flags & 2)) {
        goto block_default;
    }
    page->flags_3714 &= 0xFFFD;
    if (page->status_020A == 0) {
        goto block_13;
    }
    func_8003B42C(1);
    page->status_020A = 0;
    func_8003B9B8();

block_12:
    func_8003B9E8();
    goto block_14;

block_13:
    func_8003BA24();

block_14:
    func_8008B408(1);
    func_8008B550(1);
    func_80041284(&D_80080EA0);
    goto block_final;

block_default:
    func_800434E4();
    page->red_collar_status = 1;
    func_800B9830();
    page->word_2D5C = 0;
    func_8003BAF8(D_8006AEC4);
    func_8008B408(0);
    func_8008B550(0);

block_final:
    D_80082E60.flags &= 0x3FF9;
    func_8009FF28();
    func_800B9890();
    func_800B98B4();
    func_800C0FA4();
}
