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

/* Queues a textured quad at the supplied world position. */
s32 func_818E6F98(void *sprite_data, void *position)
{
    u16 world_pos[4];
    s16 screen_points[4];
    WorkOutput scratch;
    register u8 *uv_source ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    DungeonState **state_address;
    register s16 *screen_base ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register WorkOutput *scratch_base ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s16 *screen_cursor;
    s32 point_index;
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
    u16 center_x;
    u32 table_offset;

    state_address = (DungeonState **)D_80083160;
    screen_base = screen_points;
    scratch_base = &scratch;
    uv_source = sprite_data;
    world_pos[0] = *(u16 *)((u8 *)position + 2);
    world_pos[1] = *(u16 *)((u8 *)position + 6);
    world_pos[2] = *(u16 *)((u8 *)position + 0xA) - 0x20;
    point_index = 0;
    screen_cursor = screen_base;
    do {
        ordering_index =
            func_80065420(world_pos, screen_cursor, scratch_base, scratch_base) - 8;
        screen_cursor += 2;
        point_index++;
        world_pos[2] += 0x40;
    } while (point_index < 2);

    width = screen_points[1] - screen_points[3];
    if (ordering_index < 0x1E0U) {
        state = *state_address;
        primitive = state->next_primitive;
        state->next_primitive = primitive + 1;
        primitive->color = 0x00C0C0C0;
        func_800666F4(primitive);
        func_80066640(primitive, 1);
        primitive->tpage = func_80066460(0, 1, 0x2C0, 0x100);
        primitive->clut = func_8006649C(0x20, 0x1F8);

        scratch.w[0] = width >> 1;
        center_x = screen_points[0];
        half_width = scratch.h[0];
        primitive->x0 = primitive->x1 = center_x + half_width;
        primitive->x2 = primitive->x3 = screen_points[0] - half_width;
        primitive->y0 = primitive->y2 = screen_points[1];
        primitive->y1 = primitive->y3 = screen_points[3];

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
    ASM_KEEP(screen_base);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

    node = *(s32 *)((u8 *)sprite_data - 8);
    if (node != 0) {
        s32 callback_state;

        sprite_data = (u8 *)node + 0x20;
        callback_state = *(s32 *)(node + 8);
        ASM_USE2(sprite_data, callback_state);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_800247D4();
    }
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    {
        register s32 zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

        return zero;
    }
}
