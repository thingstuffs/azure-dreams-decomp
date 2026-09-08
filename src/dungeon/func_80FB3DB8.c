#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80083460.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_801735B8_0 {
    u8 pad_00[0x96];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801735B8_0;   /* arg0 in func_801735B8 */



typedef struct S_801735B8_3 {
    u8 pad_00[0xC];
    union { u8 u8; s32 s32; } unk_0C;   /* accessed as both */
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_801735B8_3;   /* held_arg2 in func_801735B8 */

typedef struct S_801735B8_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_801735B8_4;   /* global_ptr in func_801735B8 */


void func_8009A028(void *);
void func_8009A3D0(s32, s32, s32);
void func_800A2FE0(void *);
void func_800A32A4(void *);
void func_800A56E0(s32);
void func_800ACF88(void *);
extern s32 D_800814A0;
extern s32 D_80083460;

/* Fades out an entity, then removes it and updates its tile flags. */
void func_801735B8(void *fade_state, void *unused, void *visual_data, void *entity) {
    register void *visual ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    M2C_UNK *world;
    s32 state;
    s32 entity_flags;
    s32 tracked_entity;
    s32 tile_x;
    s32 tile_y;
    s32 tile_mask;
    u16 countdown;

    visual = visual_data;
    state = ((S_801735B8_0 *)fade_state)->unk_9B;
    switch (state) {
    case 0:
        if (((Rec_D_80083460 *)(&D_80083460))->unk_0A != 0) {
            return;
        }
        ((S_801735B8_0 *)fade_state)->unk_9B = 1;
        /* fallthrough */
    case 1:
        entity_flags = ((Rec_D_80082E80 *)entity)->unk_14.at00_s32.v;
        if (entity_flags & 0x4000) {
            if (!(entity_flags & 0x20000000)) {
                func_800ACF88(entity);
            }
        }
        ((S_801735B8_0 *)fade_state)->unk_96.u = 6;
        ((S_801735B8_0 *)fade_state)->unk_9B =
            (u8)(((S_801735B8_0 *)fade_state)->unk_9B + 1);
        ((S_801735B8_3 *)visual)->unk_12 = 0xFF80;
        /* fallthrough */
    case 2:
        ((Rec_D_80082E80 *)entity)->unk_1C.at00_s32.v |= 0x10000000;
        countdown = ((S_801735B8_0 *)fade_state)->unk_96.u - 1;
        ((S_801735B8_0 *)fade_state)->unk_96.u = countdown;
        if ((countdown << 16) <= 0) {
            if (((S_801735B8_3 *)visual)->unk_0C.u8 >= 0x10U) {
                ((S_801735B8_3 *)visual)->unk_0C.s32 += (s32)0xFFEFEFF0;
            }
            ((S_801735B8_3 *)visual)->unk_10 = 0x20;
            ((S_801735B8_3 *)visual)->unk_14 |= 0xC;
        } else {
            ((S_801735B8_3 *)visual)->unk_0C.s32 = 0x00808080;
        }

        if (((S_801735B8_0 *)fade_state)->unk_96.s == 0) {
            func_800A56E0(0x805);
        }
        if (!(((S_801735B8_3 *)visual)->unk_14 & 0x8000)) {
            if (((S_801735B8_3 *)visual)->unk_0C.u8 >= 0x10U) {
                return;
            }
        }

        world = &D_80083460;
        tracked_entity = ((S_801735B8_4 *)world)->unk_10;
        if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
            ((S_801735B8_4 *)world)->unk_10 =
                tracked_entity & 0x7FFFFFFF;
        }
        func_800A2FE0(entity);
        func_800A32A4(entity);

        tile_x = ((S_801735B8_3 *)visual)->unk_24;
        tile_y = ((S_801735B8_3 *)visual)->unk_25;
        tile_mask = 0x3000;
        if (((Rec_D_80082E80 *)entity)->unk_1C.at00_s32.v & 0x2000) {
            tile_mask = 0x300;
        }
        func_8009A3D0(tile_x, tile_y, tile_mask);
        func_8009A028(entity);
        (*(u16 *)((u8 *)entity + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
        break;
    default:
        return;
    }
    ASM_KEEP(visual);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
}

/* MECHANISM: A natural three-case switch preserves the retail dispatch and fallthrough block order.
   A guarded s1 arg2 hold fixes the s0/s1/s2 frame roles; true-space targets remain local joins.
   Direct D_80083460+0xA access schedules the page base, and u16 0xFF80 selects the ori encoding. */
