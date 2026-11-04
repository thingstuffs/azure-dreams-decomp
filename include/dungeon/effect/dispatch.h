/* Complete resident-engine cohort contract. Review pending. */
#ifndef DUNGEON_ENGINE_EFFECT_DISPATCH_H
#define DUNGEON_ENGINE_EFFECT_DISPATCH_H
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_floor.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "shared/gpu_packets.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/sprite_frame_state.h"

/* Lifetime and activity index for the vertical particle burst update. */
typedef struct VerticalParticleBurstBody {
    u8 pad_00[0xC];
    s16 effect_index;
    u8 pad_0E[0x2];
    s16 remaining_ticks;
} VerticalParticleBurstBody;

/* The central effect creator places this state at object +0x20. The item
 * caller stores its floor-position index in the same body at state +0x20. */
typedef struct CentralChildEffectState {
    void *parent;
    u8 pad4[9];
    s8 angle;
    u8 pad14[2];
    s16 mode;
    s16 value;
    u8 pad20[4];
    s16 height;
    s16 frame;
    s16 speed;
    s16 limit;
    s16 item_position_index;
} CentralChildEffectState;

struct S_800C5D80_0;
void advance_effect_motion_and_fade(VerticalParticleBurstBody *effect_data,
                                    struct S_800C5D80_0 *motion,
                                    SpriteFrameState *primitive);

/* Eight halfword offsets per axis at 0x800DCEAC and 0x800DCEBC.
 * The next registered table starts at 0x800DCECC. */
extern u16 direction_x_offsets[8];
extern u16 direction_y_offsets[8];

void *allocate_flagged_object_node(int flags);
#endif
