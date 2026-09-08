#include "common.h"
#ifndef NULL
#define NULL 0
#endif

typedef struct {
    s16 pad0;
    u16 f2;
    s16 pad4;
    u16 f6;
    s16 pad8;
    u16 fA;
} S_80083780;

extern void *func_8009C390(s32 arg0, s32 arg1, void *arg2, s32 arg3);
extern s32 func_800AAE98(void *arg0);
extern void func_800AAEFC(void);
extern void func_800C2E84(void *arg0, s32 arg1, void *arg2);
extern void func_80033CD8(void *arg0, void *arg1);

extern s32 D_80081458[];
extern S_80083780 D_80083780;
extern u8 D_800AB1E0[];
extern u8 D_800AB708[];
extern u8 D_800D1200[];
extern u8 D_80045340[];

/* Creates an object and initializes its state, rendering data, and position. */
void func_800AB084(void) {
    s8 *object;
    s8 *state;
    s8 *position;
    s8 *render_data;

    object = (s8 *) func_8009C390(0, 0, D_800AB1E0, 0);
    state = object + 0x20;
    if (object != NULL) {
        position = *(s8 **)(object + 8);
        render_data = *(s8 **)(object + 0xC);
        *(s8 *)(state + 0x93) = 1;
        *(s32 *)(render_data + 0x28) = D_80081458[0];
        func_800C2E84(state, render_data, D_800D1200);
        func_80033CD8(state, D_80045340);
        func_800AAEFC();
        *(s16 *)(state + 0x90) = 0;
        *(void **)(state + 0x50) = D_800AB708;
        *(s16 *)(state + 0x6A) = 0;
        *(u16 *)(position + 2) = (u16) D_80083780.f2;
        *(u16 *)(position + 6) = (u16) D_80083780.f6;
        *(s16 *)(position + 0xA) = (s16) (D_80083780.fA - func_800AAE98(position));
    }
}
