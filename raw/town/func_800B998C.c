#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_80046E38();
extern void func_80067014();
extern void func_8006733C();
extern void func_800B73F0();

extern u8 D_80082E60[];
extern u8 D_80083160[];
extern u8 D_800D2FB4[];
extern volatile u8 D_800D381A[];
extern u8 D_80110EC8[];
extern u8 D_801116C8[];
extern u8 D_80111EC8[];
extern u8 D_80111F48[];
extern u16 D_80111FA8[];
extern u8 D_8012F004[];
extern u8 D_8014F004[];

void func_800B70EC(void) {
    register s32 value ASM_REG("$3");
    register s32 threshold ASM_REG("$2");
    register s32 test ASM_REG("$2");
    register s32 index ASM_REG("$2");
    register s32 offset ASM_REG("$2");
    s32 one;
    register s32 size ASM_REG("$3");
    register s32 limit ASM_REG("$6");
    register s32 seven ASM_REG("$2");
    u8 *asset;
    u8 *base;
    u8 *work;
    u8 *shared;
    u16 *config;
    register u16 *arg0 ASM_REG("$4");
    register u8 *arg1 ASM_REG("$5");
    register u8 *entry ASM_REG("$4");
    register u8 *table ASM_REG("$3");

    config = D_80111FA8;
    arg0 = config;
    arg1 = D_80110EC8;
    base = D_80083160;
    work = base + 0x1DC;
    seven = 7;
    limit = 0x7F;
    size = 0x2000;
    ASM_KEEP(config);
    ASM_KEEP(arg1);
    ASM_KEEP4(work, seven, limit, size);
    FIELD(work, s16, 0x14) = seven;
    seven = 7;
    FIELD(work, s16, 0x16) = seven;
    FIELD(work, s16, 0x18) = limit;
    FIELD(work, s16, 0x1C) = size;
    FIELD(work, s16, 0x1A) = limit;
    FIELD(work, s16, 0x1E) = size;
    shared = D_80082E60;
    D_80111FA8[0] = 0x328;
    config[1] = 0x80;
    config[2] = 8;
    config[3] = 0x80;
    FIELD(shared, u16, 0x16) |= 1;
    asset = D_8014F004;
    func_8006733C(arg0, arg1, limit);

    value = D_800D2FB4[D_800D381A[0] << 5];
    ASM_KEEP(value);
    one = 1;
    threshold = 0x21;
    if (value != threshold) {
        ASM_KEEP(threshold);
        if ((s32)value < 0x21) {
            goto common;
        }
        if ((s32)value >= 0x29) {
            goto common;
        }
        test = (s32)value < 0x26;
        if (test) {
            goto common;
        }
        D_80111FA8[0] = 0x330;
        config[1] = 0x80;
        config[2] = 8;
        config[3] = 0x80;
        func_8006733C(config, D_801116C8);
        D_80111FA8[0] = 0;
        config[1] = 0x1FB;
        config[2] = 0x40;
        config[3] = one;
        func_8006733C(config, D_80111EC8);
    } else {
        D_80111FA8[0] = 0x10;
        config[1] = 0x1C1;
        config[2] = 0x30;
        config[3] = one;
        func_8006733C(config, D_80111F48);
    }

common:
    func_80067014(0);
    *(void **)work = asset;
    func_800B73F0(asset);
    table = D_800D2FB4;
    index = D_800D381A[0];
    offset = index << 5;
    entry = table + offset;
    ASM_KEEP(offset);
    ASM_KEEP(entry);
    value = *entry;
    ASM_KEEP(value);
    if (value != 0x29) {
        func_80046E38(value, D_8012F004);
    }
}
