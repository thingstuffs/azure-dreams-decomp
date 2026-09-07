#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64();            /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern u8 D_80083160[];
extern M2C_UNK D_80083498;
extern M2C_UNK D_800BB894;

typedef struct Copy24 {
    s32 words[6];
} Copy24;

typedef struct S_800BB798_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_800BB798_0;   /* arg0 in func_800BB798 */

typedef struct S_800BB798_1 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_800BB798_1;   /* temp_s1 in func_800BB798 */

typedef struct S_800BB798_2 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
} S_800BB798_2;   /* temp_v0 in func_800BB798 */

typedef struct S_800BB798_3 {
    u8 pad_00[0x48];
    s16 unk_48;
    s16 unk_4A;
} S_800BB798_3;   /* temp_v0_2 in func_800BB798 */

/* Converts polar spawn data to components and initializes a new object with it. */
s32 func_800BB798(S_800BB798_0 *spawn_data, s16 state_48, s16 state_4a) {
    s32 angle;
    s32 radius_fixed;
    s32 radius;
    u8 *angle_state;
    s32 component;
    s32 trig_factor;
    void *object;
    S_800BB798_3 *object_state;
    void *object_data;

    angle_state = D_80083160;
    angle = spawn_data->unk_10 + ((S_800BB798_1 *)angle_state)->unk_C8;
    radius_fixed = spawn_data->unk_0C;
    trig_factor = func_80064584(angle);
    radius = radius_fixed >> 0xC;
    component = radius * trig_factor;
    spawn_data->unk_0C = component;
    angle = spawn_data->unk_10 + ((S_800BB798_1 *)angle_state)->unk_C8;
    trig_factor = func_800644B8(angle);

    component = radius * trig_factor;
    spawn_data->unk_10 = component;
    object = func_8003FD64(0x312, &D_80083498);
    if (object != NULL) {
        object_data = ((S_800BB798_2 *)object)->unk_08;
        ((S_800BB798_2 *)object)->unk_10 = &D_800BB894;
        *(Copy24 *)object_data = *(Copy24 *)spawn_data;
        object_state = object + 0x20;
        object_state->unk_48 = state_48;
        object_state->unk_4A = state_4a;
    }
    return 0;
}
