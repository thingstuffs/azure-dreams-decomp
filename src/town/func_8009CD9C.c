#include "common.h"
#include "records/Rec_func_80094268_arg0.h"




#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80033CD8();
extern M2C_UNK func_80098928();
extern u8 D_80082660[];
extern M2C_UNK D_800970FC;


void func_8009A4FC(Rec_func_80094268_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_80033CD8(arg0, &D_800970FC);
    D_80082660[arg0->unk_40 * 8] = 0;
    func_80098928(arg0, arg1, arg2);
}
