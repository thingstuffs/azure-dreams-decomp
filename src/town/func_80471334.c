#include "common.h"
#include "m2c_compat.h"

typedef struct S_80471334_0 {
    u8 pad_00[0x38];
    void * unk_38;
} S_80471334_0;   /* D_80016000 in func_80471334 */

typedef struct S_80471334_1 {
    u8 pad_00[0x2D5C];
    s32 unk_2D5C;
} S_80471334_1;   /* temp_a0 in func_80471334 */


M2C_UNK func_800181DC();                            /* extern */
M2C_UNK func_80019098();                   /* extern */
extern S_80471334_0 *D_80016000;
extern s32 D_8001B210;
extern M2C_UNK D_8001B218;

void func_80471334(void) {
    S_80471334_1 *temp_a0;

    func_800181DC();
    func_80019098(&D_8001B218);
    temp_a0 = D_80016000->unk_38;
    temp_a0->unk_2D5C = (s32) (temp_a0->unk_2D5C - D_8001B210);
}
