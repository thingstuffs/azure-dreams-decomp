#include "common.h"

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
extern void func_8052E00C(void) __attribute__((noreturn));
extern void func_8052E034(void) __attribute__((noreturn));
extern void func_8052E038(void) __attribute__((noreturn));
extern void func_8052E10C(void) __attribute__((noreturn));
extern void func_8052E1B8(void) __attribute__((noreturn));
extern void func_8052E1BC(void) __attribute__((noreturn));

extern u8 D_8003C558[16];
extern void *D_8052676C[];
extern u8 D_8028DFD8[16];
extern u8 D_8052E40C[0x2000];

void func_80813368(void *arg0) {
    static void *const init_keepalive[] = {
        &&init_case0, &&init_case1, &&init_case2, &&init_case3, &&init_case4
    };
    volatile u8 frame_pad[32];
    void *obj;
    void *part;
    s32 i;
    s32 value;
    u16 flag_value;
    s32 table_index;
    s32 init_kind;
    s32 state;
    u16 counter;

    state = S16_AT(arg0, 0x18);
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_done;
    }
    func_8052E1BC();

state_zero:
        S16_AT(arg0, 0xC) = 0x410;
        S16_AT(arg0, 4) = 0x340;
        S16_AT(arg0, 0xE) = 0x348;
        S16_AT(arg0, 6) = 0x348;
        S16_AT(arg0, 0x10) = -0x60;
        S16_AT(arg0, 8) = -0x60;

        (void)init_keepalive;
        init_kind = S16_AT(arg0, 0x22);
        if ((u32)init_kind >= 5) {
            goto init_done;
        }
        goto *D_8052676C[init_kind];

init_case0:
        value = -0x60;
        ASM_TAILSLOT_PIN_TIED(value);   /* MATCH pin: retail delay-slot contents depend on it */
        func_8052E00C();
init_case1:
        value = -0x98;
        ASM_TAILSLOT_PIN_TIED(value);   /* MATCH pin: retail delay-slot contents depend on it */
        func_8052E00C();
init_case2:
        value = -0x30;
init_pair:
        S16_AT(arg0, 0x1E) = value;
        S16_AT(arg0, 0x1C) = value;
        func_8052E038();
init_case3:
        value = -0xB0;
        S16_AT(arg0, 0x1C) = value;
        value = -0x10;
        ASM_TAILSLOT_PIN_TIED(value);   /* MATCH pin: retail delay-slot contents depend on it */
        func_8052E034();
init_case4:
        value = -0x10;
        S16_AT(arg0, 0x1C) = value;
        value = -0xB0;
init_last:
        S16_AT(arg0, 0x1E) = value;
init_done:

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
                S32_AT(obj, 0x20) = (s32)arg0;
                S16_AT(obj, 0x28) = i;
            }
        }
        S16_AT(arg0, 0x18) = 1;
state_done:

    counter = U16_AT(arg0, 0x1A) + 1;
    U16_AT(arg0, 0x1A) = counter;
    if ((counter >> 2) & 1) {
        table_index = S16_AT(arg0, 0x22);
        if ((U16_AT(PTR_AT(arg0, 0), 0x62) &
             *(u16 *)(D_8052E40C + 0x1DD8 + (table_index * 2))) != 0) {
            S32_AT(arg0, 0x14) = 0x00FFFFFF;
            func_8052E10C();
        } else {
            S32_AT(arg0, 0x14) = 0;
        }
    } else {
        S32_AT(arg0, 0x14) = 0;
    }

    if (U16_AT(PTR_AT(arg0, 0), 0x64) >= U16_AT(arg0, 0x20)) {
        register s32 target_x ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
        s32 target_y;
        s32 current_x;
        register s32 current_y ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
        u16 upper_flag;

        target_x = S16_AT(arg0, 0x1C);
        current_x = S16_AT(arg0, 8);
        target_y = S16_AT(arg0, 0x1E);
        ASM_KEEP(target_y);   /* MATCH pin: retail schedule: same instructions, different order without it */
        current_y = S16_AT(arg0, 0x10);
        current_x += (target_x - current_x) >> 1;
        current_y += (target_y - current_y) >> 1;
        upper_flag = U16_AT(arg0, 0x24) & ~1;
        S16_AT(arg0, 8) = current_x;
        S16_AT(arg0, 0x10) = current_y;
        ASM_TAILSLOT_PIN_TIED(upper_flag);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_8052E1B8();
    } else {
        register s32 target_const ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
        s32 retreat_x;
        register s32 retreat_y ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
        s32 delta_x;
        register s32 motion_value ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */

        target_const = -0x60;
        retreat_x = S16_AT(arg0, 8);
        retreat_y = S16_AT(arg0, 0x10);
        delta_x = target_const - retreat_x;
        retreat_x += delta_x >> 1;
        ASM_KEEP(retreat_x);   /* MATCH pin: retail schedule: same instructions, different order without it */
        target_const -= retreat_y;
        target_const >>= 1;
        retreat_y += target_const;
        S16_AT(arg0, 0x10) = retreat_y;
        motion_value = (s16)retreat_y + 0x60;
        if (motion_value < 0) {
            motion_value = -motion_value;
        }
        ASM_KEEP(motion_value);   /* MATCH pin: retail delay-slot contents depend on it */
        S16_AT(arg0, 8) = retreat_x;
        if (motion_value < 2) {
            flag_value = U16_AT(arg0, 0x24) | 1;
store_flag:
            U16_AT(arg0, 0x24) = flag_value;
        }
    }
}
