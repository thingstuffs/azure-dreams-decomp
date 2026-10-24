/* Complete resident-engine cohort contract. Review pending. */
#ifndef DUNGEON_ENGINE_MENU_EFFECTS_H
#define DUNGEON_ENGINE_MENU_EFFECTS_H
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/def_table.h"
#include "shared/dir_step.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/entity_height_offsets.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "shared/gpu_packets.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"

/* Callback-specific marker body, initialized by create_familiar_selection_marker. */
typedef union MarkerHalf { s16 s; u16 u; } MarkerHalf;
typedef struct FamiliarMarkerWork {
    ActorRecord **target;
    u8 pad_04[8];
    MarkerHalf phase;
    MarkerHalf frames_left;
} FamiliarMarkerWork;

/* Twelve-byte sprite command. Flag 0x20 changes the last word from texture
 * bytes to an attachment callback; draw_transformed_sprite_parts advances 12. */
typedef struct SpritePartCommand {
    u8 flags, code;
    u8 offset_x, offset_y;
    u16 tpage, clut;
    union {
        struct { u8 u, v, width, height; } texture;
        s32 (*callback)(void *, s32, void *, void *, void *);
    } data;
} SpritePartCommand;

/* POLY_FT4 packet view preserving word, halfword and seam-byte operations. */
typedef struct SpritePartQuad {
    union { s32 word; struct { u8 addr[3], length; } bytes; } tag;
    s32 color;
    struct {
        union { s32 word; struct { s16 x, y; } parts; } xy;
        union { s16 pair; struct { u8 u, v; u16 attr; } bytes; } uv;
    } vertex[4];
} SpritePartQuad;

void update_familiar_selection_marker(FamiliarMarkerWork *state, ObjectPosition *position_arg, SpriteFrameState *marker_arg);

void *allocate_flagged_object_node(int flags);
#endif
