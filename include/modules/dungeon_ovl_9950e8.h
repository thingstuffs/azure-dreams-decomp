#ifndef MODULE_DUNGEON_OVL_9950E8_H
#define MODULE_DUNGEON_OVL_9950E8_H

#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_809750E8_0 {
    u16 unk_00;
    u8 pad_02[0x96];
    s16 unk_98;
    u8 pad_9A[0x12];
    s16 unk_AC;
} S_809750E8_0;   /* arg0 in func_801708E8; pointer addresses record offset 0x2 */


#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)


/* Applies countdown-scaled intensity and sets completion flags when the countdown expires. */

typedef struct S_80975170_0_pre {
    u16 unk_00;
} S_80975170_0_pre;   /* the 0x2 bytes before arg0 in func_80170970, addressed as arg0[-1] */

typedef struct S_80975170_0 {
    u8 pad_00[0x96];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x12];
    s16 unk_AA;
    u8 pad_AC[0x4];
    void * unk_B0;
} S_80975170_0;   /* arg0 in func_80170970 */

typedef struct S_80975170_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80975170_1;   /* arg1 in func_80170970 */

typedef struct S_80975170_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80975170_2;   /* src in func_80170970 */


extern void func_800478B8(void *render_state);


/* Copy the source transform, advance and fade the effect, and flag completion when its timer expires. */
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"

typedef struct {
    s32 word0;
    s32 word1;
    s32 word2;
    s32 word3;
} Block16;

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, u8, s32);
void advance_and_fade_transformed_effect(void *effect, S_80975170_1 *transform, Rec_D_80082E80 *render_state);
extern u8 D_80174128[8];

typedef struct S_80975244_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x12];
    s16 unk_AA;
    u8 pad_AC[0x4];
    void * unk_B0;
} S_80975244_0;   /* temp_v1 in func_80170A44 */

typedef struct S_80975244_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80975244_1;   /* temp_v0 in func_80170A44 */

typedef struct S_80975244_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x2];
    u16 unk_22;
    u8 pad_24[0x8];
    M2C_UNK * unk_2C;
} S_80975244_2;   /* temp_s0 in func_80170A44 */

typedef struct S_80975244_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80975244_3;   /* arg3 in func_80170A44 */

typedef struct S_80975244_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80975244_4;   /* temp_v1_2 in func_80170A44 */

typedef struct S_80975244_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80975244_5;   /* arg1 in func_80170A44 */

/* Creates an effect from a sprite template and sets its directional frame and position. */
#endif
