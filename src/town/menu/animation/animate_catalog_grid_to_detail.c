#include "common.h"
#include "records/Rec_func_801237A4_arg0.h"
#include "shared/object_payload.h"
#include "town/menu.h"
#include "town/menu/catalog_parts.h"

extern void store_cached_value_at_pointer(void);

/* Updates or clears table entries according to the request code. */
void animate_catalog_grid_to_detail(Rec_func_801237A4_arg0 *request)
{
    s32 action_index;

    action_index = (s16)(request->unk_04.as_u16 - 1);
    switch (action_index) {
    case 0:
        store_cached_value_at_pointer();
        refresh_catalog_primary_detail(request);
        return;
    case 7:
    case 8:
    case 9:
    {
        s32 entry_index;
        u8 *entry_table;
        ItemMenuPart **entry_slot;
        ItemMenuPart *entry;
        CatalogDisplayVector *entry_data;
        u16 field_value;

        entry_index = 0x1C;
        entry_table = (u8 *)&catalog_display_node_slots;
        entry_slot = (ItemMenuPart **)(entry_table + 0x70);
        do {
            entry = *entry_slot;
            entry_data = (CatalogDisplayVector *)entry->vector;
            field_value = entry_data->unsigned_halves.unk_02;
            do {
                entry_index++;
            } while (0);
            field_value += 0x100;
            entry_data->unsigned_halves.unk_02 = field_value;
            entry_slot += 1;
        } while (entry_index < 0x62);
    }
        return;
    case 10:
    {
        s32 entry_index;
        u8 *entry_table;
        ItemMenuPart **entry_slot;
        ItemMenuPart *entry;

        entry_index = 0x1E;
        entry_table = (u8 *)&catalog_display_node_slots;
        entry_slot = (ItemMenuPart **)(entry_table + 0x78);
        do {
            do {
                entry = *entry_slot;
            } while (0);
            entry_index++;
            entry->handler = 0;
            entry_slot += 1;
        } while (entry_index < 0x62);
    }
    case 11:
    case 12:
    case 13:
    {
        s32 entry_index;
        u8 *entry_table;
        ItemMenuPart **entry_slot;
        ItemMenuPart *entry;
        CatalogDisplayVector *entry_data;
        u16 field_value;

        entry_index = 0x1C;
        entry_table = (u8 *)&catalog_display_node_slots;
        entry_slot = (ItemMenuPart **)(entry_table + 0x70);
        do {
            entry = *entry_slot;
            entry_data = (CatalogDisplayVector *)entry->vector;
            field_value = entry_data->unsigned_halves.unk_02;
            do {
                entry_index++;
            } while (0);
            field_value += 0x100;
            entry_data->unsigned_halves.unk_02 = field_value;
            entry_slot += 1;
        } while (entry_index < 0x62);
    }
        break;
    case 14:
    {
        s32 entry_index;
        u8 *entry_table;
        ItemMenuPart **entry_slot;
        ItemMenuPart *entry;
        CatalogDisplayVector *entry_data;
        u16 field_value;

        entry_index = 0x1C;
        entry_table = (u8 *)&catalog_display_node_slots;
        entry_slot = (ItemMenuPart **)(entry_table + 0x70);
        do {
            entry = *entry_slot;
            entry_data = (CatalogDisplayVector *)entry->vector;
            field_value = entry_data->unsigned_halves.unk_02;
            do {
                entry_index++;
            } while (0);
            field_value += 0x100;
            entry_data->unsigned_halves.unk_02 = field_value;
            entry_slot += 1;
        } while (entry_index < 0x62);
    }
        {
            s32 entry_index;
            u8 *entry_table;
            ItemMenuPart **entry_slot;
            ItemMenuPart *entry;

            entry_index = 0x1C;
            entry_table = (u8 *)&catalog_display_node_slots;
            entry_slot = (ItemMenuPart **)(entry_table + 0x70);
            do {
                do {
                    entry = *entry_slot;
                } while (0);
                entry_index++;
                entry->handler = 0;
                entry_slot += 1;
            } while (entry_index < 0x1E);
        }
    case 19:
    default:
        break;
    }
}
