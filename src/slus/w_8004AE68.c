#include "common.h"

/* Comparator: subtracts two table-lookup values through two independent
   record pointers. Known maspsx-fold-false-positive family
   (see item_clear_recorded_category_pair/set_packed_2bit_flag siblings) — see comment below. */
typedef struct {
    u8 pad0;
    u8 key;
} S_8004AE68_Rec;

typedef struct {
    S_8004AE68_Rec *rec;
} S_8004AE68_Outer;

extern u8 D_800713E4[256];

/* Compares two records by subtracting their key-indexed table values. */
s32 table_handle_compares_two_records_subtracting_key_indexed_table_values(S_8004AE68_Outer *left, S_8004AE68_Outer *right)
{
    return D_800713E4[left->rec->key] - D_800713E4[right->rec->key];
}
