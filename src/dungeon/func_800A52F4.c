#include "common.h"
#include "shared/game_work.h"


extern void func_80042518(void *slots, s32 type);
extern s32 func_80042900(void *entry, s32 effect_id);
extern void func_80042B68(void *owner, s32 match_type);
extern void func_80047784(void *object, s32 table_index, s32 entry_index);

/* Initializes actor state and selects a display variant for its facing direction. */
void func_800AAA54(void *actor, void *unused, void *display, u8 *facing_variants) {
    *((u8 *) actor + 0x9A) = 8;
    *((u8 *) actor + 0x9B) = 0;
    *(s32 *) ((u8 *) actor + 0x8C) = 0;
    *(s32 *) ((u8 *) display + 0x2C) = (s32) facing_variants;
    if (facing_variants != 0) {
        func_80047784(display, facing_variants[(s32) (gameWork.view.viewAngle + *(s16 *) ((u8 *) actor + 0x2A) + 0x100)
            >> 9 & 7], 0);
    }
    *(s32 *) ((u8 *) actor + 0x1C) = *(s32 *) ((u8 *) actor + 0x1C) | 0x04000000;
    func_80042B68(actor, 4);
    if ((func_80042900(actor, 0xA) << 0x10) != 0) {
        *((u8 *) actor + 0x13) = *((u8 *) actor + 0xA8);
        func_80042518(actor, 0xA);
    }
    *(s16 *) ((u8 *) actor + 0x96) = 0x40;
}
