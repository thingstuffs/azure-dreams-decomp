#include "common.h"
#include "m2c_compat.h"

typedef struct S_800BDA44_0 {
    s32 unk_00;
    u8 pad_04[0x27];
    u8 unk_2B;
    s32 unk_2C;
    u8 pad_30[0xE];
    u8 unk_3E;
    u8 pad_3F[0x41];
    u8 unk_80;
    u8 pad_81[0xA7];
    s32 unk_128;
} S_800BDA44_0;   /* arg0 in func_800BDA44; pointer addresses record offset 0x18 */


M2C_UNK func_80041E70();                      /* extern */
M2C_UNK func_8008D330(); /* extern */
M2C_UNK func_80098B38();                         /* extern */
M2C_UNK func_80099844();           /* extern */
M2C_UNK func_800A5F38();                 /* extern */
M2C_UNK func_800A63B8();            /* extern */
s32 func_800AD6FC();            /* extern */
void func_800BDB5C();                               /* extern */
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

s32 func_800BDA44(void *arg0, s32 arg1, s16 arg2) {
    if (arg0 == D_800E3D7C) {
        ((S_800BDA44_0 *)((u8 *)arg0 - 0x18))->unk_128 = arg1;
        func_8008D330(arg0, &D_80083780, &D_80082E80, arg0);
        return 0;
    }
    if ((u32) arg0 <= 0x9FFFFFFFU) {
        func_800A63B8(arg0, arg1, arg2);
        if (func_800AD6FC(arg0, (D_800DDE84[((S_800BDA44_0 *)((u8 *)arg0 - 0x18))->unk_2B] >> 6) & 3, 0) == 0) {
            func_800A5F38(arg0, arg1);
            return 1;
        }
        goto block_8;
    }
block_8:
    func_800C4AFC(((S_800BDA44_0 *)((u8 *)arg0 - 0x18))->unk_00, 0x2020C0, arg0);
    ((S_800BDA44_0 *)((u8 *)arg0 - 0x18))->unk_3E = (u8) ((S_800BDA44_0 *)((u8 *)arg0 - 0x18))->unk_80;
    func_80041E70(arg0);
    if (((S_800BDA44_0 *)((u8 *)arg0 - 0x18))->unk_2C & 0x4000) {
        func_80099844(arg0, &D_800E0EE1);
    }
    func_80098B38(arg1);
    D_80083460.fieldA = (u16) (D_80083460.fieldA - 1);
    return 1;
}
