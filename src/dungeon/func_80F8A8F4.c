#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_801740F4_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_801740F4_1;   /* work in func_801740F4 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80047784();
extern s32 func_800990FC(void);
extern s32 func_80099194();
extern s32 func_80099290();
extern s32 func_80099734();
extern s32 func_800A04F0();
extern s32 func_800A2BDC();
extern s32 func_800A5720();
extern s32 func_800A6D30(void);

extern M2C_UNK D_80170854;
extern u8 D_80174B0C[];

/* Start the actor's hit reaction, then build and post the damage message for it. */
void func_801740F4(void *work, void *part_a, void *part_b, EntityRec *actor) {
    s32 flags;
    void *call_arg;
    u32 pass_result;
    s32 raw_result;
    s32 result;
    s32 field_60;
    u8 *table_base;

    actor->unk_71 = (u8)(actor->unk_71 & 0x7F);
    if (!(dungeonStatus.flags & 0x2000) && ((func_800A2BDC(actor) << 0x10) == 0)) {
        ((S_801740F4_1 *)work)->unk_8C = 0;
        ((S_801740F4_1 *)work)->unk_9A = 0x17;
        ((S_801740F4_1 *)work)->unk_9B = 0;
        if (actor->flags1C & 0x400) {
            flags = actor->flags14;
            if (!(flags & 0x80000000)) {
                flags |= 0x80000000;
                actor->flags14 = (s32)flags;
                actor->facing = (u16)(((u16)actor->facing) + ((func_800A6D30() & 7) << 9));
            }
        }
        field_60 = func_800A04F0(actor, ((Rec_D_80082E80 *)part_b)->unk_24, ((Rec_D_80082E80 *)part_b)->unk_25,
            (s16)((u16)actor->facing));
        table_base = D_80174B0C;
        actor->target = field_60;
        (*(u8 **)((u8 *)part_b + 0x2C)) = table_base;
        func_80047784(part_b, table_base[((s32)(gameWork.view.viewAngle + (s16)((u16)actor->facing) + 0x100)
            >> 9) & 7], 0);
        actor->unk_6D = (u8)(((u8)actor->unk_6D) - 1);
        dungeonStatus.unk_0A = (u16)(((u16)dungeonStatus.unk_0A) + 1);
        raw_result = func_800990FC();
        call_arg = actor;
        pass_result = raw_result;
        result = pass_result;
        raw_result = func_80099734(call_arg, pass_result);
        func_80099290(func_80099194(&D_80170854, raw_result));
        func_800A5720(result);
    }
}
