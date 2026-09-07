#include "common.h"

extern u8 D_80083160[];

extern s32 func_80065420();
extern s32 func_80066460();
extern void func_80066640();
extern void func_80066690();
extern void func_80067F20();
extern s32 func_80069EF8();

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

s32 func_8182121C(void *arg0)
{
    u16 outputs[3];
    void *outer;
    void *item;
    register s32 next ASM_REG("$4");
    u8 **global;
    u8 *packet0;
    u8 *packet1;
    u32 index;
    register s32 i ASM_REG("$20");
    register u32 low_mask ASM_REG("$19");
    u32 high_mask;
    s32 kind;
    s32 offset;
    u32 *entry;
    u32 entry_value;

    outer = arg0;
    global = (u8 **)D_80083160;
    low_mask = 0x00FFFFFF;
    high_mask = 0xFF000000;

    do {
        item = outer;
        i = 3;
        do {
            packet0 = global[0] + 0x8D0;
            packet0 = *(u8 **)packet0;
            *(u8 **)(global[0] + 0x8D0) = packet0 + 0xC;

            packet1 = *(u8 **)(global[0] + 0x8D0);
            *(u8 **)(global[0] + 0x8D0) = packet1 + 0x14;

            FIELD(packet1, s32, 4) = FIELD(item, s32, 0x48);
            func_80066690(packet1);
            func_80066640(packet1, 1);

            kind = 3;
            if (FIELD(item, s16, 0x54) > 0) {
                kind = 1;
            }
            func_80067F20(packet0, 0, 0,
                func_80066460(0, kind, 0, 0) & 0xFFFF, 0);

            offset = (i * 8) + 0x28;
            index = func_80065420((u8 *)item + offset,
                outputs, &outputs[2], &outputs[2]) - 8;

            FIELD(packet1, s16, 8) = outputs[0] + (func_80069EF8() & 1) + 1;
            FIELD(packet1, s16, 0xA) = outputs[1] + (func_80069EF8() & 1) + 1;
            FIELD(packet1, s16, 0xC) = outputs[0] - (func_80069EF8() & 1) - 1;
            FIELD(packet1, s16, 0xE) = outputs[1] + (func_80069EF8() & 1) + 1;
            FIELD(packet1, s16, 0x10) = outputs[0] + (func_80069EF8() & 4) - 2;
            FIELD(packet1, s16, 0x12) = outputs[1] - (func_80069EF8() & 1) - 1;

            if (index < 0x1E0U) {
                offset = index * 4;
                FIELD(packet1, u32, 0) =
                    (FIELD(packet1, u32, 0) & high_mask) |
                    (((u32 *)(global[0] + 0xB0))[index] & low_mask);
                entry = (u32 *)(offset + (s32) global[0]);
                entry_value = FIELD(entry, u32, 0xB0);
                FIELD(entry, u32, 0xB0) = (entry_value & high_mask) |
                    ((u32)packet1 & low_mask);

                FIELD(packet0, u32, 0) =
                    (FIELD(packet0, u32, 0) & high_mask) |
                    (((u32 *)(global[0] + 0xB0))[index] & low_mask);
                ((u32 *)(global[0] + 0xB0))[index] =
                    (((u32 *)(global[0] + 0xB0))[index] & high_mask) |
                    ((u32)packet0 & low_mask);
            }
            i--;
        } while (i >= 0);

        next = FIELD(outer, s32, -8);
        outer = (void *)(next + 0x20);
    } while (next != 0);

    ASM_KEEP(i);
    ASM_KEEP(low_mask);
    ASM_KEEP(next);
    return 0;
}
