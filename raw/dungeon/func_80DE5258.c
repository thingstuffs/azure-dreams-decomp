#include "common.h"
extern int abs(int);
#include "m2c_compat.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
s32 func_8003F270(void);                         /* extern */
M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
void *func_800A05A4(void *, u8, u8, s16, s32);      /* extern */
M2C_UNK func_800A2B04(void *, u8, u8);              /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
s32 func_800A94A0(void *, u8 *, s32, void *);       /* extern */
M2C_UNK func_800BB044(void *);                      /* extern */
extern u8 D_8006DE24[];
extern void *D_800814A8;
extern u8 D_80174520[8];
extern void func_80170E5C(void *,void *,void *,void *);


typedef struct S_80172A58_0 {
    u8 pad_00[0x8C];
    void (*unk_8C)(void *,void *,void *,void *);
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172A58_0;   /* arg0 in func_80172A58 */

typedef struct S_80172A58_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x4];
    s8 unk_72;
    s8 unk_73;
} S_80172A58_1;   /* arg3 in func_80172A58 */

typedef struct S_80172A58_2 {
    u8 pad_00[0x12];
    u8 unk_12;
} S_80172A58_2;   /* ((*var_s0 * 0x14) + D_8006DE24) in func_80172A58 */

typedef struct S_80172A58_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172A58_3_pre;   /* the 0x14 bytes before var_v0 in func_80172A58, addressed as var_v0[-1] */

typedef struct S_80172A58_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172A58_4;   /* temp_v1_3 in func_80172A58 */

typedef struct S_80172A58_5 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80172A58_5;   /* arg2 in func_80172A58 */

typedef struct S_80172A58_6 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172A58_6;   /* arg1 in func_80172A58 */

typedef struct S_80172A58_7 {
    u8 pad_00[0xA6];
    u16 unk_A6;
} S_80172A58_7;   /* D_800814A8 in func_80172A58 */

typedef struct S_80172A58_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172A58_8;   /* &D_80083460 in func_80172A58 */

