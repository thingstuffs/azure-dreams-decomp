/* Complete resident-engine cohort contract. Review pending. */
#ifndef DUNGEON_ENGINE_MENU_EFFECTS_H
#define DUNGEON_ENGINE_MENU_EFFECTS_H
#include "common.h"
#include "dungeon/effect/tracked_sprite.h"
#include "shared/sprite_frame_state.h"
#include "shared/sprite_part_command.h"
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

/* Allocated by create_timed_model_effect; update_arcing_effect advances its phase and arc. */
typedef struct ArcingEffectBody {
    void *unk_00;
    void *unk_04;
    ObjectPosition *unk_08;
    s32 unk_0C;
    u8 pad_10[0x10];
    s16 phase;
    u8 pad_22[0x4];
    s16 arc_steps;
    u16 unk_28;
    u8 pad_2A[0x8];
    s16 unk_32;
} ArcingEffectBody;

/* Callback-specific marker body, initialized by create_familiar_selection_marker. */
typedef union MarkerHalf { s16 s; u16 u; } MarkerHalf;
typedef struct FamiliarMarkerWork {
    ActorRecord **target;
    u8 pad_04[8];
    MarkerHalf phase;
    MarkerHalf frames_left;
} FamiliarMarkerWork;


/* POLY_FT4 packet view preserving word, halfword and seam-byte operations. */
typedef struct SpritePartQuad {
    union { s32 word; struct { u8 addr[3], length; } bytes; } tag;
    s32 color;
    struct {
        union { s32 word; struct { s16 x, y; } parts; } xy;
        union { s16 pair; struct { u8 u, v; u16 attr; } bytes; } uv;
    } vertex[4];
} SpritePartQuad;

/* Wrapped VRAM scroll state stored after the object-node header. */
typedef struct WrappedTextureScrollBody {
    u8 pad_00[2];
    u16 scroll_offset;
    u8 pad_04[8];
    u16 scroll_step;
} WrappedTextureScrollBody;

/* Texture bounds, segment count and vertex colors for draw_textured_ellipse. */
typedef struct DungeonParameters {
    u8 pad0[4];
    u16 flags;
    u16 texture;
    u8 x0;
    u8 y0;
    u8 x1;
    u8 y1;
    u8 x2;
    u8 y2;
    u16 count;
    SpriteColor center_color;
    SpriteColor outer_color;
} DungeonParameters;

void update_familiar_selection_marker(FamiliarMarkerWork *state, ObjectPosition *position_arg, SpriteFrameState *marker_arg);
void update_wrapped_texture_scroll(WrappedTextureScrollBody *scroll_state);
s32 is_selectable_menu_target(ActorRecord *object);
void create_timed_model_effect(ObjectNodeHeader *owner, u16 *context, void *child, void *tail);

void *allocate_flagged_object_node(int flags);
#endif
