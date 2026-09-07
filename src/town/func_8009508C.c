#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80035208();                         /* extern */
M2C_UNK func_8008B158();                         /* extern */
M2C_UNK func_80092A30();                            /* extern */
M2C_UNK func_80092A60();                            /* extern */
M2C_UNK func_80093D38();     /* extern */
M2C_UNK func_8009455C();     /* extern */
M2C_UNK func_800945B8();     /* extern */
M2C_UNK func_80094660();     /* extern */
M2C_UNK func_800946A0();     /* extern */
M2C_UNK func_80094774();     /* extern */
s32 func_80094B0C();                          /* extern */
M2C_UNK func_80094C1C();                      /* extern */
M2C_UNK func_80095094();                      /* extern */
M2C_UNK func_8009550C();                      /* extern */
M2C_UNK func_8009567C();                   /* extern */
s32 func_80095760();                       /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80095C80();                      /* extern */
M2C_UNK func_800988C8();     /* extern */
M2C_UNK func_80099754();                      /* extern */
s32 func_8009FF50();                                /* extern */
s32 func_800A9D74();                     /* extern */
extern u8 D_80083160[];
extern M2C_UNK D_80093B00;
extern M2C_UNK D_8009B828;
extern M2C_UNK D_8009B8E8;
extern M2C_UNK D_8009B9BC;
extern M2C_UNK D_800CFCB4;
extern void *D_800CFCC4;
extern u8 D_800CFCEF[];
extern M2C_UNK D_800FE488;
extern s32 D_800FE518[];
extern s32 *D_800FE5D8;



typedef struct S_800927EC_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_800927EC_1;   /* state in func_800927EC */

typedef struct S_800927EC_2 {
    u8 pad_00[0x14];
    u8 unk_14;
} S_800927EC_2;   /* D_800CFCC4 in func_800927EC */


typedef struct S_800927EC_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800927EC_4;   /* var_v0 in func_800927EC */

typedef struct S_800927EC_5 {
    u8 pad_00[0x50];
    s32 unk_50;
} S_800927EC_5;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_2C in func_800927EC */

void func_800927EC(void *arg0, Rec_D_800E3D7C *arg1, M2C_UNK arg2) {
    u8 *state = D_80083160;
    M2C_UNK *var_v0;
    s16 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;

    func_80095C80(arg1);
    func_80094C1C(arg0);
    func_80095094(arg1);
    temp_v0 = func_80095978(arg1, &D_800FE488);
    if ((temp_v0 - arg1->unk_08.at02_s16.v) >= 4) {
        if (D_800CFCEF[0] == 0) {
            func_80094660(arg0, arg1, arg2);
            func_80092A60();
            return;
        }
        goto block_6;
    }
    if (D_800CFCEF[0] == 0) {
        func_80095A94(arg1, temp_v0, &D_800FE488);
    }
block_6:
    if (((S_800927EC_1 *)state)->unk_10 & 0x10) {
        func_800945B8(arg0, arg1, arg2);
        func_80092A60();
        return;
    }
    if (((S_800927EC_1 *)state)->unk_10 & 0x80) {
        if ((D_800CFCC4 != NULL) && (((S_800927EC_2 *)D_800CFCC4)->unk_14 == 4)) {
            func_8009550C(arg1);
            func_80094774(arg0, arg1, arg2);
            D_800FE518[0] = 1;
            func_80092A60();
            return;
        }
        func_80099754(arg1);
        func_8009550C(arg1);
        if (func_80094B0C(arg0 - 0x20) != 0) {
            register u32 page ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */

            func_80093D38(arg0, arg1, arg2);
            page = 0x80100000;
            ASM_PAGEBASE_PIN(page);   /* MATCH pin: retail delay-slot contents depend on it */
            func_80092A30();
        }
    } else {
        if (((S_800927EC_1 *)state)->unk_10 & 0x40) {
            func_800946A0(arg0, arg1, arg2);
            func_80092A60();
            return;
        }
        if ((func_80095760(&D_800CFCB4) == -1) && (func_8009FF50() == 0)) {
            func_8009567C(&D_800CFCB4);
            func_80094C1C(arg0);
            func_800988C8(arg0, arg1, arg2);
            temp_v1 = ((S_800927EC_5 *)(((Rec_func_80094268_arg0 *)arg0)->unk_2C))->unk_50;
            if ((temp_v1 != &D_8009B828) && (temp_v1 != &D_8009B8E8)) {
                if (temp_v1 != &D_8009B9BC) {
                    ((Rec_func_80094268_arg0 *)arg0)->unk_2C = NULL;
                }
            }
            var_v0 = &D_800CFCB4;
            temp_v0_2 = func_800A9D74(((S_800927EC_4 *)var_v0)->unk_10, ((Rec_func_80094268_arg0 *)arg0)->unk_2C);
            if (temp_v0_2 != 0) {
                register u32 page ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */

                func_80035208(temp_v0_2);
                page = 0x80100000;
                ASM_PAGEBASE_PIN(page);   /* MATCH pin: retail delay-slot contents depend on it */
                func_80092A30();
                return;
            }
            func_8008B158(((S_800927EC_4 *)var_v0)->unk_10);
            D_800FE5D8 = &D_80093B00;
            func_80092A60();
            return;
        }
        if (((S_800927EC_1 *)state)->unk_08 & 0xF000) {
            func_8009455C(arg0, arg1, arg2);
        }
    }
}
