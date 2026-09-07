#include "common.h"

typedef s32 M2C_UNK;
typedef void (*Callback)();

#ifdef NON_MATCHING
typedef union {
    long long value;
    struct { u32 low; s32 high; } word;
} DivProduct;
#else
typedef union {
    long long value;
    struct { s32 high; u32 low; } word;
} DivProduct;
#endif

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

extern void func_800353F4();
extern void func_80047738();
extern void func_800478B8();
extern void func_800A020C();
extern s32 func_800A9E70();
extern void func_800AA36C();
extern s16 func_800BCB04();
extern void func_801713B8(void) __attribute__((noreturn));
extern void func_8017143C(void) __attribute__((noreturn));
extern void func_801714F0(void) __attribute__((noreturn));

extern u16 D_80013714;
extern s16 D_80083228;
extern u16 D_80083462;
extern s16 D_8008346A;
extern u8 *D_800E3D7C[];
extern M2C_UNK D_80171514;
extern Callback D_80173EF4[];
extern M2C_UNK D_80173FC8[];

void func_8017112C(void *arg0, void *arg1, void *arg2)
{
    void *entity = arg0;
    void *motion = arg1;
    register void *monster ASM_REG("$19") = arg2;
    void *actor = entity;
    register s16 state_direction ASM_REG("$17");
    register u8 raw_state ASM_REG("$2");
    register void *call_entity ASM_REG("$4");
    register void *call_motion ASM_REG("$5");
    register void *call_monster ASM_REG("$6");
    register s32 normalized_state ASM_REG("$2");
    s32 current_state;
    register s32 direction_calc ASM_REG("$2");
    register s32 next_current ASM_REG("$2");
    Callback callback;
    Callback active_callback;
    s16 floor;
    register s32 target ASM_REG("$5");
    register s32 current_raw ASM_REG("$4");
    register s32 current ASM_REG("$3");
    s32 distance;
    u16 global_flags;
    u16 *flag_word;
    register s32 delta ASM_REG("$2");
    register s32 position ASM_REG("$4");
    s32 division_magic;
    s32 quotient;
    DivProduct product;
    u8 *slot;
    void *node;
    void *record;

    if (FIELD(actor, u8, 0xBB) == 0 && D_8008346A == 0) {
        FIELD(actor, u8, 0xBB) = 1;
        func_800353F4(D_80173FC8);
        FIELD(actor, u8, 0x6D) = 0;
        FIELD(actor, u8, 0x9B) = 0;
    }

    ASM_MEM_BARRIER();
    flag_word = &D_80013714;
    global_flags = *flag_word;
    if (global_flags & 8) {
        s32 i = 1;
        slot = D_800E3D7C[0] + 4;
        do {
            node = FIELD(slot, void *, 0xAC);
            if (node != 0) {
                record = FIELD(node, void *, -0x14);
                FIELD(record, u16, 0x14) &= 0xFFBF;
            }
            i--;
            slot -= 4;
        } while (i >= 0);
    }

    if (D_80083462 & 0x2000) {
        callback = FIELD(entity, Callback, 0x8C);
        if (callback == (Callback)&D_80171514) {
            callback(entity, motion, monster, actor);
            func_801714F0();
            return;
        }
        FIELD(actor, u8, 0x71) &= 0x7F;
        func_801714F0();
        return;
    }

    call_entity = entity;
    call_motion = motion;
    call_monster = monster;
    ASM_USE2_NV(call_entity, call_motion);
    ASM_USE_NV(call_monster);
    raw_state = FIELD(actor, volatile u8, 0x6D);
    state_direction = ((s32)raw_state << 24) >> 24;
    if (func_800A9E70(call_entity, call_motion, call_monster, actor) != 0) {
        return;
    }

    active_callback = FIELD(entity, Callback, 0x8C);
    if (active_callback != 0) {
        active_callback(entity, motion, monster, actor);
    }
    D_80173EF4[FIELD(entity, u8, 0x9A)](entity, motion, monster, actor);

    normalized_state = (s32)state_direction << 16;
    ASM_USE_NV(normalized_state);
    current_state = FIELD(actor, s8, 0x6D);
    ASM_USE_NV(current_state);
    normalized_state >>= 16;
    ASM_USE2_NV(normalized_state, current_state);
    if (normalized_state != current_state) {
        func_800AA36C(entity, motion, monster, actor);
    }

    FIELD(motion, s32, 0) += FIELD(motion, s32, 0xC);
    FIELD(motion, s32, 4) += FIELD(motion, s32, 0x10);

    direction_calc = D_80083228 + FIELD(actor, s16, 0x2A) + 0x100;
    ASM_USE_NV(direction_calc);
    state_direction = (direction_calc >> 9) & 7;
    if (FIELD(entity, s16, 0x94) != state_direction) {
        func_80047738(monster,
                     *((u8 *)FIELD(monster, void *, 0x2C) + state_direction),
                     FIELD(monster, s8, 4));
        FIELD(entity, s16, 0x94) = state_direction;
    }

    FIELD(monster, u16, 0x14) &= 0xFFFE;
    func_800A020C(FIELD(actor, s32, 0x1C), (u8 *)monster + 0xC);

    if (!(FIELD(actor, s32, 0x1C) & 0x20)) {
        if (!(FIELD(monster, u16, 0x14) & 0x40)) {
            func_800478B8(monster);
            func_801713B8();
            return;
        }
    } else {
        FIELD(monster, u16, 0x14) |= 0x7000;
        FIELD(actor, s32, 0x1C) &= 0xFFFBFFFF;
    }

    if (FIELD(entity, s16, 0xB8) == 1) {
        target = FIELD(motion, s16, 0x16);
        ASM_KEEP_NV(target);
        current = FIELD(motion, s16, 0xA);
        ASM_KEEP_NV(current);
        current_raw = FIELD(motion, u16, 0xA);
        ASM_KEEP_NV(current_raw);
        if (target > current) {
            distance = target - current;
            if (distance < 0) {
                distance = -distance;
            }
            division_magic = 0x66660000;
            if (distance >= 0x65) {
                next_current = current_raw + 8;
                ASM_KEEP_NV(next_current);
                FIELD(motion, s16, 0xA) = next_current;
                func_8017143C();
                return;
            }
            ASM_KEEP_NV(division_magic);
            delta = FIELD(motion, s32, 0x14);
            position = FIELD(motion, s32, 8);
            ASM_SCHED_BARRIER();
            division_magic |= 0x6667;
            ASM_KEEP_NV(division_magic);
            delta -= position;
            if (delta < 0) {
                delta = -delta;
            }
            ASM_KEEP_NV(delta);
            product.value = (long long)delta * division_magic;
            quotient = (product.word.high >> 2) - (delta >> 31);
            position += quotient;
            ASM_KEEP_NV(position);
            FIELD(motion, s32, 8) = position;
        }
    }

    if (FIELD(entity, s16, 0xB8) == 2 && FIELD(motion, s16, 0xA) >= -0x3EF) {
        FIELD(motion, s16, 0xA) = FIELD(motion, u16, 0xA) - 4;
    }

    if (FIELD(actor, s32, 0x1C) & 0x40000000) {
        FIELD(actor, s32, 0x1C) &= 0xBFFFFFFF;
        floor = func_800BCB04((FIELD(monster, u8, 0x24) << 6) | 0x20,
                              (FIELD(monster, u8, 0x25) << 6) | 0x20,
                              (s16)(FIELD(actor, u16, 0x88) - 0x20));
        if (floor < 0x200) {
            FIELD(entity, u16, 0x92) += FIELD(actor, u16, 0x88) - floor;
            FIELD(actor, u16, 0x88) = floor;
        }
    }

    FIELD(monster, u16, 0x14) |= 0x40;
    ASM_KEEP(entity);
    ASM_KEEP(motion);
    ASM_KEEP(monster);
    ASM_KEEP(actor);
}
