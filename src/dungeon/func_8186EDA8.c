#include "modules/dungeon_ovl_188e800.h"
#include "modules/dungeon_native_abi.h"
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

   /* arg1 in func_8186EDA8 */

   /* arg0 in func_8186EDA8; pointer addresses record offset 0x2 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern s16 D_80025308;
s32 func_800644B8(s16);                          /* extern */
s32 func_80064584(s16);                          /* extern */





/* Updates a rotating dungeon effect through delay, contraction, fade, and completion. */
void func_800245A8(DungeonState *anim, S_8186EDA8_0 *position, DungeonEffect *input_effect) {
    s16 phase;
    s16 fade_angle;
    s16 shrink_angle;
    s16 radius;
    s32 radius_step;
    u16 delay_timer;
    u16 finish_timer;
    u8 fade_level;
    DungeonEffect *effect = input_effect;
    s32 first_angle = anim->angle;


    position->unk_00 = (s32) (anim->base0 + (anim->count * func_800644B8((*(u16 *)&D_80025308 = 1,
        first_angle)) * 0x10));
    position->unk_04 = (s32) (anim->base1 + (anim->count * func_80064584(anim->angle) * 0x10));
    func_800478B8(effect);
    phase = anim->state;
    switch (phase) {
    case 0:
        delay_timer = ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_04 - 1;
        ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_04 = delay_timer;
        if ((delay_timer << 0x10) <= 0) {
            ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_02.u = (s16) ((u16) ((S_8186EDA8_1 *)((u8 *)anim
                - 0x2))->unk_02.u + 1);
        }
        break;
    case 1:
        shrink_angle = (u16) ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_0E - ((S_8186EDA8_1 *)((u8 *)anim
            - 0x2))->unk_10;
        ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_0E = shrink_angle;
        if (shrink_angle < 0) {
            ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_0E = (s16) (shrink_angle + 0x1000);
        }
        if ((s16) ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_10 < 0x7F8) {
            ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_10 = (u16) (((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_10 + 8);
        }
        radius = ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_0C;
        if (radius >= 0x41) {
            if (radius >= 0x65) {
                radius_step = 3;
            } else if (radius >= 0x47) {
                radius_step = 2;
            } else if (radius >= 0x33) {
                radius_step = 2;
            } else {
                radius_step = 1;
            }
            ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_0C = (s16) ((u16) ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_0C
                - radius_step);
            effect->x1C -= 0x46;
            effect->y1E -= 0x46;
            effect->c += 4;
            effect->d += 4;
            effect->e += 4;
            break;
        }
        ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_04 = 0x28U;
        ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_02.u = (s16) ((u16) ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_02.u
            + 1);
        break;
    case 2:
        fade_angle = (u16) ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_0E - ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_10;
        ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_0E = fade_angle;
        if (fade_angle < 0) {
            ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_0E = (s16) (fade_angle + 0x1000);
        }
        if ((s16) ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_10 < 0x100) {
            ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_10 = (u16) (((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_10 + 8);
        }
        radius = ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_0C;
        if (radius >= 0x1B) {
            ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_0C = (s16) (radius - 1);
        }
        fade_level = effect->c;
        if (fade_level >= 2U) {
            effect->c = (u8) (fade_level - 2);
            effect->d -= 2;
            effect->e -= 2;
        }
        if (effect->c == 0) {
            ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_04 = 0U;
            ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_02.u = (s16) ((u16) ((S_8186EDA8_1 *)((u8 *)anim
                - 0x2))->unk_02.u + 1);
        }
        effect->x1C -= 0x14;
        effect->y1E += 0xC8;
        break;
    case 3:
        finish_timer = ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_04 - 1;
        ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_04 = finish_timer;
        if ((finish_timer << 0x10) <= 0) {
            ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_00 = (u16) (((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_00
                | 0x8000);
            objectFlagBlock.flags |= 0x8000;
        }
        break;
    }
    if (effect->flags14 & 0x8000) {
        ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_00 = (u16) (((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_00 | 0x8000);
        objectFlagBlock.flags |= 0x8000;
    }
    return;

}
