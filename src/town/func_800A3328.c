#include "common.h"
#include "m2c_compat.h"

s32 func_800A0988();                       /* extern */
extern M2C_UNK D_800A0CF8;
extern M2C_UNK D_800D4404;

typedef struct S_800A0A88_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x3C];
    s16 unk_90;
} S_800A0A88_0;   /* temp_v1 in func_800A0A88 */

/* into_dn_door_demo_set: Initialize the dungeon entrance door demo state and handler. */
void func_800A0A88(void) {
    s32 door_object;
    S_800A0A88_0 *door;

    door_object = func_800A0988(&D_800D4404);
    door = door_object + 0x20;
    if (door_object != 0) {
        door->unk_90 = 6;
        door->unk_50 = &D_800A0CF8;
    }
}
