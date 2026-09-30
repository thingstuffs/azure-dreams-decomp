#include "common.h"
#include "shared/entity_objects.h"
extern int abs(int);

typedef struct {
    void *callback;
    s16 x;
    s16 z;
    s16 range_x;
    s16 range_z;
    u8 pad_C[4];
    s16 effect_a;
    s16 effect_b;
    s16 check_id;
} TownObject;

typedef struct {
    s16 pad_0;
    s16 x;
    s16 pad_4;
    s16 z;
    s16 pad_8;
    s16 pad_A;
} TownPosition;

extern s32 func_80033B2C(s32);
extern void tw_sd_sq_ld_call(s32, s32);
extern u8 D_800C21F8[];

/* Applies an eligible nearby object's effects and updates its callback. */
s32 func_800C2124(TownObject *object) {
    TownPosition *position;
    s32 coord_value_3;
    s32 offset_x;
    s32 check_id;
    register void *callback;
    s16 distance_x;
    s16 distance_z;

    position = (TownPosition *)((u8 *)(&D_80083780));
    ASM_KEEP(position);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    offset_x = object->x - position->x;
    distance_x = abs(offset_x);
    distance_z = abs(object->z - position->z);
    check_id = object->check_id;
    if (func_80033B2C(check_id) != 0) {
        if (object->range_x >= distance_x) {
            coord_value_3 = distance_z;
            if (object->range_z >= coord_value_3) {
                tw_sd_sq_ld_call(object->effect_a, object->effect_b);
                callback = D_800C21F8;
                object->callback = callback;
                return 1;
            }
        }
        return 0;
    }
    return 0;
}
