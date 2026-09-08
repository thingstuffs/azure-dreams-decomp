#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A0668_arg0.h"

s32 func_8008FAC0();              /* extern */
extern M2C_UNK D_800834B8;
extern M2C_UNK D_80091260;
extern M2C_UNK D_80091528;
extern M2C_UNK D_800CFCB4;


typedef struct S_800A0F10_0 {
    u8 pad_00[0x10];
    u16 unk_10;
} S_800A0F10_0;   /* global_base in func_800A0F10 */


s32 func_800A0F10(Rec_func_800A0668_arg0 *arg0, M2C_UNK arg1) {
    if (func_8008FAC0(arg1, &D_800CFCB4) != 0) {
        s32 *global_base = &D_800834B8;
        s32 global_angle = ((S_800A0F10_0 *)global_base)->unk_10;
        s32 object_angle;

        ASM_KEEP(global_angle);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        object_angle = arg0->unk_72;

        if ((u32) (((object_angle & 0xFFF) - (global_angle & 0xFFF)) + 0x3FF) < 0x7FFU) {
            if ((D_800834B8 == (s32)&D_80091260) || (D_800834B8 == (s32)&D_80091528)) {
                return 1;
            }
            return 0;
        }
    }
    return 0;
}
