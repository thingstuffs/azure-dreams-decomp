#include "common.h"
#include "m2c_compat.h"

extern u8 D_80045340[];
extern u8 D_80083498[];
extern u8 D_800DEC70[];
void *func_8003FC64();
s32 func_8004491C();
extern u8 D_800F6000[];
extern M2C_UNK D_800F6A44;


typedef struct S_80921B2C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80921B2C_0;   /* temp_v0 in func_80921B2C */

typedef struct S_80921B2C_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x8];
    s16 unk_10;
    u8 pad_12[0x2];
    union { u16 n; volatile u16 v; } unk_14;   /* accessed as both */
} S_80921B2C_1;   /* temp_a0 in func_80921B2C */

typedef struct S_80921B2C_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
} S_80921B2C_2;   /* temp_a0_2 in func_80921B2C */

typedef struct S_80921B2C_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80921B2C_3;   /* arg0 in func_80921B2C */

typedef struct S_80921B2C_4 {
    u8 pad_00[0x2A];
    volatile u16 unk_2A;
} S_80921B2C_4;   /* temp_s6 in func_80921B2C */

typedef struct S_80921B2C_5 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_80921B2C_5;   /* temp_a0_3 in func_80921B2C */

typedef struct S_80921B2C_6 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80921B2C_6;   /* (s8 *)temp_buf + (((u16) ((S_80921B2C_4 *)temp_s6)->unk_2A >> 7) & 0x1C) in func_80921B2C */

/* Creates an effect at an offset position with direction-based motion and sprite settings. */
void func_80921B2C(S_80921B2C_3 *position, s32 x_offset, s32 y_offset, s32 z_offset) {
    u8 direction_table[32];
    u8 *direction_source;
    s32 saved_y_offset = y_offset;
    s32 saved_z_offset = z_offset;
    u16 render_flags;
    register s32 effect_type ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register u8 *global_state ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u8 *direction_state ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    S_80921B2C_2 *motion;
    S_80921B2C_5 *sprite;
    S_80921B2C_0 *effect;

    direction_source = D_800F6000;
    memcpy(direction_table, direction_source, 0x20);
    effect_type = 0x212;
    ASM_USE_NV(effect_type);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    global_state = D_80083498;
    direction_state = global_state + 0x20;
    effect = func_8003FC64(effect_type);
    if (effect != NULL) {
        u8 *directions = direction_table;

        effect->unk_10 = &D_800F6A44;
        func_8004491C(effect, D_80045340);
        {
            S_80921B2C_1 *render_state;

            render_state = effect->unk_0C;
            render_flags = render_state->unk_14.n;
            ASM_USE(render_flags);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            render_state->unk_10 = 0x20;
            render_state->unk_06 = 6;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            render_flags |= 0xC;
            render_state->unk_14.v = render_flags;
            render_flags |= 2;
            render_state->unk_14.v = render_flags;
        }
        motion = effect->unk_08;
        motion->unk_00.at00.v = (s32) position->unk_00;
        motion->unk_04.at00.v = (s32) position->unk_04;
        motion->unk_08.at00.v = (s32) position->unk_08;
        motion->unk_00.at02.v = (u16) (motion->unk_00.at02.v + x_offset);
        motion->unk_04.at02.v = (u16) (motion->unk_04.at02.v + saved_y_offset);
        motion->unk_08.at02.v = (u16) (motion->unk_08.at02.v + saved_z_offset);
        motion->unk_0C = (s32) ((*(s16 *)((u8 *)directions + (((u16) ((S_80921B2C_4 *)direction_state)->unk_2A >> 7) & 0x1C))) * 0x180000);
        motion->unk_10 = (s32) ((s16) ((S_80921B2C_6 *)((s8 *)directions + (((u16) ((S_80921B2C_4 *)direction_state)->unk_2A >> 7) & 0x1C)))->unk_02 * 0x180000);
        sprite = effect->unk_0C;
        sprite->unk_1E = 0x800;
        sprite->unk_1C = 0x800;
        sprite->unk_0E = 0x80;
        sprite->unk_0D = 0x80;
        sprite->unk_0C = 0x80;
        func_8003DB94(sprite, D_800DEC70, 0);
    }
}
