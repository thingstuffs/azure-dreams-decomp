#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800AD058_arg0.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s16 D_8008346A[];
extern u8 D_80083780[12];
extern s32 D_80083460[3];
extern s32 D_800814A0[3];
s32 func_800644B8(s32);
s32 func_80064584(s32);
M2C_UNK func_8009A028();
M2C_UNK func_8009A3D0();
M2C_UNK func_800A2FE0();
M2C_UNK func_800A32A4();
M2C_UNK func_800A56E0();
M2C_UNK func_800ACF88();
s32 func_80042900();
M2C_UNK func_800B8228();



typedef struct S_800AD058_1 {
    u8 pad_00[0xC];
    union { struct { s32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x1];
    u8 unk_27;
} S_800AD058_1;   /* arg2 in func_800AD058 */

typedef struct S_800AD058_2_pre {
    u16 unk_00;
} S_800AD058_2_pre;   /* the 0x2 bytes before arg3_local in func_800AD058, addressed as arg3_local[-1] */

typedef struct S_800AD058_2 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x29];
    u8 unk_49;
    u8 pad_4A[0x1];
    u8 unk_4B;
    u8 pad_4C[0x3C];
    s16 unk_88;
} S_800AD058_2;   /* arg3_local in func_800AD058 */

typedef struct S_800AD058_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
} S_800AD058_3;   /* arg1 in func_800AD058 */


typedef struct S_800AD058_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800AD058_5;   /* base in func_800AD058 */

