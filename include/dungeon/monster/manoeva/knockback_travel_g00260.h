#ifndef DUNGEON_MONSTER_MANOEVA_KNOCKBACK_TRAVEL_G00260_H
#define DUNGEON_MONSTER_MANOEVA_KNOCKBACK_TRAVEL_G00260_H
#include "dungeon/level.h"
#include "engine/graphics/select_sprite_entry_api.h"
#include "shared/entity.h"
#include "engine/node/allocation.h"
#include "shared/object_node.h"
#include "engine/node.h"

struct ObjectPosition;
/* Samples nearby terrain and creates a copied-sprite travel effect for a reachable tile. */

#include "common.h"
#include "shared/dir_step.h"
#include "shared/sprite_frame_state.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;









typedef struct {
    u8 pad0[0xC];
    u32 color;
    u8 pad10[2];
    u16 f12;
    u8 pad14[8];
    s16 f1C;
    s16 f1E;
    u8 pad20[8];
    s32 f28;
} Display;

typedef struct KnockbackTravelObjectBody {
    s16 *facing;
    u8 pad04[8];
    ObjectNodeHeader *unk_0C;
    ActorRecord *unk_10;
    SpriteFrameState *source;
    struct ObjectPosition *position;
    u8 pad1C[2];
    union { s16 s; u16 u; } unk_1E;
    union { s16 s; u16 u; } unk_20;
    u8 pad22[0x10];
    s16 unk_32;
    s16 unk_34;
    union { s16 s; u16 u; } unk_36;
    union { u16 s; u16 u; } unk_38;
    u16 unk_3A;
    u16 owner_byte;
} KnockbackTravelObjectBody;

typedef KnockbackTravelObjectBody Work;

typedef struct {
    ObjectNodeHeader node;
    Work work;
} Object;

extern s32 *manoeva_knockback_callback_address;
extern s8 D_801766F0[];

extern void project_vector_by_view_angle(Vec3s *, Vec3s *);


/* Functions defined in this translation unit. */
s32 check_adjacent_tile_height(s16 tile_x, s16 tile_y, s32 height, s16 direction, s16 *sample_out);
void create_knockback_travel_object(ActorRecord *owner_data,struct ObjectPosition *position_arg, SpriteFrameState *source_arg, ActorRecord *context_arg);
void update_knockback_travel_object(KnockbackTravelObjectBody *motion, void *position, SpriteFrameState *record);

#endif
