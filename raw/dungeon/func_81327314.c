#include "common.h"

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern u8 D_80045340;
extern u8 D_800777B8;
extern u8 D_8016E528;
extern void *D_80174704;
extern s16 D_80174708[16];

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

void func_8016EB14(void)
{
    s32 x;
    s32 y;
    s32 table_y;
    void *root;
    void *source;
    void *owner;
    register void *body ASM_REG("$16");
    register void *object ASM_REG("$17");
    void *part;
    void *target;
    u8 *table;
    u8 *entry;

    root = D_80174704;
    source = FIELD(root, void *, 8);
    owner = (u8 *)root + 0x20;
    object = func_8003FC64(0x12);
    if (object != 0) {
        FIELD(object, void *, 0x10) = &D_8016E528;
        func_8004491C(object, &D_80045340);
        part = FIELD(object, void *, 0xC);
        FIELD(part, u16, 0x14) &= 0xFFF3;
        body = (u8 *)object + 0x20;
        FIELD(body, void *, 0x24) = owner;
        target = FIELD(object, void *, 8);
        FIELD(target, u16, 2) = FIELD(source, u16, 2);
        FIELD(target, u16, 6) = FIELD(source, u16, 6);
        FIELD(target, s16, 0xA) = FIELD(source, u16, 0xA) - 0x20;
#ifdef NON_MATCHING
        table = (u8 *)D_80174708;
#else
        table = (u8 *)0x80170000;
        ASM_KEEP(table);
        table += 0x4708;
#endif
        x = *(s16 *)(u8 *)(((FIELD(owner, u16, 0x2A) >> 7) & 0x1C) +
                           (u32)table);
        FIELD(body, s32, 0x4C) = x << 18;
        table_y = *(s16 *)((u8 *)(((FIELD(owner, u16, 0x2A) >> 7) & 0x1C) +
                                  (u32)table) + 2);
        FIELD(body, s32, 0x54) = 0xFFF80000;
        FIELD(body, s32, 0x60) = 0x14900;
        FIELD(body, s32, 0x50) = table_y << 18;

        FIELD(body, s16, 0x18) = (FIELD(owner, u16, 0x2A) >> 9) & 7;
        part = FIELD(object, void *, 0xC);
        FIELD(part, s16, 0x1E) = 0x1000;
        FIELD(part, s16, 0x1C) = 0x1000;
        ASM_KEEP(table);
        entry = (u8 *)(((FIELD(owner, u16, 0x2A) >> 7) & 0x1C) + (u32)table);
        FIELD(part, s16, 6) = *(s16 *)(entry + 2) * 6;
        FIELD(owner, s16, 0xAA) = 0x4D;

        x = FIELD(source, s16, 2);
        FIELD(body, s8, 0x48) = x / 64;
        y = FIELD(source, s16, 6);
        FIELD(body, s8, 0x49) = y / 64;
        FIELD(part, u8, 0xE) = 0x80;
        FIELD(part, u8, 0xD) = 0x80;
        FIELD(part, u8, 0xC) = 0x80;
        FIELD(part, void *, 8) = &D_800777B8;
        FIELD(body, u8, 0x44) = 0xF;
        FIELD(body, u8, 0x45) = 1;
        FIELD(body, u8, 0x46) = 0;
        FIELD(body, u8, 0x47) = 0;
    }
}
