#include "common.h"

typedef union Fixed32 {
    s32 val;
    struct {
        u16 lo;
        s16 hi;
    } h;
} Fixed32;

typedef struct Motion {
    Fixed32 x;
    Fixed32 y;
    Fixed32 z;
    Fixed32 dx;
    Fixed32 dy;
    Fixed32 dz;
} Motion;

typedef struct Owner {
    u8 pad0[0x2A];
    u16 flags;
    u8 pad2C[0x34];
    void *target;
    u8 pad64[0x24];
    s16 z;
} Owner;

typedef struct State {
    Owner *owner;
    void *field4;
    u8 pad8;
    u8 byte9;
    s16 state;
    s16 fieldC;
    s16 fieldE;
    s16 angle;
    s16 timer;
    s16 duration;
} State;

typedef struct Lookup {
    u8 pad0[8];
    void *field8;
    u8 padC[8];
    u16 flags;
    u8 pad16[14];
    u8 x;
    u8 y;
} Lookup;

typedef struct OwnerPrefix {
    u8 pad0[8];
    Motion *position;
    Lookup *lookup;
} OwnerPrefix;

typedef struct LargeInt {
    s32 value;
    s32 pad[2];
} LargeInt;

typedef struct StackLocals {
    Motion local;
    s16 diffs[3];
    u16 pad;
    u16 accum_y;
} StackLocals;

extern s16 D_8006CCD8[8];
extern s16 D_8006CCE8[8];
extern s32 D_8008346C[3];
extern LargeInt D_800814A0;
extern void *D_80024008[];

extern s32 func_8003DE58(void *, Lookup *, s16 *, s32);
extern void func_80024F0C(State *, Motion *);
extern s32 func_800A44E0(s32, s32, s16, s32);
extern s32 func_800BCB04(s32, s32, s16);
extern void func_8002523C(State *, Motion *);
extern void func_800A56E0(s32);
extern void func_80024640(State *, Motion *);
extern void func_80024024(void *, u8, Owner *);

extern void func_800254EC(void) __attribute__((noreturn));
extern void func_80025A50(void) __attribute__((noreturn));
extern void func_800259BC(void) __attribute__((noreturn));
extern void func_80025A58(void) __attribute__((noreturn));

#ifdef NON_MATCHING
#define LOAD_TABLE_X_BASE(v) ((v) = (s32)D_8006CCD8)
#define LOAD_TABLE_Y_BASE(v) ((v) = (s32)D_8006CCE8)
#else
#define LOAD_TABLE_X_BASE(v) \
    do { (v) = 0x80070000; ASM_KEEP(v); (v) -= 0x3328; } while (0)
#define LOAD_TABLE_Y_BASE(v) \
    do { (v) = 0x80070000; ASM_KEEP(v); (v) -= 0x3318; } while (0)
#endif

#define local stack.local
#define diffs stack.diffs
#define accum_y stack.accum_y

