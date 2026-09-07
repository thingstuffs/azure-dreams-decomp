#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_800BE6F0_0_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0xE];
    u16 unk_16;
} S_800BE6F0_0_pre;   /* the 0x18 bytes before arg0 in func_800BE6F0, addressed as arg0[-1] */


typedef struct S_800BE6F0_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BE6F0_1;   /* record1 in func_800BE6F0 */

typedef struct S_800BE6F0_2 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800BE6F0_2;   /* state_base1 in func_800BE6F0 */

typedef struct S_800BE6F0_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800BE6F0_3;   /* record2 in func_800BE6F0 */

typedef struct S_800BE6F0_4 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_800BE6F0_4;   /* flags_page in func_800BE6F0 */

typedef struct S_800BE6F0_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800BE6F0_5;   /* state_base2 in func_800BE6F0 */



s32 func_80042900();
s32 func_8008D330();
s32 func_80098B38();
s32 func_800990FC();
s32 func_80099194();
s32 func_80099290();
s32 func_80099368();
s32 func_80099734();
s32 func_8009A028();
s32 func_8009A3D0();
s32 func_800A32A4();
s32 func_800A5720();
s32 func_800A5F38();
s32 func_800A63B8();
s32 func_800A6620();
s32 func_800A6D30();
s32 func_800A90E8();
s32 func_800B8228();

extern u8 D_80010980[];
extern s32 D_800814A0[4];
extern u8 D_80082E80[];
extern s32 D_80083460[5];
extern u8 D_80083780[];
extern u8 D_80089360[];
extern u8 D_800E1095[0x1E];
extern u8 D_800E10B3[];
extern u8 *D_800E3D7C;

s32 func_800BE6F0(void *arg0, s32 arg1, s16 arg2)
{
    u8 local[4];
    s32 temp_s1;
    s32 temp_v0;
    s32 index;
    s32 arg_a2;
    u8 type;
    u8 type2;
    u8 record_x;
    u8 record_y;
    S_800BE6F0_1 *record1;
    S_800BE6F0_3 *record2;
    u8 *message;
    s32 *state_base1;
    s32 *state_base2;
    s32 *state_page;
    s32 *index_base;
    s32 *flags_page;
    u8 *entity_base;
    s32 state_value;
    s32 state_masked;

    if (arg0 == D_800E3D7C) {
        ((Rec_D_800E3D7C *)arg0)->unk_110 = arg1;
        func_8008D330(arg0, D_80083780, D_80082E80, arg0);
        return 0;
    }

    if ((u32)arg0 <= 0x9FFFFFFF) {
        func_800A63B8(arg0, arg1, arg2);
    }

    if (((Rec_D_800E3D7C *)arg0)->unk_14.as_s32 & 0x4000) {
        temp_s1 = func_800990FC();
        if ((u32)(((Rec_D_800E3D7C *)arg0)->unk_10.at03_u8.v - 3) < 0x2B) {
            temp_v0 = func_80099734(arg0, temp_s1);
            message = (u8 *)0x800E0000;
            ASM_KEEP(message);   /* MATCH pin: load-bearing for the whole function shape */
            message += 0x1095;
        } else {
            temp_v0 = func_80099734(arg0, temp_s1);
            temp_v0 = func_80099194(D_800E10B3, temp_v0);
            temp_v0 = func_80099368(arg1, temp_v0);
            message = D_80089360;
        }
        temp_v0 = func_80099194(message, temp_v0);
        func_80099290(temp_v0);
        func_800A5720(temp_s1);
    }

    type = ((Rec_D_800E3D7C *)arg0)->unk_10.at03_u8.v;
    if ((u32)(type - 3) < 0x2B) {
        local[0] = type;
        type2 = ((Rec_D_800E3D7C *)arg0)->unk_10.at03_u8.v;
        if ((type2 == 3) || (type2 == 5) || (type2 == 7) ||
            (type2 == 9) || (type2 == 0xB) || (type2 == 0xD) ||
            (type2 == 0xF) || (type2 == 0x11) || (type2 == 0x13)) {
            local[0]++;
        }
        local[1] = 0x12;
        local[2] = (func_800A6D30() & 0xF) + 0xA;
        local[3] = 0;
        func_800A90E8(local);

        record1 = ((S_800BE6F0_0_pre *)arg0)[-1].unk_00;
        func_800B8228(
            record1->unk_02,
            record1->unk_06,
            record1->unk_0A,
            local);

        state_page = (s32 *)0x80080000;
        ASM_KEEP(state_page);   /* MATCH pin: keeps a constant in a register as retail does */
        state_base1 = (s32 *)((u8 *)state_page + 0x3460);
        ASM_KEEP(state_base1);   /* MATCH pin: keeps a constant in a register as retail does */
        state_value = ((S_800BE6F0_2 *)state_base1)->unk_10;
        ASM_KEEP(state_value);   /* MATCH pin: retail register colouring depends on it */
        if (state_value == (s32)((u8 *)arg0 - 0x20)) {
            state_masked = state_value & 0x7FFFFFFF;
            ((S_800BE6F0_2 *)state_base1)->unk_10 = state_masked;
        }

        temp_v0 = func_800A32A4(arg0);
        if (temp_v0 != 0) {
            index = func_800A6620(temp_v0, 0);
            if (index < 0x40) {
                index_base = (s32 *)0x80010980;
                entity_base = (u8 *)0x80010000;
                ASM_KEEP(entity_base);   /* MATCH pin: keeps a constant in a register as retail does */
                entity_base[index * 0x54 + 0xA93] = 0;
                index_base[index] = 0;
            }
        }

        if ((func_80042900(arg0, 0x1B) << 16) == 0) {
            record2 = ((S_800BE6F0_0_pre *)arg0)[-1].unk_04;
            record_x = record2->unk_24;
            record_y = record2->unk_25;
            arg_a2 = 0x3000;
            if (((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 & 0x2000) {
                arg_a2 = 0x300;
            }
            func_8009A3D0(record_x, record_y, arg_a2);
        }

        func_8009A028(arg0);
        ((S_800BE6F0_0_pre *)arg0)[-1].unk_16 |= 0x8000;
        flags_page = (s32 *)0x80080000;
        ASM_KEEP(flags_page);   /* MATCH pin: retail immediate-load split depends on it */
        ((S_800BE6F0_4 *)flags_page)->unk_14A0 |= 0x8000;
        goto success_cleanup;
    }

    func_800A5F38(arg0, arg1);
    return 1;

success_cleanup:
    func_80098B38(arg1);
    state_base2 = D_80083460;
    ASM_KEEP(state_base2);   /* MATCH pin: keeps a constant in a register as retail does */
    ((S_800BE6F0_5 *)state_base2)->unk_0A--;
    return 1;
}

/* MECHANISM: A four-byte stack array and true local joins reproduce the 0x28 frame and complete CFG.
   Held literal bases preserve the a0/a1/a2 index roles and the v1 flags-page RMW.
   Splitting runtime RMW values pins v1/v0; a keep between page and low addiu fills the local-j slot. */
