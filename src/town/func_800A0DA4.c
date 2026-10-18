#include "modules/town_town_windows.h"

/* Sets object type fields and selects the corresponding resource. */
void set_object_types_and_resource(void *object, s32 index, void *output)
{
    u32 resource;
    u8 mode;
    u8 type;

    mode = BU(object, 0x94);
    if (mode == 0) {
        configure_the_set_mode_n_4(object, index, D_800D073C);
        initialize_optional_object_state(object, index, output, D_800D076C);
        BU(object, 0x4C) = BU(object, 0x95);
        BU(object, 0x4D) = BU(object, 0x96);
    } else
    if ((s8)mode == -1) {
        configure_the_set_mode_n_3(object, index, D_800D073C);
        initialize_optional_object_state(object, index, output, 0);
        BU(object, 0x4C) = BU(object, 0x95);
        BU(object, 0x4D) = BU(object, 0x96);
    } else {
        configure_the_set_mode_n_4(object, index, D_800D073C);
        initialize_optional_object_state(object, index, output, D_800D0788);
        {
            u8 *type_table;

            type_table = (u8 *)0x80010000;
            BU(object, 0x4C) = type_table[BU(object, 0x95) * 4 + 0x980];
            BU(object, 0x4D) = type_table[BU(object, 0x95) * 4 + 0x981];
            BU(object, 0x4E) = type_table[BU(object, 0x95) * 4 + 0x982];
            BU(object, 0x4F) = type_table[BU(object, 0x95) * 4 + 0x983];
        }
        initialize_entity_flags_transform_type_dependent_variant(object, object, index, output);
    }

    if (is_unk_18_n_12_unk_1_a_between_n_37_n_41() == 0) {
        resource = (u32)&cleanup_or_dispatch_object;
        PP(object, -0x10) = (u8 *)resource;
    } else {
        resource = (u32)dispatch_object_or_switch_alternate_state;
        PP(object, -0x10) = (u8 *)resource;
    }
    if ((u32)(BU(object, 0x4D) - 0x12) < 2U) {
        PP(object, 0xC) = D_800D0754;
    }

    type = BU(object, 0x4D);
    if (type == 0x12) {
        resource = (u32)&D_8006E240;
    } else if (type == 0x13) {
        u8 *data_base = (u8 *)0x80010000;

        set_object_state_for_mode(
            object,
            output,
            BU(object, 0x4C),
            *(s32 *)&data_base[
                ((data_base[BU(object, 0x95) * 4 + 0x983] & 0x3F) * 0x54)
                    + 0xA94]);
        return;
    } else {
        resource = lookup_item_category_mapped_value(BU(object, 0x4D), BU(object, 0x4C));
    }
    WD(output, 8) = resource;
}
