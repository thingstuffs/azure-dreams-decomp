#include "modules/dungeon_ovl_1924800.h"


/* Apply a chance-based effect that halves the entity counter and reports the result. */
void func_8002405C(u8 *entity, s32 chance, void *unused_context) {
    s32 roll;
    s32 effect_result;
    s32 chance_value;
    s32 removed_count;
    s32 roll_remainder;
    s32 passes_chance;
    u8 *effect_input;

    if (func_8009D218(entity, 2) != 0) {
        return;
    }

    roll = func_800A6D30() & 0xffff;
    if (entity[3] != 0) {
        roll_remainder = roll % entity[3];   /* retail rejoins the common path at +0xBC here */
    } else {
        roll_remainder = 0;
    }
    chance_value = chance & 0xff;
    passes_chance = roll_remainder < (chance_value << 5);
    effect_input = (u8 *)roll;
    if (!passes_chance) {
        effect_input = entity;
        if (chance_value != 0xff) {
            func_80099844(effect_input, D_800E20FC);
            func_800B4C7C(0x53, entity, -1, 1);
            return;
        }
    }
    if (entity[0x27] >= 2) {
        removed_count = (entity[0x27] + 1) >> 1;
        entity[0x27] -= removed_count;
        {
            s32 message_arg;
            s32 format_code;
            s32 result_arg;

            message_arg = func_800990FC((s32)effect_input, chance_value);
            format_code = 8;
            result_arg = message_arg;
            effect_result = result_arg;
            message_arg = func_8009929C(format_code, result_arg);
            message_arg = func_80099734(entity, message_arg);
            message_arg = func_80099194(D_800E20D6, message_arg);
            func_80099290(message_arg);
        }
        func_800A5720(effect_result);
        func_800B4C7C(0x53, entity, removed_count, 1);   /* retail jumps to the shared call at +0x16C */
        return;
    }

    effect_input = entity;
    func_80099844(effect_input, D_800E20FC);
    func_800B4C7C(0x53, entity, -1, 1);
}
