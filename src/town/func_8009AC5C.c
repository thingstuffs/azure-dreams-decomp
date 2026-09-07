#include "common.h"
#include "records/Rec_D_800E3D7C.h"


extern s32 func_80098464();
extern s32 func_80098480();
extern s32 func_80098488();
extern s32 func_80098490();
extern s32 func_80098988();
extern s16 func_800C2AE8();



typedef struct S_800983BC_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
    u8 pad_0C[0x4];
    s16 unk_10;
} S_800983BC_1;   /* arg0 in func_800983BC */

void func_800983BC(S_800983BC_1 *arg0, Rec_D_800E3D7C *arg1, s32 arg2) {
    s16 temp_a0;
    u16 temp_v0;
    s32 side_v0;
    register s32 side_v1 ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */

    arg1->unk_08.at02_s16.v = func_800C2AE8(arg1);
    temp_v0 = arg0->unk_0A - 1;
    arg0->unk_0A = temp_v0;
    if ((s16)temp_v0 < 0) {
        func_80098988(arg0, arg1, arg2);
        func_80098490();
        return;
    }
    temp_a0 = arg0->unk_10;
    if (temp_a0 == 0x400) {
        goto case_400;
    }
    if (temp_a0 < 0x401) {
        if (temp_a0 == 0) {
            goto case_0;
        }
        func_80098480();
        return;
    }
    if (temp_a0 == 0xC00) {
        goto case_C00;
    }
    func_80098480();
    return;

case_400:
    side_v0 = arg1->unk_00.at00_s32.v;
    side_v1 = 0x120000;
    ASM_KEEP(side_v0);   /* MATCH pin: retail basic-block layout depends on it */
    ASM_TAILSLOT_PIN(side_v1);   /* MATCH pin: retail delay-slot contents depend on it */
    func_80098464();
    return;

case_C00:
    arg1->unk_00.at00_s32.v -= 0x120000;
    func_80098490();
    return;

case_0:
    side_v0 = arg1->unk_04.at00_s32.v;
    side_v1 = 0x120000;
    ASM_KEEP(side_v0);   /* MATCH pin: retail basic-block layout depends on it */
    ASM_LIVE_SIBCALL_PIN(side_v1, 1179648);   /* MATCH pin: load-bearing for the whole function shape */
    func_80098488();
    arg1->unk_04.at00_s32.v -= 0x120000;
}
