#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"

typedef struct S_818BDB44_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_818BDB44_0;   /* obj in create_random_spin_effect */

typedef struct S_818BDB44_1 {
    u8 pad_00[0xE];
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    s16 unk_16;
    s32 unk_18;
} S_818BDB44_1;   /* payload in create_random_spin_effect */

typedef struct S_818BDB44_2 {
    u8 pad_00[0x12];
    u16 unk_12;
    u8 pad_14[0x4];
    s32 unk_18;
} S_818BDB44_2;   /* arg0 in create_random_spin_effect */

typedef struct S_818BDB44_4 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
} S_818BDB44_4;   /* arg1 in create_random_spin_effect */

typedef struct S_818BDB44_5 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
} S_818BDB44_5;   /* dst in create_random_spin_effect */

typedef struct {
    s32 words[6];
} Copy24;

extern s32 rand();
extern void register_node(void *, void *);

extern u8 D_80024F4C[];
extern u8 tinted_sprite_entries[];

/* Allocate and initialize a randomized object from the source and initial data. */
s32 create_random_spin_effect(S_818BDB44_2 *source, S_818BDB44_4 *init_data)
{
    ObjectNodeHeader *object;
    S_818BDB44_1 *payload;
    SpriteFrameState *part;
    s32 variant_random;
    s32 random_value;
    s32 scale;

    object = allocate_flagged_object_node(0x212);
    if (object != 0) {
        payload = (u8 *)object + 0x20;
        object->update_callback = D_80024F4C;
        ((S_818BDB44_0 *)object)->unk_20 = source;
        payload->unk_0E = 0;
        payload->unk_10 = 0;

        variant_random = rand();
        payload->unk_12 = variant_random % 7;
        payload->unk_14 = source->unk_12;

        random_value = rand();
        payload->unk_16 = random_value % 0x1000;
        payload->unk_18 = source->unk_18;

        part = object->sprite;
        part->color.c.b = 0x80;
        part->color.c.g = 0x80;
        part->color.c.r = 0x80;
        part->clut = 0x7E01;
        part->source = tinted_sprite_entries;
        part->flags = part->flags | 0xC;
        part->tpage_abr = part->tpage_abr | 0x20;
        part->flags = part->flags | 0x100;

        random_value = rand();
        {
            void *setup_object = object;

            part->angle_z = random_value % 0x1000;
            scale = 0x400;
            part->scale_y = scale;
            part->scale_x = scale;
            register_node(setup_object, project_sprite_chain);
        }

        {
            S_818BDB44_5 *object_data;
            {
                object_data = object->position;
                *(Copy24 *)object_data = *(Copy24 *)init_data;
                return (s32)object;
            }
        }
    }
    {
        s32 failure_result = 0;
        return failure_result;
    }
}
