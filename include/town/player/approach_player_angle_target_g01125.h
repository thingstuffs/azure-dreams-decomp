#ifndef TOWN_PLAYER_APPROACH_PLAYER_ANGLE_TARGET_G01125_H
#define TOWN_PLAYER_APPROACH_PLAYER_ANGLE_TARGET_G01125_H
/* Approach player angle target. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01125 - CL:town/func_8009D150. */

#include "common.h"
#include "m2c_compat.h"
#include "sdk/libgte.h"

typedef struct S_8009A724_0 {
    u8 pad_00[0x4];
    s32 * unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x4];
    s16 unk_10;
    u8 pad_12[0x24];
    u16 unk_36;
    u16 unk_38;
} S_8009A724_0;

/* arg0 in approach_player_angle_target */
typedef struct S_8009A724_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_8009A724_1;

typedef struct S_8009A81C_0 {
    u8 pad_00[0x4];
    s32 * unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2A];
    s16 unk_36;
    s16 unk_38;
} S_8009A81C_0;

/* arg0 in update_player_countdown_values */
typedef struct S_8009A81C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_8009A81C_1;

extern M2C_UNK D_8009A81C;

/* Shared import declarations; data casts preserve each measured view. */


/* Functions defined in this translation unit. */
void approach_player_angle_target(S_8009A724_0 *state, S_8009A724_1 *position);
void update_player_countdown_values(S_8009A81C_0 *state, S_8009A81C_1 *values);
void player_no_op(void);
s16 approach_scalar_target(s32 divisor, s16 current, s16 target);

#endif
