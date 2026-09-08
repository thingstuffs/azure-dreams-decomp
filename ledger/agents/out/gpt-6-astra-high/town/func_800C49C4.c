#include "common.h"

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

extern s32 func_80033B2C(s32, s32);
extern void func_800C15C0(s32, s32);
extern u8 D_80083780[8];
extern u8 D_800C21F8[];

/* Applies an eligible nearby object's effects and updates its callback. */
s32 func_800C2124(TownObject *object) {
    TownPosition *position;
    register s32 coord_value ASM_REG("$2");
    register s32 offset_x ASM_REG("$5");
    s32 check_id;
    register void *callback ASM_REG("$3");
    s16 distance_x;
    register s16 distance_z ASM_REG("$18");

    position = (TownPosition *)D_80083780;
    ASM_KEEP(position);
    offset_x = object->x;
    coord_value = position->x;
    check_id = object->check_id;
    position = (TownPosition *)(s32)position->z;
    offset_x -= coord_value;
    coord_value = object->z;
    distance_x = offset_x;
    if (offset_x < 0) {
        distance_x = -distance_x;
    }
    coord_value -= (s32)position;
    distance_z = coord_value;
    if (coord_value < 0) {
        distance_z = -distance_z;
    }
    ASM_KEEP(check_id);
    if (func_80033B2C(check_id, offset_x) != 0) {
        if (object->range_x >= distance_x) {
            coord_value = distance_z;
            if (object->range_z >= coord_value) {
                func_800C15C0(object->effect_a, object->effect_b);
                coord_value = 1;
                ASM_KEEP(coord_value);
                callback = D_800C21F8;
                object->callback = callback;
                return;
            }
        }
        return 0;
    }
    return 0;
}

