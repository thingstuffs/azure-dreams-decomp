#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009D940_0 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
} S_8009D940_0;   /* temp_t0 in func_8009D940 */

typedef struct S_8009D940_1 {
    s16 unk_00;
    s16 unk_02;
} S_8009D940_1;   /* arg0 in func_8009D940 */

typedef struct S_8009D940_2 {
    s16 unk_00;
    s16 unk_02;
} S_8009D940_2;   /* arg1 in func_8009D940 */

/* Collect rectangles overlapping the query bounds into a null-terminated list. */
void func_8009D940(S_8009D940_1 *query_max, S_8009D940_2 *query_min, void **entries, void **matches) {
    s32 top;
    s32 left;
    void **entry_ptr;
    void **match_ptr;
    S_8009D940_0 *rect;

    entry_ptr = entries;
    match_ptr = matches;
    if (*entry_ptr != NULL) {
        do {
            rect = *entry_ptr;
            left = rect->unk_00 + rect->unk_04;
            if (query_max->unk_00 >= left) {
                top = rect->unk_02 + rect->unk_06;
                if ((query_max->unk_02 >= top) && ((left + rect->unk_08) >= query_min->unk_00) && ((top + rect->unk_0A) >= query_min->unk_02)) {
                    *match_ptr = rect;
                    match_ptr = (void **)((s8 *)((void **)((s8 *)match_ptr + 4)));
                }
            }
            entry_ptr = (void **)((s8 *)((void **)((s8 *)entry_ptr + 4)));
        } while (*entry_ptr != NULL);
    }
    *match_ptr = NULL;
}
