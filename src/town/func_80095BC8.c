#include "common.h"
#include "records/Rec_func_80094268_arg0.h"


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80093D18();       /* extern */
M2C_UNK func_80093D48();       /* extern */
M2C_UNK func_80094984();       /* extern */
s32 func_80094B0C();           /* extern */
M2C_UNK func_80095094();       /* extern */
M2C_UNK func_8009550C();       /* extern */
M2C_UNK func_80095C80();       /* extern */
M2C_UNK func_80099754();       /* extern */
extern M2C_UNK D_800D0078;
extern s32 D_800FE518;



/* Updates the entity and dispatches a state transition when its countdown expires. */
void func_80093328(void *state, void *entity, s32 transition_arg) {
    s16 countdown;

    func_80095C80(entity);
    func_80095094(entity);
    countdown = ((Rec_func_80094268_arg0 *)state)->unk_0A.as_u16 - 1;
    ((Rec_func_80094268_arg0 *)state)->unk_0A.as_u16 = countdown;
    if (countdown < 0) {
        func_80099754(entity);
        func_8009550C(entity);
        if (D_800FE518 != 0 && func_80094B0C(state - 0x20) != 0) {
            func_80094984(&D_800D0078, state, transition_arg);
            func_80093D18(state, entity, transition_arg);
            return;
        }
        func_80093D48(state, entity, transition_arg);
    }
}
