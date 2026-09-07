#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#define GLUE_F64(a, b) (0.0)
#define MULT_HI(a, b) (0)
#define MULTU_HI(a, b) (0)
#define DMULT_HI(a, b) (0)
#define DMULTU_HI(a, b) (0)
#define CLZ(x) (0)
#define REVERSE_BITS(x) (0)
#define ROTATE_RIGHT(x, shift) (0)
#define ARM_RRX(x, carry) (0)
#define BSWAP32(x) (0)
#define BSWAP16(x) (0)
#define BSWAP16X2(x) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

s32 func_80042900(void *, s32);
void func_80042B68(void *, s32);
void func_80047784(void *, s32, s32);
s32 func_8009A180(void *, void *);
s16 func_8009FD40(void *, void *);
s32 func_800A2C34(void *);
s32 func_800A6D30(void);
void func_800A9A04(void *);
void func_800A9A0C(void *);
void func_800AA258(void *, s32, void *, void *);
s32 func_800AA6B4(void *, s32, void *, s32);
void func_800AA79C(void *, s32, void *, void *);
void func_800AA888(void *, s32, void *, void *);
void func_8016D4B8(void *, s32, void *, void *);
extern void *D_800814A8;
extern M2C_UNK D_80082E80;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern M2C_UNK D_8016A36C;
extern u8 D_80173AC8[];
extern u8 D_80173AD0[];

void func_8016CC70(void *arg0, s32 arg1, void *arg2, void *arg3) {
    register void *obj ASM_REG("$18") = arg0;
    register s32 middle ASM_REG("$20") = arg1;
    register void *target ASM_REG("$16") = arg2;
    register void *actor ASM_REG("$17") = arg3;
    register u8 *held_base ASM_REG("$19");
    void *callback;
    void *room_base;
    register u8 *counter_base ASM_REG("$2");
    s32 state;
    s32 kind;
    s32 bits;
    s8 room;

    state = M2C_FIELD(obj, u8 *, 0x9B);
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    if (!(M2C_FIELD(target, u16 *, 0x14) & 0xE000)) {
        goto done;
    }
    kind = M2C_FIELD(obj, u8 *, 0xAC);
    if (kind == 0xE) {
        goto zero_setup;
    }
    if (kind < 0xF) {
        if (kind == 0xD) {
            goto zero_setup;
        }
        goto decrement_counter;
    }
    if (kind != 0xF) {
        goto decrement_counter;
    }
zero_setup:
    M2C_FIELD(target, u8 **, 0x2C) = D_80173AC8;
    func_80047784(target, D_80173AC8[((D_80083228 + M2C_FIELD(actor, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
decrement_counter:
    counter_base = (u8 *)&D_80083460;
    ASM_KEEP(counter_base);
    M2C_FIELD(counter_base, u16 *, 0xA)--;
    goto counter_changed;

state_one:
    kind = M2C_FIELD(obj, u8 *, 0xAC);
    if (kind == 0xE) {
        goto one_setup;
    }
    if (kind < 0xF) {
        if (kind == 0xD) {
            goto one_setup;
        }
        goto call_check;
    }
    if (kind != 0xF) {
        goto call_check;
    }
one_setup:
    if (M2C_FIELD(target, u8 **, 0x2C) != D_80173AC8) {
        M2C_FIELD(target, u8 **, 0x2C) = D_80173AC8;
        func_80047784(target, D_80173AC8[((D_80083228 + M2C_FIELD(actor, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    }
call_check:
    if ((func_80042900(actor, 1) << 0x10) != 0) {
        goto action_body;
    }
    kind = M2C_FIELD(obj, u8 *, 0xAC);
    if (kind == 0xE) {
        goto update_tiles;
    }
    if (kind < 0xF) {
        goto low_kind;
    }
    goto high_kind;

action_body:
    counter_base = (u8 *)0x80080000;
    ASM_KEEP(counter_base);
    held_base = counter_base + 0x3460;
    ASM_KEEP(held_base);
    if (M2C_FIELD(held_base, u16 *, 2) & 0x1000) {
        goto done;
    }
    if (M2C_FIELD(actor, s16 *, 0x64) != 0) {
        if (func_800AA6B4(obj, middle, target, 0) != 0) {
            goto done;
        }
    }
    if (M2C_FIELD(actor, u8 *, 0x25) == 0) {
        if (M2C_FIELD(held_base, u16 *, 2) & 0x2008) {
            goto done;
        }
        func_800AA79C(obj, middle, target, actor);
        goto done;
    }
    if ((func_800A2C34(actor) << 0x10) != 0) {
        goto done;
    }
    bits = M2C_FIELD(actor, s32 *, 0x1C);
    if (bits & 0x100) {
        func_800AA258(obj, middle, target, actor);
        goto done;
    }
    if (bits & 0x80000) {
        func_800AA888(obj, middle, target, actor);
        func_8016D4B8(obj, middle, target, actor);
        goto done;
    }
    if (M2C_FIELD(actor, s8 *, 0x6D) == 0) {
        goto done;
    }
    if ((func_800A2C34(actor) << 0x10) != 0) {
        if ((func_8009A180(actor, (u8 *)M2C_FIELD(D_800814A8, void **, 0x58) + 0x20) << 0x10) != 0) {
            goto done;
        }
    }
    func_800A9A0C(actor);
    func_800A9A04(actor);
    if ((func_80042900(actor, 1) << 0x10) != 0) {
        room_base = &D_80082E80;
        room = M2C_FIELD(target, s8 *, 0x26);
        if ((room != M2C_FIELD(room_base, s8 *, 0x26)) || (room < 0)) {
            if (func_8009FD40(room_base, target) >= 2) {
                goto second_check;
            }
        }
        if ((func_800A6D30() & 7) == 0) {
            func_80042B68(actor, 1);
        }
    }
second_check:
    if ((func_80042900(actor, 1) << 0x10) != 0) {
        goto done;
    }

post_actions:
    kind = M2C_FIELD(obj, u8 *, 0xAC);
    if (kind == 0xE) {
        goto update_tiles;
    }
    if (kind < 0xF) {
low_kind:
        if (kind == 0xD) {
            goto update_tiles;
        }
        goto after_tiles;
    }
high_kind:
    if (kind != 0xF) {
        goto after_tiles;
    }
update_tiles:
    M2C_FIELD(target, u8 **, 0x2C) = D_80173AD0;
    func_80047784(target, D_80173AD0[((D_80083228 + M2C_FIELD(actor, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);

after_tiles:
    if (M2C_FIELD(target, u16 *, 0x14) & 0x8000) {
        goto set_callback;
    }
    counter_base = (u8 *)&D_80083460;
    ASM_KEEP(counter_base);
    M2C_FIELD(counter_base, u16 *, 0xA)++;
counter_changed:
    M2C_FIELD(obj, u8 *, 0x9B)++;
    goto done;

state_two:
    if (!(M2C_FIELD(target, u16 *, 0x14) & 0xE000)) {
        goto done;
    }
    counter_base = (u8 *)&D_80083460;
    ASM_KEEP(counter_base);
    M2C_FIELD(counter_base, u16 *, 0xA)--;
set_callback:
    callback = &D_8016A36C;
    M2C_FIELD(obj, void **, 0x8C) = callback;

done:
    ASM_KEEP(obj);
    ASM_KEEP(middle);
    ASM_KEEP(target);
    ASM_KEEP(actor);
    return;
}