/* Fades or spirals an entity away, then removes it and updates dungeon state. */
s32 func_800AD058(u8 *state, s32 *position, u8 *sprite, u8 *entity_data) {
    M2C_UNK sound_id;
    M2C_UNK tile_x;
    M2C_UNK tile_y;
    M2C_UNK tile_mask;
    M2C_UNK special_tile_mask;
    s16 spiral_ticks;
    s16 fade_ticks;
    s32 effect_flags;
    s32 entity_flags;
    s32 orbit_offset;
    s32 finished;
    s32 dispatch_zero;
    u16 scale_y;
    u16 scale_x;
    u8 blue;
    s32 phase;
    u8 entity_type;
    u8 red;
    u8 green;
    void *entity = entity_data;

    phase = ((Rec_func_800AD058_arg0 *)state)->unk_9B;
    if (phase == 1) {
        goto start_fade;
    }
    if ((s32) phase < 2) {
        dispatch_zero = 0;
        if (phase == 0) {
            goto wait_to_start;
        }
        return dispatch_zero;
    }
    if (phase == 2) {
        goto update_fade;
    }
    dispatch_zero = 3;
    if (phase == 3) {
        dispatch_zero = 0;
        goto update_spiral;
    }
     /* MATCH: keep the phase-3 branch followed by the default epilogue jump. */
    return 0;

wait_to_start:
    ASM_KEEP(dispatch_zero);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    if (*D_8008346A != 0) {
        return 0;
    }
    ((Rec_func_800AD058_arg0 *)state)->unk_9B = 1U;
start_fade:
    ((S_800AD058_1 *)sprite)->unk_10 = 0x20;
    ((S_800AD058_1 *)sprite)->unk_12 = (u16) (((S_800AD058_1 *)sprite)->unk_12 - 0x80);
    ((S_800AD058_1 *)sprite)->unk_14 = (u16) (((S_800AD058_1 *)sprite)->unk_14 | 0xC);
    ((S_800AD058_2 *)entity)->unk_1C = (s32) (((S_800AD058_2 *)entity)->unk_1C | 0x10000000);
    entity_type = ((S_800AD058_2 *)entity)->unk_13;
    if ((entity_type == 5) || (sound_id = 0x805, (entity_type == 0x1E))) {
        sound_id = 0x806;
    }
    func_800A56E0(sound_id);
    ((S_800AD058_1 *)sprite)->unk_0C.at00.v = 0x808080;
    ((Rec_func_800AD058_arg0 *)state)->unk_96 = 0x10;
    ((Rec_func_800AD058_arg0 *)state)->unk_9B = (u8) (((Rec_func_800AD058_arg0 *)state)->unk_9B + 1);
update_fade:
    red = (u8) ((S_800AD058_1 *)sprite)->unk_0C.at00.v;
    ((S_800AD058_1 *)sprite)->unk_0C.at00u.v = (s8) (red + ((s32) (0x20 - red) / (s16) ((Rec_func_800AD058_arg0 *)state)->unk_96));
    green = ((S_800AD058_1 *)sprite)->unk_0C.at01.v;
    blue = ((S_800AD058_1 *)sprite)->unk_0C.at02.v;
    ((S_800AD058_1 *)sprite)->unk_0C.at01.v = (u8) (green + ((s32) (0x20 - green) / (s16) ((Rec_func_800AD058_arg0 *)state)->unk_96));
    ((S_800AD058_1 *)sprite)->unk_0C.at02.v = (u8) (blue + ((s32) (0x20 - blue) / (s16) ((Rec_func_800AD058_arg0 *)state)->unk_96));
    fade_ticks = (u16) ((Rec_func_800AD058_arg0 *)state)->unk_96 - 1;
    ((Rec_func_800AD058_arg0 *)state)->unk_96 = fade_ticks;
    if (((fade_ticks << 0x10) <= 0) || (finished = 0, ((((S_800AD058_1 *)sprite)->unk_14 & 0x8000) != 0))) {
        if (!(((S_800AD058_2 *)entity)->unk_14 & 0x20000000)) {
            s32 *shared_state = D_80083460;
            if (shared_state[4] == (s32) (entity - 0x20)) {
                shared_state[4] = (s32) (shared_state[4] & 0x7FFFFFFF);
            }
        }
        entity_flags = ((S_800AD058_2 *)entity)->unk_14;
        if (!(entity_flags & 0x4000)) {
            func_800A2FE0(entity);
            func_800A32A4(entity);
            if (((S_800AD058_2 *)entity)->unk_49 == 0) {
                goto finish_removal;
            }
            {
                if (((S_800AD058_2 *)entity)->unk_4B & 0x20) {
                    goto finish_removal;
                }
                func_800B8228(((S_800AD058_3 *)position)->unk_00.at02.v, ((S_800AD058_3 *)position)->unk_04.at02.v, ((S_800AD058_2 *)entity)->unk_88, entity + 0x48);
                goto finish_removal;
            }
        }
        if (!(entity_flags & 0x20000000)) {
            func_800ACF88(entity);
        }
        func_800A2FE0(entity);
        func_800A32A4(entity);
        if ((func_80042900(entity, 0x1B) << 0x10) == 0) {
            effect_flags = ((S_800AD058_2 *)entity)->unk_1C;
            tile_x = ((S_800AD058_1 *)sprite)->unk_24;
            tile_y = ((S_800AD058_1 *)sprite)->unk_25;
            special_tile_mask = 0x3000;
            if (effect_flags & 0x2000) {
                special_tile_mask = 0x300;
            }
            func_8009A3D0(tile_x, tile_y, special_tile_mask);
        }
        func_8009A028(entity);
        ((S_800AD058_2_pre *)entity)[-1].unk_00 = (u16) (((S_800AD058_2_pre *)entity)[-1].unk_00 | 0x8000);
        D_800814A0[0] |= 0x8000;
        func_800A56E0(0x609);
        return 1;
    }
    return finished;

update_spiral:
    orbit_offset = (((Rec_func_800AD058_arg0 *)state)->unk_96 * func_80064584(((S_800AD058_1 *)sprite)->unk_27 << 7)) << 5;
    ((S_800AD058_3 *)position)->unk_00.at00.v += (s32) ((((Rec_D_800E3D7C *)D_80083780)->unk_00.at00_s32.v + orbit_offset - ((S_800AD058_3 *)position)->unk_00.at00.v) >> 2);
    orbit_offset = (((Rec_func_800AD058_arg0 *)state)->unk_96 * func_800644B8(((S_800AD058_1 *)sprite)->unk_27 << 7)) << 5;
    ((S_800AD058_3 *)position)->unk_04.at00.v += (s32) ((((Rec_D_800E3D7C *)D_80083780)->unk_04.at00_s32.v + orbit_offset - ((S_800AD058_3 *)position)->unk_04.at00.v) >> 2);
    {
        s32 vertical_step;

        vertical_step = func_800644B8(((Rec_func_800AD058_arg0 *)state)->unk_96 * 8) >> 6;
        ((S_800AD058_2 *)entity)->unk_88 = (s16) ((u16) ((S_800AD058_2 *)entity)->unk_88 +
            ((((Rec_D_800E3D7C *)D_80083780)->unk_08.at02_s16.v - vertical_step - ((S_800AD058_2 *)entity)->unk_88) >> 4));
    }
    scale_x = ((S_800AD058_1 *)sprite)->unk_1C;
    scale_y = ((S_800AD058_1 *)sprite)->unk_1E;
    ((S_800AD058_1 *)sprite)->unk_1C = (u16) (scale_x - ((s32) scale_x / (s16) ((Rec_func_800AD058_arg0 *)state)->unk_96));
    ((S_800AD058_1 *)sprite)->unk_1E = (u16) (scale_y - ((s32) scale_y / (s16) ((Rec_func_800AD058_arg0 *)state)->unk_96));
    ((S_800AD058_1 *)sprite)->unk_27 = (u8) (((S_800AD058_1 *)sprite)->unk_27 + 1);
    spiral_ticks = (u16) ((Rec_func_800AD058_arg0 *)state)->unk_96 - 1;
    ((Rec_func_800AD058_arg0 *)state)->unk_96 = spiral_ticks;
    finished = 0;
    if ((spiral_ticks << 0x10) <= 0) {
        register s32 *shared_state ASM_REG("$2") = D_80083460;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        ((S_800AD058_5 *)shared_state)->unk_0A = (u16) (((S_800AD058_5 *)shared_state)->unk_0A - 1);
        func_800A2FE0(entity);
        func_800A32A4(entity);
        goto finish_removal;
    }
    return finished;

finish_removal:
    if ((func_80042900(entity, 0x1B) << 0x10) == 0) {
        effect_flags = ((S_800AD058_2 *)entity)->unk_1C;
        tile_x = ((S_800AD058_1 *)sprite)->unk_24;
        tile_y = ((S_800AD058_1 *)sprite)->unk_25;
        tile_mask = 0x3000;
        if (effect_flags & 0x2000) {
            tile_mask = 0x300;
        }
        func_8009A3D0(tile_x, tile_y, tile_mask);
    }
    func_8009A028(entity);
    ((S_800AD058_2_pre *)entity)[-1].unk_00 = (u16) (((S_800AD058_2_pre *)entity)[-1].unk_00 | 0x8000);
    finished = 1;
    D_800814A0[0] |= 0x8000;
    return finished;
}
