/* Complete resident-engine cohort contract; review pending. */
#ifndef DUNGEON_ENGINE_DUNGEON_UTIL_H
#define DUNGEON_ENGINE_DUNGEON_UTIL_H
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80083160.h"
#include "records/Rec_func_800A5DFC_arg1.h"
#include "shared/dungeon_floor.h"
#include "shared/dungeon_item_entries.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/gpu_packets.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/sys_flags.h"
#include "shared/tile_object.h"
#include "modules/dungeon_engine_dungeon_util_fragment_c05e4.h"
#include "modules/dungeon_engine_dungeon_util_fragment_c1094.h"
#include "dungeon/item/message/text.h"
s32 display_text_with_fullwidth_adjustment(s8 *text);
/* Cleared object work for create_textured_ellipse_effect and its pulsing
 * callback. The constructor stores the linked actor at +4 and seeds a
 * four-tick brightening phase; the callback then fades over sixteen ticks. */
typedef union PulseHalf {
    s16 s;
    u16 u;
    struct { u8 low, high; } bytes;
} PulseHalf;
typedef struct PulsingEffectWork {
    u8 pad_00[4];
    void *target;
    u8 pad_08[0x5C];
    PulseHalf phase;
    PulseHalf timer;
    PulseHalf tick;
    PulseHalf brightness;
} PulsingEffectWork;

void update_pulsing_effect_brightness(PulsingEffectWork *effect, s32 unused, SpriteFrameState *sprite);

#endif
