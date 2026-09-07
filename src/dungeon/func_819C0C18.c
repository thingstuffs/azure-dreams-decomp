#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct {
    s16 x;
    u16 y;
} OffsetPair;

typedef struct {
    OffsetPair entries[8];
} OffsetTable;

typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} Position;

typedef struct {
    u8 pad0[0x2A];
    u16 unk2A;
    u8 pad2C[0x6A];
    s16 unk96;
    u8 pad98[0x0E];
    u16 unkA6;
    u8 unkA8;
    u8 unkA9;
    u8 unkAA;
} GlobalObj;

typedef struct {
    u16 flags;
} ChildObj;

extern OffsetTable D_80024028;
extern void *D_80024048[];
extern s16 D_8002992E;
extern u8 D_8006E8A0[];
extern u8 D_8006EE50[];
extern s32 D_800814A0;
extern GlobalObj *D_800814A8[3];
extern u16 D_80082E86;
extern u16 D_80082E94;
extern u8 D_80083160[];
extern u8 D_80083460[];
extern Position D_80083780;

extern void func_80024BA0(void);
extern void func_80025CE8(s32, s32, s32, s32);
extern void func_8002626C(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_80026898(void) __attribute__((noreturn));
extern void func_800268A0(void) __attribute__((noreturn));
extern void func_80026924(void) __attribute__((noreturn));
extern void func_8003F80C(void *, s32, s32, s32);
extern s32 func_80040490(void *, void *);
extern void func_800542BC(void);
extern s32 func_80069EF8(void);
extern void func_800A56E0(s32);
extern void func_800C77D0(void *, void *, s32, s32);

void func_819C0C18(void *arg0)
{
    static void *const keep_cases[] __attribute__((used)) = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4, &&done, &&done
    };
    s32 rect[2];
    OffsetTable offsets = D_80024028;
    u8 *colors = D_80083160;
    s32 state;

    state = FIELD(arg0, s16, 0xA);
    if ((u32)state >= 7) {
        goto done;
    }
    goto *D_80024048[state];

case_0:
    {
        s32 rect0;
        s32 rect1;
        void *owner;
        ChildObj *child;
        u16 state;

        func_800C77D0((u8 *)D_800814A8[0] - 0x20, &D_80083780, 8, 0x400);
        rect0 = 0x010003A0;
        rect1 = 0x00400020;
        FIELD(D_800814A8[0], u8, 0x102) = 1;
        rect[0] = rect0;
        rect[1] = rect1;
        func_80040490(D_8006E8A0, rect);
        func_8003F80C(D_8006EE50, 0x7AC0, 1, 2);
        func_80024BA0();

        owner = D_800814A8[0];
        FIELD(owner, s32, 0xF4) = 0;
        FIELD(owner, s16, 0x96) = 30;
        state = FIELD(arg0, u16, 0xA);
        D_8002992E = 1;
        FIELD(arg0, u16, 0x2A) = 0;
        FIELD(arg0, u16, 0xA) = state + 1;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
        child = FIELD(arg0, ChildObj *, 4);
        if ((child->flags & 0x80) == 0) {
            return;
        }
        func_800A56E0(0x300);
        func_800542BC();
        func_80026898();
        return;
    }

case_1:
    {
        u16 timer = FIELD(arg0, u16, 0x28);
        register GlobalObj *owner ASM_REG("$3");   /* MATCH pin: keeps a constant in a register as retail does */
        Position *position;
        OffsetPair *offsetBase;
        u16 nextState;
        u16 direction;
        s16 i;

        FIELD(arg0, u16, 0x28) = timer + 1;
        if ((s16)timer >= 0x52) {
            owner = D_800814A8[0];
            FIELD(arg0, s16, 0x1C) = 0x21;
            FIELD(owner, u16, 0xA6) = FIELD(owner, u16, 0xA6) - 1;
            FIELD(owner, u8, 0xA8) = FIELD(arg0, u8, 8);
            owner = D_800814A8[0];
            nextState = FIELD(arg0, u16, 0xA);
            direction = FIELD(owner, u16, 0x2A);
            FIELD(arg0, u16, 0xA) = nextState + 1;
            FIELD(arg0, u16, 0x28) = 0;
            FIELD(arg0, s16, 0x24) = (direction >> 9) & 7;
        }

        i = 0;
        if (FIELD(arg0, s16, 0x28) == 0x4A) {
            Position *callPosition = &D_80083780;

            func_80025CE8(FIELD(callPosition, s16, 2),
                          FIELD(callPosition, s16, 6),
                          FIELD(callPosition, s16, 0xA),
                          FIELD(D_800814A8[0], s16, 0x2A));
        }

        FIELD(arg0, s16, 0x24) = (FIELD(D_800814A8[0], u16, 0x2A) >> 9) & 7;
        position = &D_80083780;
        offsetBase = offsets.entries;
        do {
            s32 ry;
            s32 rx;
            s32 rz;

            ry = (s16)((func_80069EF8() & 0x7F) - 0x40);
            rx = (s16)((func_80069EF8() & 0x7F) - 0x40);
            rz = (s16)((func_80069EF8() & 0x7F) - 0x40);

            func_8002626C((u8 *)arg0 - 0x20, FIELD(arg0, s16, 0x24),
                          0x00C0C0C0, 0x28, ry, rx, rz,
                          (s16)(position->x + ({
                              OffsetPair *offset = (OffsetPair *)
                                  ((u8 *)offsetBase +
                                  FIELD(arg0, s16, 0x24) * 4);
                              offset->x;
                          }) * 128),
                          (s16)(position->y + ({
                              OffsetPair *offset = (OffsetPair *)
                                  ((u8 *)offsetBase +
                                  FIELD(arg0, s16, 0x24) * 4);
                              (s32)(offset->y << 16) >> 9;
                          })),
                          (s16)(position->z - 0x74));
            i++;
        } while (i < 2);

        if (colors[0xA8] < 0x3D) {
            return;
        }
        colors[0xA8] -= 2;
        colors[0xA9] -= 2;
        colors[0xAA] -= 2;
        func_80026924();
        return;
    }

case_2:
    {
        s32 resetTimer;
        u16 deadState;

        FIELD(arg0, u16, 0x28) = 0;
        FIELD(arg0, u16, 0xA) = FIELD(arg0, u16, 0xA) + 1;
        if (colors[0xA8] >= 0x3D) {
            colors[0xA8] -= 2;
            colors[0xA9] -= 2;
            colors[0xAA] -= 2;
        }
        FIELD(arg0, u16, 0x1C) = FIELD(arg0, u16, 0x1C) - 1;
        if (FIELD(arg0, s16, 0x1C) > 0) {
            return;
        }
        resetTimer = 0x3C;
        deadState = FIELD(arg0, u16, 0xA);
        ASM_KEEP(deadState);   /* MATCH pin: retail delay-slot fill depends on it */
        FIELD(arg0, s16, 0x1C) = resetTimer;
        func_800268A0();
        return;
    }

case_3:
    {
        s8 color = colors[0xA8];
        s32 dungeonMode;

        if ((u8)color < 0x80) {
            colors[0xA8] += 10;
            colors[0xA9] += 10;
            colors[0xAA] += 10;
        }
        if ((D_80082E94 & 0x8000) == 0) {
            FIELD(arg0, u16, 0x1C) = FIELD(arg0, u16, 0x1C) - 1;
            if (FIELD(arg0, s16, 0x1C) >= 0) {
                return;
            }
        }
        dungeonMode = D_8002992E;
        FIELD(arg0, s16, 0x1C) = 0;
        if (dungeonMode == 0) {
            FIELD(arg0, u16, 0x28) = 0;
            FIELD(arg0, u16, 0xA) = FIELD(arg0, u16, 0xA) + 1;
            func_80026924();
            return;
        } else {
            D_8002992E = 0;
            func_80026924();
            return;
        }
    }

case_4:
    {
        u16 timer = FIELD(arg0, u16, 0x28);

        FIELD(arg0, u16, 0x28) = timer + 1;
        if ((s16)timer < 4) {
            return;
        }
        colors[0xAA] = 0x80;
        colors[0xA9] = 0x80;
        colors[0xA8] = 0x80;
        {
            u8 *dungeonState = D_80083460;

            FIELD(dungeonState, s32, 0xC) = 0;
            FIELD(dungeonState, u16, 0xA) =
                FIELD(dungeonState, u16, 0xA) - 1;
        }
        D_80082E86 = 0;
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        return;
    }

done:
    return;
}
