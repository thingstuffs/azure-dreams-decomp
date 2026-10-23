#include "common.h"
#include "shared/object_node.h"
#include "shared/entity_objects.h"

typedef struct S_800BFB00_0 {
    u8 pad_00[0x10];
    void (*unk_10)(void);
    u8 pad_14[0xC];
    u16 unk_20;
} S_800BFB00_0;

typedef struct S_800BFB00_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x2];
    s16 unk_08;
    s16 unk_0A;
    u8 pad_0C[0x2];
    s16 unk_0E;
} S_800BFB00_1;

extern void *allocate_list_node(s32, void *);
extern void spawn_randomized_timed_objects(void);

/* town_rain_in: creates a rain object with its callback, preset values, and position. */
void town_rain_in(s16 x, s16 y) {
    u16 preset_value;
    S_800BFB00_1 *state;
    ObjectNodeHeader *object;

    object = allocate_list_node(2, ((u8 *)(&scene_object_list_anchor)));
    if (object != 0) {
        object->update_callback = spawn_randomized_timed_objects;
        ((S_800BFB00_0 *)object)->unk_20 = ((u16)view_reference_entity.x.w.i);
        state = (s8 *)object + 0x20;
        state->unk_02 = ((u16)view_reference_entity.y.w.i);
        preset_value = ((u16)view_reference_entity.z.w.i);
        state->unk_08 = x;
        state->unk_0A = y;
        state->unk_0E = 6;
        state->unk_04 = preset_value;
    }
}
