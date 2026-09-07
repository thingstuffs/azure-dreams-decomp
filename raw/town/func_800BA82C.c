#include "common.h"

extern void func_800672D8(void *, void *);
extern void *D_800893F8[];
extern u8 D_80110EC8[];
extern u8 D_801110C8[];
extern u8 D_801112C8[];
extern u8 D_801114C8[];
extern u16 D_80111F48[];
extern u16 D_80111F68[];
extern u16 D_80111F88[];

void func_800B7F8C(u16 *arg0)
{
    static void *const keepalive[] = {
        &&L0, &&after_first, &&after_first, &&after_first,
        &&L4, &&after_first, &&after_first, &&after_first,
        &&L8, &&after_first, &&after_first, &&after_first,
        &&L12, &&after_first, &&after_first, &&after_first,
        &&L8, &&after_first, &&after_first, &&after_first,
        &&L4
    };
    register s32 page ASM_REG("$3");
    register s32 page2 ASM_REG("$2");
    register void *rect ASM_REG("$4");
    register void *data ASM_REG("$5");
    register s32 index6 ASM_REG("$4");
    s32 value;
    s32 index24;

    value = *arg0 + 1;
    *arg0 = value;
    if ((s16)value >= 24) {
        *arg0 = 0;
    }

    index24 = (s16)*arg0 % 24;
    if ((u32)index24 >= 21) {
        goto after_first;
    }
    (void)keepalive;
    goto *D_800893F8[index24];

L0:
        page = (s32)0x80110000;
        ASM_KEEP(page);
        rect = (void *)(page + 0x1FA8);
        ASM_KEEP(rect);
        data = D_80110EC8;
        goto first_common;
L4:
        page = (s32)0x80110000;
        ASM_KEEP(page);
        rect = (void *)(page + 0x1FA8);
        ASM_KEEP(rect);
        data = D_801110C8;
        goto first_common;
L8:
        page = (s32)0x80110000;
        ASM_KEEP(page);
        rect = (void *)(page + 0x1FA8);
        ASM_KEEP(rect);
        data = D_801112C8;
        goto first_common;
L12:
        page = (s32)0x80110000;
        ASM_KEEP(page);
        rect = (void *)(page + 0x1FA8);
        ASM_KEEP(rect);
        data = D_801114C8;
        goto first_common;

first_common:
    *(u16 *)(page + 0x1FA8) = 808;
    ((u16 *)rect)[1] = 128;
    ((u16 *)rect)[2] = 8;
    ((u16 *)rect)[3] = 32;
    func_800672D8(rect, data);

after_first:
    index6 = (s16)*arg0 % 6;
    ASM_KEEP(index6);
    switch (index6) {
    case 0:
        page2 = (s32)0x80110000;
        ASM_KEEP(page2);
        rect = (void *)(page2 + 0x1FA8);
        ASM_KEEP(rect);
        data = D_80111F48;
        goto second_common;
    case 2:
        page2 = (s32)0x80110000;
        ASM_KEEP(page2);
        rect = (void *)(page2 + 0x1FA8);
        ASM_KEEP(rect);
        data = D_80111F68;
        goto second_common;
    case 4:
    page2 = (s32)0x80110000;
    ASM_KEEP(page2);
    rect = (void *)(page2 + 0x1FA8);
    ASM_KEEP(rect);
    data = D_80111F88;
        goto second_common;
    default:
        return;
    }

second_common:
    *(u16 *)(page2 + 0x1FA8) = 16;
    ((u16 *)rect)[1] = 449;
    ((u16 *)rect)[2] = 16;
    ((u16 *)rect)[3] = 1;
    func_800672D8(rect, data);
}
