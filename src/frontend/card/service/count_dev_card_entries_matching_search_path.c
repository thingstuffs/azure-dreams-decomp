#include "common.h"
#include "frontend/card/service.h"
#include "frontend/card/server_aliases.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"
#include "frontend/card/dev_card_directory_data.h"

extern s32 dev_card_paths[2];


/* Collects entries matching the selected search path and returns their count. */
s32 count_dev_card_entries_matching_search_path(void) {
    s32 search_path[8];
    s32 *path_prefix;
    DevCardDirectoryEntry *entry;
    s32 entry_count;

    entry_count = 0;
    entry = dev_card_directory;
    path_prefix = &dev_card_paths[0];
    if (card_selected_channel != 0) {
        path_prefix = &dev_card_paths[0] + 1;
    }
    func_8007BF80(&search_path, *path_prefix);
    func_8007BF50(&search_path, &D_804000F4);
    if (func_8007CAB8(&search_path, entry) != 0) {
        do {
            entry_count += 1;
            entry++;
        } while (func_8007CAC8(entry) == entry);
    }
    return entry_count;
}
