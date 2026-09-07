#include "common.h"


typedef void (*Callback)(void *, void *, void *, void *);

extern u8 D_8006CCF8[9];
extern s16 D_80083228[5];
extern u8 D_80083460[9];
extern u8 D_80171058[];
extern u8 D_80174880[9];
extern Callback D_80174900[];

extern void func_80047738(void *, u8, s8);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern void func_800A020C(s32, void *);
extern s32 func_800A9E70(void *, void *, void *, void *);
extern void func_800AA36C(void *, void *, void *, void *);
extern s32 func_800BCB04(s32, s32, s32);
extern void func_80170C0C(void) __attribute__((noreturn));
extern void func_80170CB4(void) __attribute__((noreturn));
extern void func_80170D20(void) __attribute__((noreturn));
extern void func_80170F8C() __attribute__((noreturn));
extern void func_80171030(void) __attribute__((noreturn));


typedef struct S_80170A78_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80170A78_0;   /* arg1 in func_80170A78 */

typedef struct S_80170A78_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    union { u8 * p; void * p2; } unk_2C;   /* accessed as both */
} S_80170A78_1;   /* arg2 in func_80170A78 */

typedef struct S_80170A78_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80170A78_2;   /* state in func_80170A78 */

void func_80170A78(void *arg0, void *arg1, void *arg2)
{
    void *obj = arg0;
    void *motion = arg1;
    void *part = arg2;
    register void *state ASM_REG("$18") = arg0;   /* MATCH pin: load-bearing for the whole function shape */
    register s32 work ASM_REG("$16");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 direction ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register u32 raw_work ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    Callback callback;
    s32 floor_y;
    s16 delta;
    u16 part_flags;
    register u16 count ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    register s32 flags ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    s32 amount;
    u8 collision;

    if (*(u16 *)(D_80083460 + 2) & 0x2000) {
        callback = (*(Callback *)((u8 *)arg0 + 0x8C));
        if (callback == (Callback)D_80171058) {
            void *entry_obj = arg0;
            ASM_KEEP(entry_obj);   /* MATCH pin: retail register colouring depends on it */
            callback(entry_obj, arg1, arg2, entry_obj);
            return func_80171030();
        } else {
            return ((*(u8 *)((u8 *)arg0 + 0x71)) &= 0x7F, func_80171030());
        }
    }

#define arg0 obj
#define arg1 motion
#define arg2 part

    ASM_KEEP(obj);   /* MATCH pin: retail register colouring depends on it */
    raw_work = *(volatile u8 *)((u8 *)arg0 + 0x6D);
    raw_work <<= 24;
    work = (s32)raw_work >> 24;
    if (func_800A9E70(arg0, arg1, arg2, arg0) != 0) {
        return;
    }

    {
        Callback callback2;
        callback2 = (*(Callback *)((u8 *)arg0 + 0x8C));
        if (callback2 != 0) {
            callback2(arg0, arg1, arg2, arg0);
        }
    }
    D_80174900[(*(u8 *)((u8 *)arg0 + 0x9A))](arg0, arg1, arg2, arg0);
    raw_work = (u32)work << 16;
    if (((s32)raw_work >> 16) != (*(s8 *)((u8 *)arg0 + 0x6D))) {
        func_800AA36C(arg0, arg1, arg2, arg0);
    }

    {
        s32 old_x = ((S_80170A78_0 *)arg1)->unk_00.at00.v;
        s32 temp_a0 = ((S_80170A78_0 *)arg1)->unk_0C;
        s32 old_y = ((S_80170A78_0 *)arg1)->unk_04.at00.v;
        s32 temp_a1 = ((S_80170A78_0 *)arg1)->unk_10;
        ((S_80170A78_0 *)arg1)->unk_00.at00.v = old_x + temp_a0;
        ((S_80170A78_0 *)arg1)->unk_04.at00.v = old_y + temp_a1;

        if (!((*(s32 *)((u8 *)arg0 + 0x1C)) & 0x40000) &&
            !((*(u16 *)((u8 *)arg0 + 0x98)) & 8)) {
            ((S_80170A78_0 *)arg1)->unk_14 += (*(s8 *)((u8 *)arg0 + 0x9D)) * 0x14000;
            (*(u8 *)((u8 *)arg0 + 0x9D)) += 1;
            return func_80170C0C();
        } else {
            (*(u8 *)((u8 *)arg0 + 0x9D)) = 0;
            ASM_KEEP(obj);   /* MATCH pin: retail register colouring depends on it */
        }
    }

    (*(s32 *)((u8 *)arg0 + 0x90)) += ((S_80170A78_0 *)arg1)->unk_14;
    part_flags = ((S_80170A78_1 *)arg2)->unk_14;
    if (!(part_flags & 0x8000)) {
        raw_work = *(s16 *)((u8 *)D_80083460 - 0x238) +
            ((S_80170A78_2 *)state)->unk_2A + 0x100;
        direction = ((s32)raw_work >> 9) & 7;
        work = direction;
        if ((*(s16 *)((u8 *)arg0 + 0x94)) != work) {
            func_80047738(arg2,
                *(u8 *)(((S_80170A78_1 *)arg2)->unk_2C.p + work),
                ((S_80170A78_1 *)arg2)->unk_04);
            (*(s16 *)((u8 *)arg0 + 0x94)) = direction;
        }
        collision = D_8006CCF8[work];
        ASM_KEEP(work);   /* MATCH pin: load-bearing for the whole function shape */
        if (collision != 0) {
            raw_work = *(volatile u16 *)((u8 *)arg2 + 0x14) | 1;
            ASM_TAILSLOT_PIN(raw_work);   /* MATCH pin: retail delay-slot contents depend on it */
            return func_80170CB4();
        } else {
            ((S_80170A78_1 *)arg2)->unk_14 &= 0xFFFE;
        }

        func_800A020C(((S_80170A78_2 *)state)->unk_1C, (u8 *)arg2 + 0xC);
        if (!(((S_80170A78_2 *)state)->unk_1C & 0x20)) {
            if (!(((S_80170A78_1 *)arg2)->unk_14 & 0x40)) {
                func_800478B8(arg2);
                raw_work = 0xF7FF0000;
                ASM_PAGEBASE_PIN(raw_work);   /* MATCH pin: retail delay-slot contents depend on it */
                return func_80170D20();
            }
        } else {
            ((S_80170A78_1 *)arg2)->unk_14 |= 0x7000;
            ((S_80170A78_2 *)state)->unk_1C &= 0xFFFBFFFF;
        }
        raw_work = 0xF7FFFFFF;
        flags = ((S_80170A78_2 *)state)->unk_1C & raw_work;
        ((S_80170A78_2 *)state)->unk_1C = flags;
        if (!(flags & 0x40000)) {
            goto reset_height;
        }

        if (!(((S_80170A78_1 *)arg2)->unk_14 & 0x40) &&
            ((S_80170A78_1 *)arg2)->unk_2C.p2 == D_80174880) {
            count = (*(u16 *)((u8 *)arg0 + 0xB2));
            (*(u16 *)((u8 *)arg0 + 0xB2)) = count + 1;
            (*(s32 *)((u8 *)arg0 + 0xA4)) += func_800644B8((s16)count * 0xAA) << 5;
        }
        if (!((*(u16 *)((u8 *)arg0 + 0x98)) & 8)) {
            delta = func_800BCB04(((S_80170A78_0 *)arg1)->unk_00.at02.v, ((S_80170A78_0 *)arg1)->unk_04.at02.v,
                        (s16)(((S_80170A78_2 *)state)->unk_88 - 0x20)) -
                    ((S_80170A78_2 *)state)->unk_88;
            floor_y = (*(s16 *)((u8 *)arg0 + 0x92));
            if (floor_y > delta - 0x18) {
                (*(s16 *)((u8 *)arg0 + 0x92)) = (*(s16 *)((u8 *)arg0 + 0x92)) - 8;
                return func_80170F8C(floor_y, delta);
            }
            if (floor_y < delta - 0x20) {
                (*(s16 *)((u8 *)arg0 + 0x92)) = (*(u16 *)((u8 *)arg0 + 0x92)) + 8;
            }
        }
        goto finish_height;
    }

    if (part_flags & 0x800) {
        ((S_80170A78_1 *)arg2)->unk_14 = part_flags & 0x8FFF;
    } else {
        ((S_80170A78_1 *)arg2)->unk_14 = part_flags | 0x7000;
    }
    raw_work = 0xF7FFFFFF;
    flags = ((S_80170A78_2 *)state)->unk_1C & raw_work;
    ((S_80170A78_2 *)state)->unk_1C = flags;
    if (!(flags & 0x40000)) {
reset_height:
        amount = (*(s32 *)((u8 *)arg0 + 0xA4));
        (*(u16 *)((u8 *)arg0 + 0xB2)) = 0;
        (*(s32 *)((u8 *)arg0 + 0xA4)) = 0;
        (*(s32 *)((u8 *)arg0 + 0x90)) -= amount;
        if (!((*(u16 *)((u8 *)arg0 + 0x98)) & 8)) {
            delta = func_800BCB04(((S_80170A78_0 *)arg1)->unk_00.at02.v, ((S_80170A78_0 *)arg1)->unk_04.at02.v,
                        (s16)(((S_80170A78_2 *)state)->unk_88 - 0x20)) -
                    ((S_80170A78_2 *)state)->unk_88;
            if (delta < (*(s16 *)((u8 *)arg0 + 0x92))) {
                (*(s16 *)((u8 *)arg0 + 0x92)) = delta;
                (*(u8 *)((u8 *)arg0 + 0x9D)) = 0;
                ((S_80170A78_0 *)arg1)->unk_14 = 0;
                ((S_80170A78_2 *)state)->unk_1C |= 0x08000000;
                return func_80170F8C();
            }
        }
        goto finish_height;
    }

    if (!(((S_80170A78_1 *)arg2)->unk_14 & 0x40) &&
        ((S_80170A78_1 *)arg2)->unk_2C.p2 == D_80174880) {
        count = (*(u16 *)((u8 *)arg0 + 0xB2));
        (*(u16 *)((u8 *)arg0 + 0xB2)) = count + 1;
        (*(s32 *)((u8 *)arg0 + 0xA4)) += func_800644B8((s16)count * 0xAA) << 5;
    }
    if (!((*(u16 *)((u8 *)arg0 + 0x98)) & 8)) {
        delta = func_800BCB04(((S_80170A78_0 *)arg1)->unk_00.at02.v, ((S_80170A78_0 *)arg1)->unk_04.at02.v,
                    (s16)(((S_80170A78_2 *)state)->unk_88 - 0x20)) -
                ((S_80170A78_2 *)state)->unk_88;
        floor_y = (*(s16 *)((u8 *)arg0 + 0x92));
        if (floor_y > delta - 0x18) {
            (*(s16 *)((u8 *)arg0 + 0x92)) = (*(s16 *)((u8 *)arg0 + 0x92)) - 8;
            goto finish_height;
        }
        if (floor_y < delta - 0x20) {
            (*(s16 *)((u8 *)arg0 + 0x92)) = (*(u16 *)((u8 *)arg0 + 0x92)) + 8;
        }
    }

finish_height:
    if (((S_80170A78_2 *)state)->unk_1C & 0x40000000) {
        ((S_80170A78_2 *)state)->unk_1C &= 0xBFFFFFFF;
        delta = func_800BCB04((((S_80170A78_1 *)arg2)->unk_24 << 6) | 0x20,
            (((S_80170A78_1 *)arg2)->unk_25 << 6) | 0x20,
            (s16)(((S_80170A78_2 *)state)->unk_88 - 0x20));
        if ((s16)delta < 0x200) {
            (*(s16 *)((u8 *)arg0 + 0x92)) += ((S_80170A78_2 *)state)->unk_88 - delta;
            ((S_80170A78_2 *)state)->unk_88 = delta;
        }
    }
    ((S_80170A78_0 *)arg1)->unk_0A = ((S_80170A78_2 *)state)->unk_88 +
        (*(u16 *)((u8 *)arg0 + 0x92)) - (*(u16 *)((u8 *)arg0 + 0xA6));
    ((S_80170A78_1 *)arg2)->unk_14 |= 0x40;
}
