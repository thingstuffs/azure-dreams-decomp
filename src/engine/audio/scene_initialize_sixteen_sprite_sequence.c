#include "shared/object_node.h"
#include "common.h"
#include "engine/audio.h"
#include "engine/effect.h"
#include "engine/graphics.h"
#include "engine/node.h"
#include "slus/data.h"



/* Sub-object embedded at offset 0x20 of the entity (same family as
 * init_color_fade_effect / init_fade_in_out_effect): owner backpointer, four zeroed shorts,
 * a table pointer, then a walked slot array of s32 (16 entries, +4/step). */
struct S_8005313C;

typedef struct S_80053374_Sub {
    /* 0x00 */ void *owner;
    /* 0x04 */ s16 f04;
    /* 0x06 */ s16 f06;
    /* 0x08 */ s16 f08;
    /* 0x0A */ s16 f0A;
    /* 0x0C */ void *tbl;
            /* 0x10 */ /* s32 slots[16] walked via s32* p = (s32 *)sub; p[4].. */
} S_80053374_Sub;

typedef struct S_80053374_obj {
    ObjectNodeHeader header;
    /* 0x20 */ S_80053374_Sub sub;
} S_80053374_obj;

extern void init_shaded_line_effect(void *a0, s16 a1);

/* Initializes the entity state and sub-object, creates up to 16 slots, and initializes the global table. */
void scene_initialize_sixteen_sprite_sequence(S_80053374_obj *entity, void *owner)
{
    s16 *sub;
    s32 slot_index;
    s32 *slot_cursor;
    void *slot;

    slot_index = 0;
    sub = (s16 *)((u8 *)entity + 0x20);
    entity->header.update_callback = play_timed_animation_sequence;
    entity->sub.owner = owner;
    sub[2] = 0;
    sub[3] = 0;
    sub[4] = 0;
    sub[5] = 0;
    *(void **)(sub + 6) = &sixteen_sprite_sequence_source;
    slot_cursor = (s32 *)sub;

    do {
        slot = allocate_list_node(0x212, &entity->header.next);
        if (slot != 0) {
            init_shaded_line_effect(slot, (s16)slot_index);
            slot_cursor[4] = (s32)slot;
        }
        slot_index++;
        slot_cursor++;
    } while (slot_index < 0x10);

    init_sixteen_packed_templates();
}
