#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_801727C8_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s32 unk_A4;
    s16 unk_A8;
} S_801727C8_0;   /* arg0 in func_801727C8 */


typedef struct S_801727C8_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801727C8_2_pre;   /* the 0x14 bytes before owner in func_801727C8, addressed as owner[-1] */

typedef struct S_801727C8_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801727C8_3;   /* temp_v1_3 in func_801727C8 */


typedef struct S_801727C8_5 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_801727C8_5;   /* temp_s6 in func_801727C8 */



typedef struct S_801727C8_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_801727C8_8;   /* var_v0_3 in func_801727C8 */


typedef struct {
    u8 pad_00[0x12];
    u8 type;
    u8 pad_13;
} DungeonEntry;

extern void *D_80170838[];
s32 func_8003F270();
void func_80047784();
void *func_800A05A4();
M2C_UNK func_800A2B04();
M2C_UNK func_800A4ACC();
M2C_UNK func_800A56E0();
s32 func_800A94A0();
M2C_UNK func_800DB2DC();
extern DungeonEntry D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern s32 D_8008346C;
extern M2C_UNK D_801711A4;
extern u8 D_8017418C;
extern u8 D_801741B4;
extern u8 D_801741BC;

void func_801727C8(void *arg0, void *arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7 };
    u8 *var_a1;
    M2C_UNK *var_v0_3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1_2;
    s32 var_s5;
    s32 var_v0_2;
    s32 var_v1;
    u16 temp_v0_3;
    u8 *var_s1;
    s32 temp_v1;
    s32 state_selector;
    void *temp_s6;
    void *temp_s7;
    void *temp_v1_3;
    void *var_v0;

    var_s5 = 0;
    temp_v0 = ((S_801727C8_0 *)arg0)->unk_A4;
    state_selector = ((S_801727C8_0 *)arg0)->unk_9B;
    temp_s6 = temp_v0 + 0x20;
    temp_s7 = temp_v0 + 0x28;
    if (state_selector == 1) {
        goto block_37;
    }
    if ((s32) state_selector >= 2) {
        goto block_4;
    }
    if (state_selector == 0) {
        goto block_7;
    }
    return;
block_4:
    if (state_selector == 2) {
        goto block_40;
    }
    if (state_selector == 3) {
        goto block_45;
    }
    return;
