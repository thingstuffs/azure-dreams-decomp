#include "common.h"
#include "shared/dungeon_moving_views.h"
#include "shared/types3a_types.h"

   /* arg0 in spawn_radial_effect_objects */

typedef struct S_800A895C_1 {
    union { u16 u16; s32 s32; } unk_00;   /* accessed as both */
    union { u16 u16; s32 s32; } unk_04;   /* accessed as both */
    union { u16 u16; s32 s32; } unk_08;   /* accessed as both */
} S_800A895C_1;   /* arg1 in spawn_radial_effect_objects */

   /* object in spawn_radial_effect_objects */

typedef struct S_800A895C_3 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800A895C_3;   /* ((S_800A895C_2 *)object)->unk_08 in spawn_radial_effect_objects */


extern s32 scale_random_to_unsigned_halfword_limit(u16 value);
extern s32 func_800644B8(s32 value);
extern s32 func_80064584(s32 value);
extern s32 rand(void);
extern void *create_reverse_motion_effect(void *source_motion, s16 flags);

typedef struct {
    s16 unk0;
    s16 x;
    s16 unk4;
    s16 z;
    s16 unk8;
    u16 y;
    s32 fieldC;
    s32 field10;
    s16 unk14;
    s16 field16;
} StackRecord;

/* Spawns objects at randomized positions around a center with evenly spaced angles. */
void spawn_radial_effect_objects(MovingPosition *center, S_800A895C_1 *spread, s32 count) {
    StackRecord record;
    s32 angle;
    s32 angle_step;
    s32 first_trig_value;
    s32 spawn_index;
    s32 angle_value;
    s32 y;
    u16 initial_y;
    ObjectPayloadView *object;

    if (count != 0) {
        angle_step = 0x1000 / count;
        angle = rand();
        initial_y = center->unk_0A;
        record.field16 = -4;
        record.y = initial_y;
        for (spawn_index = 0; spawn_index < count; spawn_index++) {
            record.x = (center->unk_02 +
                        scale_random_to_unsigned_halfword_limit(spread->unk_00.u16)) -
                       (spread->unk_00.s32 / 2);
            record.z = (center->unk_06 +
                        scale_random_to_unsigned_halfword_limit(spread->unk_04.u16)) -
                       (spread->unk_04.s32 / 2);
            y = (center->unk_0A +
                 scale_random_to_unsigned_halfword_limit(spread->unk_08.u16)) -
                (spread->unk_08.s32 / 2);
            record.y = y;
            record.fieldC = func_80064584(angle) << 5;
            first_trig_value = func_800644B8(angle);
            {
                void *record_ptr = &record;
                first_trig_value <<= 5;
                record.field10 = first_trig_value;
                object = create_reverse_motion_effect(record_ptr, angle);
            }
            if (object != 0) {
                angle_value = func_800644B8(angle) << 5;
                if (angle_value < 0) {
                    angle_value = -angle_value;
                }
                ((S_800A895C_3 *)(object->unk_08))->unk_14 = -angle_value;
            }
            angle += angle_step;
        }
    }
}
