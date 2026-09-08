#include "common.h"

#include "common.h"

extern s32 func_80042900(void *, s8);
extern s8 D_800712E4[];
extern u8 D_800712F0[];

/* Selects a table value from descending object queries, with an adjustment for query 7. */
u8 func_80049E88(void *object) {
    s32 query_index;
    s32 query_base;
    void *query_object;
    u8 *result_entry;
    s32 query_table_addr;
    u8 query_id;

    query_object = object;
    query_index = 0xB;
    query_table_addr = (s32) D_800712E4;
    query_base = query_table_addr;
    do {
        if ((func_80042900(query_object, *(s8 *) (query_index + query_base)) << 0x10) != 0) {
            break;
        }
        query_index--;
    } while (query_index > 0);

    query_id = *(u8 *) (query_index + query_base);
    __asm__ volatile("" : "=r"(query_base) : "0"(query_base));
    if ((query_id == 7) && ((func_80042900(query_object, (s8) query_id) << 0x10) > 0)) {
        query_index--;
    }

    result_entry = D_800712F0;
    result_entry += query_index;
    return *result_entry;
}
