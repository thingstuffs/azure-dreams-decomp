#include "common.h"
#include "shared/entity_objects.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800AD058_arg0.h"

typedef s32 M2C_UNK;

s32 func_800644B8(s32);
s32 func_80064584(s32);
void func_8009A028(); /* extern */
void func_8009A3D0();
void func_800A2FE0(); /* extern */
s32 func_800A32A4(); /* extern */
s32 func_800A56E0(); /* extern */
void func_800ACF88(); /* extern */
s32 func_80042900();
void *func_800B8228();


typedef struct S_800AD058_1 {
    u8 pad_00[0xC];
    union {
        struct { s32 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
    } unk_0C;   /* overlapping accesses */
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
    s32 sound_id;
    s32 tile_x;
    s32 tile_y;
    s32 tile_mask;
    s32 special_tile_mask;
    s16 spiral_ticks;
    s16 fade_ticks;
    s32 effect_flags;
    s32 entity_flags;
    s32 orbit_offset;
    s32 finished;
    s32 dispatch_zero;
    s16 active_count;
    u16 scale_y;
    u16 scale_x;
    u8 blue;
    s32 phase;
    u8 entity_type;
    u8 red;
    u8 green;
    void *entity = entity_data;

    switch (((Rec_func_800AD058_arg0 *)state)->unk_9B) {
    case 0:
        if ((active_count = dungeonStatus.unk_0A) != 0) {
            return 0;
        }
        ((Rec_func_800AD058_arg0 *)state)->unk_9B = 1U;
    case 1:
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
    case 2:
        red = (u8) ((S_800AD058_1 *)sprite)->unk_0C.at00.v;
        ((S_800AD058_1 *)sprite)->unk_0C.at00u.v = (s8) (red + ((s32) (0x20
            - red) / (s16) ((Rec_func_800AD058_arg0 *)state)->unk_96));
        green = ((S_800AD058_1 *)sprite)->unk_0C.at01.v;
        blue = ((S_800AD058_1 *)sprite)->unk_0C.at02.v;
        ((S_800AD058_1 *)sprite)->unk_0C.at01.v = (u8) (green + ((s32) (0x20
            - green) / (s16) ((Rec_func_800AD058_arg0 *)state)->unk_96));
        ((S_800AD058_1 *)sprite)->unk_0C.at02.v = (u8) (blue + ((s32) (0x20
            - blue) / (s16) ((Rec_func_800AD058_arg0 *)state)->unk_96));
        fade_ticks = (u16) ((Rec_func_800AD058_arg0 *)state)->unk_96 - 1;
        ((Rec_func_800AD058_arg0 *)state)->unk_96 = fade_ticks;
        if (((fade_ticks << 0x10) <= 0) || (finished = 0, ((((S_800AD058_1 *)sprite)->unk_14 & 0x8000) != 0))) {
            if (!(((S_800AD058_2 *)entity)->unk_14 & 0x20000000)) {
                s32 *shared_state = ((s32 *)(&dungeonStatus));
                if (shared_state[4] == (s32) (entity - 0x20)) {
                    shared_state[4] = (s32) (shared_state[4] & 0x7FFFFFFF);
                }
            }
            entity_flags = ((S_800AD058_2 *)entity)->unk_14;
            if (!(entity_flags & 0x4000)) {
                func_800A2FE0(entity);
                func_800A32A4(entity);
                if (((S_800AD058_2 *)entity)->unk_49 != 0 && !(((S_800AD058_2 *)entity)->unk_4B & 0x20)) {
                    func_800B8228(((S_800AD058_3 *)position)->unk_00.at02.v, ((S_800AD058_3 *)position)->unk_04.at02.v,
                        ((S_800AD058_2 *)entity)->unk_88, entity + 0x48);
                }
                break;
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
            objectFlagBlock.flags |= 0x8000;
            func_800A56E0(0x609);
            return 1;
        }
        return finished;

    case 3:
        orbit_offset = (((Rec_func_800AD058_arg0 *)state)->unk_96 * func_80064584(((S_800AD058_1 *)sprite)->unk_27
            << 7)) << 5;
        ((S_800AD058_3 *)position)->unk_00.at00.v += (s32) ((((EntityRec *)((u8 *)(&D_80083780)))->x.v + orbit_offset
            - ((S_800AD058_3 *)position)->unk_00.at00.v) >> 2);
        orbit_offset = (((Rec_func_800AD058_arg0 *)state)->unk_96 * func_800644B8(((S_800AD058_1 *)sprite)->unk_27
            << 7)) << 5;
        ((S_800AD058_3 *)position)->unk_04.at00.v += (s32) ((((EntityRec *)((u8 *)(&D_80083780)))->y.v + orbit_offset
            - ((S_800AD058_3 *)position)->unk_04.at00.v) >> 2);
        {
            s32 vertical_step;

            vertical_step = func_800644B8(((Rec_func_800AD058_arg0 *)state)->unk_96 * 8) >> 6;
            ((S_800AD058_2 *)entity)->unk_88 = (s16) ((u16) ((S_800AD058_2 *)entity)->unk_88 +
                ((((EntityRec *)((u8 *)(&D_80083780)))->z.w.i - vertical_step - ((S_800AD058_2 *)entity)->unk_88)
                    >> 4));
        }
        scale_x = ((S_800AD058_1 *)sprite)->unk_1C;
        scale_y = ((S_800AD058_1 *)sprite)->unk_1E;
        ((S_800AD058_1 *)sprite)->unk_1C = (u16) (scale_x
            - ((s32) scale_x / (s16) ((Rec_func_800AD058_arg0 *)state)->unk_96));
        ((S_800AD058_1 *)sprite)->unk_1E = (u16) (scale_y
            - ((s32) scale_y / (s16) ((Rec_func_800AD058_arg0 *)state)->unk_96));
        ((S_800AD058_1 *)sprite)->unk_27 = (u8) (((S_800AD058_1 *)sprite)->unk_27 + 1);
        spiral_ticks = (u16) ((Rec_func_800AD058_arg0 *)state)->unk_96 - 1;
        ((Rec_func_800AD058_arg0 *)state)->unk_96 = spiral_ticks;
        finished = 0;
        if ((spiral_ticks << 0x10) <= 0) {
            s32 *shared_state = ((s32 *)(&dungeonStatus));

            active_count = ((S_800AD058_5 *)shared_state)->unk_0A;
            active_count--;
            ((S_800AD058_5 *)shared_state)->unk_0A = active_count;
            func_800A2FE0(entity);
            func_800A32A4(entity);
        } else {
            return finished;
        }
        break;
    default:
        return 0;
    }
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
    objectFlagBlock.flags |= 0x8000;
    return finished;
}
