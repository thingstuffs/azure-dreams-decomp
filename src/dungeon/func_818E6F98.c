#include "common.h"

typedef struct Primitive {
    u32 tag;
    u32 color;
    s16 x0;
    s16 y0;
    u8 u0;
    u8 v0;
    u16 clut;
    s16 x1;
    s16 y1;
    u8 u1;
    u8 v1;
    u16 tpage;
    s16 x2;
    s16 y2;
    u8 u2;
    u8 v2;
    u16 pad1;
    s16 x3;
    s16 y3;
    u8 u3;
    u8 v3;
    u8 pad2[0xE];
} Primitive;

typedef struct DungeonState {
    u8 pad0[0xB0];
    u32 ordering_table[0x208];
    Primitive *next_primitive;
} DungeonState;

typedef union WorkOutput {
    u16 h[4];
    s32 w[2];
} WorkOutput;

extern u8 D_80083160[];
extern void func_800247D4(void) __attribute__((noreturn));
extern s32 func_80065420(void *, void *, void *, void *);
extern s16 func_80066460(s32, s32, s32, s32);
extern s16 func_8006649C(s32, s32);
extern void func_80066640(Primitive *, s32);
extern void func_800666F4(Primitive *);

s32 func_818E6F98(void *arg0, void *arg1)
{
    u16 input[4];
    s16 output0[4];
    WorkOutput output1;
    register u8 *uv_source ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    DungeonState **state_address;
    register s16 *output_base ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register WorkOutput *output1_base ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s16 *output_cursor;
    s32 i;
    u32 ordering_index;
    s32 width;
    Primitive *primitive;
    DungeonState *state;
    DungeonState *table_state;
    s32 uv;
    s32 uv_low;
    s32 uv_high;
    register s32 node ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u16 half_width;
    u16 left_x;
    u32 table_offset;

    state_address = (DungeonState **)D_80083160;
    output_base = output0;
    output1_base = &output1;
    uv_source = arg0;
    input[0] = *(u16 *)((u8 *)arg1 + 2);
    input[1] = *(u16 *)((u8 *)arg1 + 6);
    input[2] = *(u16 *)((u8 *)arg1 + 0xA) - 0x20;
    i = 0;
    output_cursor = output_base;
    do {
        ordering_index =
            func_80065420(input, output_cursor, output1_base, output1_base) - 8;
        output_cursor += 2;
        i++;
        input[2] += 0x40;
    } while (i < 2);

    width = output0[1] - output0[3];
    if (ordering_index < 0x1E0U) {
        state = *state_address;
        primitive = state->next_primitive;
        state->next_primitive = primitive + 1;
        primitive->color = 0x00C0C0C0;
        func_800666F4(primitive);
        func_80066640(primitive, 1);
        primitive->tpage = func_80066460(0, 1, 0x2C0, 0x100);
        primitive->clut = func_8006649C(0x20, 0x1F8);

        output1.w[0] = width >> 1;
        left_x = output0[0];
        half_width = output1.h[0];
        primitive->x0 = primitive->x1 = left_x + half_width;
        primitive->x2 = primitive->x3 = output0[0] - half_width;
        primitive->y0 = primitive->y2 = output0[1];
        primitive->y1 = primitive->y3 = output0[3];

        uv = *(u8 *)(uv_source + 0x52);
        table_offset = ordering_index << 2;
        uv = (uv & 3) << 5;
        uv_low = uv - 0x80;
        uv_high = uv - 0x61;
        primitive->u0 = primitive->u1 = uv_low;
        primitive->u2 = primitive->u3 = uv_high;

        uv = ((s16)*(u16 *)(uv_source + 0x52) >> 2) << 5;
        uv_low = uv - 0x80;
        uv_high = uv - 0x61;
        primitive->v0 = primitive->v2 = uv_low;
        primitive->v1 = primitive->v3 = uv_high;

        table_state = *(DungeonState *volatile *)state_address;
        primitive->tag = (primitive->tag & 0xFF000000) |
                         (*(u32 *)((u8 *)table_state + 0xB0 + table_offset) &
                          0x00FFFFFF);
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        table_state = *(DungeonState *volatile *)state_address;
        *(u32 *)((u8 *)table_state + 0xB0 + table_offset) =
            (*(u32 *)((u8 *)table_state + 0xB0 + table_offset) & 0xFF000000) |
            ((u32)primitive & 0x00FFFFFF);
    }
    ASM_KEEP(output_base);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

    node = *(s32 *)((u8 *)arg0 - 8);
    if (node != 0) {
        s32 callback_state;

        arg0 = (u8 *)node + 0x20;
        callback_state = *(s32 *)(node + 8);
        ASM_USE2(arg0, callback_state);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_800247D4();
    }
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    {
        register s32 zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

        return zero;
    }
}
