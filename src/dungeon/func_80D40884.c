#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_80176084_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x14];
    u8 unk_B0;
    u8 unk_B1;
    u8 pad_B2[0x2];
    u8 unk_B4;
    s8 unk_B5;
} S_80176084_0;   /* arg0 in func_80176084 */




typedef struct S_80176084_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80176084_4;   /* global in func_80176084 */



extern M2C_UNK func_80042B68();
extern M2C_UNK func_80047784();
extern M2C_UNK func_800A2B04();
extern M2C_UNK func_800A56E0();
extern M2C_UNK func_800AA36C();
extern M2C_UNK func_801708B8();

extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_800E23E0[];
extern u8 D_800E2448[];
extern u8 D_80171A80[];

/* Advance a two-phase animation transition and finalize the entity state. */
void func_80176084(void *state, void *motion, void *sprite, void *entity) {
    u16 start_ticks;
    u16 finish_ticks;
    u8 phase;
    u8 step;
    u32 active_step;

    phase = ((S_80176084_0 *)state)->unk_9B;
    if (phase != 0) {
        if (phase != 1) {
            return;
        }
        goto update_finish;
    }
    step = ((S_80176084_0 *)state)->unk_B1;
    active_step = 1;
    if (step != 0) {
        if (step != active_step) {
            goto check_finish;
        }
        goto update_start;
    }
    do {
        ((S_80176084_0 *)state)->unk_B1 = active_step;
    } while (0);
    ((S_80176084_0 *)state)->unk_96 = 4U;
    (*(M2C_UNK * *)((u8 *)sprite + 0x2C)) = (M2C_UNK *)D_800E2448;
    func_80047784(sprite, D_800E2448[((s32)(D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    if ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) ||
        (func_800A56E0(0x801), ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) != 0))) {
update_start:
        start_ticks = ((S_80176084_0 *)state)->unk_96;
        ((S_80176084_0 *)state)->unk_96 = (u16)(start_ticks - 1);
        if (((start_ticks << 0x10) <= 0) || (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
            ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
            ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
            func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
            ((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 |= 0x40000;
            ((S_80176084_0 *)state)->unk_B5 = 0;
            ((S_80176084_0 *)state)->unk_98 |= 8;
            (*(M2C_UNK * *)((u8 *)sprite + 0x2C)) = (M2C_UNK *)D_800E23E0;
            func_80047784(sprite, D_800E23E0[((s32)(D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
            ((S_80176084_0 *)state)->unk_96 = 5U;
            ((S_80176084_0 *)state)->unk_9B++;
            ((S_80176084_0 *)state)->unk_B1++;
            if (((S_80176084_0 *)state)->unk_B0 == 0) {
                func_801708B8(state, motion, sprite);
            }
        }
check_finish:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
update_finish:
            finish_ticks = ((S_80176084_0 *)state)->unk_96;
            ((S_80176084_0 *)state)->unk_96 = (u16)(finish_ticks - 1);
            if (((finish_ticks << 0x10) <= 0) || (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
                ((Rec_D_80082E80 *)sprite)->unk_06.as_s16 = 0;
                ((S_80176084_0 *)state)->unk_8C = (M2C_UNK *)D_80171A80;
                func_80042B68(entity, 0x1B);
                if (((S_80176084_0 *)state)->unk_B4 == 0) {
                    u8 *shared_state = (u8 *)&D_80083460;
                    ((S_80176084_4 *)shared_state)->unk_0C = 0;
                    ((S_80176084_4 *)shared_state)->unk_0A--;
                    ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v &= 0x7FFF;
                }
                func_800AA36C(state, motion, sprite, entity);
            }
        }
    }
}
