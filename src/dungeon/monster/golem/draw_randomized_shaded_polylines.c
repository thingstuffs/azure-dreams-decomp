#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "dungeon/monster/golem.h"
#include "sdk/libc.h"

typedef struct S_80175A90_0 {
    u8 pad_00[0x18];
    union { void * p; u32 * p2; } unk_18;   /* accessed as both */
    u8 pad_1C[0x48];
    u16 unk_64;
    u16 unk_66;
    u16 unk_68;
    u8 pad_6A[0x2];
    union { s16 s; u16 u; } unk_6C;   /* accessed as both */
    union { s16 s; u16 u; } unk_6E;   /* accessed as both */
    union { s16 s; u16 u; } unk_70;   /* accessed as both */
    u8 pad_72[0x2];
    u16 unk_74;
    u16 unk_76;
    u16 unk_78;
    u8 pad_7A[0x3A];
    union { s32 s; u32 u; } unk_B4;   /* accessed as both */
    u8 pad_B8[0x20];
    u16 unk_D8;
    u16 unk_DA;
    u16 unk_DC;
    u16 unk_DE;
    u16 unk_E0;
    u16 unk_E2;
} S_80175A90_0;   /* scratch in draw_randomized_shaded_polylines */

   /* context in draw_randomized_shaded_polylines */

typedef struct S_80175A90_2 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u16 unk_08;
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u16 unk_12;
    u8 unk_14;
    u8 unk_15;
    u8 unk_16;
    u8 pad_17[0x1];
    u16 unk_18;
    u16 unk_1A;
    u32 unk_1C;
} S_80175A90_2;   /* prim in draw_randomized_shaded_polylines */

typedef struct S_80175A90_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80175A90_3;   /* arg0 in draw_randomized_shaded_polylines */

extern s32 func_80065530(void *, void *, void *, void *, void *, void *, void *, void *);

/*
 * Projects six jittered red three-point lines plus a center line between two positions, and queues
 * them by depth.
 */
void draw_randomized_shaded_polylines(S_80175A90_3 *start_pos, EntityRec *end_pos)
{
    void **context_ptr = (void **)((u8 *)(&g_game_work));
    S_80175A90_0 *scratch = (S_80175A90_0 *)0x1F800000;
    S_80175A90_2 *prim;
    s32 line_index = 0;
    s32 endpoint_red = 0xC0;
    u32 addr_mask = 0x00FFFFFF;
    u32 length_mask = 0xFF000000;

    scratch->unk_18.p = (u8 *)*context_ptr + 0xB0;

    do {
        GpuContext *context = *context_ptr;
        s32 offset;

        prim = context->packetCursor;
        context->packetCursor = (u8 *)prim + 0x20;

        prim->unk_07 = 0x58;
        prim->unk_00.at03.v = 7;
        prim->unk_1C = 0x55555555;
        prim->unk_07 |= 2;

        scratch->unk_64 = start_pos->unk_02;
        scratch->unk_66 = start_pos->unk_06;
        scratch->unk_68 = start_pos->unk_0A;

        scratch->unk_6C.s =
            (((s16)start_pos->unk_02) + end_pos->x.w.i) / 2;
        scratch->unk_6E.s =
            (((s16)start_pos->unk_06) + end_pos->y.w.i) / 2;
        scratch->unk_70.s =
            (((s16)start_pos->unk_0A) + end_pos->z.w.i) / 2;

        scratch->unk_74 = ((u16)end_pos->x.w.i);
        scratch->unk_76 = ((u16)end_pos->y.w.i);
        scratch->unk_78 = ((u16)end_pos->z.w.i);

        offset = (rand() % 9) + 4;
        switch (line_index) {
        case 0:
            scratch->unk_64 -= 2;
            scratch->unk_6C.u += offset;
            scratch->unk_74 -= offset;
            break;
        case 1:
            scratch->unk_66 -= 2;
            scratch->unk_6E.u += offset;
            scratch->unk_76 -= offset;
            break;
        case 2:
            scratch->unk_68 -= 2;
            scratch->unk_70.u += offset;
            scratch->unk_78 -= offset;
            break;
        case 3:
            scratch->unk_64 += 2;
            scratch->unk_6C.u -= offset;
            scratch->unk_74 += offset;
            break;
        case 4:
            scratch->unk_66 += 2;
            scratch->unk_6E.u -= offset;
            scratch->unk_76 += offset;
            break;
        case 5:
            scratch->unk_68 += 2;
            scratch->unk_70.u -= offset;
            scratch->unk_78 += offset;
            break;
        case 6:
            break;
        }

        prim->unk_05 = 0x40;
        prim->unk_06 = 0x40;
        prim->unk_0C = 0x40;
        prim->unk_15 = 0x40;
        prim->unk_16 = 0x40;
        prim->unk_04 = endpoint_red;
        prim->unk_0D = 0;
        prim->unk_0E = 0;
        prim->unk_14 = endpoint_red;

        scratch->unk_B4.s = func_80065530(
            &scratch->unk_64, &scratch->unk_6C, &scratch->unk_74,
            &scratch->unk_D8, &scratch->unk_DC, &scratch->unk_E0,
            (u8 *)scratch + 0x84, (u8 *)scratch + 0x88);

        prim->unk_08 = scratch->unk_D8;
        prim->unk_0A = scratch->unk_DA;
        prim->unk_10 = scratch->unk_DC;
        prim->unk_12 = scratch->unk_DE;
        prim->unk_18 = scratch->unk_E0;
        prim->unk_1A = scratch->unk_E2;

        {
            u32 depth = scratch->unk_B4.u;
            if (depth < 0x1E0) {
                prim->unk_00.at00.v =
                    (prim->unk_00.at00.v & length_mask) |
                    ((*(u32 *)((u8 *)(scratch->unk_18.p2) + depth * 4)) & addr_mask);
                (*(u32 *)((u8 *)(scratch->unk_18.p2) + scratch->unk_B4.u * 4)) =
                    ((*(u32 *)((u8 *)(scratch->unk_18.p2)
                        + scratch->unk_B4.u * 4)) & length_mask) |
                    ((u32)prim & addr_mask);
            }
        }

        line_index++;
    } while (line_index < 7);
}
