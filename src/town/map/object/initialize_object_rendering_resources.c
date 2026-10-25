#include "common.h"
#include "town/player.h"
#include "town/map/course.h"
#include "m2c_compat.h"
#include "shared/town_handler.h"

typedef struct S_800C02C4_0 {
    void * unk_00;
    u8 pad_04[0x1C];
    s16 unk_20;
    s16 unk_22;
    u8 pad_24[0x4];
    s16 unk_28;
} S_800C02C4_0;   /* arg0 in initialize_object_rendering_resources; pointer addresses record offset 0x10 */

void unlink_node_if_registered(void *);                      /* extern */
void apply_pending_indexed_value();          /* extern */
void apply_pending_table_entry();          /* extern */

extern void D_800C035C();
extern M2C_UNK D_800D0C58;

/* Initializes object and rendering data and registers its resources. */
void initialize_object_rendering_resources(TownCourseActor *object_data, void *unused, SpriteFrameState *render_data) {
    ((S_800C02C4_0 *)((u8 *)object_data - 0x10))->unk_00 = &D_800C035C;
    object_data->sprite_direction = -1;
    object_data->facing.s = 0xC00;
    object_data->unk_18 = 0xC00;
    render_data->scale_y = 0x1000;
    render_data->scale_x = 0x1000;
    render_data->color.word = 0x808080;
    render_data->frameTable = &D_800D0C58;
    store_the_in_forwards_field_10_callee_800949_c_4((s32) &D_800D0C58, object_data, render_data);
    unlink_node_if_registered(object_data);
    apply_pending_table_entry(0x24, store_value_and_get_masked_offset);
    apply_pending_indexed_value(0xE4, read_and_clear_stored_value);
}
