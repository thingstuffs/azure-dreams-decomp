#include "modules/town_town_windows.h"

/* Collect rectangles overlapping the query bounds into a null-terminated list. */
void func_8009D940(func_800A01E0_S_8009D940_1 *query_max, func_800A01E0_S_8009D940_2 *query_min, void **entries, void **matches) {
    s32 top;
    s32 left;
    void **entry_ptr;
    void **match_ptr;
    func_800A01E0_S_8009D940_0 *rect;

    entry_ptr = entries;
    match_ptr = matches;
    if (*entry_ptr != NULL) {
        do {
            rect = *entry_ptr;
            left = rect->unk_00 + rect->unk_04;
            if (query_max->unk_00 >= left) {
                top = rect->unk_02 + rect->unk_06;
                if ((query_max->unk_02 >= top) && ((left + rect->unk_08) >= query_min->unk_00)
                    && ((top + rect->unk_0A) >= query_min->unk_02)) {
                    *match_ptr = rect;
                    match_ptr = (void **)((s8 *)((void **)((s8 *)match_ptr + 4)));
                }
            }
            entry_ptr = (void **)((s8 *)((void **)((s8 *)entry_ptr + 4)));
        } while (*entry_ptr != NULL);
    }
    *match_ptr = NULL;
}
