#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8009EEAC(s32, s32, s32, s32);                            /* extern */
M2C_UNK func_8009F3D4(); /* extern */
extern u8 D_800E3548[];
extern u8 D_800E36C8[];

typedef struct S_8009F020_0 {
    u8 unk_00;
    u8 unk_01;
} S_8009F020_0;   /* var_s0 in func_8009F020 */

typedef struct S_8009F020_1 {
    u8 unk_00;
    u8 unk_01;
} S_8009F020_1;   /* var_s1 in func_8009F020 */

/* Create blue markers at the positions of enabled entries. */
void func_8009F020(s32 setup_arg_0, s32 setup_arg_1, s32 setup_arg_2, s32 setup_arg_3) {
    u8 *entry_state;
    u8 *entry_position;
    s32 entry_index;

    func_8009EEAC(setup_arg_0, setup_arg_1, setup_arg_2, setup_arg_3);
    entry_index = 0;
    entry_position = D_800E36C8;
    entry_state = D_800E3548;
    do {
        if ((((S_8009F020_0 *)entry_state)->unk_01 != 0) && (((S_8009F020_0 *)entry_state)->unk_00 != 0)) {
            func_8009F3D4(((S_8009F020_1 *)entry_position)->unk_00, ((S_8009F020_1 *)entry_position)->unk_01, 0x802020, 2, entry_index);
        }
        entry_position += 0xC;
        entry_index += 1;
        entry_state += 4;
    } while (entry_index < 0x40);
}