block_7:
    if (!(((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x2000)) {
        goto block_13;
    }
    temp_v0_2 = ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x3FFF;
    if ((u32) (temp_v0_2 - 1) >= 7U) {
        goto block_21;
    }
    (void)jt_keep; goto *D_80170838[(u32)((temp_v0_2) - 1)];
jt_c7:
    var_s5 = 1;
    goto block_18;
jt_c6:
    var_s5 = 1;
    goto block_19;
jt_c5:
    var_s5 = 1;
    goto block_20;
block_13:
    temp_v1_2 = ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x3FFF;
    if (temp_v1_2 == 2) {
        goto block_19;
    }
    if (temp_v1_2 >= 3) {
        goto block_17;
    }
    var_s1 = NULL;
    if (temp_v1_2 == 1) {
        goto block_20;
    }
    goto block_22;
block_17:
    var_s1 = NULL;
    if (temp_v1_2 != 3) {
        goto block_22;
    }
jt_c3:
block_18:
    var_s1 = arg3 + 0xE;
    goto block_22;
jt_c2:
block_19:
    var_s1 = arg3 + 0xB;
    goto block_22;
jt_c1:
block_20:
    var_s1 = arg3 + 8;
    goto block_22;
jt_c4:
block_21:
    var_s1 = NULL;
block_22:
    if (*var_s1 == 0) {
        goto block_36;
    }
    *(volatile u16 *)((s8 *)arg0 + 0x98) = (u16) (((S_801727C8_0 *)arg0)->unk_98 & 0xFF7F);
    {
        s32 special_test;

        special_test = var_s5;
        ASM_KEEP(special_test);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        if (special_test == 0) {
            goto block_25;
        }
    }
    var_v0 = D_800814A8;
    ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv = var_v0;
    goto block_27;
block_25:
    if (D_8006DE24[*var_s1].type != 2) {
        goto block_28;
    }
    var_v0 = ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv;
    var_a1 = (u8 *)0x80170000;
    if (var_v0 == NULL) {
        goto block_34;
    }
block_27:
    {
        register void *owner ASM_REG("$2") = var_v0;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        temp_v1_3 = ((S_801727C8_2_pre *)owner)[-1].unk_00;
        ASM_USE(owner);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ((Rec_D_800E3D7C *)arg3)->unk_72.as_s8 = (s8) ((S_801727C8_3 *)temp_v1_3)->unk_24;
        ((Rec_D_800E3D7C *)arg3)->unk_73.as_s8 = (s8) ((S_801727C8_3 *)temp_v1_3)->unk_25;
    }
    goto block_33;
block_28:
    {
        void *spawned;

        spawned = func_800A05A4(arg3, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 0x10);
        ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv = spawned;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    }
    var_v0_2 = ((Rec_D_800E3D7C *)arg3)->unk_72.as_s8;
    var_v1 = ((Rec_D_800E3D7C *)arg3)->unk_73.as_s8;
    if (var_v0_2 >= 0) {
        goto block_30;
    }
    var_v0_2 = 0 - var_v0_2;
block_30:
    if (var_v1 >= 0) {
        goto block_32;
    }
    var_v1 = 0 - var_v1;
block_32:
    ((Rec_D_800E3D7C *)arg3)->unk_72.as_s8 = var_v0_2;
    ((Rec_D_800E3D7C *)arg3)->unk_73.as_s8 = var_v1;
block_33:
    var_a1 = (u8 *)0x80170000;
block_34:
    var_a1 += 0x41B4;
    ((S_801727C8_5 *)temp_s6)->unk_04 = (u16) (((S_801727C8_5 *)temp_s6)->unk_04 & 0x7FFF);
    (*(M2C_UNK **)((u8 *)temp_s7 + 0x2C)) = var_a1;
    func_80047784(temp_s7, *((u8 *) ((((s32) (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7) + (s32) var_a1)), 0);
    if (func_800A94A0(arg3, var_s1, var_s5, arg0 + 0x98) == 0) {
        goto block_54;
    }
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xF7FF);
    func_800DB2DC(arg1, arg2, arg3, 0xA);
    func_800A56E0(0x703);
    temp_v1 = ((S_801727C8_0 *)arg0)->unk_9B;
    {
        register s32 next_state ASM_REG("$3") = 6;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        ((S_801727C8_0 *)arg0)->unk_96 = (u16)next_state;
    }
    goto block_44_increment;
block_36:
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
    D_8008346C = 0;
    ((Rec_D_800814A8 *)D_800814A8)->unk_A6 = (u16) ((*(u16 *)((u8 *)D_800814A8 + 0xA6)) - 1);
    func_800A4ACC(arg3);
    ((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8 = (u8) (((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8 - 1);
    ((S_801727C8_0 *)arg0)->unk_8C = &D_801711A4;
    ((Rec_D_800E3D7C *)arg3)->unk_73.as_s8 = 0;
    ((Rec_D_800E3D7C *)arg3)->unk_72.as_s8 = 0;
    ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v = (u16) (((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x7FFF);
    return;
block_37:
    if (func_8003F270() == 0) {
        goto block_39;
    }
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v | 0x800);
    return;
block_39:
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xF7FF);
    ((S_801727C8_0 *)arg0)->unk_9B = (u8) (((S_801727C8_0 *)arg0)->unk_9B + 1);
block_40:
    temp_v0_3 = ((S_801727C8_0 *)arg0)->unk_96 - 1;
    ((S_801727C8_0 *)arg0)->unk_96 = temp_v0_3;
    if ((temp_v0_3 << 0x10) <= 0) {
        goto block_42;
    }
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
        goto block_54;
    }
block_42:
    ((S_801727C8_0 *)arg0)->unk_98 = (u16) (((S_801727C8_0 *)arg0)->unk_98 | 0x80);
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
        goto block_54;
    }
    (*(M2C_UNK **)((u8 *)arg2 + 0x2C)) = &D_801741BC;
    func_80047784(arg2, *((((s32) (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7) + &D_801741BC), 0);
block_44:
    temp_v1 = ((S_801727C8_0 *)arg0)->unk_9B;
block_44_increment:
    ((S_801727C8_0 *)arg0)->unk_9B = (u8) (temp_v1 + 1);
    return;
block_45:
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
        goto block_54;
    }
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
    if (((Rec_D_80082E80 *)arg2)->unk_2C.as_pm == &D_8017418C) {
        var_v0_3 = &D_80083460;
        goto block_50;
    }
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x6000)) {
        goto block_49;
    }
    ((S_801727C8_5 *)temp_s6)->unk_04 = (u16) (((S_801727C8_5 *)temp_s6)->unk_04 | 0x8000);
    ((S_801727C8_0 *)arg0)->unk_A8 = 0;
    (*(M2C_UNK **)((u8 *)arg2 + 0x2C)) = &D_8017418C;
    func_80047784(arg2, *((((s32) (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7) + &D_8017418C), 0);
block_49:
    var_v0_3 = &D_80083460;
block_50:
    if (((S_801727C8_8 *)var_v0_3)->unk_0C != 0) {
        goto block_54;
    }
    ((S_801727C8_8 *)var_v0_3)->unk_0A = (u16) (((S_801727C8_8 *)var_v0_3)->unk_0A - 1);
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xF7FF);
    ((S_801727C8_0 *)arg0)->unk_8C = &D_801711A4;
    func_800A4ACC(arg3);
    if ((s8) ((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8 <= 0) {
        goto block_53;
    }
    ((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8 = (u8) (((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8 - 1);
block_53:
    ((Rec_D_800E3D7C *)arg3)->unk_73.as_s8 = 0;
    ((Rec_D_800E3D7C *)arg3)->unk_72.as_s8 = 0;
    ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v = (u16) (((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x7FFF);
    func_800A56E0(0xB4);
block_54:
    return;
}
