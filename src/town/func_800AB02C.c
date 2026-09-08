#include "common.h"
#include "m2c_compat.h"

s32 func_800374F4();                         /* extern */
M2C_UNK func_8003DB94();  /* extern */
void *func_8003FC64(s32);               /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 rand();                           /* extern */
extern M2C_UNK D_80045340;
extern s16 D_8006CCD8[8];
extern s16 D_8006CCE8[8];
extern M2C_UNK D_800A86BC;
extern M2C_UNK D_800F15AC;

typedef struct S_800A878C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800A878C_0;   /* temp_v0 in func_800A878C */

typedef struct S_800A878C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800A878C_1;   /* temp_s1 in func_800A878C */

typedef struct S_800A878C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
} S_800A878C_2;   /* arg0 in func_800A878C */

typedef struct S_800A878C_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800A878C_3;   /* temp_s0 in func_800A878C */

typedef struct S_800A878C_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    s32 unk_04;
} S_800A878C_4;   /* temp_s3 in func_800A878C */

/* Creates an effect behind the source with randomized reverse motion and launch speed. */
void *func_800A878C(S_800A878C_2 *source_motion, u32 flags) {
    s16 *direction_y;
    s16 launch_speed;
    s16 stored_speed;
    s32 direction_index;
    s32 speed_roll;
    s32 velocity_x;
    s32 velocity_y;
    u32 direction;
    S_800A878C_3 *sprite;
    S_800A878C_1 *motion;
    S_800A878C_4 *launch;
    void *effect;

    direction = (flags >> 9) & 7;
    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        motion = ((S_800A878C_0 *)effect)->unk_08;
        sprite = ((S_800A878C_0 *)effect)->unk_0C;
        ((S_800A878C_0 *)effect)->unk_10 = &D_800A86BC;
        func_8004491C(effect, &D_80045340);
        direction_index = direction;
        motion->unk_02 = (s16) (source_motion->unk_02 - (D_8006CCD8[direction_index] * 0x10));
        direction_y = &D_8006CCE8[direction_index];
        motion->unk_06 = (s16) (source_motion->unk_06 - (*direction_y * 0x10));
        motion->unk_0A = (u16) source_motion->unk_0A;
        velocity_x = 0 - (source_motion->unk_0C * ((rand(direction_y) & 1) + 2));
        launch = effect + 0x20;
        if (velocity_x < 0) {
            velocity_x += 0xF;
        }
        motion->unk_0C = (s32) (velocity_x >> 4);
        velocity_y = 0 - (source_motion->unk_10 * ((rand() & 1) + 2));
        if (velocity_y < 0) {
            velocity_y += 0xF;
        }
        motion->unk_10 = (s32) (velocity_y >> 4);
        motion->unk_14 = (s32) ((~rand() & 1) << 0xF);
        func_8003DB94(sprite, &D_800F15AC, 0);
        sprite->unk_0E = 0xFF;
        sprite->unk_0D = 0xFF;
        sprite->unk_0C = 0xFF;
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_10 = 0x60;
        sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
        speed_roll = func_800374F4(7);
        launch_speed = speed_roll + func_800374F4(7);
        launch->unk_02 = launch_speed;
        motion->unk_14 = (s32) (0 - (launch_speed << 0x10));
        stored_speed = launch->unk_02;
        launch->unk_04 = (s32) ((s32) (stored_speed * stored_speed) / 2);
    }
    return effect;
}
