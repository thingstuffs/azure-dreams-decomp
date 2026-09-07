#include "common.h"

extern u8 D_80083780[12];
extern u8 *D_800814A8;
extern s16 D_80083228[];
extern s32 D_8008346C[];
extern u8 D_8016A36C[];
extern s16 D_801760D8[];
extern u8 D_801739A0[];
extern void *D_801649B8[];

extern void func_800419EC(s32, s32, void *);
extern void func_80047784(void *, u8, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A56E0(s32);
extern void func_801676CC(void *);
extern void func_801690D8(void *, void *, void *, void *);
extern void func_80169C1C(void *, void *, void *);

/* Advances a timed actor sequence, updating effects and directional animation before clearing completion flags. */
void func_8016DBB4(u8 *sequence, u8 *transform, u8 *sprite_arg, u8 *actor_arg) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5 };
    u8 state;
    s32 anim_mode;
    u8 *anim_table;
    u8 *current_anim_table;
    void *effect_actor;
    u16 timer;
    u16 next_timer;
    s16 old_timer;
    s32 direction;
    u8 *sprite = sprite_arg;
    u8 *actor = actor_arg;
    state = sequence[0x9B];
    if (state >= 6U) {
        goto epilogue;
    }
    (void)jt_keep;
    goto *D_801649B8[(u32)state];

jt_c0:
    func_801676CC(transform);
    *(u16 *)(sequence + 0x96) = 5;
    sequence[0x9B] = sequence[0x9B] + 1;
    func_800A56E0(0x703);
    D_801760D8[0] = 0;
    goto epilogue;

jt_c1:
    timer = *(u16 *)(sequence + 0x96) - 1;
    *(u16 *)(sequence + 0x96) = timer;
    if ((timer << 0x10) <= 0) {
        goto advance;
    }
    if (!( *(u16 *)(sprite + 0x14) & 0xE000)) {
        goto epilogue;
    }
    goto advance;

jt_c2:
    timer = *(u16 *)(sequence + 0x96) + 1;
    *(u16 *)(sequence + 0x96) = timer;
    if ((s16)timer == 1) {
        func_801690D8(sequence, transform, sprite, D_80083780);
    }
    if (*(s16 *)(sequence + 0x96) == 2) {
        effect_actor = D_800814A8;
        *(u16 *)((u8 *)effect_actor + 0x10C) |= 1;
        *(s16 *)((u8 *)effect_actor + 0x6A) = *(u16 *)((u8 *)effect_actor + 0x2A) + 0x800;
        func_800419EC(6, 0xC, effect_actor);
        func_800A56E0(0x601);
        func_80169C1C(sequence, transform, sprite);
    }
    if (*(s16 *)(sequence + 0x96) == 0xB) {
        goto advance;
    }
    goto epilogue;

jt_c3:
    if (!( *(u16 *)(sprite + 0x14) & 0xE000)) {
        goto epilogue;
    }
    *(s32 *)(transform + 0x14) = 0;
    *(s32 *)(transform + 0x10) = 0;
    *(s32 *)(transform + 0x0C) = 0;
    func_800A2B04(transform, sprite[0x24], sprite[0x25]);
    anim_mode = sequence[0xAC];
    if (anim_mode == 1) {
        goto set_base1;
    }
    if (anim_mode < 2) {
        if (anim_mode == 0) {
            goto set_base0;
        }
        goto advance;
    }
    if (anim_mode == 2) {
        goto set_base2;
    }
    if (anim_mode == 3) {
        goto set_base3;
    }
    goto advance;

set_base0:
    current_anim_table = *(u8 **)(sprite + 0x2C);
    anim_table = D_801739A0;
    goto shared_base;
set_base1:
    current_anim_table = *(u8 **)(sprite + 0x2C);
    anim_table = D_801739A0 + 0x8;
    goto shared_base;
set_base2:
    current_anim_table = *(u8 **)(sprite + 0x2C);
    anim_table = D_801739A0 + 0x10;
    goto shared_base;
set_base3:
    current_anim_table = *(u8 **)(sprite + 0x2C);
    anim_table = D_801739A0 + 0x18;
    goto shared_base;

shared_base:
    if (current_anim_table != anim_table) {
        *(u8 **)(sprite + 0x2C) = anim_table;
        direction = ((s32)(D_80083228[0] + *(s16 *)(actor + 0x2A) + 0x100) >> 9) & 7;
        func_80047784(sprite, *(u8 *)((u32)direction + (u32)anim_table), 0);
    }
    goto advance;

jt_c4:
    old_timer = *(u16 *)(sequence + 0x96);
    next_timer = old_timer + 1;
    *(u16 *)(sequence + 0x96) = next_timer;
    if (old_timer < 0x50) {
        goto epilogue;
    }
    goto advance;

advance:
    state = sequence[0x9B];
    *(u16 *)(sequence + 0x96) = 0;
    sequence[0x9B] = state + 1;
    goto epilogue;

jt_c5:
    actor[0x73] = 0;
    actor[0x72] = 0;
    *(u8 **)(sequence + 0x8C) = D_8016A36C;
    D_8008346C[0] = 0;
    *(u16 *)(actor + 0x46) &= 0x7FFF;

epilogue:
    return;
}
