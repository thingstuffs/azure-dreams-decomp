#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct {
    u32 words[6];
} Copy24;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
} Vec3u16;

extern void *func_8003FC64(s32 size);
extern void func_8004491C(void *object, void *callback);
extern void func_80047784(void *object, s32 kind, s32 arg2);
extern void *func_8003DE58(void *arg0, void *arg1, Vec3u16 *out, s32 arg3);

extern s32 D_80045340;
extern u8 D_8006CCD8;
extern u8 D_8006CCE8;
extern u8 D_80175978;

void *func_80175D04(void *arg0, Copy24 *input, void *source)
{
    Copy24 local;
    Vec3u16 delta;
    u16 selector;
    s32 table_offset;
    s16 table_value;
    Copy24 *out;
    void *object;
    void *child;
    void *render;

    selector = FIELD(arg0, u16, 0x2A);
    local = *input;
    table_offset = (selector >> 8) & 0xE;

    table_value = *(s16 *)((u8 *)&D_8006CCD8 + table_offset);
    FIELD(&local, u16, 2) +=
        (table_value * FIELD(arg0, s16, 0xB2) * 0x40) +
        (table_value * 0x20);

    table_value = *(s16 *)((u8 *)&D_8006CCE8 + table_offset);
    FIELD(&local, u16, 6) +=
        (table_value * FIELD(arg0, s16, 0xB2) * 0x40) +
        (table_value * 0x20);

    object = func_8003FC64(0x312);
    if (object != 0) {
        FIELD(object, void *, 0x10) = &D_80175978;
        func_8004491C(object, &D_80045340);

        render = FIELD(object, void *, 0xC);
        FIELD(render, s32, 0x28) = FIELD(source, s32, 0x28);
        FIELD(render, s16, 0x1E) = 0x800;
        FIELD(render, s16, 0x1C) = 0x800;
        FIELD(render, u32, 0xC) = 0x00808080;
        FIELD(render, u16, 0x14) |= 0xC;
        FIELD(render, u16, 0x10) |= 0x20;
        func_80047784(render, 0x47, 0);

        child = FIELD(object, void *, 8);
        FIELD(object, Copy24, 0x24) = *input;
        out = (Copy24 *)((u8 *)object + 0x20);

        delta.z = 0;
        delta.y = 0;
        delta.x = 0;
        if (func_8003DE58(FIELD(source, void *, 8), source, &delta, 1) != 0) {
            FIELD(out, u16, 6) += delta.x;
            FIELD(child, u16, 2) = FIELD(out, u16, 6);
            FIELD(out, u16, 0xA) += delta.y;
            FIELD(child, u16, 6) = FIELD(out, u16, 0xA);
            FIELD(out, u16, 0xE) += delta.z;
            FIELD(child, u16, 0xA) = FIELD(out, u16, 0xE);
        }

        FIELD(out, s32, 0x10) =
            ((s32)local.words[0] - FIELD(out, s32, 4)) / 0x20;
        FIELD(out, s32, 0x14) =
            ((s32)local.words[1] - FIELD(out, s32, 8)) / 0x20;

        return object;
    }

    return 0;
}
