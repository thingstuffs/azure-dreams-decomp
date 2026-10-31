#ifndef DUNGEON_MONSTER_BELDO_H
#define DUNGEON_MONSTER_BELDO_H

/* Function contracts owned by src/dungeon/monster/beldo/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_moving_views.h"
#include "shared/entity.h"

typedef struct AttachedSpriteWithOffsetBody {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x68];
    u16 unk_94;
    u8 pad_96[0x16];
    union {
        void * pointer;
        s32 integer;
    } unk_AC;
    union { s16 s; u16 u; } unk_B0;
    union { s16 s; u16 u; } unk_B2;
    union { s16 s; u16 u; } unk_B4;
    s16 unk_B6;
    u8 pad_B8[0x1C];
    union {
        u32 word;
        u16 halfwords[8];
        u8 bytes[0x10];
    } unk_D4;
    union {
        u16 halfword;
        u16 halfwords[8];
    } unk_E4;
    union {
        u16 halfword;
        u16 halfwords[8];
        u32 words[4];
    } unk_F4;
    u8 pad_104[0xE];
} AttachedSpriteWithOffsetBody;

void create_attached_sprite_with_offset(void *owner_data, MovingPosition *base_position, SpriteFrameState *sprite_template, s16 offset_id);
void copy_part_state(AttachedSpriteWithOffsetBody *root, void *out_pos_arg, void *dst_part_arg);
void create_flagged_actor_object_2(AttachedSpriteWithOffsetBody *root, void *output_pos, void *target_data);


void run_actor_callbacks_and_adjust_global_flag(void *entity_ptr, void *motion, void *check_arg, void *actor_arg);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void update_actor_movement_and_height(ActorRecord *entity_arg, ObjectPosition *motion_arg, SpriteFrameState *monster_arg);

#endif
