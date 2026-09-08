#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_80041E70();                      /* extern */
M2C_UNK func_8008D330(); /* extern */
M2C_UNK func_80098B38();                         /* extern */
M2C_UNK func_80099844();           /* extern */
M2C_UNK func_800A5F38();                 /* extern */
M2C_UNK func_800A63B8();            /* extern */
s32 func_800AD6FC();            /* extern */
M2C_UNK func_800C4AFC();            /* extern */
typedef struct {
    u8 pad[0xA];
    u16 fieldA;
} D_80083460_t;

extern M2C_UNK D_80082E80;
extern D_80083460_t D_80083460;
extern M2C_UNK D_80083780;
extern u16 D_800DDE84[];
extern M2C_UNK D_800E0EE1;
extern s32 D_800E3D7C;


typedef struct S_800BDA44_0_pre {
    s32 unk_00;
    u8 pad_04[0x14];
} S_800BDA44_0_pre;   /* the 0x18 bytes before arg0 in func_800BDA44, addressed as arg0[-1] */


s32 func_800BDA44(void *arg0, s32 arg1, s16 arg2) {
    if (arg0 == D_800E3D7C) {
        ((Rec_D_800E3D7C *)arg0)->unk_110 = arg1;
        func_8008D330(arg0, &D_80083780, &D_80082E80, arg0);
        return 0;
    }
    if ((u32) arg0 <= 0x9FFFFFFFU) {
        func_800A63B8(arg0, arg1, arg2);
        if (func_800AD6FC(arg0, (D_800DDE84[((Rec_D_800E3D7C *)arg0)->unk_10.at03_u8.v] >> 6) & 3, 0) == 0) {
            func_800A5F38(arg0, arg1);
            return 1;
        }
        goto block_8;
    }
block_8:
    func_800C4AFC(((S_800BDA44_0_pre *)arg0)[-1].unk_00, 0x2020C0, arg0);
    ((Rec_D_800E3D7C *)arg0)->unk_26 = (u8) ((Rec_D_800E3D7C *)arg0)->unk_68;
    func_80041E70(arg0);
    if (((Rec_D_800E3D7C *)arg0)->unk_14.as_s32 & 0x4000) {
        func_80099844(arg0, &D_800E0EE1);
    }
    func_80098B38(arg1);
    D_80083460.fieldA = (u16) (D_80083460.fieldA - 1);
    return 1;
}
