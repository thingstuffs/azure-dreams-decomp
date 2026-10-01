#include "common.h"
#include "shared/dungeon_status.h"

extern s32 func_80042900(void *, s32);
extern s8 func_8009FB34(u8, u8);
extern s32 func_800A03C4(void *, u8, u8);
extern s32 func_800A1C58(void *);
extern s32 func_800A2C34(s32);
extern void func_800AA258(void *, s32, void *, void *);
extern s32 func_800AA6B4(void *, s32, void *, s32);
extern void func_800AA888(void *, s32, void *, void *);
extern void func_800ACB98(void *, s32, void *, void *);
extern void func_800B318C(void *, s32, void *, void *);

/* Dispatch an target action and update the actor and destination state. */
void func_800B2A60(u8 *actor, s32 action_context, u8 *destination, u8 *target)
{
    DungeonGlobalStatus *flags = &dungeonStatus;
    u8 *idle_actor = actor;


    if (!(flags->flags & 0x1000)) {
        if (*(u8 *)(target + 0x25) == 0) {
            *(s8 *)(actor + 0xAD) = 0;
            func_800ACB98(idle_actor, action_context, destination, target);
            return;
        }

        if ((func_80042900(target, 1) << 16) == 0) {
            if (!(flags->flags & 0x2000)) {
                if (*(s32 *)(target + 0x1C) & 0x100) {
                    func_800AA258(actor, action_context, destination, target);
                    return;
                }

                if (*(u8 *)(actor + 0x9A) != 0xE) {
                    *(u8 *)(actor + 0x9A) = 0xE;
                }
                *(u16 *)(actor + 0x98) &= 0xFFF3;

                if ((*(s16 *)(target + 0x64) != 0) &&
                    (func_800AA6B4(actor, action_context, destination, 0) != 0)) {
                    return;
                }

                if (*(s32 *)(target + 0x1C) & 0x80000) {
                    func_800AA888(actor, action_context, destination, target);
                    func_800B318C(actor, action_context, destination, target);
                    return;
                }

                if ((func_800A1C58(target) << 16) != 0) {
                    *(s8 *)(actor + 0xAD) = 0;
                    func_800ACB98(actor, action_context, destination, target);
                    return;
                }
            }

            *(s8 *)(destination + 0x26) = func_8009FB34(*(u8 *)(destination + 0x24),
                                                     *(u8 *)(destination + 0x25));
            if (*(s8 *)(target + 0x6D) <= 0) {
                return;
            }
            if (dungeonStatus.flags & 0x1000) {
                return;
            }
            if ((func_800A2C34(0) << 16) != 0) {
                return;
            }
            if (func_800A03C4(target, *(u8 *)(destination + 0x24),
                              *(u8 *)(destination + 0x25)) == 0) {
                goto clear;
            }
        } else {
            *(s8 *)(actor + 0xAD) = 0;
            func_800ACB98(actor, action_context, destination, target);
            return;
        }

fail:
        *(s8 *)(actor + 0xAD) = 0;
        func_800ACB98(actor, action_context, destination, target);
        return;

clear:
        *(s8 *)(target + 0x6D) = 0;
    }

    return;
}
