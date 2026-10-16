#include "modules/dungeon_ovl_7f0f7800_p05.h"

/* Advances a timed actor animation and applies its completion effects. */
void func_801727CC(T_801727CC_Obj0 *action, s32 context, T_801727CC_Obj2 *sprite, T_801727CC_Obj3 *actor) {
    s16 ticks_left;
    s32 state;
    s32 volume;

    state = action->field9B;
    ticks_left = action->field96 - 1;
    action->field96 = ticks_left;
    switch (state) {
    case 0:
        if (sprite->field14 & 0x8000) {
            action->field9B = 0xFF;
            sprite->field14 |= 0x6000;
            func_8009C12C(actor, sprite, actor->field2A, 1);
            return;
        }
        if (action->field98 & 0x8000) {
            sprite->field2C = D_80174010;
            ticks_left = 10;
        } else {
            sprite->field2C = D_80173FE8;
            ticks_left = 4;
        }
        action->field96 = ticks_left;
        func_80047784(sprite, sprite->field2C[(((s32) (gameWork.view.viewAngle + actor->field2A + 0x100) >> 9) & 7)],
            0);
        action->field9B++;
        return;
    case 1:
        if ((ticks_left << 16) > 0)
            return;
        func_800A56E0(0x809);
        func_8009C12C(actor, sprite, actor->field2A, 1);
        action->field9B = 0xFF;
        return;
    case 0xFF:
        if ((sprite->field14 & 0xE000) == 0)
            return;
        func_800A2B04(context, sprite->field24, sprite->field25);
        volume = 0x100;
        if (action->field98 & 0x8000)
            volume = 0x800;
        func_800AD594(actor, volume);
        action->field8C = &func_80170F68;
        dungeonStatus.unk_0C = 0;
        func_800A4ACC(actor);
        if (actor->field6D == 0) {
            actor->field46 &= 0x7FFF;
            return;
        }
        *D_800E3DE8 = (void *)((s8 *)actor - 0x20);

        return;
    default:
        return;
    }
}
