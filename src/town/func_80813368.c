#include "common.h"
extern int abs(int);

#ifndef NULL
#define NULL 0
#endif

#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define U8_AT(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(void **)((u8 *)(p) + (o)))

extern void *func_800373DC(s32);
extern void func_8003BC18(void *, void *);

extern u8 D_8003C558[16];
extern u8 D_8028DFD8[16];
extern u8 D_8052E40C[0x2000];

/* Per-frame portrait step: lay out the panel on first entry, blink its tint and ease it toward its target. */
void func_80813368(void *hud) {
    u8 frame_pad[32];
    void *obj;
    void *part;
    s32 i;
    s32 value;
    s32 table_index;
    s32 init_kind;
    s32 state;
    u16 counter;

    state = S16_AT(hud, 0x18);
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_done;
    }
    return;

state_zero:
        S16_AT(hud, 0xC) = 0x410;
        S16_AT(hud, 4) = 0x340;
        S16_AT(hud, 0xE) = 0x348;
        S16_AT(hud, 6) = 0x348;
        S16_AT(hud, 0x10) = -0x60;
        S16_AT(hud, 8) = -0x60;

        init_kind = S16_AT(hud, 0x22);
        switch (init_kind) {
        case 0:
            value = -0x60;
            goto init_pair;
        case 1:
            value = -0x98;
            goto init_pair;
        case 2:
            value = -0x30;
    init_pair:
            S16_AT(hud, 0x1E) = value;
            S16_AT(hud, 0x1C) = value;
            break;
        case 3:
            value = -0xB0;
            S16_AT(hud, 0x1C) = value;
            value = -0x10;
            goto init_last;
        case 4:
            value = -0x10;
            S16_AT(hud, 0x1C) = value;
            value = -0xB0;
    init_last:
            S16_AT(hud, 0x1E) = value;
        }

        for (i = 1; i >= 0; i--) {
            obj = func_800373DC(0x136);
            if (obj != NULL) {
                S32_AT(obj, 0x10) = (s32)D_8052E40C;
                func_8003BC18(obj, D_8003C558);
                part = PTR_AT(obj, 0xC);
                S16_AT(part, 0x1E) = 0x800;
                S16_AT(part, 0x1C) = 0x800;
                S32_AT(part, 8) = (s32)D_8028DFD8;
                U8_AT(part, 4) = 0;
                U8_AT(part, 5) = 0;
                S32_AT(part, 0xC) = 0x00808080;
                S32_AT(obj, 0x20) = (s32)hud;
                S16_AT(obj, 0x28) = i;
            }
        }
        S16_AT(hud, 0x18) = 1;
state_done:

    counter = U16_AT(hud, 0x1A) + 1;
    U16_AT(hud, 0x1A) = counter;
    if ((counter >> 2) & 1) {
        table_index = S16_AT(hud, 0x22);
        if ((U16_AT(PTR_AT(hud, 0), 0x62) &
             *(u16 *)(D_8052E40C + 0x1DD8 + (table_index * 2))) != 0) {
            S32_AT(hud, 0x14) = 0x00FFFFFF;
        } else {
            S32_AT(hud, 0x14) = 0;
        }
    } else {
        S32_AT(hud, 0x14) = 0;
    }

    if (U16_AT(PTR_AT(hud, 0), 0x64) >= U16_AT(hud, 0x20)) {
        s32 tx, x, ty, y;
        tx = S16_AT(hud, 0x1C);
        x = S16_AT(hud, 8);
        ty = S16_AT(hud, 0x1E);
        y = S16_AT(hud, 0x10);
        S16_AT(hud, 8) = x + ((tx - x) >> 1);
        S16_AT(hud, 0x10) = y + ((ty - y) >> 1);
        U16_AT(hud, 0x24) &= ~1;
    } else {
        s32 x, y;
        x = S16_AT(hud, 8);
        y = S16_AT(hud, 0x10);
        x += (-0x60 - x) >> 1;
        y += (-0x60 - y) >> 1;
        S16_AT(hud, 8) = x;
        S16_AT(hud, 0x10) = y;
        if (abs(S16_AT(hud, 0x10) + 0x60) < 2) {
            U16_AT(hud, 0x24) |= 1;
        }
    }
}
