#include "common.h"
#include "records/Rec_func_80094268_arg0.h"




#define M2C_FIELD(expr, type, offset) (*(type)((s8 *)(expr) + (offset)))

extern void func_800C2E84(void *arg0, s32 arg2, void *arg3);
extern u8 D_80082660;
extern M2C_UNK D_800C3B7C;
extern M2C_UNK D_800D5670;


/* Initialize the actor state, clear its entry flag, and set a callback with a 32-tick countdown. */
void func_800C62E4(void *actor, s32 unused, s32 state_context) {
    func_800C2E84(actor, state_context, &D_800D5670);
    *((((Rec_func_80094268_arg0 *)actor)->unk_60 * 8) + &D_80082660) = 0;
    ((Rec_func_80094268_arg0 *)actor)->unk_54 = &D_800C3B7C;
    ((Rec_func_80094268_arg0 *)actor)->unk_6C.as_s16 = 0x20;
}
