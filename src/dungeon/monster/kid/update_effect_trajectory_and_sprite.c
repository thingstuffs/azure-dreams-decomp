#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_801743EC_0 {
    u8 pad_00[0x4];
    u16 unk_04;
    u8 pad_06[0x2];
    u16 unk_08;
    u8 pad_0A[0x42];
    union { s16 s; u16 u; } unk_4C;   /* accessed as both */
} S_801743EC_0;   /* arg0 in update_effect_trajectory_and_sprite */

   /* arg1 in update_effect_trajectory_and_sprite */

typedef struct {
    u8 bytes[8];
} Unaligned8;

typedef struct {
    void *field0;
    void *field4;
    Unaligned8 field8;
    Unaligned8 field10;
    s16 field18;
    s16 field1A;
    u32 unused1C;
} CallRecord;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
} OutputVector;

extern void advance_sprite_animation_and_textures(void *);
extern void transform_rotated_vertices(void *);

/* Update the effect trajectory and sprite, then flag completion when its animation ends. */
void update_effect_trajectory_and_sprite(void *effect, MovingPosition *position, void *sprite)
{
    CallRecord transform;
    OutputVector transformed_position;
    s16 state;
    s32 quarter_angle;
    u16 angle;

    state = ((S_801743EC_0 *)effect)->unk_4C.s;
    switch (state) {
    case 0:
        advance_sprite_animation_and_textures(sprite);
        if (((SpriteFrameState *)sprite)->flags & 0x6000) {
            ((SpriteFrameState *)sprite)->unk_04 = 0;
            ((SpriteFrameState *)sprite)->unk_05 = 0;
        }
        ((SpriteFrameState *)sprite)->color.word += 0xFFE7E7E8;
        if ((u8)((SpriteFrameState *)sprite)->color.word < 0x30U) {
            ((S_801743EC_0 *)effect)->unk_4C.u++;
        }

        angle = ((S_801743EC_0 *)effect)->unk_08 + 10;
        quarter_angle = (s32)(angle << 16) >> 18;
        ((S_801743EC_0 *)effect)->unk_08 = angle;
        ((S_801743EC_0 *)effect)->unk_04 = (u16)(-(quarter_angle * quarter_angle) >> 4);

        transform.field0 = (u8 *)effect + 4;
        transform.field4 = &transformed_position;
        transform.field8 = *(Unaligned8 *)((u8 *)effect + 0x14);
        transform.field10 = *(Unaligned8 *)((u8 *)effect + 0xC);
        transform.field18 = 1;
        transform.field1A = 1;
        transform_rotated_vertices(&transform);
        position->unk_02 = transformed_position.x;
        position->unk_06 = transformed_position.y;
        position->unk_0A = transformed_position.z;

        break;
    case 1:
        (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        break;
    }
}
