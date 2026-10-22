#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_moving_views.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800C542C_2_pre {
    void * unk_00;
    s32 unk_04;
    u8 pad_08[0x10];
} S_800C542C_2_pre;   /* the 0x18 bytes before arg0 in create_orbiting_teleport_effect, addressed as arg0[-1] */

   /* target in create_orbiting_teleport_effect */

   /* source in create_orbiting_teleport_effect */

typedef struct S_800C542C_5 {
    u8 pad_00[0x1C];
    void * unk_1C;
    s32 unk_20;
    void * unk_24;
    u8 pad_28[0x2];
    s16 unk_2A;
    s16 unk_2C;
    s16 unk_2E;
    s16 unk_30;
    s16 unk_32;
    u8 pad_34[0x2];
    s16 unk_36;
} S_800C542C_5;   /* record in create_orbiting_teleport_effect */

extern u8 D_800C4F20[];
extern u8 D_800C55A0[];
extern u8 D_800DF630[];

extern void register_node(void *, void *);
extern int rand(void);
extern void play_sound_if_enabled(s32);

/* Creates and initializes a display object linked to its owner. */
void *create_orbiting_teleport_effect(void *owner, s16 effect_value, s16 direction, s16 effect_mode)
{
    ObjectNodeHeader *object;
    SpriteFrameState *display;
    MovingPosition *source;
    MovingPosition *target;
    S_800C542C_5 *record;
    void *callback;
    s16 saved_mode;
    s16 initial_state;
    s32 direction_fixed;
    s32 parent;

    object = allocate_flagged_object_node(0x12);
    saved_mode = effect_mode;
    if (object != NULL) {
        callback = D_800C4F20;
        object->unk_10 = callback;
        register_node(object, D_800C55A0);

        display = object->sprite;
        display->color.word = 0x808080;
        display->source = D_800DF630;
        display->unk_06 = 0xC;

        source = ((S_800C542C_2_pre *)owner)[-1].unk_00;
        target = object->position;
        target->unk_02 = source->unk_02;
        target->unk_06 = source->unk_06;
        record = (u8 *)object + 0x20;
        target->unk_0A = source->unk_0A;

        record->unk_30 = effect_value;
        direction_fixed = direction << 0x10;
        record->unk_1C = source;
        parent = ((S_800C542C_2_pre *)owner)[-1].unk_04;
        record->unk_2E = (s16)(direction_fixed >> 5);
        record->unk_24 = owner;
        record->unk_20 = parent;
        display->unk_20 = 0x2000;
        record->unk_32 = 0x400;
        record->unk_2C = rand();

        if (effect_mode == 1) {
            record->unk_2A = 0;
        } else {
            if (effect_mode == 0) {
                play_sound_if_enabled(0x802);
                initial_state = 0x10;
            } else {
                play_sound_if_enabled(0x802);
                initial_state = 0x20;
            }
            record->unk_2A = initial_state;
        }

        record->unk_36 = saved_mode;
        ((Rec_D_80082E80 *)owner)->unk_14.at00_s32.v |= 0x100000;
    }
    return object;
}

/* MECHANISM: The true rowbase function uses a 0x30 frame with s2/s4/s5/s3
   holding the four arguments, a post-call s6 copy, and s1/s0 object bases.
   The 800C5558/800C555C targets are local mode-store joins, not tail calls. */
