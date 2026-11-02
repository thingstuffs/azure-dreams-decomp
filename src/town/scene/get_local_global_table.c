#include "script_symbols.h"
#include "common.h"
#include "town/player/state.h"

typedef struct {
    s32 values[3];
} ValueTriple;

typedef struct {
    ValueTriple first;
    s32 last;
} ValueTable;

extern ValueTable D_80016028;

/* Return the selected value from a local copy of the global table. */
s32 get_local_global_table(void) {
    ValueTable table;

    table = D_80016028;
    return ((s32 *)&table)[read_script_flag_range(F_sbs34_pad16, 2)];
}

/* MECHANISM: A whole 16-byte aggregate with a volatile final word splits into
   retail's 3+1 stack copy in the 0x28 frame. The callee's true two-argument ABI
   frees a2 as the sole held global base; cdk emits the split lui/addiu shape. */
