#include "common.h"





typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#ifndef NULL
#define NULL 0
#endif

M2C_UNK func_8004CC38();
M2C_UNK func_8004CCBC();
extern M2C_UNK *D_80129728;
extern M2C_UNK D_801298B8;
extern M2C_UNK D_80129ED8;
extern M2C_UNK D_8012A4F8;

typedef struct S_801264AC_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_801264AC_0;   /* var_a0 in func_801264AC */

typedef struct S_801264AC_1 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    M2C_UNK * unk_0C;
} S_801264AC_1;   /* *var_v1 in func_801264AC */

typedef struct S_801264AC_2 {
    u8 pad_00[0x54];
    s32 unk_54;
    M2C_UNK ** unk_58;
} S_801264AC_2;   /* arg0 in func_801264AC */

typedef struct S_801264AC_3 {
    u8 pad_00[0x184];
    s32 unk_184;
} S_801264AC_3;   /* &D_80129728 in func_801264AC */

/* Initializes 98 linked nodes and attaches their table to the context. */
s32 func_801264AC(S_801264AC_2 *context) {
    M2C_UNK **node_slot;
    M2C_UNK *node;
    M2C_UNK *node_data;
    M2C_UNK *node_aux;
    M2C_UNK *prev_node;
    s32 node_count;
    s32 result;

    prev_node = NULL;
    node_count = 0;
    node_slot = &D_80129728;
    node_aux = &D_8012A4F8;
    node_data = &D_80129ED8;
    node = &D_801298B8;
    do {
        *node_slot = node;
        ((S_801264AC_0 *)node)->unk_04 = node_data;
        node_data += 4;
        node += 4;
        node_count += 1;
        ((S_801264AC_1 *)(*node_slot))->unk_08 = node_aux;
        node_aux += 3;
        ((S_801264AC_1 *)(*node_slot))->unk_0C = prev_node;
        prev_node = *node_slot;
        node_slot += 1;
    } while (node_count < 0x62);
    func_8004CC38(&D_80129728, 0x62, node_aux, node_count);
    func_8004CCBC(&D_80129728, 0x62);
    context->unk_58 = &D_80129728;
    context->unk_54 = (s32)((S_801264AC_3 *)(&D_80129728))->unk_184;
    result = 1;
    ASM_KEEP(result);   /* MATCH pin: keeps a statement from moving across a call/branch */
    return result;
}

/* MECHANISM: The natural loop shape yields the exact 32-byte frame and s1/s0/ra saves.
   A post-store ASM_SCHED_BARRIER makes the tail load/store reuse v0 instead of v1.
   An unpinned named return kept at last use places li v0,1 before the epilogue reloads. */
