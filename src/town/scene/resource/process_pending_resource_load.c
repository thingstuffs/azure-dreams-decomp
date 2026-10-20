#include "common.h"

extern u32 D_80081458[];
/* D_800CF838 through the next catalog object, D_800CFBA0: 0x368 bytes. */
extern s32 D_800CF838[218];
extern s32 D_800CF874[203];

extern void func_80067014(s32 value);
extern s32 load_cd_resource(s32 entry_value);

/* Processes the selected catalog entry, stores its result, and updates the selection. */
void process_pending_resource_load(void)
{
    s32 entry_result;
    s32 *catalog_entries;

    if (D_800CF874[0] != 0) {
        func_80067014(0);
        catalog_entries = &D_800CF838[15];
        entry_result = load_cd_resource(catalog_entries[D_800CF874[0]]);
        D_80081458[0] = entry_result;
        if (D_800CF874[0] == 1) {
            D_800CF874[0] = 0;
            return;
        }
        D_800CF874[0] = 1;
    }
}
