#include "common.h"
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

typedef struct S_800C02C4_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    void * unk_2C;
} S_800C02C4_1;   /* arg2 in initialize_object_rendering_resources */


void unlink_node_if_registered(void *);                      /* extern */
void apply_pending_indexed_value();          /* extern */
void apply_pending_table_entry();          /* extern */
extern char D_800A62E8[];
extern char D_800A630C[];
extern M2C_UNK D_800C035C;
extern M2C_UNK D_800D0C58;

/* Initializes object and rendering data and registers its resources. */
void initialize_object_rendering_resources(void *object_data, void *unused, S_800C02C4_1 *render_data) {
    ((S_800C02C4_0 *)((u8 *)object_data - 0x10))->unk_00 = &D_800C035C;
    ((S_800C02C4_0 *)((u8 *)object_data - 0x10))->unk_22 = -1;
    ((S_800C02C4_0 *)((u8 *)object_data - 0x10))->unk_20 = 0xC00;
    ((S_800C02C4_0 *)((u8 *)object_data - 0x10))->unk_28 = 0xC00;
    render_data->unk_1E = 0x1000;
    render_data->unk_1C = 0x1000;
    render_data->unk_0C = 0x808080;
    render_data->unk_2C = &D_800D0C58;
    store_the_in_forwards_field_10_callee_800949_c_4((s32) &D_800D0C58, object_data, render_data);
    unlink_node_if_registered(object_data);
    apply_pending_table_entry(0x24, &D_800A62E8);
    apply_pending_indexed_value(0xE4, &D_800A630C);
}
