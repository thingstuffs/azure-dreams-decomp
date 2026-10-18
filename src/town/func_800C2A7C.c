#include "common.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "m2c_compat.h"
#include "shared/entity.h"

extern void *initialize_scene_object_in_buffer();
extern void initialize_circular_list_head();
extern void handle_insert_initialize_two_values_status_flags();
extern void initialize_pointer_table_self_links();
extern void initialize_the_store_two_values_set_state_flags();
extern void run_the_three_update_routines_context();
extern s16 query_lowered_transform_position();

extern M2C_UNK D_8006ADBC;
extern M2C_UNK D_800C02C4;
extern M2C_UNK D_800CFCB4;
extern M2C_UNK D_800D0420;
extern s32 D_800D0438;
extern M2C_UNK D_800FE490;

typedef struct S_800C01DC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_800C01DC_0;

typedef struct S_800C01DC_1 {
    u8 pad_00[0x10];
    u16 * unk_10;
    u16 unk_14;
    u16 unk_16;
} S_800C01DC_1;   /* base in initialize_object_at_current_position */

/* Initializes the town object and sets its position from the current position entry. */
void initialize_object_at_current_position(void) {
    S_800C01DC_0 *object;

    D_800D0438 = 0;
    object = initialize_scene_object_in_buffer(0, ((void *)&D_80083498.next), 0x22);
    object->unk_10 = &D_800C02C4;
    object->unk_0C = &D_80082E80.unk_000;
    object->unk_08 = &D_80083780.x.v;
    initialize_circular_list_head();
    handle_insert_initialize_two_values_status_flags(&D_800CFCB4, &D_80083780.x.v, &D_800D0420);
    initialize_pointer_table_self_links();
    initialize_the_store_two_values_set_state_flags(&D_800FE490, &D_80083780.x.v, &D_800D0420);
    {
        s8 *position_data;
        u16 *position_entry;

        position_data = (s8 *) &D_8006ADBC;
        position_entry = ((S_800C01DC_1 *)position_data)->unk_10;
        D_80083780.x.w.i = (s16) (((S_800C01DC_1 *)position_data)->unk_14 + position_entry[0]);
        D_80083780.y.w.i = (s16) (((S_800C01DC_1 *)position_data)->unk_16 + position_entry[1]);
        D_80083780.z.w.i = query_lowered_transform_position(&D_80083780.x.v);
    }
    run_the_three_update_routines_context(&D_80083780.x.v);
}
