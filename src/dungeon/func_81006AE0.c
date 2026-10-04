#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef s32 M2C_UNK;

typedef struct S_801722E0_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0xC];
    void * unk_A8;
} S_801722E0_2;

extern M2C_UNK func_80047784();
extern s32 func_800990FC();
extern s32 func_80099194();
extern void * func_80099290();
extern s32 func_80099734();
extern s32 func_800A2BDC();
extern s32 func_800A5720();

extern u8 D_80170838[16];
extern u8 D_80170848[16];
extern u8 D_80174880[9];

#line 1 "a"
/* Step the actor's walk animation: clear its 0x71 busy bit and, when the global 0x2000 mode is off and the ready query says 0, arm state 0x17, point the part at the direction table and advance the shared counters. */
void func_801722E0(void *owner, void *unused, void *part, EntityRec *actor) {
    s32 original_value;
    s32 current_value;
    s32 adjusted_value;

    actor->unk_71 = (u8)(actor->unk_71 & 0x7F);
    if (!(dungeonStatus.flags & 0x2000) &&
        ((func_800A2BDC(actor) << 0x10) == 0)) {
        u8 *table = D_80174880;

        ((S_801722E0_2 *)owner)->unk_9A = 0x17;
        ((S_801722E0_2 *)owner)->unk_8C = 0;
        ((S_801722E0_2 *)owner)->unk_9B = 0;
        (*(u8 * *)((u8 *)part + 0x2C)) = table;
        func_80047784(
            part,
            table[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        actor->unk_6D = (u8)(((u8)actor->unk_6D) - 1);
        dungeonStatus.unk_0A = (u16)(((u16)dungeonStatus.unk_0A) + 1);
        adjusted_value = func_80099734(actor, current_value = func_800990FC());
        original_value = current_value;
        current_value = adjusted_value;
        func_80099290(func_80099194(
            D_80170848,
            func_80099734(((S_801722E0_2 *)owner)->unk_A8,
                func_80099194(D_80170838, current_value))));
        func_800A5720(original_value);
    }
}
