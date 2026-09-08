#include "common.h"


typedef void (*Callback)(void *, void *, void *, void *);

extern void func_80047738(void *, u8, s8);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern void func_800A020C(s32, void *);
extern s32 func_800A9E70(void *, void *, void *, void *);
extern void func_800AA36C(void *, void *, void *, void *);
extern s32 func_800BCB04(u16, u16, s16);
extern void func_80170C0C(void) __attribute__((noreturn));
extern void func_80170D30(void) __attribute__((noreturn));
extern void func_80171064(void) __attribute__((noreturn));
extern void func_80171068(void) __attribute__((noreturn));

extern u8 D_8006CCF8[];
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80171138[];
extern Callback D_80174B1C[];


typedef struct S_80170A70_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80170A70_0;   /* arg1 in func_80170A70 */

typedef struct S_80170A70_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80170A70_1;   /* arg2 in func_80170A70 */

typedef struct S_80170A70_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_80170A70_2;   /* object in func_80170A70 */

void func_80170A70(void *arg0, void *raw_arg1, void *raw_arg2)
{
    static void *const phase_entries[] = {
        &&phase_update_a,
        &&phase_update_b,
    };
    S_80170A70_2 *object = arg0;
    register void *arg1 ASM_REG("$21");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *arg2 ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    Callback callback;
    Callback callback2;
    s16 old_state;
    s16 direction;
    s16 ground;
    register s32 ground32 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s16 angle;
    s32 bob;
    u16 flags;
    u16 new_flags;

    arg1 = raw_arg1;
    arg2 = raw_arg2;
    bob = 0;
    if (D_80083462 & 0x2000) {
        callback = (*(Callback *)((u8 *)arg0 + (0x8C)));
        if (callback == (Callback)D_80171138) {
            callback(arg0, raw_arg1, raw_arg2, arg0);
            return;
        }
        (*(u8 *)((u8 *)arg0 + (0x71))) &= 0x7F;
        return;
    }

    ASM_KEEP_NV(arg1);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ASM_KEEP_NV(arg2);   /* MATCH pin: keeps a statement from moving across a call/branch */
    old_state = (s8)(*(u8 *)((u8 *)arg0 + (0x6D)));
    if (func_800A9E70(arg0, arg1, arg2, arg0) != 0) {
        return;
    }

    callback2 = (*(Callback *)((u8 *)arg0 + (0x8C)));
    if (callback2 != 0) {
        callback2(arg0, arg1, arg2, arg0);
    }
    D_80174B1C[(*(u8 *)((u8 *)arg0 + (0x9A)))](arg0, arg1, arg2, arg0);
    if ((s16)old_state != (*(s8 *)((u8 *)arg0 + (0x6D)))) {
        func_800AA36C(arg0, arg1, arg2, arg0);
    }

    ((S_80170A70_0 *)arg1)->unk_00.at00.v += ((S_80170A70_0 *)arg1)->unk_0C;
    ((S_80170A70_0 *)arg1)->unk_04.at00.v += ((S_80170A70_0 *)arg1)->unk_10;

    if (!((*(s32 *)((u8 *)arg0 + (0x1C))) & 0x40000) &&
        !((*(u16 *)((u8 *)arg0 + (0x98))) & 8)) {
        ((S_80170A70_0 *)arg1)->unk_14 += (*(s8 *)((u8 *)arg0 + (0x9D))) * 0x14000;
        (*(u8 *)((u8 *)arg0 + (0x9D)))++;
        func_80170C0C();
    }

    do { (*(u8 *)((u8 *)arg0 + (0x9D))) = 0; } while (0);
    (*(s32 *)((u8 *)arg0 + (0x90))) += ((S_80170A70_0 *)arg1)->unk_14;
    flags = ((S_80170A70_1 *)arg2)->unk_14;

    if (!(flags & 0x8000)) {
        angle = ((D_80083228 + object->unk_2A + 0x100) >> 9) & 7;
        old_state = angle;
        if ((*(s16 *)((u8 *)arg0 + (0x94))) != old_state) {
            func_80047738(arg2,
                ((u8 *)((S_80170A70_1 *)arg2)->unk_2C)[old_state],
                ((S_80170A70_1 *)arg2)->unk_04);
            (*(s16 *)((u8 *)arg0 + (0x94))) = angle;
        }

        {
            u16 bit_flags;

            if (D_8006CCF8[old_state] != 0) {
                bit_flags = ((S_80170A70_1 *)arg2)->unk_14 | 1;
            } else {
                bit_flags = ((S_80170A70_1 *)arg2)->unk_14 & 0xFFFE;
            }
            ((S_80170A70_1 *)arg2)->unk_14 = bit_flags;
        }

        if ((*(u8 *)((u8 *)arg0 + (0x9A))) != 8) {
            func_800A020C(object->unk_1C, (u8 *)arg2 + 0xC);
        }

        if (!(object->unk_1C & 0x20)) {
            if (!(((S_80170A70_1 *)arg2)->unk_14 & 0x40)) {
                func_800478B8(arg2);
                {
                    u32 tail_v0 = 0xF7FF0000;
                    ASM_TAILSLOT_PIN(tail_v0);   /* MATCH pin: retail delay-slot contents depend on it */
                    func_80170D30();
                }
            }
            goto clear_motion_flag;
        }

        ((S_80170A70_1 *)arg2)->unk_14 |= 0x7000;
        object->unk_1C &= 0xFFFBFFFF;

clear_motion_flag:
        object->unk_1C &= 0xF7FFFFFF;
        if (object->unk_1C & 0x40000) {
            if (!(((S_80170A70_1 *)arg2)->unk_14 & 0x40)) {
                {
                    s32 value = func_800644B8(
                        ((*(s16 *)((u8 *)arg0 + (0xA0))) << 12) / 40);
                    bob = value >> 9;
                    if ((*(u8 *)((u8 *)arg0 + (0x9A))) == 0x12) {
                        bob = value >> 10;
                    }
                }
phase_update_a:
                (*(s16 *)((u8 *)arg0 + (0xA0))) = ((*(s16 *)((u8 *)arg0 + (0xA0))) + 1) % 40;
            }

            if (!((*(u16 *)((u8 *)arg0 + (0x98))) & 8)) {
                ground = (s16)(func_800BCB04(
                    ((S_80170A70_0 *)arg1)->unk_00.at02.v, ((S_80170A70_0 *)arg1)->unk_04.at02.v,
                    (s16)(object->unk_88.u - 0x20)) -
                    object->unk_88.u);
                if ((*(s16 *)((u8 *)arg0 + (0x92))) > ground - 0x30) {
                    (*(s16 *)((u8 *)arg0 + (0x92))) =
                        (u16)(*(s16 *)((u8 *)arg0 + (0x92))) - 8;
                    func_80171068();
                }
                ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
                if (ground - 0x3A > (*(s16 *)((u8 *)arg0 + (0x92)))) {
                    (*(s16 *)((u8 *)arg0 + (0x92))) =
                        (u16)(*(s16 *)((u8 *)arg0 + (0x92))) + 8;
                    func_80171068();
                }
            }
            goto reset_bob;
        }

        (*(s16 *)((u8 *)arg0 + (0xA0))) = 0;
        if (!((*(u16 *)((u8 *)arg0 + (0x98))) & 8)) {
            register s32 object_height ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */

            ground32 = (s16)func_800BCB04(
                ((S_80170A70_0 *)arg1)->unk_00.at02.v, ((S_80170A70_0 *)arg1)->unk_04.at02.v,
                (s16)(object->unk_88.u - 0x20));
            object_height = object->unk_88.s;
            ground32 -= object_height;
            if ((*(s16 *)((u8 *)arg0 + (0x92))) > ground32) {
                (*(s16 *)((u8 *)arg0 + (0x92))) = ground32;
                (*(u8 *)((u8 *)arg0 + (0x9D))) = 0;
                ((S_80170A70_0 *)arg1)->unk_14 = 0;
                object->unk_1C |= 0x08000000;
                func_80171068();
            }
        }
        goto reset_bob;
    }

    {
        if (flags & 0x800) {
            new_flags = flags & 0x8FFF;
        } else {
            new_flags = flags | 0x7000;
        }
        ((S_80170A70_1 *)arg2)->unk_14 = new_flags;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
    }
    object->unk_1C &= 0xF7FFFFFF;

    if (!(object->unk_1C & 0x40000)) {
        (*(s16 *)((u8 *)arg0 + (0xA0))) = 0;
        (*(s16 *)((u8 *)arg0 + (0x92))) = (u16)(*(s16 *)((u8 *)arg0 + (0x92))) - bob;
        bob = 0;
        if (!((*(u16 *)((u8 *)arg0 + (0x98))) & 8)) {
            register s32 object_height ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */

            ground32 = (s16)func_800BCB04(
                ((S_80170A70_0 *)arg1)->unk_00.at02.v, ((S_80170A70_0 *)arg1)->unk_04.at02.v,
                (s16)(object->unk_88.u - 0x20));
            object_height = object->unk_88.s;
            ground32 -= object_height;
            if ((*(s16 *)((u8 *)arg0 + (0x92))) > ground32) {
                (*(s16 *)((u8 *)arg0 + (0x92))) = ground32;
                (*(u8 *)((u8 *)arg0 + (0x9D))) = 0;
                ((S_80170A70_0 *)arg1)->unk_14 = 0;
                object->unk_1C |= 0x08000000;
                func_80171064();
            }
        }
        goto finish_height;
    }

    if (!(((S_80170A70_1 *)arg2)->unk_14 & 0x40)) {
        {
            s32 value = func_800644B8(
                ((*(s16 *)((u8 *)arg0 + (0xA0))) << 12) / 40);
            bob = value >> 9;
            if ((*(u8 *)((u8 *)arg0 + (0x9A))) == 0x12) {
                bob = value >> 10;
            }
        }
phase_update_b:
        (*(s16 *)((u8 *)arg0 + (0xA0))) = ((*(s16 *)((u8 *)arg0 + (0xA0))) + 1) % 40;
    }

    if (!((*(u16 *)((u8 *)arg0 + (0x98))) & 8)) {
        ground = (s16)(func_800BCB04(
            ((S_80170A70_0 *)arg1)->unk_00.at02.v, ((S_80170A70_0 *)arg1)->unk_04.at02.v,
            (s16)(object->unk_88.u - 0x20)) -
            object->unk_88.u);
        if ((*(s16 *)((u8 *)arg0 + (0x92))) > ground - 0x30) {
            (*(s16 *)((u8 *)arg0 + (0x92))) =
                (u16)(*(s16 *)((u8 *)arg0 + (0x92))) - 8;
        } else if (ground - 0x3A > (*(s16 *)((u8 *)arg0 + (0x92)))) {
            (*(s16 *)((u8 *)arg0 + (0x92))) =
                (u16)(*(s16 *)((u8 *)arg0 + (0x92))) + 8;
        } else {
            goto finish_height;
        }
    }

finish_height:
    (*(s16 *)((u8 *)arg0 + (0xA0))) = 0;

reset_bob:
    if (object->unk_1C & 0x40000000) {
        object->unk_1C &= 0xBFFFFFFF;
        ground = func_800BCB04(
            (((S_80170A70_1 *)arg2)->unk_24 << 6) | 0x20,
            (((S_80170A70_1 *)arg2)->unk_25 << 6) | 0x20,
            (s16)(object->unk_88.u - 0x20));
        if (ground < 0x200) {
            (*(s16 *)((u8 *)arg0 + (0x92))) =
                (u16)(*(s16 *)((u8 *)arg0 + (0x92))) +
                (object->unk_88.u - ground);
            object->unk_88.u = ground;
        }
    }

    ((S_80170A70_0 *)arg1)->unk_0A =
        object->unk_88.u + (u16)(*(s16 *)((u8 *)arg0 + (0x92))) + bob;
    ((S_80170A70_1 *)arg2)->unk_14 |= 0x40;
}
