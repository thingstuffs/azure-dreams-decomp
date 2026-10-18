#include "modules/dungeon_ovl_188898c.h"

void func_80024060(s32 x, s32 y, void *kind, s32 flags) {
    u8 *actor = D_800E3D7C;
    x = (s16)x;
    y = (s16)y;
    flags = ((u8)flags >> 2) + 0x10;
    do {
        if ((s16)check_entity_interaction_compatibility(kind, actor) != 0) {
            u8 *header = *(u8 **)(actor - 0x14);
            if (abs(header[0x24] - x) < 3 && abs(header[0x25] - y) < 3 && (s16)check_entity_eligibility(actor) != 0) {
                s32 amount = flags + (generate_random_value() & 3);
                s32 mode = 0x10;
                if (D_800E3D68 == 0xFF) mode = 0xFF;
                try_apply_status_effect(actor, mode, amount);
            }
        }
        actor = *(u8 **)(actor + 0x5C) + 0x20;
    } while (actor != D_800E3D7C);
}
