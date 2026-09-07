#include "common.h"

typedef struct S_8008CD4C_0 {
    u8 pad_00[0x24];
    u8 unk_24;
    union { u8 s; volatile u8 u; } unk_25;   /* accessed as both */
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_8008CD4C_0;   /* arg2 in func_8008CD4C */

typedef struct S_8008CD4C_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x88];
    s32 unk_124;
} S_8008CD4C_1;   /* arg0 in func_8008CD4C */

typedef struct S_8008CD4C_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x5C];
    s16 unk_88;
} S_8008CD4C_2;   /* actor in func_8008CD4C */

typedef struct S_8008CD4C_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    s16 unk_04;
} S_8008CD4C_3;   /* control in func_8008CD4C */


typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

M2C_UNK func_80048A44();
M2C_UNK func_80094ED4();
M2C_UNK func_8009A21C();
M2C_UNK func_8009A3D0();
s32 func_8009ADB8();
s32 func_8009B25C();
M2C_UNK func_8009F644();
M2C_UNK func_800A56E0();

extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s16 D_80083228[5];
extern u8 D_80083460[9];
extern u8 D_800DCFB8[];
extern u8 D_800DD018[];

/* Checks the next tile and updates the actor's movement state and directional animation. */
void func_8008CD4C(S_8008CD4C_1 *action, M2C_UNK context, S_8008CD4C_0 *sprite, void *actor_data, s32 move_state) {
    register S_8008CD4C_2 *actor ASM_REG("$20") = actor_data;   /* MATCH pin: retail address form (%hi/%lo vs base+direction_offset) depends on it */
    register s32 state ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 direction_offset;
    s32 next_x;
    s32 next_y;
    s32 target;
    u16 *x_step;
    u16 *y_step;
    u8 *control;

    sprite->unk_2C = D_800DD018;
    state = move_state;
    action->unk_9A = 0x18;
    action->unk_9B = 0;
    action->unk_8C = 0;

    if ((s16)state != -2) {
        direction_offset = ((actor->unk_2A.s >> 8) & 0xE);
        x_step = (u16 *)((u8 *)D_8006CCD8 + direction_offset);
        next_x = sprite->unk_24 + *x_step;
        y_step = (u16 *)((u8 *)D_8006CCE8 + direction_offset);
        next_y = sprite->unk_25.s + *y_step;
        target = func_8009B25C(actor, next_x & 0xFFFF, next_y & 0xFFFF,
                            actor->unk_88);
        if (target != 0) {
            if ((func_8009ADB8(actor, target, (s16)next_x, (s16)next_y,
                               actor->unk_88) << 16) != 0) {
                action->unk_124 = target;
                func_8009A3D0(sprite->unk_24,
                              sprite->unk_25.s, 0x300);
                sprite->unk_24 =
                    sprite->unk_24 + *(u8 *)x_step;
                sprite->unk_25.u =
                    sprite->unk_25.s + *(u8 *)y_step;
                func_8009A21C(sprite->unk_24,
                              sprite->unk_25.u, 0x300);

                actor->unk_1C |= 0x40000000;
                control = D_80083460;
                ((S_8008CD4C_3 *)control)->unk_04 = 0x20;
                ((S_8008CD4C_3 *)control)->unk_02 |= 8;
                action->unk_9B = 0x10;
                sprite->unk_2C = D_800DCFB8;
                action->unk_96 = 4;
                func_8009F644(actor, 8, 0, 0);
                func_800A56E0(0x50B);
                func_80094ED4(action, context, sprite, actor);
            }
        }
    }

    func_80048A44(
        sprite,
        sprite->unk_2C
            [((D_80083228[0] + actor->unk_2A.u + 0x100) >> 9) & 7],
        0, 1);
    ASM_KEEP(actor);   /* MATCH pin: retail schedule: same instructions, different order without it */
}
