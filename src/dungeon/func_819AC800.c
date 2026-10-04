#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct {
    u8 pad00[0xA];
    s16 state;
    s32 result;
    u8 pad10[0xA];
    s16 timer1A;
    s16 timer1C;
    u8 pad1E[2];
    s16 mode20;
    s16 timer22;
} EventState;

typedef struct {
    u8 pad00[0xA6];
    u16 countA6;
    u8 colorA8;
    u8 padA9;
    u8 colorAA;
    u8 padAB[0x49];
    s32 resultF4;
    u8 padF8[0xA];
    u8 flag102;
} DungeonObject;

extern u8 D_80027452[16];
extern s32 D_8002744C;
extern u8 D_80028260[];
extern u8 D_80028780[];
extern s16 D_800287A0;
extern u8 D_800287A2;
extern s32 D_800287A4;
extern void *D_800814A8_count __asm__("D_800814A8");

extern void *func_800244C4(void *, void *);
extern void func_8003F80C(void *, s32, s32, s32);
extern void func_80040490(void *, void *);
extern void func_800A56E0(s32);

void func_80024020(EventState *event);

/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol func_80024000).  The state table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */
void (*const module_entry)(EventState *) __asm__("func_80024000") = func_80024020;

/* Advances a dungeon event through setup, activation, timed color fades, and cleanup. */
void func_80024020(EventState *event) {
    s32 setup[2];
    GameWork *colors;
    s32 state;

    colors = &gameWork;
    state = event->state;
    switch (state) {
    case 0:
    {
        EntityRec *object;
        u8 event_option;

        setup[0] = 0x010003A0;
        setup[1] = 0x00400020;
        func_80040490(D_80028260, setup);
        func_8003F80C(D_80028780, 0x7AC0, 1, 2);
        object = D_800814A8;
        D_800287A0 = 1;
        event_option = ((u8 *)event)[9];
        D_8002744C = 0;
        D_800287A2 = event_option;
        D_800287A4 = *(s32 *)event;
        object->unk_F4 = 0;
        object->unk_A8 = ((u8 *)event)[8];
        D_800814A8->unk_102 = 1;
        event->state++;
    }
    case 1:
        if ((**(u16 **)((u8 *)event + 4) & 0x80) == 0) {
            break;
        }
        event->result = (s32)func_800244C4(*(void **)(*(u8 **)event - 0x18), *(void **)event);
        if (event->result == 0) {
            break;
        }
        event->mode20 = -1;
        event->timer22 = 0x20;
        event->timer1C = 0x10;
        ((DungeonObject *)D_800814A8_count)->countA6--;
        event->state++;
        func_800A56E0(0x300);
        break;

    case 2:
    {
        s16 wait_ticks;

        wait_ticks = (s16)(event->timer1C - 1);
        event->timer1C = wait_ticks;
        if (wait_ticks >= 0) {
            break;
        }
    }
        event->state++;
        break;

    case 3:
        D_800287A0 = 0;
        event->timer1A = 0x20;
        event->mode20 = 0;
        event->state++;
        break;

    case 4:
    {
        s16 fade_ticks;

        colors->view.unk_090 += (u8)((0x80 - colors->view.unk_090) / event->timer1A);
        colors->view.unk_092 += (u8)((0x80 - colors->view.unk_092) / event->timer1A);
        fade_ticks = (s16)(event->timer1A - 1);
        event->timer1A = fade_ticks;
        if (fade_ticks > 0) {
            break;
        }
        colors->view.unk_092 = 0x80;
        colors->view.unk_090 = 0x80;
    }
        event->state++;
        break;

    case 5:
        if (*(s16 *)D_80027452 == 0) {
            {
                dungeonStatus.unk_0C = 0;
                dungeonStatus.unk_0A--;
            }
            *(u16 *)((u8 *)event - 2) |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }
    }
    if (event->mode20 < 0) {
        s16 fade_ticks;

        colors->view.unk_090 += (u8)((0x20 - colors->view.unk_090) / event->timer22);
        colors->view.unk_092 += (u8)((0x20 - colors->view.unk_092) / event->timer22);
        fade_ticks = (s16)(event->timer22 - 1);
        event->timer22 = fade_ticks;
        if (fade_ticks <= 0) {
            event->mode20 = 0;
        }
    }
    *(s16 *)D_80027452 = 0;
}
