#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"


extern s32 func_8003AD08();
extern void dungeonBeginDeferredItemAction();
extern void dungeonClearSlotAndUpdateLinkedState();
extern s32 func_800990FC(void);
extern s32 func_80099194();
extern void func_80099290();
extern s32 func_80099734();
extern void func_800A5720();
extern void func_800A5F38();
extern void func_800A63B8();
extern s32 func_800A6D30();
extern s16 dungeonApplyActorFoodPreference();
extern void dungeonCreateTimedPairedParticleEmitter();

extern s32 D_800893E0;
extern s32 D_800E18A4;


typedef struct S_800C4490_0_pre {
    s32 unk_00;
    u8 pad_04[0x14];
} S_800C4490_0_pre;   /* the 0x18 bytes before arg0 in dungeonUseItemToHealSmallRandomAmount, addressed as arg0[-1] */


/* Applies a capped random stat gain to the target and displays its effect message. */
s32 dungeonUseItemToHealSmallRandomAmount(void *target, s32 source, s16 effect_mode) {
    s16 stat_gap;
    s32 stat_gain;
    s32 effect_text;
    s32 message_context;

    if (target == ((s32)D_800E3D7C)) {
        ((EntityRec *)target)->unk_110 = source;
        dungeonBeginDeferredItemAction(target, &D_80083780.x.v, &D_80082E80.unk_000, target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        func_800A63B8(target, source, effect_mode);
        if (dungeonApplyActorFoodPreference(target,
                          (*(u16 *)(((u8 *)D_800DDE84) +
                                    (*(u8 *)((u8 *)&((EntityRec *)target)->unk_10 + 3)) * 2) >> 6) & 3,
                          source) == 0) {
            func_800A5F38(target, source);
            return 1;
        }
    }

    stat_gain = (func_800A6D30() & 3) + 7;
    if (stat_gain >= 0x100) {
        stat_gain = 0xFF;
    }

    stat_gap = ((EntityRec *)target)->unk_29 - ((EntityRec *)target)->unk_28;
    if (stat_gap < stat_gain) {
        stat_gain = stat_gap;
    }
    ((EntityRec *)target)->unk_64 = stat_gain;

    if (((EntityRec *)target)->flags14 & 0x4000) {
        effect_text = func_800990FC();
        {
            void *message_target;
            s32 context_arg;

            message_target = target;
            context_arg = effect_text;
            message_context = context_arg;
            effect_text = func_80099734(message_target, context_arg);
        }
        func_80099290(func_80099194(
            &D_800893E0,
            func_8003AD08(((EntityRec *)target)->unk_64,
                          func_80099194(&D_800E18A4, effect_text))));
        func_800A5720(message_context);
    }

    dungeonCreateTimedPairedParticleEmitter(((S_800C4490_0_pre *)target)[-1].unk_00, 0x20E020, target);
    dungeonClearSlotAndUpdateLinkedState(source);
    dungeonStatus.unk_0A--;
    return 1;
}
