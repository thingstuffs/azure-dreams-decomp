#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(void **)((u8 *)(p) + (o)))
#define VS16_AT(p, o) (*(volatile s16 *)((u8 *)(p) + (o)))
#define VPTR_AT(p, o) (*(void * volatile *)((u8 *)(p) + (o)))
#define S16_REV_AT(o, p) (*(s16 *)&((p)[(o)]))

typedef struct {
    s16 values[8][3][3];
} LocalPositionTable;

typedef struct {
    u32 words[4];
} Copy16;

typedef struct {
    u32 words[4];
} __attribute__((packed)) PackedCopy16;

extern void func_8003DB94(void *, void *, s32, void *);
extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);

extern u8 D_80045340;
extern u8 D_800DEAE0[];
extern LocalPositionTable D_8016484C;
extern u8 D_80167C74[];
extern u8 D_80175DD8[];

/* Creates a color-coded effect with direction-based offsets and initializes its vertex buffer. */
void func_801685CC(void *source_obj, void *origin, s32 unused, s32 effect_param, u16 color_mode)
{
    register u8 *copy_src ASM_REG("$6");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register u8 *copy_dst ASM_REG("$7");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register u8 *copy_end;
    register u32 copy_word_0;
    register u32 copy_word_1;
    register u32 copy_word_2;
    register u32 copy_word_3;
    register void *held_source ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    LocalPositionTable positions;
    void *obj;
    u8 *part;
    void *render;
    register void *effect_pos ASM_REG("$3");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 mode;
    register s32 neg_one ASM_REG("$3");   /* MATCH pin: retail schedule: same instructions, different order without it */
    u32 base_intensity;
    register void *callback_obj ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 table_offset ASM_REG("$5");   /* MATCH pin: keeps a constant in a register as retail does */
    register u8 *position_base ASM_REG("$6");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 table_index ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    void *callback_data;
    s32 direction;
    register void *db_render ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    void *db_data;
    u8 *copy_src_init;
    s32 src_misalignment;
    s32 coord_offset;
    s32 coord_index;
    s32 vertex_offset;
    s32 vertex_index;
    s32 pair_offset;
    register s32 held_vertex_offset ASM_REG("$12");   /* MATCH pin: load-bearing for the whole function shape */
    s32 pair_index;
    u16 *coord_src;
    u16 coord_value;
    u8 *vertex_base;
    u8 *out_base;
    register s32 out_index ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

    copy_dst = (u8 *)&positions;
    copy_src_init = (u8 *)&D_8016484C;
    src_misalignment = (s32)copy_src_init & 3;
    held_source = source_obj;
    if (src_misalignment) {
        copy_src = copy_src_init;
        copy_end = copy_src + 0x90;
        do {
            copy_word_0 = ((PackedCopy16 *)copy_src)->words[0];
            copy_word_1 = ((PackedCopy16 *)copy_src)->words[1];
            copy_word_2 = ((PackedCopy16 *)copy_src)->words[2];
            copy_word_3 = ((PackedCopy16 *)copy_src)->words[3];
            ((PackedCopy16 *)copy_dst)->words[0] = copy_word_0;
            ((PackedCopy16 *)copy_dst)->words[1] = copy_word_1;
            ((PackedCopy16 *)copy_dst)->words[2] = copy_word_2;
            ((PackedCopy16 *)copy_dst)->words[3] = copy_word_3;
            ASM_KEEP(copy_word_0);   /* MATCH pin: retail register colouring depends on it */
               /* MATCH pin: retail register colouring depends on it */
            copy_src += 0x10;
            copy_dst += 0x10;
        } while (copy_src != copy_end);
        goto copy_done;
    }
    ASM_KEEP_NV(copy_src_init);   /* MATCH pin: retail schedule: same instructions, different order without it */
    copy_src = copy_src_init;
    copy_end = copy_src + 0x90;
    do {
        copy_word_0 = ((Copy16 *)copy_src)->words[0];
        copy_word_1 = ((Copy16 *)copy_src)->words[1];
        copy_word_2 = ((Copy16 *)copy_src)->words[2];
        copy_word_3 = ((Copy16 *)copy_src)->words[3];
        ((Copy16 *)copy_dst)->words[0] = copy_word_0;
        ((Copy16 *)copy_dst)->words[1] = copy_word_1;
        ((Copy16 *)copy_dst)->words[2] = copy_word_2;
        ((Copy16 *)copy_dst)->words[3] = copy_word_3;
        ASM_KEEP(copy_word_0);   /* MATCH pin: retail register colouring depends on it */
           /* MATCH pin: retail register colouring depends on it */
        copy_src += 0x10;
        copy_dst += 0x10;
    } while (copy_src != copy_end);
copy_done:
    obj = func_8003FC64(0x212);
    callback_obj = obj;
    if (obj != NULL) {
        callback_data = &D_80045340;
        ASM_KEEP(callback_data);   /* MATCH pin: retail schedule: same instructions, different order without it */
        part = (u8 *)obj + 0x20;
        S16_AT(part, 0x18) = 0x50;
        S16_AT(part, 0x1A) = 0x50;
        U16_AT(part, 0x1C) = color_mode;
        S32_AT(part, 0x24) = effect_param;
        PTR_AT(obj, 0x10) = D_80167C74;
        func_8004491C(callback_obj, callback_data);

        render = PTR_AT(obj, 0xC);
        base_intensity = 0x60;
        S16_AT(render, 0x10) = base_intensity;
        U16_AT(render, 0x14) |= 0x8C;

        effect_pos = PTR_AT(obj, 8);
        S32_AT(effect_pos, 0) = S32_AT(origin, 0);
        S32_AT(effect_pos, 4) = S32_AT(origin, 4);
        S32_AT(effect_pos, 8) = S32_AT(origin, 8);

        neg_one = -1;
        VS16_AT(part, 0x7A) = 1;
        VS16_AT(part, 0x86) = 1;
        VS16_AT(part, 0x74) = neg_one;
        VS16_AT(part, 0x80) = neg_one;
        VS16_AT(part, 0x78) = -0x14;
        VS16_AT(part, 0x7E) = -0x14;
        VS16_AT(part, 0x84) = -0x14;
        VS16_AT(part, 0x8A) = -0x14;

        render = VPTR_AT(obj, 0xC);
        VS16_AT(render, 0x1E) = 0x1000;
        VS16_AT(render, 0x1C) = 0x1000;
        U8_AT(render, 0xE) = base_intensity;
        U8_AT(render, 0xD) = base_intensity;
        U8_AT(render, 0xC) = base_intensity;

        mode = (s16)color_mode;
        if (mode == 0) {
            U8_AT(render, 0xC) = 0xC0;
        }
        if (mode == 1) {
            U8_AT(render, 0xD) = 0xC0;
        }
        if (mode == 2) {
            U8_AT(render, 0xE) = 0xC0;
        }

        table_offset = mode * 6;
        position_base = (u8 *)&positions;
        table_index =
            ((U16_AT(held_source, 0x2A) >> 9) & 7) * 0x12;
        table_index = table_offset + table_index;
        table_index = (s32)position_base + table_index;
        S32_AT(part, 0x5C) =
            *(s16 *)table_index * 0x50000;
        table_index =
            ((U16_AT(held_source, 0x2A) >> 9) & 7) * 0x12;
        table_index = table_offset + table_index;
        table_index = (s32)position_base + table_index;
        S32_AT(part, 0x60) =
            S16_AT((u8 *)table_index, 2) * 0x50000;
        db_render = render;
        direction = U16_AT(held_source, 0x2A) >> 9;
        direction &= 7;
        table_offset +=
            ((direction << 3) + direction) << 1;
        position_base += table_offset;
        ASM_KEEP(held_source);   /* MATCH pin: retail schedule: same instructions, different order without it */
        db_data = D_800DEAE0;
        S32_AT(part, 0x64) =
            S16_AT(position_base, 4) << 19;
        func_8003DB94(db_render, db_data, 0, render);

        pair_index = 0;
        out_base = D_80175DD8;
        pair_offset = pair_index;
        do {
            vertex_index = 0;
            vertex_base = part;
            vertex_offset = 0;
copy_vertex:
            coord_index = 0;
            held_vertex_offset = vertex_offset;
            coord_src = (u16 *)(vertex_base + 0x74);
copy_coord:
            coord_value = *coord_src++;
            coord_offset = coord_index * 2;
            coord_index += 1;
            out_index =
                (s16)S16_AT(part, 0x1C) * 0x60;
            out_index = out_index + (s32)out_base;
            out_index = pair_offset + out_index;
            out_index = held_vertex_offset + out_index;
            *(u16 *)(coord_offset + out_index) = coord_value;
            if (coord_index < 3) {
                goto copy_coord;
            }
            vertex_base += 6;
            vertex_index += 1;
            vertex_offset += 6;
            if (vertex_index < 2) {
                goto copy_vertex;
            }
            pair_index += 1;
            pair_offset += 0xC;
        } while (pair_index < 8);
        ASM_KEEP(part);   /* MATCH pin: retail register colouring depends on it */
    }

    (void)unused;
}
