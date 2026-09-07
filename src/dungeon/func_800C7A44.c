#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80099844(void *, void *);
extern void func_800A56E0(s32);
extern void func_800A6508(void);
extern void func_800C5BBC(s32, s32, s32, s32, s32, s32);
extern s32 func_800C8ABC(void *, s32, s32);
extern void func_800CD280(void);
extern void func_800DC1B8(s32);
extern s32 D_800DCF0C;
extern u8 D_800E1BF3[];
extern u8 D_800E3D40[];


typedef struct S_800CD1A4_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800CD1A4_0_pre;   /* the 0x14 bytes before arg0 in func_800CD1A4, addressed as arg0[-1] */

typedef struct S_800CD1A4_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x74];
    s16 unk_88;
} S_800CD1A4_0;   /* arg0 in func_800CD1A4 */

typedef struct S_800CD1A4_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800CD1A4_1;   /* temp_v1 in func_800CD1A4 */

s32 func_800CD1A4(void *arg0) {
    s32 var_a1;
    S_800CD1A4_1 *temp_v1;

    var_a1 = 0x40;
    if (D_800E3D40[0] != 0) {
        var_a1 = 0x400;
    }
    if (func_800C8ABC(arg0, var_a1, 0x10) == 0) {
        if (((S_800CD1A4_0 *)arg0)->unk_13 == 0) {
            func_800A6508();
            func_800CD280();
            return 1;
        }
        return 1;
    }
    func_80099844(arg0, &D_800E1BF3);
    if (((S_800CD1A4_0 *)arg0)->unk_13 == 0) {
        func_800DC1B8(D_800DCF0C);
    }
    temp_v1 = ((S_800CD1A4_0_pre *)arg0)[-1].unk_00;
    if (!(temp_v1->unk_14 & 0x8000)) {
        func_800C5BBC((temp_v1->unk_24 << 6) | 0x20,
                      (temp_v1->unk_25 << 6) | 0x20,
                      ((S_800CD1A4_0 *)arg0)->unk_88, 0x808080, 0x20, 0);
        func_800A56E0(0x520);
    }
    return 1;
}
