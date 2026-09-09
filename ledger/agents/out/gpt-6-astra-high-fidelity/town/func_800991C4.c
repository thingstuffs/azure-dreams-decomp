#include "common.h"

typedef struct Vec3i {
    s32 x;
    s32 y;
    s32 z;
} Vec3i;

typedef struct Record {
    u8 flags;
    u8 pad1;
    s8 scale;
    s8 height;
} Record;

extern void *func_80096A30(void *arg0, s32 arg1, s32 arg2);
extern Record *func_8004CAE8(void *arg0, u32 arg1);
extern s32 func_80064584(s32 angle);
extern s32 func_800644B8(s32 angle);

extern Vec3i D_800D0AE4;
extern Vec3i D_800D0AFC;
extern Vec3i *D_80100D20;

void func_80096924(void *arg0, Vec3i *arg1, void *arg2) {
    Record *record;
    s32 angle;
    s32 x_offset;
    s32 y_offset;
    s32 trig;
    register s32 height ASM_REG("$7"); /* MATCH: Preserve the retail height register after removing the pseudo-call. */

    record = func_8004CAE8(
        func_80096A30(arg2, *(s32 *)((u8 *)arg0 + 0x1C), 4), 0);
    if (record != 0) {
        register Vec3i *out ASM_REG("$6"); /* MATCH: Preserve the retail output register after removing the pseudo-call. */
        s32 base_y;
        s32 input_y;
        register s32 y_value ASM_REG("$4"); /* MATCH: Reuse the page register for the offset after forming the output pointer. */
        u8 *global_page;
        register u8 *out_page ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register u8 *base_page ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

        angle = (*(u16 *)((u8 *)arg0 + 0x10) - 0xC00) & 0xFFF;
        x_offset = (record->scale * func_80064584(angle)) << 5;
        trig = func_800644B8(angle);
        global_page = (u8 *)0x80100000;
        out_page = (u8 *)0x800D0000;
        ASM_KEEP(out_page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        base_page = (u8 *)0x800D0000;
        ASM_KEEP(global_page);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(base_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        y_offset = (-record->scale * trig) << 5;
        height = record->height;

        *(s32 *)(out_page + 0xAFC) = *(s32 *)(base_page + 0xAE4) + arg1->x + x_offset;
        base_page += 0xAE4;
        base_y = *(s32 *)(base_page + 4);
        input_y = *(volatile s32 *)&arg1->y;
        out = (Vec3i *)(out_page + 0xAFC);
        *(Vec3i * volatile *)(global_page + 0xD20) = out;
        y_value = y_offset;
        out->y = base_y + input_y + y_value;
        out->z = *(s32 *)(base_page + 8) + arg1->z + (height << 17);
        return;
    }
    D_80100D20 = 0;
}
