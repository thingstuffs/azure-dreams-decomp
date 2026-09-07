#include "common.h"

typedef struct S_800B70EC_0 {
    u8 pad_00[0x14];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_800B70EC_0;   /* work in func_800B70EC */



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
    register s32 value ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 threshold;
    register s32 test ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 index;
    s32 offset;
    s32 one;
    s32 size;
    s32 limit;
    register s32 seven ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    u8 *asset;
    u8 *base;
    u8 *work;
    u8 *shared;
    u16 *config;
    register u16 *arg0 ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    u8 *arg1;
    register u8 *entry ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register u8 *table ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

    config = D_80111FA8;
    arg0 = config;
    arg1 = D_80110EC8;
    base = D_80083160;
    work = base + 0x1DC;
    seven = 7;
    limit = 0x7F;
    size = 0x2000;
    ASM_KEEP(config);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ASM_KEEP(arg1);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP4(work, seven, limit, size);   /* MATCH pin: retail immediate-load split depends on it */
    ((S_800B70EC_0 *)work)->unk_14 = seven;
    seven = 7;
    ((S_800B70EC_0 *)work)->unk_16 = seven;
    ((S_800B70EC_0 *)work)->unk_18 = limit;
    ((S_800B70EC_0 *)work)->unk_1C = size;
    ((S_800B70EC_0 *)work)->unk_1A = limit;
    ((S_800B70EC_0 *)work)->unk_1E = size;
    shared = D_80082E60;
    D_80111FA8[0] = 0x328;
    config[1] = 0x80;
    config[2] = 8;
    config[3] = 0x80;
    (*(u16 *)((u8 *)shared + 0x16)) |= 1;
    asset = D_8014F004;
    func_8006733C(arg0, arg1, limit);

    value = D_800D2FB4[D_800D381A[0] << 5];
    ASM_KEEP(value);   /* MATCH pin: keeps a statement from moving across a call/branch */
    one = 1;
    threshold = 0x21;
    if (value != threshold) {
        ASM_KEEP(threshold);   /* MATCH pin: load-bearing for the whole function shape */
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
    ASM_KEEP(offset);   /* MATCH pin: load-bearing for the whole function shape */
    ASM_KEEP(entry);   /* MATCH pin: load-bearing for the whole function shape */
    value = *entry;
    if (value != 0x29) {
        func_80046E38(value, D_8012F004);
    }
}
