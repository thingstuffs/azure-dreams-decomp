#include "common.h"

extern s32 func_800990FC(s32, s32);
extern s32 func_80099194(u8 *, s32);
extern void func_80099290(s32);
extern s32 func_8009929C(s32, s32);
extern s32 func_80099734(u8 *, s32);
extern void func_80099844(u8 *, u8 *);
extern s32 func_8009D218(u8 *, s32);
extern void func_800A5720(s32);
extern s32 func_800A6D30(void);
extern void func_800B4C7C(s32, u8 *, s32, s32);

extern u8 D_800E20D6[];
extern u8 D_800E20FC[];

#ifdef __mips__
static const u32 bank_words[] __asm__("func_81904800")
    __attribute__((section(".text.func_81904800"), aligned(4))) = {
    0x800257d0,
    0x01000340,
    0x00540060,
    0x01540340,
    0x00040004,
    0x00000020,
    0x00200020,
    0x00200000,
    0x0020ffe0,
    0x0000ffe0,
    0xffe0ffe0,
    0xffe00000,
    0xffe00020,
    0x00000000,
    0x800258ec,
    0x80025960,
    0x80025c28,
    0x80025e48,
    0x80026490,
    0x800265f0,
    0x80026634,
    0x80026730,
    0x800266cc,
};
__asm__(".globl func_81904800\n"
        ".size func_81904800, 400");
#define BODY_NAME func_8190485C
#else
#define BODY_NAME func_81904800
#endif

/* Apply a chance-based effect that halves the entity counter and reports the result. */
void BODY_NAME(u8 *entity, u8 chance) {
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
            goto fallback_call;
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
fallback_call:
    func_80099844(effect_input, D_800E20FC);
    func_800B4C7C(0x53, entity, -1, 1);
}
