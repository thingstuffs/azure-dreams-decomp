#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/slus_callbacks.h"

#ifndef NULL
#define NULL 0
#endif

extern s32 register_node();
extern s32 rand();
extern M2C_UNK D_800254E0;
extern M2C_UNK tinted_sprite_entries;

typedef struct S_818BDD8C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_818BDD8C_0;

typedef struct S_818BDD8C_1 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_818BDD8C_1;

typedef struct S_818BDD8C_2 {
    u8 pad_00[0x12];
    u16 unk_12;
} S_818BDD8C_2;   /* arg0 in create_owner_tinted_effect */

typedef struct S_818BDD8C_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818BDD8C_4;   /* arg1 in create_owner_tinted_effect */

typedef struct S_818BDD8C_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818BDD8C_5;

/* Creates an object with its owner, rendering parameters, and supplied data. */
void *create_owner_tinted_effect(S_818BDD8C_2 *owner, S_818BDD8C_4 *initial_data)
{
    s32 copy_word_2;
    s32 copy_word_3;
    s32 copy_word_0;
    s32 copy_word_1;
    s32 draw_flags;
    s16 render_flags;
    SpriteFrameState *render;
    ObjectNodeHeader *object;
    S_818BDD8C_1 *state;
    S_818BDD8C_5 *object_data;

    object = allocate_flagged_object_node(0x212);
    if (object != NULL) {
        state = ((void *)object) + 0x20;
        object->update_callback = &D_800254E0;
        ((S_818BDD8C_0 *)object)->unk_20 = owner;
        state->unk_10 = 0;
        state->unk_14 = (u16)owner->unk_12;
        render = object->sprite;
        render->color.c.b = 0x80;
        render->color.c.g = 0x80;
        render->color.c.r = 0x80;
        render->clut = 0x7E01;
        render->source = &tinted_sprite_entries;
        render->flags |= 0xC;
        render->tpage_abr |= 0x20;
        render->flags |= 0x100;
        {
            void *call_obj;
            s32 scale;

            render->angle_z = (s16)(rand() % 0x1000);
            call_obj = object;
            scale = 0x400;
            render->scale_y = scale;
            render->scale_x = scale;
            register_node(call_obj, project_sprite_chain);
        }
        object_data = object->position;
        *object_data = *(S_818BDD8C_5 *)initial_data;
        return object;
    }
    return 0;
}

/* MECHANISM: The natural 0x20 frame holds owner/object/initial_data in s0/s1/s2. A v1 flags accumulator
   plus a separate v0 flags word prevents OR fusion. */
