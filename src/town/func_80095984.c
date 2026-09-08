#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80093D48();     /* extern */
M2C_UNK func_80093ED8();     /* extern */
M2C_UNK func_800942B0();     /* extern */
M2C_UNK func_80094378();     /* extern */
M2C_UNK func_80095094();                      /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80095C80();                      /* extern */
s32 func_8009FF50();                                /* extern */
extern u8 D_80083160[];
extern u8 D_800CFCEF;
extern u8 D_800FE488[];


typedef struct S_800930E4_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800930E4_0;   /* target in func_800930E4 */

typedef struct S_800930E4_1 {
    u8 unk_00;
} S_800930E4_1;   /* &D_800CFCEF in func_800930E4 */

typedef struct S_800930E4_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800930E4_2;   /* self in func_800930E4 */

typedef struct S_800930E4_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_800930E4_3;   /* state in func_800930E4 */

void func_800930E4(void *arg0, void *arg1, M2C_UNK arg2) {
    void *self;
    register void *target ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    M2C_UNK third;
    s16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u8 *state;

    self = arg0;
    target = arg1;
    third = arg2;
    state = D_80083160;

    func_80095C80(target);
    ASM_KEEP(self);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(target);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(third);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    func_80095094(target);
    if (func_8009FF50() == 0) {
        temp_v0 = func_80095978(target, D_800FE488);
        if ((temp_v0 - ((S_800930E4_0 *)target)->unk_0A) >= 4) {
            if (((S_800930E4_1 *)(&D_800CFCEF))->unk_00 == 0) {
                func_80094378(self, target, third);
                return;
            }
            goto block_7;
        }
        if (((S_800930E4_1 *)(&D_800CFCEF))->unk_00 == 0) {
            func_80095A94(target, temp_v0, D_800FE488);
        }
block_7:
        temp_v0_2 = ((S_800930E4_2 *)self)->unk_0A - 1;
        ((S_800930E4_2 *)self)->unk_0A = temp_v0_2;
        if ((s16) temp_v0_2 >= 0) {
            if (((S_800930E4_3 *)state)->unk_08 & 0xF000) {
                func_80093ED8(self, target, third);
                return;
            }
            if (((S_800930E4_3 *)state)->unk_10 & 0x10) {
                func_800942B0(self, target, third);
                return;
            }
        } else {
            goto block_15;
        }
    } else {
        temp_v0_3 = ((S_800930E4_2 *)self)->unk_0A - 1;
        ((S_800930E4_2 *)self)->unk_0A = temp_v0_3;
        if ((s16) temp_v0_3 < 0) {
block_15:
            func_80093D48(self, target, third);
        }
    }
}
/* MECHANISM: A 0x28 frame comes from pinned s0/s1/s2 argument holds plus
   D_80083160 held in s4; cdk materializes its address through v0.
   Signed halfword tests and one shared D_800CFCEF address fix the body.
   Moving ASM_KEEP after the first call lets sw s3 fill its jal delay slot. */
