#include "shared/entity_height_offsets.h"
#include "shared/entity.h"
#include "common.h"
#include "shared/object_node.h"
#include "m2c_compat.h"

typedef struct {
    s32 words[3];
} TableEntry;

extern s32 resolve_record_orientation_or_fallback();
extern void *allocate_list_node();
extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */

extern s32 D_80026680[3];
extern TableEntry linked_effect_direction_entries[];
extern s32 linked_mesh_processor_address[3];

typedef struct S_80026C88_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80026C88_0;   /* callee_arg in create_and_link_six_offset_objects */

typedef struct S_80026C88_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_80026C88_1;

typedef struct S_80026C88_2 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0xE];
    s16 unk_1A;
    u8 pad_1C[0x2];
    s16 unk_1E;
    u8 pad_20[0x2];
    s16 unk_22;
    u8 pad_24[0x42];
    s16 unk_66;
    u8 pad_68[0x6];
    s16 unk_6E;
} S_80026C88_2;


typedef struct S_80026C88_4 {
    u8 pad_00[0x8];
    TableEntry * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80026C88_4;

typedef struct S_80026C88_5 {
    u8 pad_00[0x24];
    u16 unk_24;
    u16 unk_26;
    u16 unk_28;
} S_80026C88_5;

/* Create and link up to six objects with source-relative positions and initialized render data. */
void *create_and_link_six_offset_objects(u16 x, u16 y, s16 z, void *source)
{
    u16 position_offset[3];
    s32 *callback;
    TableEntry *table_entry;
    s32 object_index;

    ObjectPosition *coords;
    ObjectNodeHeader *object;
    void *point_cursor;
    S_80026C88_0 *source_object;
    union { u16 *offset; S_80026C88_4 *render; } pointers;
    void *list_head;

    list_head = NULL;
    source_object = source;
    pointers.offset = position_offset;
    position_offset[0] = position_offset[1] = 0;
    if (resolve_record_orientation_or_fallback(source_object->unk_08, source_object, pointers.offset, 0) == 0) {
        position_offset[2] = (0 - entity_height_offsets[0]) + 0x10;
    }
    object_index = 0;
    callback = D_80026680;
    table_entry = linked_effect_direction_entries;
    do {
        object = allocate_list_node(0x212, ((s32 *)(&scene_object_list_anchor)));
        if (object != NULL) {
            s32 point_index;
            S_80026C88_2 *state;
            void *self_link;

            object->update_callback = callback;
            register_node(object, linked_mesh_processor_address);
            state = ((void *)object) + 0x20;
            state->unk_1A = (s16) (x + position_offset[0]);
            state->unk_1E = (s16) (y + position_offset[1]);
            state->unk_22 = (s16) (z + position_offset[2]);
            coords = object->position;
            coords->x.w.i = x;
            *((u16 *)&coords->velocity_x + 1) = x;
            coords->y.w.i = y;
            *((u16 *)&coords->velocity_y + 1) = y;
            coords->z.w.i = z - 0x100;
            *((u16 *)&coords->velocity_z + 1) = z - 0x100;
            pointers.render = object->sprite;
            pointers.render->unk_1E = 0x1000;
            pointers.render->unk_1C = 0x1000;
            self_link = ((void *)object) + 0x38;
            pointers.render->unk_08 = table_entry;
            pointers.render->unk_14 = (u16) (pointers.render->unk_14 | 0xC);
            ((S_80026C88_1 *)object)->unk_20 = self_link;
            state->unk_66 = 0x20;
            state->unk_6E = object_index;
            for (point_index = 0; point_index < 8; point_index++) {
                point_cursor = (u8 *)state + point_index * 8;
                ((S_80026C88_5 *)point_cursor)->unk_24 = (u16) *(u16 *)&coords->x.w.i;
                ((S_80026C88_5 *)point_cursor)->unk_26 = (u16) *(u16 *)&coords->y.w.i;
                ((S_80026C88_5 *)point_cursor)->unk_28 = (u16) *(u16 *)&coords->z.w.i;
            }
            state->unk_08 = list_head;
            list_head = object;
        }
        object_index += 1;
        table_entry += 1;
    } while (object_index < 6);
    return object;
}

