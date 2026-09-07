#include "common.h"

typedef struct {
    u16 x;
    s16 y;
    s16 w;
    s16 h;
    s16 u;
    s16 v;
} LocalArgs;

typedef struct {
    u8 pad00[0xC];
    u16 *field0C;
    u8 *field10;
    u8 pad14[2];
    u8 field16;
    u8 state;
    u8 pad18[4];
    void *field1C;
} Actor;

typedef struct {
    u8 pad00[2];
    u16 field02;
    u8 pad04[2];
    u16 field06;
    u8 pad08[2];
    s16 field0A;
} Output;

extern void func_8004491C(void *, void *);
extern void func_8006658C(void *, void *);
extern void func_80067E2C(void *, void *);
extern void func_80174FC0(void *, s32, s32);
extern void func_801750E4(s32, s32, s32, s32, s32, s32, void *, void *, void *, s32, s32);

extern s32 D_800814A0;
typedef struct {
    u8 *ptr;
} PagePtr;

extern PagePtr D_80083160;
extern s32 D_800CEEFC[3];
extern u8 D_801C9E40[16];

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))
#define DUNGEON_INITIAL (D_80083160.ptr)
#define DUNGEON_FROM_PAGE (D_80083160.ptr)

void func_80174AD4(u8 *arg0, u8 *arg1, u8 *arg2)
{
    LocalArgs local;
    Actor *actor;
    Output *out;
    u8 *dungeon0;
    u8 *dungeon1;
    u8 *dungeon2;
    u8 *dungeon_end;
    u8 *scratch;
    void *packet0;
    void *packet1;
    void *packet2;
    u8 other;
    u8 flag;
    s16 count;
    s16 next_count;
    s32 y;
    s32 u;
    s32 wh;
    s32 state;
    u8 timer3;
    u8 timer_default;

    actor = (Actor *)arg0;
    out = (Output *)arg1;
    dungeon0 = DUNGEON_INITIAL;
    dungeon_end = D_801C9E40;
    state = actor->state;
    other = dungeon0 != dungeon_end;
    scratch = dungeon0 + 0xB0;

    if (state == 0) {
        packet0 = FIELD(dungeon0, void *, 0x8D0);
        FIELD(dungeon0, void *, 0x8D0) = (u8 *)packet0 + 0xC;
        func_80067E2C(packet0, DUNGEON_FROM_PAGE);
        func_8006658C(scratch, packet0);

        y = 0x110;
        local.x = 0x340;
        local.y = 0x100;
        local.w = 0x20;
        local.h = 0x20;
        u = 0x350;
        local.u = u;
        flag = other;
        if (flag != 0) {
            y = 0x30;
        }
        local.v = y;

        func_801750E4(0x10, 0x10, 0, 0, u, local.v,
                     actor, (u8 *)actor + 4, scratch, 0, 0x20);

        dungeon1 = DUNGEON_FROM_PAGE;
        packet1 = FIELD(dungeon1, void *, 0x8D0);
        FIELD(dungeon1, void *, 0x8D0) = (u8 *)packet1 + 0x10;
        FIELD(packet1, s32, 4) = 0x60000000;
        FIELD(packet1, s8, 3) = 3;
        FIELD(packet1, u16, 8) = local.x;
        y = local.y;
        if (flag != 0) {
            y -= 0xE0;
        }
        wh = *(s32 *)&local.w;
        FIELD(packet1, s16, 0xA) = y;
        FIELD(packet1, s32, 0xC) = wh;
        func_8006658C(scratch, packet1);

        dungeon2 = DUNGEON_FROM_PAGE;
        packet2 = FIELD(dungeon2, void *, 0x8D0);
        FIELD(dungeon2, void *, 0x8D0) = (u8 *)packet2 + 0xC;
        func_80067E2C(packet2, (void *)&local);
        func_8006658C(scratch, packet2);
    } else if (state == 1) {
        func_8004491C((u8 *)actor - 0x20, D_800CEEFC);
    } else if (state == 3) {
        timer3 = FIELD(arg2, u8, 0xC);
        if (timer3 != 0) {
            timer3 -= 8;
            FIELD(arg2, u8, 0xC) = timer3;
            if (timer3 == 0) {
                FIELD(actor, u16, -2) |= 0x8000;
                D_800814A0 |= 0x8000;
            }
        }
        goto tail;
    } else {
        timer_default = FIELD(arg2, u8, 0xC);
        if (timer_default < 0xC0) {
            FIELD(arg2, u8, 0xC) = timer_default + 0x20;
        }
        if (actor->field16 == *actor->field10) {
            goto tail;
        }
    }
    actor->state++;
tail:
    count = 4;
    if (actor->state != 3) {
        out->field02 = FIELD(actor->field1C, u16, 2);
        out->field06 = FIELD(actor->field1C, u16, 6);
        out->field0A = FIELD(actor->field1C, u16, 0xA) - 0xC;
        do {
            func_80174FC0((u8 *)actor - 0x20, (FIELD(FIELD(actor, void *, 0xC), u16, 0) >> 9) & 7, 0xFF);
            next_count = count - 1;
            count = next_count;
        } while ((next_count << 16) > 0);
    }
}
