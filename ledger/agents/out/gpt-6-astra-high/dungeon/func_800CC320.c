#include "common.h"
#include "m2c_compat.h"

typedef struct S_800D1A80_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_800D1A80_0;   /* arg0 in func_800D1A80 */

typedef struct S_800D1A80_1 {
    u8 pad_00[0xC];
    union { struct { s32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800D1A80_1;   /* arg2 in func_800D1A80 */

typedef struct S_800D1A80_2_pre {
    u16 unk_00;
} S_800D1A80_2_pre;   /* the 0x2 bytes before arg3 in func_800D1A80, addressed as arg3[-1] */

typedef struct S_800D1A80_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800D1A80_2;   /* arg3 in func_800D1A80 */

typedef struct S_800D1A80_3 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800D1A80_3;   /* var_a0 in func_800D1A80 */


#define M2C_BREAK() 0
#define M2C_SYNC() 0

extern s16 D_8008346A[];
extern s32 D_80083460[3];
extern s32 D_800814A0[3];
void func_8009A028(void *arg0);
void func_8009A3D0(u8 arg0, u8 arg1, s32 arg2);
void func_800A32A4(void *arg0);
void func_800A56E0(s32 arg0);
s32 func_80042900(void *arg0, s32 arg1);

/* Fade the entity to dark gray, then remove it and update its tile flags. */
s32 func_800D1A80(S_800D1A80_0 *state, void *unused, S_800D1A80_1 *visual, void *entity) {
    s16 *fade_blocked = D_8008346A;
    s16 fade_frames;
    M2C_UNK tile_flags;
    s16 frames_left;
    s32 entity_ref;
    s32 *entity_tracker;
    u8 blue;
    u8 phase;
    u8 red;
    u8 green;
    u8 tile_x;
    u8 tile_y;

    phase = state->unk_9B;
    if (phase != 0) {
        if (phase != 1) {
            return 0;
        }
        goto update_fade;
    }
    if (*fade_blocked == 0) {
        visual->unk_10 = 0x20;
        visual->unk_12 = (u16) (visual->unk_12 - 0x80);
        visual->unk_14 = (u16) (visual->unk_14 | 0xC);
        ((S_800D1A80_2 *)entity)->unk_1C = (s32) (((S_800D1A80_2 *)entity)->unk_1C | 0x10000000);
        func_800A56E0(0x805);
        visual->unk_0C.at00.v = 0x808080;
        state->unk_96 = 0x10;
        state->unk_9B = (u8) (state->unk_9B + 1);
update_fade:
        red = visual->unk_0C.at00u.v;
        fade_frames = state->unk_96;
        visual->unk_0C.at00u.v = (u8) (red + ((s32) (0x20 - red) / fade_frames));
        green = visual->unk_0C.at01.v;
        blue = visual->unk_0C.at02.v;
        fade_frames = state->unk_96;
        visual->unk_0C.at01.v = (u8) (green + ((s32) (0x20 - green) / fade_frames));
        visual->unk_0C.at02.v = (u8) (blue + ((s32) (0x20 - blue) / (s16) state->unk_96));
        frames_left = (u16) state->unk_96 - 1;
        state->unk_96 = frames_left;
        if (((frames_left << 0x10) > 0) && ((visual->unk_14 & 0x8000) == 0)) {
            return 0;
        }
        entity_tracker = D_80083460;
        {
            entity_ref = ((S_800D1A80_3 *)entity_tracker)->unk_10;
            if (entity_ref == (entity - 0x20)) {
                ((S_800D1A80_3 *)entity_tracker)->unk_10 = (s32) (entity_ref & 0x7FFFFFFF);
            }
            func_800A32A4(entity);
            if ((func_80042900(entity, 0x1B) << 0x10) == 0) {
                tile_x = visual->unk_24;
                tile_y = visual->unk_25;
                tile_flags = 0x3000;
                if (((S_800D1A80_2 *)entity)->unk_1C & 0x2000) {
                    tile_flags = 0x300;
                }
                func_8009A3D0(tile_x, tile_y, tile_flags);
            }
            func_8009A028(entity);
            ((S_800D1A80_2_pre *)entity)[-1].unk_00 = (u16) (((S_800D1A80_2_pre *)entity)[-1].unk_00 | 0x8000);
            D_800814A0[0] = D_800814A0[0] | 0x8000;
            return 1;
        }
        return 0;
    }
    return 0;
}
