#include "common.h"

extern u8 D_8009DEBC[];
extern u8 D_800D073C[];
extern u8 D_800D0754[];
extern u8 D_800D076C[];
extern u8 D_800D0788[];
extern u8 D_80010000[];
extern u8 T_80010000[];
__asm__(".set D_80010000, 0x80010000");
__asm__(".set T_80010000, 0x80010000");

extern s32 func_8004A658();
extern void func_8008F0D4();
extern void func_8008F104();
extern void func_8009B218();
extern void func_8009DC8C();
extern void func_8009F148();
extern s32 func_8009FF50();
extern u8 D_8009DD40;
extern u8 D_8006E240;

#define BU(p, off) (*(u8 *)((u8 *)(p) + (off)))
#define WD(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define PP(p, off) (*(u8 **)((u8 *)(p) + (off)))
#define TB(idx, off) (D_80010000[(idx) * 4 + (off)])

/* Sets object type fields and selects the corresponding resource. */
void func_8009E504(void *object, s32 index, void *output)
{
    u32 resource;
    u8 mode;
    u8 type;

    mode = BU(object, 0x94);
    if (mode == 0) {
        func_8008F0D4(object, index, D_800D073C);
        func_8009B218(object, index, output, D_800D076C);
        goto store_common;
    }
    if ((s8)mode == -1) {
        func_8008F104(object, index, D_800D073C);
        func_8009B218(object, index, output, 0);
store_common:
        BU(object, 0x4C) = BU(object, 0x95);
        BU(object, 0x4D) = BU(object, 0x96);
    } else {
        func_8008F0D4(object, index, D_800D073C);
        func_8009B218(object, index, output, D_800D0788);
        {
            u8 *type_table;

            type_table = (u8 *)0x80010000;
            BU(object, 0x4C) = type_table[BU(object, 0x95) * 4 + 0x980];
            BU(object, 0x4D) = type_table[BU(object, 0x95) * 4 + 0x981];
            BU(object, 0x4E) = type_table[BU(object, 0x95) * 4 + 0x982];
            BU(object, 0x4F) = type_table[BU(object, 0x95) * 4 + 0x983];
        }
        func_8009F148(object, object, index, output);
    }

    if (func_8009FF50() == 0) {
        resource = (u32)&D_8009DD40;
    } else {
        resource = (u32)D_8009DEBC;
    }
    PP(object, -0x10) = (u8 *)resource;
    ASM_KEEP(resource);
    if ((u32)(BU(object, 0x4D) - 0x12) < 2U) {
        PP(object, 0xC) = D_800D0754;
    }

    type = BU(object, 0x4D);
    if (type == 0x12) {
        resource = (u32)&D_8006E240;
    } else if (type == 0x13) {
        u8 *data_base = (u8 *)0x80010000;

        func_8009DC8C(
            object,
            output,
            BU(object, 0x4C),
            *(s32 *)&data_base[
                ((data_base[BU(object, 0x95) * 4 + 0x983] & 0x3F) * 0x54)
                    + 0xA94]);
        return;
    } else {
        resource = func_8004A658(BU(object, 0x4D), BU(object, 0x4C));
    }
    WD(output, 8) = resource;
}
