#ifndef TOWN_MENU_RANDOMIZED_EFFECT_MOTION_G00570_H
#define TOWN_MENU_RANDOMIZED_EFFECT_MOTION_G00570_H
/* inferred-strong G00570: randomized_effect_motion_g00570; shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D0B20. */

#include "common.h"
#include "shared/sprite_source.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_D_80082E80.h"
#include "m2c_compat.h"
#include "shared/entity.h"

typedef struct S_800A3508_1 {
    void * unk_00;
    u8 pad_04[0x1E];
    s16 unk_22;
    s32 unk_24;
    u8 pad_28[0x8];
    s32 unk_30;
    s32 unk_34;
} S_800A3508_1;

typedef struct S_800A378C_0 {
    void (*unk_00)();
    u8 pad_04[0x1E];
    s16 unk_22;
    s32 unk_24;
    u8 pad_28[0x4];
    s32 unk_2C;
    s32 unk_30;
    s32 unk_34;
} S_800A378C_0;

extern void select_record_entry_and_value(void *,void *, s32);
extern void register_node(void *, void *);
extern s32 rsin(s32);
extern s32 rcos(s32);
extern u8 D_800A378C[];
extern s16 D_800D0B18[];
extern u8 *D_800D0B50[];
/* extern */
void advance_sprite_animation_and_textures(void *entity);
/* extern */
extern void D_800A38A8(void *object, void *unused_context, u8 *primitive);

extern SpriteSourceEntry *D_800D0B20[];

/* Functions defined in this translation unit. */
void initialize_randomized_motion_vector(u8 *obj, s32 *vec, SpriteFrameState *record);
void advance_motion_and_reset_appearance(S_800A378C_0 *state, ObjectPosition *transform, SpriteFrameState *appearance);

#endif
