#ifndef MODULE_DUNGEON_OVL_9950E8_H
#define MODULE_DUNGEON_OVL_9950E8_H

#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "engine/node.h"
#include "engine/node/allocation.h"

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

   /* the 0x2 bytes before arg0 in func_80170970, addressed as arg0[-1] */

typedef struct S_80975170_0 {
    u8 pad_00[0x96];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x12];
    s16 unk_AA;
    u8 pad_AC[0x4];
    void * unk_B0;
} S_80975170_0;   /* arg0 in func_80170970 */

   /* arg1 in func_80170970 */

   /* src in func_80170970 */

extern void advance_sprite_animation_and_textures(void *render_state);

/* Copy the source transform, advance and fade the effect, and flag completion when its timer expires. */
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_links.h"

typedef struct {
    s32 word0;
    s32 word1;
    s32 word2;
    s32 word3;
} Block16;

extern void select_sprite_entry(void *, u8, s32);
extern void func_80047784(void *, u8, s32);
void advance_and_fade_transformed_effect(void *effect, MovingPosition *transform, SpriteFrameState *render_state);
extern u8 D_80174128[8];

typedef struct S_80975244_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x12];
    s16 unk_AA;
    u8 pad_AC[0x4];
    void * unk_B0;
} S_80975244_0;   /* temp_v1 in func_80170A44 */

typedef struct S_80975244_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80975244_3;   /* arg3 in func_80170A44 */

   /* temp_v1_2 in func_80170A44 */

   /* arg1 in func_80170A44 */

/* Creates an effect from a sprite template and sets its directional frame and position. */
#endif
