#include "common.h"

extern u32 loaded_town_resource_attributes[];
/* D_800CF838 through the next catalog object, D_800CFBA0: 0x368 bytes. */
extern s32 town_resource_descriptors[218];
extern s32 town_resource_request[203];

extern void DrawSync(s32 value);
extern s32 load_cd_resource(s32 entry_value);

/* Processes the selected catalog entry, stores its result, and updates the selection. */
void process_pending_resource_load(void)
{
    s32 entry_result;
    s32 *catalog_entries;

    if (town_resource_request[0] != 0) {
        DrawSync(0);
        catalog_entries = &town_resource_descriptors[15];
        entry_result = load_cd_resource(catalog_entries[town_resource_request[0]]);
        loaded_town_resource_attributes[0] = entry_result;
        if (town_resource_request[0] == 1) {
            town_resource_request[0] = 0;
            return;
        }
        town_resource_request[0] = 1;
    }
}
