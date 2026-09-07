#include "common.h"

typedef struct S_80174AD4_0 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_80174AD4_0;   /* dungeon0 in func_80174AD4 */

typedef struct S_80174AD4_1 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_80174AD4_1;   /* dungeon1 in func_80174AD4 */

typedef struct S_80174AD4_2 {
    u8 pad_00[0x3];
    s8 unk_03;
    s32 unk_04;
    u16 unk_08;
    s16 unk_0A;
    s32 unk_0C;
} S_80174AD4_2;   /* packet1 in func_80174AD4 */

typedef struct S_80174AD4_3 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_80174AD4_3;   /* dungeon2 in func_80174AD4 */

typedef struct S_80174AD4_4 {
    u8 pad_00[0xC];
    u8 unk_0C;
} S_80174AD4_4;   /* arg2 in func_80174AD4 */

typedef struct S_80174AD4_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80174AD4_5;   /* actor->field1C in func_80174AD4 */

typedef struct S_80174AD4_6 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_80174AD4_6;   /* actor in func_80174AD4 */

typedef struct S_80174AD4_7 {
    u16 unk_00;
} S_80174AD4_7;   /* ((S_80174AD4_6 *)actor)->unk_0C in func_80174AD4 */


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
        packet0 = ((S_80174AD4_0 *)dungeon0)->unk_8D0;
        ((S_80174AD4_0 *)dungeon0)->unk_8D0 = (u8 *)packet0 + 0xC;
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
        packet1 = ((S_80174AD4_1 *)dungeon1)->unk_8D0;
        ((S_80174AD4_1 *)dungeon1)->unk_8D0 = (u8 *)packet1 + 0x10;
        ((S_80174AD4_2 *)packet1)->unk_04 = 0x60000000;
        ((S_80174AD4_2 *)packet1)->unk_03 = 3;
        ((S_80174AD4_2 *)packet1)->unk_08 = local.x;
        y = local.y;
        if (flag != 0) {
            y -= 0xE0;
        }
        wh = *(s32 *)&local.w;
        ((S_80174AD4_2 *)packet1)->unk_0A = y;
        ((S_80174AD4_2 *)packet1)->unk_0C = wh;
        func_8006658C(scratch, packet1);

        dungeon2 = DUNGEON_FROM_PAGE;
        packet2 = ((S_80174AD4_3 *)dungeon2)->unk_8D0;
        ((S_80174AD4_3 *)dungeon2)->unk_8D0 = (u8 *)packet2 + 0xC;
        func_80067E2C(packet2, (void *)&local);
        func_8006658C(scratch, packet2);
    } else if (state == 1) {
        func_8004491C((u8 *)actor - 0x20, D_800CEEFC);
    } else if (state == 3) {
        timer3 = ((S_80174AD4_4 *)arg2)->unk_0C;
        if (timer3 != 0) {
            timer3 -= 8;
            ((S_80174AD4_4 *)arg2)->unk_0C = timer3;
            if (timer3 == 0) {
                (*(u16 *)((u8 *)actor + -2)) |= 0x8000;
                D_800814A0 |= 0x8000;
            }
        }
        goto tail;
    } else {
        timer_default = ((S_80174AD4_4 *)arg2)->unk_0C;
        if (timer_default < 0xC0) {
            ((S_80174AD4_4 *)arg2)->unk_0C = timer_default + 0x20;
        }
        if (actor->field16 == *actor->field10) {
            goto tail;
        }
    }
    actor->state++;
tail:
    count = 4;
    if (actor->state != 3) {
        out->field02 = ((S_80174AD4_5 *)(actor->field1C))->unk_02;
        out->field06 = ((S_80174AD4_5 *)(actor->field1C))->unk_06;
        out->field0A = ((S_80174AD4_5 *)(actor->field1C))->unk_0A - 0xC;
        do {
            func_80174FC0((u8 *)actor - 0x20, (((S_80174AD4_7 *)(((S_80174AD4_6 *)actor)->unk_0C))->unk_00 >> 9) & 7, 0xFF);
            next_count = count - 1;
            count = next_count;
        } while ((next_count << 16) > 0);
    }
}
