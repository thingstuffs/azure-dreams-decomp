#include "common.h"

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

typedef struct {
    u8 pad00[0xA];
    s16 state;
    s32 result;
} GlobalState;

extern u8 D_80027452[16];
extern s32 D_8002744C;
extern void *D_80024008[];
extern u8 D_80028260[];
extern u8 D_80028780[];
extern s16 D_800287A0;
extern u8 D_800287A2;
extern s32 D_800287A4;
extern s32 D_800814A0;
extern void *D_800814A8;
extern void *D_800814A8_count __asm__("D_800814A8");
extern u8 D_80083160[];
extern s32 D_80083460;

extern void *func_800244C4(void *, void *);
extern void func_8003F80C(void *, s32, s32, s32);
extern void func_80040490(void *, void *);
extern void func_800A56E0(s32);

#ifdef __mips__
#define BODY_NAME jt_body_819AC800
#define BODY_LINKAGE static
#else
#define BODY_NAME func_80024000
#define BODY_LINKAGE
#endif

BODY_LINKAGE void BODY_NAME(EventState *event);

/* Advances a dungeon event through setup, activation, timed color fades, and cleanup. */
BODY_LINKAGE void BODY_NAME(EventState *event) {
#ifdef __mips__
    static void *const state_table[] __asm__("func_80024000")
        __attribute__((section(".text.func_80024000"), aligned(4))) = {
        (void *)BODY_NAME, 0,
        &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5
    };
#else
    static void *const state_table[] = {
        &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5
    };
#endif
    s32 setup[2];
    u8 *colors;
    s32 state;

    colors = D_80083160;
    state = event->state;
    if ((u32)state >= 6) {
        goto common_tail;
    }
    (void)state_table;
    goto *D_80024008[(u32)state];

jt_c0: {
        DungeonObject *object;
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
        object->resultF4 = 0;
        object->colorA8 = ((u8 *)event)[8];
        ((DungeonObject *)D_800814A8)->flag102 = 1;
        event->state++;
    }
jt_c1:
        if ((**(u16 **)((u8 *)event + 4) & 0x80) == 0) {
            goto common_tail;
        }
        event->result = (s32)func_800244C4(*(void **)(*(u8 **)event - 0x18), *(void **)event);
        if (event->result == 0) {
            goto common_tail;
        }
        event->mode20 = -1;
        event->timer22 = 0x20;
        event->timer1C = 0x10;
        ((DungeonObject *)D_800814A8_count)->countA6--;
        event->state++;
        func_800A56E0(0x300);
        goto common_tail;

jt_c2: {
        s16 wait_ticks;

        wait_ticks = (s16)(event->timer1C - 1);
        event->timer1C = wait_ticks;
        if (wait_ticks >= 0) {
            goto common_tail;
        }
        goto advance_state;
    }

jt_c3:
        D_800287A0 = 0;
        event->timer1A = 0x20;
        event->mode20 = 0;
        event->state++;
        goto common_tail;

jt_c4: {
        s16 fade_ticks;

        colors[0xA8] += (u8)((0x80 - colors[0xA8]) / event->timer1A);
        colors[0xAA] += (u8)((0x80 - colors[0xAA]) / event->timer1A);
        fade_ticks = (s16)(event->timer1A - 1);
        event->timer1A = fade_ticks;
        if (fade_ticks > 0) {
            goto common_tail;
        }
        colors[0xAA] = 0x80;
        colors[0xA8] = 0x80;
    }
advance_state:
        event->state++;
        goto common_tail;

jt_c5:
        if (*(s16 *)D_80027452 != 0) {
            goto common_tail;
        }
        {
            GlobalState *global_state = (GlobalState *)&D_80083460;
            global_state->result = 0;
            global_state->state--;
        }
        *(u16 *)((u8 *)event - 2) |= 0x8000;
        D_800814A0 |= 0x8000;

common_tail:
    if (event->mode20 < 0) {
        s16 fade_ticks;

        colors[0xA8] += (u8)((0x20 - colors[0xA8]) / event->timer22);
        colors[0xAA] += (u8)((0x20 - colors[0xAA]) / event->timer22);
        fade_ticks = (s16)(event->timer22 - 1);
        event->timer22 = fade_ticks;
        if (fade_ticks <= 0) {
            event->mode20 = 0;
        }
    }
    *(s16 *)D_80027452 = 0;
}

#ifdef __mips__
__asm__(".globl func_80024000\n"
        ".size func_80024000, 808");
#endif