void func_818C3B90(State *arg0, Motion *raw1, Motion *raw2)
{
    static void *const jt_keep[] = {
        &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6
    };
    register Motion *arg1 ASM_REG("$20") = raw1;   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    Motion *arg2 = raw2;
    register OwnerPrefix *prefix ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    Owner *owner;
    s32 state;
    s32 i;
    StackLocals stack;
    state = arg0->state;
    owner = arg0->owner;
    arg0->timer++;
    if ((u32)state >= 7) {
        goto done;
    }
    (void)jt_keep;
    goto *D_80024008[(u32)state];

jt_c0:
    {
        Motion *position;
        u16 position_z;

        arg0->timer = 0;
        arg0->state++;
        arg0->angle = (owner->flags >> 9) & 7;
        arg2->dx.val = 0x00808080;

jt_c1:
        prefix = (OwnerPrefix *)((u8 *)owner - 0x20);
        if (func_8003DE58(prefix->lookup->field8, prefix->lookup, diffs, 0) == 0 &&
            !(prefix->lookup->flags & 0x8000)) {
            goto done;
        }

        position = prefix->position;
        arg1->x.h.hi = position->x.h.hi;
        arg1->y.h.hi = position->y.h.hi;
        position_z = position->z.h.hi;
        arg1->z.h.hi = position_z;

        if (!(prefix->lookup->flags & 0x8000)) {
            s32 tail;
            arg1->x.h.hi += diffs[0];
            arg1->y.h.hi += diffs[1];
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            tail = (u16)arg1->z.h.hi;
            tail += (u16)diffs[2];
            ASM_TAILSLOT_PIN_TIED(tail);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_800254EC();
        }
        ASM_KEEP(position_z);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        arg1->z.h.hi = position_z - 64;
    }

    if (*(u16 *)arg0->field4 & 0x80) {
        i = 1;
        if (owner->target != 0) {
            register Motion *target ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            register s32 xdiff ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 other_diff;
            s32 rhs;
            register u8 *iter ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            target = *(Motion **)((u8 *)owner->target - 24);
            other_diff = arg1->x.h.hi;
            xdiff = target->x.h.hi - other_diff;
            if (xdiff < 0) {
                xdiff = -xdiff;
            }
            diffs[0] = xdiff;
            other_diff = target->y.h.hi;
            rhs = arg1->y.h.hi;
            other_diff -= rhs;
            if (other_diff < 0) {
                other_diff = -other_diff;
            }
            diffs[1] = other_diff;
            iter = (u8 *)&local + 2;
            rhs = arg1->z.h.hi;
            other_diff = *(s16 *)((u8 *)owner->target + 0x88) - rhs;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            if (other_diff < 0) {
                other_diff = -other_diff;
            }
            diffs[2] = other_diff;

            arg0->duration = xdiff;
            do {
                s32 test = *(s16 *)(iter + 24);
                u32 value = *(u16 *)(iter + 24);
                if (test > arg0->duration) {
                    arg0->duration = value;
                }
                i++;
                iter += 2;
            } while (i < 3);
            arg0->duration = arg0->duration >> 4;
            if (arg0->duration == 0) {
                arg0->duration = 1;
            }

            arg1->dx.val = (target->x.val - arg1->x.val) / arg0->duration;
            arg1->dy.val = (target->y.val - arg1->y.val) / arg0->duration;
            arg1->dz.val =
                ((*(s16 *)((u8 *)owner->target + 0x88) << 16) - arg1->z.val) /
                arg0->duration;
            func_80024F0C(arg0, arg1);
            {
                s32 tail;
                tail = (u16)arg0->state + 1;
                ASM_TAILSLOT_PIN_TIED(tail);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                func_80025A50();
            }
        } else {
            register s32 x ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            s32 y;
            s32 saved_x;
            Motion *local_ptr;
            register s32 next_x ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 next_y;
            register s32 work_x ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register s16 *table ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            register u8 *iter ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            register s32 temp_t0 ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            s16 *table_x_entry;
            s16 *table_y_entry;
            u16 *update_x_entry;
            u16 *update_y_entry;
            register s32 loop_owner_z ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            s32 table_offset;
            register s32 update_offset ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            s16 probe_result;

            i = 0;
            table = (s16 *)prefix->lookup;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            next_y = 0x80070000;
            ASM_KEEP(next_y);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            x = ((Lookup *)table)->x;
            y = ((Lookup *)table)->y;
            saved_x = x;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            accum_y = y;

            for (; i < 8;) {
                s16 sx;
                s16 sy;
                s32 probe;

                sx = x;
                sy = y;
                probe = func_800A44E0(
                    (sx << 6) & 0xFFC0,
                    (sy << 6) & 0xFFC0,
                    owner->z,
                    (s32)((u32)(u16)arg0->angle << 25) >> 16);
                if ((s16)probe != 0) {
                    break;
                }

                LOAD_TABLE_X_BASE(temp_t0);
                ASM_KEEP(temp_t0);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                table_offset = (s16)arg0->angle;
                loop_owner_z = (u16)owner->z;
                table_offset *= 2;
                table_x_entry = (s16 *)(table_offset + temp_t0);
                ASM_KEEP(table_x_entry);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                loop_owner_z -= 32;
                loop_owner_z = (s16)loop_owner_z;
                LOAD_TABLE_Y_BASE(temp_t0);
                table_y_entry = (s16 *)(table_offset + temp_t0);
                ASM_KEEP(table_y_entry);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                probe_result = func_800BCB04(
                    ((sx + *table_x_entry) * 64 + 32) & 0xFFE0,
                    ((sy + *table_y_entry) * 64 + 32) & 0xFFE0,
                    loop_owner_z);
                if (probe_result >= 513 ||
                    (s16)(probe_result - (u16)owner->z) < -63) {
                    break;
                }

                LOAD_TABLE_X_BASE(temp_t0);
                update_offset = (s16)arg0->angle;
                i++;
                update_offset *= 2;
                update_x_entry = (u16 *)(update_offset + temp_t0);
                LOAD_TABLE_Y_BASE(temp_t0);
                update_y_entry = (u16 *)(update_offset + temp_t0);
                ASM_KEEP(update_y_entry);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                next_x = x + *update_x_entry;
                x = next_x;
                next_y = y + *update_y_entry;
                y = next_y;
                accum_y = next_y;
                ASM_KEEP4_NV(next_x, next_y, x, y);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                saved_x = next_x;
            }

            local_ptr = &local;
            ASM_KEEP_NV(local_ptr);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            i = 1;
            ASM_KEEP_NV(i);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            work_x = (u32)saved_x << 16;
            table = D_8006CCD8;
            work_x = (s32)work_x >> 10;
            iter = (u8 *)&local + 2;
            work_x += (table[arg0->angle] + 1) << 5;
            local_ptr->x.h.hi = work_x;
            work_x = (s16)work_x;
            next_x = (s32)((u32)(u16)(temp_t0 = accum_y) << 16) >> 10;
            table = D_8006CCE8;
            next_x += (table[arg0->angle] + 1) << 5;
            local_ptr->y.h.hi = next_x;
            next_x = (u32)next_x << 16;
            next_y = (u16)arg1->z.h.hi + 32;
            local_ptr->z.h.hi = next_y;

            {
                s32 rhs;

                rhs = arg1->x.h.hi;
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                next_x = (s32)next_x >> 16;
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                work_x -= rhs;
                if (work_x < 0) {
                    work_x = -work_x;
                }
                diffs[0] = work_x;

                rhs = arg1->y.h.hi;
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                next_y = (u32)next_y << 16;
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                next_x -= rhs;
                if (next_x < 0) {
                    next_x = -next_x;
                }
                diffs[1] = next_x;

                rhs = arg1->z.h.hi;
                next_y = (s32)next_y >> 16;
                next_y -= rhs;
                if (next_y < 0) {
                    next_y = -next_y;
                }
                diffs[2] = next_y;
            }

            arg0->duration = work_x;
            do {
                s32 test = *(s16 *)(iter + 24);
                u32 value = *(u16 *)(iter + 24);
                if (test > arg0->duration) {
                    arg0->duration = value;
                }
                i++;
                iter += 2;
            } while (i < 3);
            arg0->duration = arg0->duration >> 4;
            if (arg0->duration == 0) {
                arg0->duration = 1;
            }

            arg1->dx.val = (local_ptr->x.val - arg1->x.val) / arg0->duration;
            arg1->dy.val = (local_ptr->y.val - arg1->y.val) / arg0->duration;
            arg1->dz.val = (local_ptr->z.val - arg1->z.val) / arg0->duration;
            func_8002523C(arg0, arg1);
            {
                s32 tail;
                tail = 6;
                ASM_TAILSLOT_PIN_TIED(tail);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                func_80025A50();
            }
        }
    }
    goto done;

jt_c2:
    arg1->x.val += arg1->dx.val;
    arg1->y.val += arg1->dy.val;
    arg1->z.val += arg1->dz.val;
    if (arg0->timer >= arg0->duration) {
        func_800A56E0(0x300);
        func_800259BC();
    }
    goto done;

jt_c3:
    if (arg0->timer >= 12) {
        func_80024640(arg0, arg1);
        func_800259BC();
    }
    goto done;

jt_c4:
    if (arg0->timer >= 49) {
        func_80024024(owner->target, arg0->byte9, owner);
        arg0->timer = 0;
        arg0->state++;
        func_80025A58();
    }
    goto done;

jt_c5:
    if (arg0->fieldC == 0) {
        D_8008346C[0] = 0;
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0.value |= 0x8000;
        func_80025A58();
    }
    goto done;

jt_c6:
    arg1->x.val += arg1->dx.val;
    arg1->y.val += arg1->dy.val;
    arg1->z.val += arg1->dz.val;
    if (arg0->timer >= arg0->duration) {
        arg0->state = 5;
        arg0->timer = 0;
    }
done:
    arg0->fieldC = 0;
}

#undef local
#undef diffs
#undef accum_y
#undef LOAD_TABLE_X_BASE
#undef LOAD_TABLE_Y_BASE
