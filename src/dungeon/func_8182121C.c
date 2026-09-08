#include "common.h"

typedef struct S_8182121C_0 {
    u32 unk_00;
    s32 unk_04;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
} S_8182121C_0;   /* packet1 in func_8182121C */

typedef struct S_8182121C_1 {
    u8 pad_00[0x48];
    s32 unk_48;
    u8 pad_4C[0x8];
    s16 unk_54;
} S_8182121C_1;   /* item in func_8182121C */

typedef struct S_8182121C_2 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} S_8182121C_2;   /* entry in func_8182121C */

typedef struct S_8182121C_3 {
    u32 unk_00;
} S_8182121C_3;   /* packet0 in func_8182121C */

typedef struct S_8182121C_4_pre {
    s32 unk_00;
    u8 pad_04[0x4];
} S_8182121C_4_pre;   /* the 0x8 bytes before outer in func_8182121C, addressed as outer[-1] */


extern u8 D_80083160[];

extern s32 func_80065420();
extern s32 func_80066460();
extern void func_80066640();
extern void func_80066690();
extern void func_80067F20();
extern s32 func_80069EF8();


s32 func_8182121C(void *arg0)
{
    u16 outputs[3];
    void *outer;
    void *item;
    register s32 next ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 **global;
    u8 *packet0;
    u8 *packet1;
    u32 index;
    s32 i;
    register u32 low_mask ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
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

            ((S_8182121C_0 *)packet1)->unk_04 = ((S_8182121C_1 *)item)->unk_48;
            func_80066690(packet1);
            func_80066640(packet1, 1);

            kind = 3;
            if (((S_8182121C_1 *)item)->unk_54 > 0) {
                kind = 1;
            }
            func_80067F20(packet0, 0, 0,
                func_80066460(0, kind, 0, 0) & 0xFFFF, 0);

            offset = (i * 8) + 0x28;
            index = func_80065420((u8 *)item + offset,
                outputs, &outputs[2], &outputs[2]) - 8;

            ((S_8182121C_0 *)packet1)->unk_08 = outputs[0] + (func_80069EF8() & 1) + 1;
            ((S_8182121C_0 *)packet1)->unk_0A = outputs[1] + (func_80069EF8() & 1) + 1;
            ((S_8182121C_0 *)packet1)->unk_0C = outputs[0] - (func_80069EF8() & 1) - 1;
            ((S_8182121C_0 *)packet1)->unk_0E = outputs[1] + (func_80069EF8() & 1) + 1;
            ((S_8182121C_0 *)packet1)->unk_10 = outputs[0] + (func_80069EF8() & 4) - 2;
            ((S_8182121C_0 *)packet1)->unk_12 = outputs[1] - (func_80069EF8() & 1) - 1;

            if (index < 0x1E0U) {
                offset = index * 4;
                (*(u32 *)((u8 *)packet1 + 0)) =
                    (((S_8182121C_0 *)packet1)->unk_00 & high_mask) |
                    (((u32 *)(global[0] + 0xB0))[index] & low_mask);
                entry = (u32 *)(offset + (s32) global[0]);
                entry_value = ((S_8182121C_2 *)entry)->unk_B0;
                (*(u32 *)((u8 *)entry + 0xB0)) = (entry_value & high_mask) |
                    ((u32)packet1 & low_mask);

                (*(u32 *)((u8 *)packet0 + 0)) =
                    (((S_8182121C_3 *)packet0)->unk_00 & high_mask) |
                    (((u32 *)(global[0] + 0xB0))[index] & low_mask);
                ((u32 *)(global[0] + 0xB0))[index] =
                    (((u32 *)(global[0] + 0xB0))[index] & high_mask) |
                    ((u32)packet0 & low_mask);
            }
            i--;
        } while (i >= 0);

        next = ((S_8182121C_4_pre *)outer)[-1].unk_00;
        outer = (void *)(next + 0x20);
    } while (next != 0);

    ASM_KEEP(next);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    return 0;
}
