#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct Palette {
    s32 value[5];
} Palette;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);

extern Palette D_800201B4;
extern u8 D_80023FA8[];
extern u8 D_80044BB0[];

void func_80956E6C(s32 arg0, s32 arg1, void *arg2, s32 arg3)
{
    Palette palette;
    register s32 *palette_ptr ASM_REG("$17");
    register u16 value ASM_REG("$2");
    u32 color;
    s32 palette_value;
    void *object;
    void *position;
    void *position2;
    void *primitive;

    palette = D_800201B4;
    object = func_8003FC64(0x15);
    if (object != 0) {
        palette_ptr = palette.value;
        FIELD(object, void *, 0x10) = D_80023FA8;
        func_8004491C(object, D_80044BB0);

        primitive = FIELD(object, void *, 0xC);
        value = arg0;
        position = FIELD(object, void *, 8);
        if (arg0 < 0) {
            ASM_KEEP(value);
            value = -value;
        }
        FIELD(position, s16, 2) = value;
        value = 0x80;
        position2 = FIELD(object, void *, 8);
        FIELD(position2, s16, 6) = value;

        FIELD(primitive, s16, 0x10) = 0x60;
        FIELD(primitive, u16, 0x14) |= 0xC;

        value = FIELD(arg2, u16, 0x48);
        object = (u8 *)object + 0x20;
        if (arg0 < 0) {
            value = -value;
        }
        FIELD(primitive, u16, 0x1A) = value;
        FIELD(object, s16, 8) = arg3;

        value = FIELD(arg2, u16, 0x4A);
        ASM_KEEP(value);
        color = 0xC0C0C0;
        FIELD(primitive, u16, 0x1E) = value;
        FIELD(primitive, u16, 0x1C) = value;
        palette_value = palette_ptr[arg1];
        FIELD(primitive, s8, 4) = 0;
        FIELD(primitive, s8, 5) = 0;
        FIELD(primitive, s32, 0xC) = color;
        FIELD(primitive, s32, 8) = palette_value;
        ASM_KEEP(palette_ptr);
    }
}

/* MECHANISM: A 20-byte Palette local produces the 0x48 frame and five-word stack copy.
   Guarded s1 table-base and v0 value roles reproduce the saved set and temporary coloring.
   Split position, palette-value, and color live ranges place both load-delay fillers exactly. */
