#include "common.h"
#include "shared/sys_flags.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad00[8];
    s32 field08;
    u8 pad0c[0x80];
    void *field8c;
    u8 pad90[6];
    u16 countdown;
    u8 pad98[3];
    u8 state;
    u8 pad9c[0x30];
    u8 *table;
    u8 padd0[0x3e];
    s16 field10e;
    s32 field110;
    s32 field114;
} S_8003E2D8;

typedef struct {
    u8 pad00[8];
    s32 field08;
    u8 pad0c[8];
    u16 flags;
    u8 pad16[0x16];
    void *field2c;
} S_arg2;

typedef struct {
    u8 pad00[0x2a];
    s16 coord;
} S_arg3;

extern u8 D_800DD148[];
extern u8 D_800DD150[];
extern u8 D_8008ACDC[];

extern s32 func_8003DE58(s32, void *, void *, s32);
extern void func_80048A44(void *, u8, s16, s32);
extern void func_8008D368(void *, void *, void *, u8 *, s32);
extern void func_80091934(void *, void *, void *);
extern void func_800D7A14(s32);

/* Advance the actor's directional animation state and delayed transition. */
void func_80092BB8(S_8003E2D8 *controller, void *context, S_arg2 *actor, S_arg3 *facing) {
    s32 state;
    s32 query_result;
    s32 direction;

    state = controller->state;
    switch (state) {
    case 0:
        if ((s32)((((s32)gameWork.view.viewAngle + facing->coord + 0x100) >> 9) & 7) == 2) {
            u8 *animation_table;

            animation_table = controller->table;
            actor->field2c = animation_table;
            direction = (((s32)gameWork.view.viewAngle + facing->coord + 0x100) >> 9) & 7;
            func_80048A44(actor, animation_table[direction], controller->field10e, 1);
            controller->state++;
        } else {
            facing->coord = (u16)facing->coord + 0x200;
        }
        break;
    case 1:
        if (D_80013714 & 8) {
            if (actor->flags & 0x6000) {
                if (actor->field2c == D_800DD148) {
                    controller->state = 0x10;
                } else {
                    controller->field8c = D_8008ACDC;
                }
            }
        } else if ((func_8003DE58(actor->field08, actor, &query_result, 0) != 0) || (actor->flags & 0x8000)) {
            func_800D7A14(controller->field114);
            controller->state++;
        }
        break;
    case 2:
        if ((actor->flags & 0x8000) || (dungeonStatus.unk_0A < 2)) {
            if (controller->field110 != 0) {
                func_80091934(controller, context, actor);
                return;
            }
            actor->field2c = D_800DD150;
            func_80048A44(actor, D_800DD150[(((s32)gameWork.view.viewAngle + facing->coord + 0x100) >> 9) & 7], 2, 1);
            controller->field8c = D_8008ACDC;
        }
        break;
    case 0x10: {
        u16 countdown;

        countdown = controller->countdown - 1;
        controller->countdown = countdown;
        if ((s32)(countdown << 16) <= 0) {
            func_8008D368(controller, context, actor, D_800DD150, 0);
        }
        break;
    }
    }
}
