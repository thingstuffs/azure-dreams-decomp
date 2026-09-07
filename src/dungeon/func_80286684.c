#include "common.h"

extern void func_800197C8(void) __attribute__((noreturn));
extern void func_80019860(void) __attribute__((noreturn));
extern s32 func_80019894(s32);
extern void func_8003E4FC(s32, void *, s32);
extern void func_8003F320(void);
extern void func_8004425C(s32);
extern void func_8004450C(s16);
extern void func_80044698(void);
extern void func_80053DA8(s32);

typedef struct Object {
    s32 field_0;
} Object;

extern Object *D_8006E704[];
extern Object *D_8006E704_remat[] __asm__("D_8006E704");
extern s8 D_80080AF3;
extern Object *D_80080AF4[2];
extern Object *D_80080AF4_fresh[2] __asm__("D_80080AF4");
extern s16 D_80080AFC;
extern s16 D_80080AFC_fresh __asm__("D_80080AFC");
extern s32 D_801BEE40[4];
extern s32 D_801C4640[4];

s32 func_80019684(s16 arg0, s16 arg1, s32 arg2) {
    register s32 early_arg2 ASM_REG("$18") = arg2;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u16 saved_index = ({ ASM_KEEP_NV(early_arg2); 0; });
    register s16 held_arg0 ASM_REG("$22") = arg0;   /* MATCH pin: keeps a statement from moving across a call/branch */
    s16 tail_arg1 = arg1;
    s16 held_arg2_tail = (s16)early_arg2;
    s32 slot_offset = (s32)arg0 << 16;
    Object **slot_base = D_8006E704;
    register Object **slot ASM_REG("$16") =
        (Object **)((u8 *)slot_base + (slot_offset >> 14));
    Object **table = D_80080AF4;
    u16 index;
    Object *current;
    register Object *object ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    Object *other;
    u32 word;
    register u32 packed ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register u32 mask ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    if (*slot == table[D_80080AFC]) {
        s32 tail_result = 1;
        ASM_TAILSLOT_PIN(tail_result);   /* MATCH pin: retail delay-slot contents depend on it */
        func_80019860();
        return 1;
    }

    if ((func_80019894(1) << 16) != 0) {
        func_8004425C(0xC);
    }
    {
        register s32 arg2_test ASM_REG("$2") = early_arg2 << 16;   /* MATCH pin: load-bearing for the whole function shape */
        if (arg2_test == 0) {
            saved_index = (u16)D_80080AFC;
        }
    }

    index = (u16)D_80080AFC;
    current = *slot;
    index ^= 1;
    D_80080AFC = index;
    if (current != table[(s16)index]) {
        if (D_80080AF3 != (s16)arg1) {
            func_80044698();
        }

        object = *slot;
        mask = 0xFF800000;
        object->field_0 &= mask;
        other = *slot;
        word = other->field_0;
        {
            mask = 0x007F0000;
            if (D_80080AFC != 0) {
                u32 tail_addr;
                mask |= 0xFFFF;
                ASM_KEEP(mask);   /* MATCH pin: retail basic-block layout depends on it */
                tail_addr = (u32)D_801C4640;
                ASM_TAILSLOT_PIN(tail_addr);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                func_800197C8();
                return 0;
            }

            ASM_KEEP(held_arg0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            ASM_KEEP_DEP_NV(mask, word);   /* MATCH pin: retail basic-block layout depends on it */
            mask |= 0xFFFF;
            packed = (u32)D_801BEE40;
            ASM_KEEP_NV(packed);   /* MATCH pin: load-bearing for the whole function shape */
            packed &= mask;
            packed = word | packed;
        }
        {
            register s32 remat_index ASM_REG("$16");   /* MATCH pin: retail schedule: same instructions, different order without it */
            register Object **remat_base ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
            s32 call_kind = 6;
            ASM_KEEP_NV(call_kind);   /* MATCH pin: retail keeps a computation the compiler would drop */
            remat_index = (s32)held_arg0 << 16;
            other->field_0 = packed;
            remat_base = D_8006E704_remat;
            remat_index >>= 14;
            slot = (Object **)((u8 *)remat_base + remat_index);
            func_8003E4FC(call_kind, *slot, 0);
            D_80080AF4_fresh[D_80080AFC_fresh] = *slot;
            func_8003F320();
        }
    }

    func_8004450C(tail_arg1);
    {
        s32 tail_arg2_test =
            (s32)held_arg2_tail << 16;
        if (tail_arg2_test != 0) {
        s32 effect = 0x21;
        if (D_80080AFC != 0) {
            effect = 0x22;
        }
        func_80053DA8(effect);
        {
            s32 tail_result = 0;
            ASM_TAILSLOT_PIN(tail_result);   /* MATCH pin: retail delay-slot contents depend on it */
        }
        func_80019860();
        return 0;
        }
    }

    D_80080AFC = saved_index;
    return 0;
}
