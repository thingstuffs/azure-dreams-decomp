#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))
#define OTSLOT() FIELD(FIELD(scratch, u32 *, 0x24), u32, FIELD(scratch, s32, 0xC4) * 4)

extern u8 *D_80083160[3];

extern void func_800649A0(void);
extern void func_80064A40(void);
extern s32 func_800654B0(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80066640(void *, s32);
extern void func_80066844(void *);
extern void func_80067F20(void *, s32, s32, u16, s32);
extern s32 rand(void);
extern void func_800A1330(void *, void *);
extern void func_800A2DF0(void *, void *);
extern void func_800AA068(void *, void *, void *);

/* Transform and queue mesh quads with randomized vertex colors. */
void func_800AA10C(u8 *mesh, void *transform)
{
    u8 *scratch;
    u8 *initial_state;
    u8 *vertices;
    u32 *color_masks;
    s16 *quad_indices;
    u8 *vertex_0;
    u8 *vertex_1;
    u8 *vertex_2;
    u8 *vertex_3;
    u8 *vertex_work;
    u8 *render_state;
    u8 **render_state_ptr;
    u32 *quad;
    u32 *draw_mode;
    s32 random_factor;
    u32 address_mask;
    u32 length_mask;

    quad_indices = FIELD(mesh, s16 *, 4);
    vertices = FIELD(mesh, u8 *, 0);
    render_state_ptr = D_80083160;
    initial_state = *render_state_ptr;
    color_masks = FIELD(mesh, u32 *, 0x20);
    scratch = (u8 *)0x1F800000;
    FIELD(scratch, u8 *, 0x24) = initial_state + 0xB0;

    if (*quad_indices != -1) {
        vertex_0 = scratch + 0x74;
        vertex_1 = scratch + 0x7C;
        vertex_2 = scratch + 0x84;
        vertex_3 = scratch + 0x8C;
        vertex_work = scratch + 0x44;
        address_mask = 0x00FFFFFF;

        do {
            render_state = *render_state_ptr;
            quad = FIELD(render_state, u32 *, 0x8D0);
            FIELD(render_state, u8 *, 0x8D0) = (u8 *)quad + 0x28;

            random_factor = rand();
            quad[1] = (random_factor * rand()) & color_masks[0];
            random_factor = rand();
            quad[3] = (random_factor * rand()) & color_masks[1];
            random_factor = rand();
            quad[5] = (random_factor * rand()) & color_masks[2];
            random_factor = rand();
            quad[7] = (random_factor * rand()) & color_masks[3];

            func_80066844(quad);
            func_80066640(quad, 1);

            func_800A1330(vertex_0, vertices + (quad_indices[0] * 8));
            func_800A1330(vertex_1, vertices + (quad_indices[1] * 8));
            func_800A1330(vertex_2, vertices + (quad_indices[2] * 8));
            func_800A1330(vertex_3, vertices + (quad_indices[3] * 8));

            func_800649A0();
            func_800AA068(mesh, vertex_0, vertex_work);
            func_800AA068(mesh, vertex_1, vertex_work);
            func_800AA068(mesh, vertex_2, vertex_work);
            func_800AA068(mesh, vertex_3, vertex_work);
            func_80064A40();

            func_800A2DF0(vertex_0, transform);
            func_800A2DF0(vertex_1, transform);
            func_800A2DF0(vertex_2, transform);
            func_800A2DF0(vertex_3, transform);

            FIELD(scratch, s32, 0xC4) = func_800654B0(
                vertex_0, vertex_1, vertex_2, vertex_3,
                scratch + 0xE8, scratch + 0xEC,
                scratch + 0xF0, scratch + 0xF4,
                scratch + 0x94, scratch + 0x98) - 0x30;

            FIELD(quad, u16, 0x08) = FIELD(scratch, u16, 0xE8);
            FIELD(quad, u16, 0x0A) = FIELD(scratch, u16, 0xEA);
            FIELD(quad, u16, 0x10) = FIELD(scratch, u16, 0xEC);
            FIELD(quad, u16, 0x12) = FIELD(scratch, u16, 0xEE);
            FIELD(quad, u16, 0x18) = FIELD(scratch, u16, 0xF0);
            FIELD(quad, u16, 0x1A) = FIELD(scratch, u16, 0xF2);
            FIELD(quad, u16, 0x20) = FIELD(scratch, u16, 0xF4);
            FIELD(quad, u16, 0x22) = FIELD(scratch, u16, 0xF6);

            if (FIELD(scratch, s32, 0xC4) >= 0x1E0)
                FIELD(scratch, s32, 0xC4) = 0x1DF;
            if (FIELD(scratch, s32, 0xC4) < 0)
                FIELD(scratch, s32, 0xC4) = 0;

            render_state = *render_state_ptr;
            draw_mode = FIELD(render_state, u32 *, 0x8D0);
            FIELD(render_state, u8 *, 0x8D0) = (u8 *)draw_mode + 0xC;
            func_80067F20(draw_mode, 1, 0,
                          (u16)func_80066460(0, 0, 0x140, 0), 0);

            length_mask = 0xFF000000;
            draw_mode[0] = (draw_mode[0] & length_mask) | (OTSLOT() & address_mask);
            OTSLOT() = (OTSLOT() & length_mask) | ((u32)draw_mode & address_mask);
            quad[0] = (quad[0] & length_mask) | (OTSLOT() & address_mask);
            OTSLOT() = (OTSLOT() & length_mask) | ((u32)quad & address_mask);

            render_state = *render_state_ptr;
            draw_mode = FIELD(render_state, u32 *, 0x8D0);
            FIELD(render_state, u8 *, 0x8D0) = (u8 *)draw_mode + 0xC;
            func_80067F20(draw_mode, 1, 0,
                          (u16)func_80066460(0, 1, 0x140, 0), 0);

            length_mask = 0xFF000000;
            quad_indices += 4;
            draw_mode[0] = (draw_mode[0] & length_mask) | (OTSLOT() & address_mask);
            OTSLOT() = (OTSLOT() & length_mask) | ((u32)draw_mode & address_mask);
        } while (*quad_indices != -1);
    }
}
