#include "common.h"

typedef struct {
    s32 field_00;
    u8 unk04[8];
    s32 field_0C;
} Vec3;

typedef struct {
    u8 unk00[6];
    s16 field_06;
    u8 unk08[4];
    u8 field_0C;
    u8 field_0D;
    u8 field_0E;
    u8 unk0F;
    s16 field_10;
    u8 unk12[2];
    u16 flags_14;
    u8 unk16[6];
    s16 field_1C;
    s16 field_1E;
    u8 unk20[12];
    u8 *field_2C;
} Sub;

typedef struct {
    u8 unk00[42];
    s16 field_2A;
    u8 unk2C[106];
    u16 field_96;
    u8 unk98[2];
    u8 field_9A;
    u8 unk9B[3];
    s16 field_9E;
} Extra;

typedef struct {
    u8 unk00[8];
    Vec3 *position;
    Sub *sub;
    void *callback;
} Node;

extern s16 D_80083228[5];
extern u8 D_80174B30[9];
extern Node *D_80174CDC;

extern void func_800419EC(s32, s32);
extern void func_80170DCC(void *, Vec3 *, Sub *);
extern void func_800A56E0(s32);
extern void func_80047784(Sub *, u8, s32);
extern void func_80170CE0(s32, s32, s32, s32);
extern void func_800478B8(Sub *);

/* Delays an effect, then moves and fades its sprite before finishing. */
void func_80170EA0(void) {
    Extra *effect;
    Vec3 *position;
    register Sub *sprite ASM_REG("$18");
    Extra *direction_data;
    Node *node;
    s32 intensity;
    u16 elapsed;
    s32 state;

    node = D_80174CDC;
    effect = (Extra *)((u8 *)node + 0x20);
    position = node->position;
    state = effect->field_9A;
    sprite = node->sub;
    direction_data = effect;

    if (state == 1) {
        goto delay;
    }
    if (state >= 2) {
        goto check_fade;
    }
    if (state == 0) {
        goto init;
    }
    goto update_sprite;

check_fade:
    if (state == 2) {
        goto fade;
    }
    goto update_sprite;

init:
    effect->field_9A = 1;
    effect->field_96 = 0;

delay:
    elapsed = effect->field_96++;
    if ((s16)elapsed >= 0x24) {
        effect->field_96 = 0x14;
        effect->field_9E = 0x14;
        effect->field_9A++;
        func_800419EC(6, 12);
        func_80170DCC(effect, position, sprite);
        func_800A56E0(0x601);
        position->field_0C = -0x200000;
        sprite->field_10 = 0x20;
        sprite->field_2C = D_80174B30;
        sprite->flags_14 |= 0xC;
        func_80047784(sprite, D_80174B30[((D_80083228[0] + direction_data->field_2A + 0x100) >> 9) & 7], 0);
        goto update_sprite;
    }
    goto update_sprite;

fade: {
    register s32 step_or_duration ASM_REG("$4") = position->field_0C;
    s32 coordinate = position->field_00;
    register s32 step ASM_REG("$2") = step_or_duration;
    register s32 forward_arg1 ASM_REG("$5");
    register s32 forward_arg2 ASM_REG("$6");
    register s32 forward_arg3 ASM_REG("$7");
    coordinate += step_or_duration;
    position->field_00 = coordinate;
    ASM_KEEP(step);
    step /= 2;
    position->field_0C = step;
    step_or_duration = effect->field_9E;
    intensity = ((s32)(s16)(effect->field_96 - 1) << 7) / step_or_duration;
    effect->field_96--;
    sprite->field_0E = (s8)intensity;
    sprite->field_0D = (s8)intensity;
    sprite->field_0C = (s8)intensity;
    if ((s16)effect->field_96 <= 0) {
        func_80170CE0(step_or_duration, forward_arg1, forward_arg2, forward_arg3);
    }
}

update_sprite:
    func_800478B8(sprite);
}
