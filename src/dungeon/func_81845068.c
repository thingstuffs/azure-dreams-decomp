#include "common.h"

typedef struct Packed8 {
    u32 word0;
    u32 word1;
} __attribute__((packed)) Packed8;

typedef struct Coord {
    s16 x;
    s16 y;
} Coord;

typedef union Scratch {
    s32 word;
    u16 half;
    u8 byte;
} Scratch;

extern u8 D_80083160[];

extern s32 func_80065420(Packed8 *, Coord *, Coord *, Coord *);
extern s32 func_80066460(s32, s32, s32, s32);
extern s32 func_8006649C(s32, s32);
extern void func_80066640(void *, s32);
extern void func_800666F4(void *);
extern s32 func_80069EF8(void);

#define LOAD_PTR(p) (*(u8 **)(p))
#define LOAD_U32(p) (*(u32 *)(p))
#define STORE_U32(p, v) (*(u32 *)(p) = (v))
#define STORE_U16(p, v) (*(u16 *)(p) = (v))
#define STORE_U8(p, v) (*(u8 *)(p) = (v))

/* Draw textured quads with randomized texture and horizontal jitter for each linked effect node. */
s32 func_81845068(u8 *first_node)
{
    u32 uv_choices[4];
    Packed8 world_pos;
    Coord screen_coords[3];
    u8 *node;
    u8 *effect_node;
    register u8 *next_link ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *render_state;
    register u8 *alloc_ctx ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    u8 *ot_ctx;
    register u8 *ot_entry ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *prim;
    Coord *screen_base;
    Coord *screen_pos;
    register Coord *scratch_or_height;
    s32 index_or_jitter;
    s32 depth_bucket;
    u16 half_width;
    u16 jitter_half_width;
    s32 tex_value;
    s32 tex_u_start;
    s32 tex_u_end;
    s32 random_value;
    register u32 addr_mask ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u32 ot_or_coord ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u16 vertex_x;
    u16 base_y;
    u16 tip_y;

    node = first_node;
    render_state = D_80083160;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    uv_choices[0] = 0xA0;
    do { uv_choices[1] = 0x80; } while (0);
    screen_base = &screen_coords[0];
    uv_choices[2] = 0;
    uv_choices[3] = 0x20;
    addr_mask = 0xFFFFFF;

    do {
        effect_node = node;
        world_pos = *(Packed8 *)(node + 4);
        index_or_jitter = 0;
        scratch_or_height = &screen_coords[2];
        screen_pos = screen_base;
        do {
            depth_bucket = func_80065420(&world_pos, screen_pos, scratch_or_height, scratch_or_height) - 8;
            screen_pos++;
            index_or_jitter++;
            *(u16 *)((u8 *)&world_pos + 4) =
                *(u16 *)((u8 *)&world_pos + 4) + 0xB0;
        } while (index_or_jitter < 2);

        scratch_or_height = (Coord *)(screen_coords[0].y - screen_coords[1].y);

        if ((u32)depth_bucket < 0x1E0) {
            alloc_ctx = LOAD_PTR(render_state);
            prim = LOAD_PTR(alloc_ctx + 0x8D0);
            LOAD_PTR(alloc_ctx + 0x8D0) = prim + 0x34;
            STORE_U32(prim + 4, 0x00808080);
            func_800666F4(prim);
            func_80066640(prim, 1);
            STORE_U16(prim + 0x16, func_80066460(0, 0, 0x2C0, 0x100));
            STORE_U16(prim + 0x0E, func_8006649C(0xA0, 0x1F7));

            ((Scratch *)&screen_coords[2])->word = (s32)scratch_or_height / 6;
            vertex_x = screen_coords[0].x;
            half_width = ((Scratch *)&screen_coords[2])->half;
            vertex_x += half_width;
            STORE_U16(prim + 0x10, vertex_x);
            STORE_U16(prim + 8, vertex_x);
            vertex_x = screen_coords[0].x - half_width;
            STORE_U16(prim + 0x20, vertex_x);
            STORE_U16(prim + 0x18, vertex_x);
            base_y = screen_coords[0].y;
            STORE_U16(prim + 0x1A, base_y);
            STORE_U16(prim + 0x0A, base_y);
            tip_y = screen_coords[1].y;
            STORE_U16(prim + 0x22, tip_y);
            STORE_U16(prim + 0x12, tip_y);

            tex_value = 7 - *(s16 *)(effect_node + 0x2A);
            ((Scratch *)&screen_coords[2])->word = tex_value;
            ot_entry = (u8 *)(depth_bucket * 4);
            ASM_KEEP_NV(ot_entry);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            tex_u_end = (((Scratch *)&screen_coords[2])->byte & 3) << 5;
            tex_u_start = tex_u_end - 0x80;
            tex_u_end -= 0x61;
            STORE_U8(prim + 0x1C, tex_u_start);
            STORE_U8(prim + 0x0C, tex_u_start);
            STORE_U8(prim + 0x24, tex_u_end);
            STORE_U8(prim + 0x14, tex_u_end);
            tex_value = ((Scratch *)&screen_coords[2])->word >> 2;
            tex_value <<= 5;
            STORE_U8(prim + 0x25, tex_value);
            STORE_U8(prim + 0x1D, tex_value);
            STORE_U8(prim + 0x15, tex_value + 0x1F);
            STORE_U8(prim + 0x0D, tex_value + 0x1F);
            {
                register u32 tag_mask ASM_REG("$5") = 0xFF000000;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                ot_ctx = LOAD_PTR(render_state);
                ot_or_coord = LOAD_U32(ot_ctx + 0xB0 + depth_bucket * 4);
                STORE_U32(prim, (LOAD_U32(prim) & tag_mask) | (ot_or_coord & addr_mask));
                ot_ctx = LOAD_PTR(render_state);
                ot_entry += (u32)ot_ctx;
                ot_or_coord = LOAD_U32(ot_entry + 0xB0);
                ot_or_coord &= tag_mask;
                STORE_U32(ot_entry + 0xB0,
                          ot_or_coord | ((u32)prim & addr_mask));
            }
        }

        alloc_ctx = LOAD_PTR(render_state);
        prim = LOAD_PTR(alloc_ctx + 0x8D0);
        LOAD_PTR(alloc_ctx + 0x8D0) = prim + 0x34;
        STORE_U32(prim + 4, 0x00161616);
        func_800666F4(prim);
        func_80066640(prim, 1);
        STORE_U16(prim + 0x16, func_80066460(0, 3, 0x2C0, 0x100));
        STORE_U16(prim + 0x0E, func_8006649C((func_80069EF8() & 0xF) << 4, 0x1F8));

        index_or_jitter = func_80069EF8() & 1;
        tex_value = *(u8 *)&uv_choices[index_or_jitter];
        STORE_U8(prim + 0x1C, tex_value);
        STORE_U8(prim + 0x0C, tex_value);
        tex_value = *(u8 *)&uv_choices[index_or_jitter] + 0x5F;
        STORE_U8(prim + 0x24, tex_value);
        STORE_U8(prim + 0x14, tex_value);
        tex_value = *((u8 *)&uv_choices[index_or_jitter] + 8) + 0x20;
        STORE_U8(prim + 0x15, tex_value);
        STORE_U8(prim + 0x0D, tex_value);
        tex_value = *((u8 *)&uv_choices[index_or_jitter] + 8);
        STORE_U8(prim + 0x25, tex_value);
        STORE_U8(prim + 0x1D, tex_value);

        random_value = func_80069EF8();
        index_or_jitter = (random_value % 64) - 0x20;
        ot_or_coord = (s32)scratch_or_height / 6;
        ((Scratch *)&screen_coords[2])->word = ot_or_coord;
        index_or_jitter = (index_or_jitter >> 1) + (index_or_jitter >> 2);
        ot_or_coord = (u16)screen_coords[0].x;
        jitter_half_width = ((Scratch *)&screen_coords[2])->half;
        vertex_x = ot_or_coord + jitter_half_width + index_or_jitter;
        STORE_U16(prim + 0x10, vertex_x);
        STORE_U16(prim + 8, vertex_x);
        vertex_x = screen_coords[0].x - jitter_half_width + index_or_jitter * 2;
        STORE_U16(prim + 0x20, vertex_x);
        STORE_U16(prim + 0x18, vertex_x);
        base_y = screen_coords[0].y;
        ot_entry = (u8 *)(depth_bucket * 4);
        STORE_U16(prim + 0x1A, base_y);
        STORE_U16(prim + 0x0A, base_y);
        tip_y = screen_coords[1].y;
        STORE_U16(prim + 0x22, tip_y);
        STORE_U16(prim + 0x12, tip_y);

        {
            register u32 tag_mask ASM_REG("$5") = 0xFF000000;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            ot_ctx = LOAD_PTR(render_state);
            ot_or_coord = LOAD_U32(ot_ctx + 0xB0 + depth_bucket * 4);
            STORE_U32(prim, (LOAD_U32(prim) & tag_mask) | (ot_or_coord & addr_mask));
            ot_ctx = LOAD_PTR(render_state);
            ot_entry += (u32)ot_ctx;
            ot_or_coord = LOAD_U32(ot_entry + 0xB0);
            ot_or_coord &= tag_mask;
            STORE_U32(ot_entry + 0xB0,
                      ot_or_coord | ((u32)prim & addr_mask));
        }

        next_link = LOAD_PTR(node - 8);
        node = next_link + 0x20;
    } while (next_link != 0);

    ASM_SET(next_link);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    return 0;
}
