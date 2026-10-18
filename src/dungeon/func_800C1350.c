#include "common.h"
#include "shared/object_node.h"

typedef struct {
    s32 unk0[4];
    void *field10;
} Func8003FF2CResult;

extern Func8003FF2CResult *initialize_runtime_node_storage(s32, s32 *, s16, s32 *);
extern void dispatch_action_callback_by_opcode(u8 *w);
extern s32 D_800E58B8[];

/* Create a record and assign dispatch_action_callback_by_opcode to its field10 pointer. */
void create_record_with_effect_callback(void) {
    initialize_runtime_node_storage(0, D_800E58B8, 0x10, ((s32 *)(&D_80083498)))->field10 = dispatch_action_callback_by_opcode;
}
