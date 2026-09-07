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

void func_801685CC(void *arg0, void *arg1, s32 arg2, s32 arg3, u16 arg4)
{
    register u8 *copy_src ASM_REG("$6");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register u8 *copy_dst ASM_REG("$7");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register u8 *copy_end;
    register u32 copy0;
    register u32 copy1;
    register u32 copy2;
    register u32 copy3;
    register void *held_arg0 ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    LocalPositionTable positions;
    void *obj;
    u8 *part;
    void *render;
    register void *dest ASM_REG("$3");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 mode;
    register s32 neg_one ASM_REG("$3");   /* MATCH pin: retail schedule: same instructions, different order without it */
    u32 sixty;
    register void *callback_obj ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 table_offset ASM_REG("$5");   /* MATCH pin: keeps a constant in a register as retail does */
    register u8 *position_base ASM_REG("$6");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 table_index ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    void *callback_data;
    s32 third_direction;
    register void *db_render ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    void *db_data;
    u8 *copy_src_init;
    s32 src_misalignment;
    s32 temp_a0_2;
    s32 var_a2_2;
    s32 var_t0;
    s32 var_t2;
    s32 var_t3;
    register s32 var_t4 ASM_REG("$12");   /* MATCH pin: load-bearing for the whole function shape */
    s32 var_t5;
    u16 *var_a3_2;
    u16 temp_a1_4;
    u8 *var_t1;
    u8 *out_base;
    register s32 out_index ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

    copy_dst = (u8 *)&positions;
    copy_src_init = (u8 *)&D_8016484C;
    src_misalignment = (s32)copy_src_init & 3;
    held_arg0 = arg0;
    if (src_misalignment) {
        copy_src = copy_src_init;
        copy_end = copy_src + 0x90;
        do {
            copy0 = ((PackedCopy16 *)copy_src)->words[0];
            copy1 = ((PackedCopy16 *)copy_src)->words[1];
            copy2 = ((PackedCopy16 *)copy_src)->words[2];
            copy3 = ((PackedCopy16 *)copy_src)->words[3];
            ((PackedCopy16 *)copy_dst)->words[0] = copy0;
            ((PackedCopy16 *)copy_dst)->words[1] = copy1;
            ((PackedCopy16 *)copy_dst)->words[2] = copy2;
            ((PackedCopy16 *)copy_dst)->words[3] = copy3;
            ASM_KEEP(copy0);   /* MATCH pin: retail register colouring depends on it */
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
        copy0 = ((Copy16 *)copy_src)->words[0];
        copy1 = ((Copy16 *)copy_src)->words[1];
        copy2 = ((Copy16 *)copy_src)->words[2];
        copy3 = ((Copy16 *)copy_src)->words[3];
        ((Copy16 *)copy_dst)->words[0] = copy0;
        ((Copy16 *)copy_dst)->words[1] = copy1;
        ((Copy16 *)copy_dst)->words[2] = copy2;
        ((Copy16 *)copy_dst)->words[3] = copy3;
        ASM_KEEP(copy0);   /* MATCH pin: retail register colouring depends on it */
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
        U16_AT(part, 0x1C) = arg4;
        S32_AT(part, 0x24) = arg3;
        PTR_AT(obj, 0x10) = D_80167C74;
        func_8004491C(callback_obj, callback_data);

        render = PTR_AT(obj, 0xC);
        sixty = 0x60;
        S16_AT(render, 0x10) = sixty;
        U16_AT(render, 0x14) |= 0x8C;

        dest = PTR_AT(obj, 8);
        S32_AT(dest, 0) = S32_AT(arg1, 0);
        S32_AT(dest, 4) = S32_AT(arg1, 4);
        S32_AT(dest, 8) = S32_AT(arg1, 8);

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
        U8_AT(render, 0xE) = sixty;
        U8_AT(render, 0xD) = sixty;
        U8_AT(render, 0xC) = sixty;

        mode = (s16)arg4;
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
            ((U16_AT(held_arg0, 0x2A) >> 9) & 7) * 0x12;
        table_index = table_offset + table_index;
        table_index = (s32)position_base + table_index;
        S32_AT(part, 0x5C) =
            *(s16 *)table_index * 0x50000;
        table_index =
            ((U16_AT(held_arg0, 0x2A) >> 9) & 7) * 0x12;
        table_index = table_offset + table_index;
        table_index = (s32)position_base + table_index;
        S32_AT(part, 0x60) =
            S16_AT((u8 *)table_index, 2) * 0x50000;
        db_render = render;
        third_direction = U16_AT(held_arg0, 0x2A) >> 9;
        third_direction &= 7;
        table_offset +=
            ((third_direction << 3) + third_direction) << 1;
        position_base += table_offset;
        ASM_KEEP(held_arg0);   /* MATCH pin: retail schedule: same instructions, different order without it */
        db_data = D_800DEAE0;
        S32_AT(part, 0x64) =
            S16_AT(position_base, 4) << 19;
        func_8003DB94(db_render, db_data, 0, render);

        var_t5 = 0;
        out_base = D_80175DD8;
        var_t3 = var_t5;
        do {
            var_t2 = 0;
            var_t1 = part;
            var_t0 = 0;
loop_16:
            var_a2_2 = 0;
            var_t4 = var_t0;
            var_a3_2 = (u16 *)(var_t1 + 0x74);
loop_17:
            temp_a1_4 = *var_a3_2++;
            temp_a0_2 = var_a2_2 * 2;
            var_a2_2 += 1;
            out_index =
                (s16)S16_AT(part, 0x1C) * 0x60;
            out_index = out_index + (s32)out_base;
            out_index = var_t3 + out_index;
            out_index = var_t4 + out_index;
            *(u16 *)(temp_a0_2 + out_index) = temp_a1_4;
            if (var_a2_2 < 3) {
                goto loop_17;
            }
            var_t1 += 6;
            var_t2 += 1;
            var_t0 += 6;
            if (var_t2 < 2) {
                goto loop_16;
            }
            var_t5 += 1;
            var_t3 += 0xC;
        } while (var_t5 < 8);
        ASM_KEEP(part);   /* MATCH pin: retail register colouring depends on it */
    }

    (void)arg2;
}
