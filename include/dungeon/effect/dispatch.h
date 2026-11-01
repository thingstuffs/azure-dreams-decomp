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