void func_80172A58(void *arg0, S_80172A58_6 *arg1, S_80172A58_5 *arg2, void *arg3) {
    s32 temp_v0;
    s32 temp_v1_2;
    s16 var_s5;
    s8 var_v0_2;
    s8 var_v1;
    u16 temp_v0_2;
    u8 *var_s0;
    u8 temp_v1;
    S_80172A58_4 *temp_v1_3;
    void *var_v0;

    temp_v1 = ((S_80172A58_0 *)arg0)->unk_9B;
    var_s5 = 0;
    switch (temp_v1) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        if (((S_80172A58_1 *)arg3)->unk_1C & 0x2000) {
            switch (((S_80172A58_1 *)arg3)->unk_46 & 0x3FFF) {
            case 7: var_s5=1;
            case 3: var_s0=(u8 *)arg3+0xE; break;
            case 6: var_s5=1;
            case 2: var_s0=(u8 *)arg3+0xB; break;
            case 5: var_s5=1;
            case 1: var_s0=(u8 *)arg3+8; break;
            default: var_s0=0; break;
            }
        } else {
            switch (((S_80172A58_1 *)arg3)->unk_46 & 0x3FFF) {
            case 3: var_s0=(u8 *)arg3+0xE; break;
            case 2: var_s0=(u8 *)arg3+0xB; break;
            case 1: var_s0=(u8 *)arg3+8; break;
            default: var_s0=0; break;
            }
        }
        if (*var_s0 != 0) {
            ((S_80172A58_0 *)arg0)->unk_98 = (u16) (((S_80172A58_0 *)arg0)->unk_98 & 0xFF7F);
            if (var_s5 != 0) {
                var_v0 = D_800814A8;
                ((S_80172A58_1 *)arg3)->unk_60 = var_v0;
                    temp_v1_3 = ((S_80172A58_3_pre *)var_v0)[-1].unk_00;
                    ((S_80172A58_1 *)arg3)->unk_72 = (s8) temp_v1_3->unk_24;
                    ((S_80172A58_1 *)arg3)->unk_73 = (s8) temp_v1_3->unk_25;
            } else if (((S_80172A58_2 *)(((*var_s0 * 0x14) + D_8006DE24)))->unk_12 == 2) {
                var_v0 = ((S_80172A58_1 *)arg3)->unk_60;
                if (var_v0 != NULL) {
                    temp_v1_3 = ((S_80172A58_3_pre *)var_v0)[-1].unk_00;
                    ((S_80172A58_1 *)arg3)->unk_72 = (s8) temp_v1_3->unk_24;
                    ((S_80172A58_1 *)arg3)->unk_73 = (s8) temp_v1_3->unk_25;
                }
            } else {
                ((S_80172A58_1 *)arg3)->unk_60 = func_800A05A4(arg3, arg2->unk_24, arg2->unk_25, ((S_80172A58_1 *)arg3)->unk_2A, 0x10);
                ((S_80172A58_1 *)arg3)->unk_72 = abs(((S_80172A58_1 *)arg3)->unk_72);
                ((S_80172A58_1 *)arg3)->unk_73 = abs(((S_80172A58_1 *)arg3)->unk_73);
            }
            if (func_800A94A0(arg3, var_s0, var_s5, arg0 + 0x98) != 0) {
                func_800BB044(arg3);
                ((S_80172A58_0 *)arg0)->unk_9B = (u8) (((S_80172A58_0 *)arg0)->unk_9B + 1);
                return;
            }
            return;
        }
        arg1->unk_14 = 0;
        arg1->unk_10 = 0;
        arg1->unk_0C = 0;
        func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
        dungeonStatus.unk_0C = 0;
        ((S_80172A58_7 *)D_800814A8)->unk_A6 = (u16) (((S_80172A58_7 *)D_800814A8)->unk_A6 - 1);
        func_800A4ACC(arg3);
        ((S_80172A58_1 *)arg3)->unk_6D = (u8) (((S_80172A58_1 *)arg3)->unk_6D - 1);
        ((S_80172A58_0 *)arg0)->unk_8C = func_80170E5C;
        ((S_80172A58_1 *)arg3)->unk_73 = 0;
        ((S_80172A58_1 *)arg3)->unk_72 = 0;
        ((S_80172A58_1 *)arg3)->unk_46 = (u16) (((S_80172A58_1 *)arg3)->unk_46 & 0x7FFF);
        return;
    case 1:                                         /* switch 1 */
        if (func_8003F270() != 0) {
            arg2->unk_14 = (u16) (arg2->unk_14 | 0x800);
            return;
        }
        arg2->unk_14 = (u16) (arg2->unk_14 & 0xF7FF);
        ((S_80172A58_0 *)arg0)->unk_9B = (u8) (((S_80172A58_0 *)arg0)->unk_9B + 1);
    case 2:                                         /* switch 1 */
        if (((arg2->unk_04 == 3) && (arg2->unk_14 & 0x1000)) || (arg2->unk_14 & 0xE000)) {
            arg2->unk_14 = (u16) (arg2->unk_14 | 0x800);
            ((S_80172A58_0 *)arg0)->unk_96 = 1U;
            ((S_80172A58_0 *)arg0)->unk_98 = (u16) (((S_80172A58_0 *)arg0)->unk_98 | 0x80);
        }
        temp_v0_2 = ((S_80172A58_0 *)arg0)->unk_96 - 1;
        ((S_80172A58_0 *)arg0)->unk_96 = temp_v0_2;
        if ((temp_v0_2 << 0x10) <= 0) {
            ((S_80172A58_0 *)arg0)->unk_96 = 0U;
            arg2->unk_14 = (u16) (arg2->unk_14 & 0xF7FF);
        }
        if (arg2->unk_14 & 0xE000) {
            arg1->unk_14 = 0;
            arg1->unk_10 = 0;
            arg1->unk_0C = 0;
            func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
            if (arg2->unk_2C != D_80174520) {
                arg2->unk_2C = D_80174520;
                func_80047784(arg2, *((((s32) (gameWork.view.viewAngle + ((S_80172A58_1 *)arg3)->unk_2A + 0x100) >> 9) & 7) + D_80174520), 0);
            }
            if (dungeonStatus.unk_0C == 0) {
                dungeonStatus.unk_0A = (u16) (dungeonStatus.unk_0A - 1);
                ((S_80172A58_0 *)arg0)->unk_8C = func_80170E5C;
                func_800A4ACC(arg3);
                ((S_80172A58_1 *)arg3)->unk_73 = 0;
                ((S_80172A58_1 *)arg3)->unk_72 = 0;
                ((S_80172A58_1 *)arg3)->unk_6D = (u8) (((S_80172A58_1 *)arg3)->unk_6D - 1);
                ((S_80172A58_1 *)arg3)->unk_46 = (u16) (((S_80172A58_1 *)arg3)->unk_46 & 0x7FFF);
                func_800A56E0(0xB4);
            }
        }
        break;
    }
}
