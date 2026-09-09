#include "common.h"

typedef struct S_func_800AC9AC_0 {
    u8 *unk_00;
    s16 *unk_04;
    u8 pad_08[0x18];
    u32 *unk_20;
} S_func_800AC9AC_0;

typedef struct S_func_800AC9AC_1 {
    u8 pad_00[0x24];
    u32 *unk_24;
    u8 pad_28[0x9C];
    s32 unk_C4;
    u8 pad_C8[0x20];
    u16 unk_E8;
    u16 unk_EA;
    u16 unk_EC;
    u16 unk_EE;
    u16 unk_F0;
    u16 unk_F2;
    u16 unk_F4;
    u16 unk_F6;
} S_func_800AC9AC_1;

typedef struct S_func_800AC9AC_2 {
    u8 pad_00[0x8D0];
    void *unk_8D0;
} S_func_800AC9AC_2;

typedef struct S_func_800AC9AC_3 {
    u32 unk_00;
    u32 unk_04;
    u16 unk_08;
    u16 unk_0A;
    u32 unk_0C;
    u16 unk_10;
    u16 unk_12;
    u32 unk_14;
    u16 unk_18;
    u16 unk_1A;
    u32 unk_1C;
    u16 unk_20;
    u16 unk_22;
} S_func_800AC9AC_3;

#define OTSLOT() (*(u32 *)((u8 *)scratch->unk_24 + scratch->unk_C4 * 4))

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
void func_800AA10C(S_func_800AC9AC_0 *mesh, void *transform)
{
    S_func_800AC9AC_1 *scratch;
    u8 *initial_state;
    u8 *vertices;
    u32 *color_masks;
    s16 *quad_indices;
    u8 *vertex_0;
    u8 *vertex_1;
    u8 *vertex_2;
    u8 *vertex_3;
    u8 *vertex_work;
    S_func_800AC9AC_2 *render_state;
    u8 **render_state_ptr;
    S_func_800AC9AC_3 *quad;
    u32 *draw_mode;
    s32 random_factor;
    u32 address_mask;
    u32 length_mask;

    quad_indices = mesh->unk_04;
    vertices = mesh->unk_00;
    render_state_ptr = D_80083160;
    initial_state = *render_state_ptr;
    color_masks = mesh->unk_20;
    scratch = (S_func_800AC9AC_1 *)0x1F800000;
    scratch->unk_24 = (u32 *)(initial_state + 0xB0);

    if (*quad_indices != -1) {
        vertex_0 = (u8 *)scratch + 0x74;
        vertex_1 = (u8 *)scratch + 0x7C;
        vertex_2 = (u8 *)scratch + 0x84;
        vertex_3 = (u8 *)scratch + 0x8C;
        vertex_work = (u8 *)scratch + 0x44;
        address_mask = 0x00FFFFFF;

        do {
            render_state = (S_func_800AC9AC_2 *)*render_state_ptr;
            quad = render_state->unk_8D0;
            render_state->unk_8D0 = (u8 *)quad + 0x28;

            random_factor = rand();
            quad->unk_04 = (random_factor * rand()) & color_masks[0];
            random_factor = rand();
            quad->unk_0C = (random_factor * rand()) & color_masks[1];
            random_factor = rand();
            quad->unk_14 = (random_factor * rand()) & color_masks[2];
            random_factor = rand();
            quad->unk_1C = (random_factor * rand()) & color_masks[3];

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

            scratch->unk_C4 = func_800654B0(
                vertex_0, vertex_1, vertex_2, vertex_3,
                (u8 *)scratch + 0xE8, (u8 *)scratch + 0xEC,
                (u8 *)scratch + 0xF0, (u8 *)scratch + 0xF4,
                (u8 *)scratch + 0x94, (u8 *)scratch + 0x98) - 0x30;

            quad->unk_08 = scratch->unk_E8;
            quad->unk_0A = scratch->unk_EA;
            quad->unk_10 = scratch->unk_EC;
            quad->unk_12 = scratch->unk_EE;
            quad->unk_18 = scratch->unk_F0;
            quad->unk_1A = scratch->unk_F2;
            quad->unk_20 = scratch->unk_F4;
            quad->unk_22 = scratch->unk_F6;

            if (scratch->unk_C4 >= 0x1E0)
                scratch->unk_C4 = 0x1DF;
            if (scratch->unk_C4 < 0)
                scratch->unk_C4 = 0;

            render_state = (S_func_800AC9AC_2 *)*render_state_ptr;
            draw_mode = render_state->unk_8D0;
            render_state->unk_8D0 = (u8 *)draw_mode + 0xC;
            func_80067F20(draw_mode, 1, 0,
                          (u16)func_80066460(0, 0, 0x140, 0), 0);

            length_mask = 0xFF000000;
            draw_mode[0] = (draw_mode[0] & length_mask) | (OTSLOT() & address_mask);
            OTSLOT() = (OTSLOT() & length_mask) | ((u32)draw_mode & address_mask);
            quad->unk_00 = (quad->unk_00 & length_mask) | (OTSLOT() & address_mask);
            OTSLOT() = (OTSLOT() & length_mask) | ((u32)quad & address_mask);

            render_state = (S_func_800AC9AC_2 *)*render_state_ptr;
            draw_mode = render_state->unk_8D0;
            render_state->unk_8D0 = (u8 *)draw_mode + 0xC;
            func_80067F20(draw_mode, 1, 0,
                          (u16)func_80066460(0, 1, 0x140, 0), 0);

            length_mask = 0xFF000000;
            quad_indices += 4;
            draw_mode[0] = (draw_mode[0] & length_mask) | (OTSLOT() & address_mask);
            OTSLOT() = (OTSLOT() & length_mask) | ((u32)draw_mode & address_mask);
        } while (*quad_indices != -1);
    }
}
