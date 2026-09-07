#include "common.h"

typedef struct Scratch {
    u8 pad0[0x18];
    u8 *current;
    u8 pad1c[4];
    u32 *table;
    u8 pad24[0x4c];
    u32 value70;
    u16 half74;
    u8 pad76[2];
    u32 value78;
    u16 half7c;
    u8 pad7e[2];
    u32 value80;
    u16 half84;
    u8 pad86[2];
    u32 value88;
    u16 half8c;
    u8 pad8e[2];
    u32 out90;
    u32 out94;
    u8 pad98[0x28];
    u32 index;
} Scratch;

typedef struct Entry {
    u8 bytes[0x24];
} Entry;

typedef struct EmptyCallArg {
} EmptyCallArg;

extern u8 *D_80083160;
extern s16 D_8002632A;
extern u32 D_80026470;
extern u32 D_80026474;
extern u32 D_80026478[];

extern u32 func_800654B0(
    u32 *, u32 *, u32 *, u32 *, u32 *, u32 *, u32 *, u32 *, u32 *, u32 *,
    EmptyCallArg);
extern void func_80066708(Entry *);
extern void func_8006658C(u32 *, Entry *);
extern u32 func_80066460(u32, u32, u32, u32);
extern void func_80067F20(Entry *, u32, u32, u32, u32);

/* Builds shaded quads from adjacent vertex rows and adds them to the ordering table. */
s32 func_80024EF4(void)
{
    s32 quad_index = 0;
    Scratch *scratch = (Scratch *)0x1F800000;
    u8 *state = D_80083160;
    u8 *primitive_start = *(u8 **)(state + 0x8D0);
    u32 *vertices;
    u8 *vertex_record;

    scratch->table = (u32 *)(state + 0xB0);
    scratch->current = primitive_start;

    /* This address is needed only by the loop's terminal writeback. */
    {
        u8 **state_slot = &D_80083160;

        if (D_8002632A <= 0)
            goto done;

        vertices = D_80026478;
        vertex_record = (u8 *)vertices;

loop:
        {
            Entry *quad;
            u32 *near_vertex;
            u32 *near_next_vertex;
            register u32 *far_vertex ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
            register u32 *far_next_vertex ASM_REG("$7");   /* MATCH pin: load-bearing for the whole function shape */
            u32 *next_row;
            u32 far_next_xy;
            s32 row_start;
            s32 far_index;
            u16 near_z;
            u16 far_z;
            EmptyCallArg late_stores;

            ASM_KEEP_NV(scratch);   /* MATCH pin: load-bearing for the whole function shape */
            near_vertex = &scratch->value70;
            row_start = quad_index & ~0xF;
            quad = (Entry *)scratch->current;
            ASM_KEEP(quad);   /* MATCH pin: load-bearing for the whole function shape */
            near_next_vertex = &scratch->value78;
            ASM_KEEP(near_next_vertex);   /* MATCH pin: load-bearing for the whole function shape */
            far_vertex = &scratch->value80;
            scratch->current = (u8 *)quad + 0x24;
            scratch->value70 = *(u32 *)vertex_record;
            next_row = vertices + 0x20;
            scratch->value78 = vertices[
                ((u32)row_start + (u32)((quad_index + 1) & 0xF)) * 2];
            scratch->value80 = next_row[quad_index * 2];
            far_next_xy = next_row[
                ((u32)row_start + (u32)((quad_index + 1) & 0xF)) * 2];
            far_next_vertex = &scratch->value88;
            near_z = *(u16 *)(vertex_record + 4);
            scratch->half74 = near_z;
            scratch->half7c = near_z;
            ASM_SCHED_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
            far_index = quad_index + 16;
            far_z = ((u16 *)vertices)[(far_index * 4) + 2];

            scratch->index = func_800654B0(
                near_vertex, near_next_vertex, far_vertex, far_next_vertex,
                (u32 *)((u8 *)quad + 8), (u32 *)((u8 *)quad + 16),
                (u32 *)((u8 *)quad + 24), (u32 *)((u8 *)quad + 32),
                &scratch->out90, &scratch->out94,
                (scratch->value88 = far_next_xy,
                 scratch->half84 = far_z,
                 scratch->half8c = far_z,
                 late_stores));
            scratch->index -= 8;

            if (scratch->index < 0x1E0U) {
                if ((quad_index % 32) < 16) {
                    *(u32 *)((u8 *)quad + 12) = D_80026470;
                    *(u32 *)((u8 *)quad + 4) = D_80026470;
                    *(u32 *)((u8 *)quad + 28) = D_80026474;
                    *(u32 *)((u8 *)quad + 20) = D_80026474;
                } else {
                    *(u32 *)((u8 *)quad + 28) = D_80026470;
                    *(u32 *)((u8 *)quad + 20) = D_80026470;
                    *(u32 *)((u8 *)quad + 12) = D_80026474;
                    *(u32 *)((u8 *)quad + 4) = D_80026474;
                }

                func_80066708(quad);
                quad->bytes[7] |= 2;
                func_8006658C(scratch->table + scratch->index, quad);

                {
                    u8 *draw_mode = scratch->current;
                    scratch->current = draw_mode + 0x0C;
                    func_80067F20(draw_mode, 0, 0,
                                  (u16)func_80066460(0, 1, 0, 0), 0);
                    func_8006658C(scratch->table + scratch->index,
                                  (Entry *)draw_mode);
                }
            }

            vertex_record += 8;
        }

        {
            s32 quad_count = D_8002632A;
            quad_index++;
            if (quad_index < quad_count)
                goto loop;
        }

done:
        *(u8 **)(*state_slot + 0x8D0) = scratch->current;
    }
    return 0;
}
