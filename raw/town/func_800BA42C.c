#include "common.h"

extern u16 D_80111FA8[];
extern u8 D_80110EC8[];
extern u8 D_801110C8[];
extern u8 D_801112C8[];
extern u8 D_801114C8[];
extern u8 D_801116C8[];
extern u8 D_801118C8[];
extern u8 D_80111AC8[];
extern u8 D_80111CC8[];
extern u8 D_80111EC8[];
extern u8 D_80111EE8[];
extern u8 D_80111F08[];
extern u8 D_80111F28[];
extern void *D_80089348[];

extern void func_800672D8();

void func_800B7B8C(u16 *arg0, s32 arg1, s32 arg2) {
    u16 value;
    s16 index;
    s32 switch_index;
    s32 page3;
    register s32 page ASM_REG("$3");
    register s16 *rect ASM_REG("$4");
    register u8 *pixels ASM_REG("$5");
    register s32 eight ASM_REG("$6");
    static void *const keepalive[] = { &&L0, &&L4, &&L8, &&L12 };

    value = *arg0 + 1;
    *arg0 = value;
    if ((s16)value >= 48) {
        *arg0 = 0;
    }

    index = *(s16 *)arg0 % 24;
    switch_index = index;
    if ((u32)switch_index >= 21) {
        goto Lafter_first;
    }
    goto *D_80089348[switch_index];

L0:
    page = 0x80110000;
    ASM_KEEP(page);
    rect = (s16 *)(page + 0x1FA8);
    ASM_KEEP(rect);
    pixels = D_80110EC8;
    goto Lfirst_common;

L4:
    page = 0x80110000;
    ASM_KEEP(page);
    rect = (s16 *)(page + 0x1FA8);
    ASM_KEEP(rect);
    pixels = D_801110C8;
    goto Lfirst_common;

L8:
    page = 0x80110000;
    ASM_KEEP(page);
    rect = (s16 *)(page + 0x1FA8);
    ASM_KEEP(rect);
    pixels = D_801112C8;
    goto Lfirst_common;

L12:
    page = 0x80110000;
    ASM_KEEP(page);
    rect = (s16 *)(page + 0x1FA8);
    ASM_KEEP(rect);
    pixels = D_801114C8;

Lfirst_common:
    *(s16 *)(page + 0x1FA8) = 0x328;
    rect[1] = 0x80;
    rect[2] = 8;
    rect[3] = 0x20;
    func_800672D8(rect, pixels, arg2);

Lafter_first:
    index = *(s16 *)arg0 % 16;
    if (index == 4) {
        goto Lsecond_4;
    }
    if (index < 5) {
        if (index == 0) {
            goto Lsecond_0;
        }
        goto Lafter_second;
    }
    eight = 8;
    if (index == eight) {
        goto Lsecond_8;
    }
    if (index == 12) {
        goto Lsecond_12;
    }
    goto Lafter_second;

Lsecond_0:
    page = 0x80110000;
    ASM_KEEP(page);
    rect = (s16 *)(page + 0x1FA8);
    ASM_KEEP(rect);
    pixels = D_801116C8;
    ASM_KEEP(page);
    *(volatile s16 *)(page + 0x1FA8) = 0x330;
    ASM_KEEP(page);
    ((volatile s16 *)rect)[1] = 0x80;
    ASM_KEEP(rect);
    ((volatile s16 *)rect)[2] = 8;
    ASM_KEEP(rect);
    goto Lsecond_tail;

Lsecond_4:
    pixels = (u8 *)0x80110000;
    ASM_KEEP(pixels);
    page = 0x80110000;
    ASM_KEEP(page);
    rect = (s16 *)(page + 0x1FA8);
    ASM_KEEP(rect);
    pixels += 0x18C8;
    *(s16 *)(page + 0x1FA8) = 0x330;
    rect[1] = 0x80;
    rect[2] = 8;
    ASM_KEEP(rect);
    goto Lsecond_tail;

Lsecond_8:
    pixels = (u8 *)0x80110000;
    ASM_KEEP(pixels);
    page = 0x80110000;
    ASM_KEEP(page);
    rect = (s16 *)(page + 0x1FA8);
    ASM_KEEP(rect);
    pixels += 0x1AC8;
    goto Lsecond_common;

Lsecond_12:
    page = 0x80110000;
    ASM_KEEP(page);
    rect = (s16 *)(page + 0x1FA8);
    ASM_KEEP(rect);
    pixels = D_80111CC8;

Lsecond_common:
    *(s16 *)(page + 0x1FA8) = 0x330;
    rect[1] = 0x80;
    {
        register s32 common_tail ASM_REG("$2");
        common_tail = 0x20;
        rect[2] = eight;
        rect[3] = common_tail;
        func_800672D8(rect, pixels);
    }
    goto Lafter_second;

Lsecond_tail:
    rect[3] = 0x20;
    func_800672D8(rect, pixels);

Lafter_second:
    index = *(s16 *)arg0 % 8;
    if (index == 2) {
        goto Lthird_2;
    }
    if (index < 3) {
        if (index == 0) {
            goto Lthird_0;
        }
        return;
    }
    if (index == 4) {
        goto Lthird_4;
    }
    if (index == 6) {
        goto Lthird_6;
    }
    return;

Lthird_0:
    page3 = 0x80110000;
    ASM_KEEP(page3);
    rect = (s16 *)(page3 + 0x1FA8);
    ASM_KEEP(rect);
    pixels = D_80111EC8;
    goto Lthird_common;

Lthird_2:
    page3 = 0x80110000;
    ASM_KEEP(page3);
    rect = (s16 *)(page3 + 0x1FA8);
    ASM_KEEP(rect);
    pixels = D_80111EE8;
    goto Lthird_common;

Lthird_4:
    page3 = 0x80110000;
    ASM_KEEP(page3);
    rect = (s16 *)(page3 + 0x1FA8);
    ASM_KEEP(rect);
    pixels = D_80111F08;
    goto Lthird_common;

Lthird_6:
    page3 = 0x80110000;
    ASM_KEEP(page3);
    rect = (s16 *)(page3 + 0x1FA8);
    ASM_KEEP(rect);
    pixels = D_80111F28;

Lthird_common:
    *(s16 *)(page3 + 0x1FA8) = 0;
    rect[1] = 0x1FB;
    rect[2] = 0x10;
    rect[3] = 1;
    func_800672D8(rect, pixels);
}
