#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"


typedef struct S_80471334_1 {
    u8 pad_00[0x2D5C];
    s32 unk_2D5C;
} S_80471334_1;   /* temp_a0 in func_80471334 */


M2C_UNK func_800181DC();                            /* extern */
M2C_UNK func_80019098();                   /* extern */
extern s32 D_8001B210;
extern M2C_UNK D_8001B218;

/* Refresh the shared state and subtract D_8001B210 from the context counter. */
void func_80471334(void) {
    S_80471334_1 *context;

    func_800181DC();
    func_80019098(&D_8001B218);
    context = D_80016000->unk_38;
    context->unk_2D5C = (s32) (context->unk_2D5C - D_8001B210);
}
