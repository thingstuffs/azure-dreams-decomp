#include "common.h"
#include "m2c_compat.h"

s32 func_80033B2C();                         /* extern */
M2C_UNK func_8008B158();                         /* extern */
M2C_UNK func_80090C44();                            /* extern */
M2C_UNK func_80093ED8();     /* extern */
M2C_UNK func_80094088();     /* extern */
M2C_UNK func_800942B0();     /* extern */
M2C_UNK func_80094378();     /* extern */
M2C_UNK func_800943B8();     /* extern */
M2C_UNK func_800944BC();     /* extern */
M2C_UNK func_8009451C();     /* extern */
M2C_UNK func_80094C1C();                      /* extern */
M2C_UNK func_80095094();                      /* extern */
s32 func_8009567C();            /* extern */
s32 func_80095840();               /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80095C80();                      /* extern */
M2C_UNK func_80098868();     /* extern */
extern u8 D_80083160[];
extern s32 D_800CFCB4;
extern M2C_UNK D_800CFCEF;
extern u8 D_800FE488[];

typedef struct S_80090A74_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80090A74_0;   /* arg1 in func_80090A74 */

typedef struct S_80090A74_1 {
    u8 unk_00;
} S_80090A74_1;   /* &D_800CFCEF in func_80090A74 */

typedef struct S_80090A74_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_80090A74_2;   /* temp_s4 in func_80090A74 */

typedef struct S_80090A74_3 {
    u8 pad_00[0x2C];
    s32 unk_2C;
} S_80090A74_3;   /* arg0 in func_80090A74 */

typedef struct S_80090A74_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80090A74_4;   /* temp_s3 in func_80090A74 */

void func_80090A74(S_80090A74_3 *arg0, S_80090A74_0 *arg1, M2C_UNK arg2) {
    s16 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    register u8 *page_v0 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register u8 *temp_s3 ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *temp_s4 = D_80083160;

    func_80095C80(arg1);
    func_80095094(arg1);
    {
        void *call_a0 = arg1;

        ASM_KEEP(call_a0);   /* MATCH pin: retail schedule: same instructions, different order without it */
        page_v0 = (u8 *)0x80100000;
        ASM_KEEP(page_v0);   /* MATCH pin: retail immediate-load split depends on it */
        temp_s3 = page_v0 - 0x1B78;
        temp_v0 = func_80095978(call_a0, temp_s3);
    }
    if ((temp_v0 - arg1->unk_0A) >= 4) {
        if (((S_80090A74_1 *)(&D_800CFCEF))->unk_00 == 0) {
            func_80094378(arg0, arg1, arg2);
            return;
        }
        goto block_6;
    }
    if (((S_80090A74_1 *)(&D_800CFCEF))->unk_00 == 0) {
        func_80095A94(arg1, temp_v0, temp_s3);
    }
block_6:
    if (((S_80090A74_2 *)temp_s4)->unk_10 & 0x10) {
        func_800942B0(arg0, arg1, arg2);
        return;
    }
    if (((S_80090A74_2 *)temp_s4)->unk_10 & 0x40) {
        temp_v0_2 = func_80095840(arg0, &D_800CFCB4);
        if (temp_v0_2 != 0) {
            if (temp_v0_2 == 2) {
                func_8009451C(arg0, arg1, arg2);
                return;
            }
            func_800944BC(arg0, arg1, arg2);
            return;
        }
        if (func_80033B2C(0xA4) != 0) {
            func_80094088(arg0, arg1, arg2);
            return;
        }
    } else {
        page_v0 = (u8 *)0x800D0000;
        ASM_KEEP(page_v0);   /* MATCH pin: retail immediate-load split depends on it */
        temp_s3 = page_v0 - 0x34C;
        temp_v0_3 = func_8009567C(temp_s3);
        if (temp_v0_3 != 0) {
            if (temp_v0_3 == -1) {
                func_80094C1C(arg0);
                func_80098868(arg0, arg1, arg2);
                arg0->unk_2C = 0;
                func_8008B158(((S_80090A74_4 *)temp_s3)->unk_10);
                return;
            }
            func_800943B8(arg0, arg1, arg2);
            return;
        }
        if (((S_80090A74_2 *)temp_s4)->unk_08 & 0xF000) {
            func_80093ED8(arg0, arg1, arg2);
        }
    }
}
/* MECHANISM: At 2.7.2-cdk-G0, s4 holds D_80083160 and s3 is reused for
   D_800FE488/D_800CFCB4 via pinned v0 page bases. The corrected one-argument
   func_8009567C ABI removes an extra move; a scoped a0 fence schedules the
   third-call argument before its page-base pair. */
