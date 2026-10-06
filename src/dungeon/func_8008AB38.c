#include "shared/dungeon_actor_callbacks.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#ifndef NULL
#define NULL 0
#endif

typedef struct {
    u8 pad0[0x14];
    u16 flags14;
    u8 pad16[0x16];
    u8 *table;
} Arg2Struct;

typedef struct {
    u8 pad0[0x1C];
    s32 flags1c;
    u8 pad20[0xA];
    s16 angle;
    u8 pad2C[0x30];
    s32 val5c;
} Arg3Struct;

typedef struct {
    u8 pad0[0x8C];
    void *handler;
    u8 pad90[6];
    u16 timer;
    u8 pad98[3];
    u8 state;
    u8 pad9C[6];
    u16 flagsa2;
} Arg0Struct;

extern u8 D_800DD0F8[];
extern void *D_8008B870;
extern u8 D_800DD0F0;

extern s32 func_80042900(void *entry, s32 effect_id);
extern void func_80048A44(void *obj, s32 frame_group, s32 frame_index, s32 slot_index);
extern void func_80099F04(s32 firstEntryBase);
extern void func_80099F70(s32 firstNodeBase);
extern void func_800A56E0(s32 query_value);
extern s32 func_800A5C70(void);

/* Advances actor animation states, periodic events, and handler transitions. */
void func_80090298(Arg0Struct *controller, void *unused, Arg2Struct *animation, Arg3Struct *actor) {
    s32 event_code;
    GameWork *scene = &gameWork;

    (void)unused;
    switch (controller->state) {
    case 0:
        if (animation->flags14 & 0xE000) {
            animation->table = &D_800DD0F0;
            func_80048A44(animation, (&D_800DD0F0)[((s32)(scene->view.viewAngle + actor->angle + 0x100) >> 9) & 7], 0,
                1);
            controller->handler = &D_8008B870;
            controller->state = (s8)(controller->state + 1);
        }
        break;

    case 1:
        if (!(controller->timer & 0x1F)) {
            event_code = 0x50F;
            if (controller->timer & 0x20) {
                event_code = 0x50E;
            }
            func_800A56E0(event_code);
        }
        if (!(dungeonStatus.flags & 4) && (controller->flagsa2 & 0x10)) {
            if ((scene->buttons & 0x20) && (func_800A5C70() != 0)) {
                dungeonStatus.flags |= 0x80;
            }
            if ((func_80042900(actor, 1) << 0x10) == 0) {
                animation->table = D_800DD0F8;
                func_80048A44(animation, D_800DD0F8[((s32)(gameWork.view.viewAngle + actor->angle + 0x100) >> 9) & 7],
                    0, 1);
                controller->handler = NULL;
                dungeonStatus.unk_0A += 1;
                controller->state += 1;
            } else {
                func_80099F70(actor->val5c);
                func_80099F04(actor->val5c);
                dungeonStatus.flags |= 0x812;
            }
        }
        break;

    case 2:
        if (animation->flags14 & 0xE000) {
            actor->flags1c &= ~0x200;
            func_80099F70(actor->val5c);
            func_80099F04(actor->val5c);
            dungeonStatus.flags |= 0x812;
            controller->handler =func_8008ACDC;
            dungeonStatus.unk_0A -= 1;
        }
        break;
    }

    controller->timer += 1;
}
