#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_8017140C[];
extern s32 D_8008346C[];
extern void *D_800E3DE8[];
extern u8 D_8017587C;
extern s16 D_80083228[5];
extern s32 func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(u32);
extern void func_800AD594(void *, s32);
extern void func_80047784(void *, u8, s32);

typedef struct S_8017278C_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8017278C_0;   /* arg0 in func_8017278C */




void func_8017278C(S_8017278C_0 *arg0, Rec_D_800E3D7C *arg1, Rec_D_80082E80 *arg2, void *arg3) {
    u16 temp_v0;
    s32 one;
    s32 status;
    u8 *table;

    one = 1;
    status = arg0->unk_9B;
    if (status == one) {
        goto state_1;
    }
    if (status < 2) {
        if (status == 0) {
            goto state_0_set;
        }
        goto cleanup;
    } else {
        if (status == 2) {
            goto state_2;
        }
        if (status != 3) {
            goto cleanup;
        }
        goto state_3;
    }

state_0_set:
    arg0->unk_9B = one;

state_1:
    if (arg2->unk_14.at00_u16.v & 0x8000) {
        arg0->unk_9B = 3U;
        arg2->unk_14.at00_u16.v = (u16) (arg2->unk_14.at00_u16.v | 0x6000);
        func_8009C12C(arg3, arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1);
        goto cleanup;
    }

state_0:
    table = &D_8017587C;
    arg1->unk_14.as_s32 = 0;
    arg1->unk_10.at00_s32.v = 0;
    arg1->unk_0C.as_s32 = 0;
    arg2->unk_2C.as_pu8 = table;
    func_80047784(arg2, table[((s32) (*D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    arg0->unk_96 = 9;
    arg0->unk_9B++;
    goto cleanup;

state_2:
    temp_v0 = arg0->unk_96 - 1;
    arg0->unk_96 = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        goto cleanup;
    }
    func_800A56E0(0x804);
    func_8009C12C(arg3, arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1);
    arg0->unk_9B++;
    goto cleanup;

state_3:
    if (arg2->unk_14.at00_u16.v & 0xE000) {
        func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
        func_800AD594(arg3, 0x100);
        arg0->unk_8C = D_8017140C;
        *D_8008346C = 0;
        func_800A4ACC(arg3);
        if (((Rec_D_800E3D7C *)arg3)->unk_6D.as_s8 == 0) {
            ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v = (u16) (((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x7FFF);
        } else {
            *D_800E3DE8 = arg3 - 0x20;
        }
    }

cleanup:
    return;
}
