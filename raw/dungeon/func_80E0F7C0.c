#include "common.h"

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

extern s32 func_8003DE58(s32, void *, u16 *, s32);
extern s32 func_8003F270(void);
extern void func_80047784(void *, u8, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);
extern void func_800BB044(void *);
extern void *func_80175858(void *, void *, void *);

extern void *D_80170850[];
extern void *D_80170870[];
extern u8 D_8006DE24[];
extern s32 D_800814A0[3];
extern void *D_800814A8[3];
extern s16 D_80083160[];
extern s16 D_80083228;
extern u8 D_80083460[];
extern s32 D_8008346C;
extern u8 D_80171094[];
extern u8 D_80176460[];
extern u8 D_80176490[];
extern u8 D_80176498[];

void func_80172FC0(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const keepalive[] = {
        &&L0, &&L1, &&L2, &&L3, &&L4, &&L5, &&L6,
        &&T1, &&T2, &&T3, &&Tdefault, &&T5, &&T6, &&T7
    };
    u16 vec[3];
    register void *arg1_s4 ASM_REG("$20") = arg1;
    s32 special;
    u8 *selector;
    u8 state;
    u16 timer;
    void *main_obj;
    register void *child ASM_REG("$2");

    ASM_KEEP(arg1_s4);
    state = FIELD(arg0, u8, 0x9B);
    special = 0;
    if (state >= 7U) {
        return;
    }
    (void)keepalive;
    goto *D_80170850[state];

L0:
    if (FIELD(arg3, u32, 0x1C) & 0x2000) {
        s32 kind;
        u32 index;

        kind = FIELD(arg3, u16, 0x46) & 0x3FFF;
        index = kind - 1;
        if (index >= 7U) {
            goto Tdefault;
        }
        goto *D_80170870[index];
T7:
        special = 1;
        goto T3;
T6:
        special = 1;
        goto T2;
T5:
        special = 1;
        goto T1;
    }

    {
        s32 kind;

        kind = FIELD(arg3, u16, 0x46) & 0x3FFF;
        if (kind == 2) {
            goto T2;
        }
        if (kind < 3) {
            selector = 0;
            if (kind == 1) {
                goto T1;
            }
            goto Tdone;
        }
        selector = 0;
        if (kind != 3) {
            goto Tdone;
        }
    }
T3:
    selector = (u8 *)arg3 + 0xE;
    goto Tdone;
T2:
    selector = (u8 *)arg3 + 0xB;
    goto Tdone;
T1:
    selector = (u8 *)arg3 + 8;
    goto Tdone;
Tdefault:
    selector = 0;
Tdone:
    if (*selector != 0) {
        void *effect;

        (*(volatile u16 *)((u8 *)arg0 + 0x98)) &= 0xFF7F;
        {
            register s32 special_test ASM_REG("$2");

            do {
                special_test = special;
            } while (0);
            ASM_KEEP(special_test);
            if (special_test != 0) {
                effect = D_800814A8[0];
                FIELD(arg3, void *, 0x60) = effect;
                goto copy_effect;
            }
        }
        if (D_8006DE24[*selector * 0x14 + 0x12] == 2) {
            effect = FIELD(arg3, void *, 0x60);
            if (effect != 0) {
                register void *owner ASM_REG("$3");
copy_effect:
                owner = FIELD(effect, void *, -0x14);
                ASM_KEEP(owner);
                FIELD(arg3, s8, 0x72) = FIELD(owner, u8, 0x24);
                FIELD(arg3, s8, 0x73) = FIELD(owner, u8, 0x25);
            }
        } else {
            s32 x;
            s32 y;

            (*(void *volatile *)((u8 *)arg3 + 0x60)) = func_800A05A4(
                arg3,
                FIELD(arg2, u8, 0x24),
                FIELD(arg2, u8, 0x25),
                FIELD(arg3, s16, 0x2A),
                0x10);
            ASM_SCHED_BARRIER();
            x = FIELD(arg3, s8, 0x72);
            y = FIELD(arg3, s8, 0x73);
            if (x < 0) {
                x = -x;
            }
            if (y < 0) {
                y = -y;
            }
            FIELD(arg3, s8, 0x72) = x;
            FIELD(arg3, s8, 0x73) = y;
        }
        if (func_800A94A0(arg3, selector, special, (u8 *)arg0 + 0x98) == 0) {
            return;
        }
        func_800BB044(arg3);
        {
            u8 next_state;

            next_state = FIELD(arg0, u8, 0x9B);
            next_state++;
            FIELD(arg0, u8, 0x9B) = next_state;
            return;
        }
    }

    FIELD(arg1_s4, s32, 0x14) = 0;
    FIELD(arg1_s4, s32, 0x10) = 0;
    FIELD(arg1_s4, s32, 0xC) = 0;
    func_800A2B04(arg1_s4, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    main_obj = D_800814A8[0];
    D_8008346C = 0;
    FIELD(main_obj, u16, 0xA6)--;
    func_800A4ACC(arg3);
    FIELD(arg3, u8, 0x6D)--;
    FIELD(arg0, void *, 0x8C) = D_80171094;
    FIELD(arg3, s8, 0x73) = 0;
    FIELD(arg3, s8, 0x72) = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    return;

L1:
    if (func_8003F270() != 0) {
        FIELD(arg2, u16, 0x14) |= 0x800;
        return;
    }
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, u16, 0xAE) = 8;
    FIELD(arg0, u8, 0x9B)++;

L2:
    timer = FIELD(arg0, u16, 0xAE) - 1;
    FIELD(arg0, u16, 0xAE) = timer;
    if ((s16)timer > 0) {
        u16 scale;

        scale = FIELD(arg2, u16, 0x1E) - 0x100;
        FIELD(arg2, u16, 0x1E) = scale;
        FIELD(arg2, u16, 0x1C) = scale;
        return;
    }

    FIELD(arg0, void *, 0xA0) = func_80175858(arg0, arg1_s4, arg2);
    do {
    } while (0);
    {
        register s16 *global ASM_REG("$16");
#ifndef NON_MATCHING
        register u8 *global_page ASM_REG("$2");
#endif
        s32 index;
        u8 table_value;
        void *model_root;
        void *model;
        void *model_table;
        void *selected_model;

#ifdef NON_MATCHING
        global = D_80083160;
#else
        global_page = (u8 *)0x80080000;
        ASM_KEEP(global_page);
        global = (s16 *)(global_page + 0x3160);
#endif
        {
            register s32 first_index ASM_REG("$2");
            s32 first_base;
            s32 first_angle;

            first_base = global[0x64];
            first_angle = FIELD(arg3, s16, 0x2A);
            model_root = FIELD(arg2, void *, 0x28);
            ASM_SCHED_BARRIER();
            do {
                first_index =
                    ((first_base + first_angle + 0x100) >> 9) & 7;
            } while (0);
            ASM_KEEP_NV(first_index);
            model = *(void **)model_root;
            model_table = *(void **)model;
            selected_model =
                ((void **)model_table)[D_80176498[first_index]];
        }
        {
            register void *call_obj ASM_REG("$5");
            s32 model_word;

            do {
                call_obj = arg2;
            } while (0);
            ASM_KEEP(call_obj);
            FIELD(arg2, void *, 0) = selected_model;
            model_word = FIELD(selected_model, s32, 4);
            {
                register u16 *call_vec ASM_REG("$6");

                do {
                    call_vec = vec;
                } while (0);
                ASM_KEEP(call_vec);
                FIELD(arg2, s32, 8) = model_word;
                vec[2] = 0;
                vec[1] = 0;
                vec[0] = 0;
                if (func_8003DE58(
                        FIELD(arg2, s32, 8), call_obj, call_vec, 0) != 0) {
                    u16 vec_z;

                    FIELD(arg1_s4, u16, 2) += vec[0];
                    FIELD(arg1_s4, u16, 6) += vec[1];
                    vec_z = vec[2];
                    FIELD(arg0, u16, 0xB2) = vec_z;
                    FIELD(arg0, u16, 0x92) =
                        FIELD(arg1_s4, u16, 0xA) - FIELD(arg3, u16, 0x88) +
                        (s16)vec_z / 2;
                }
            }
        }
        FIELD(arg0, u16, 0x98) |= 8;
        FIELD(arg3, u32, 0x1C) &= 0xBFFFFFFF;
        FIELD(arg2, void *, 0x2C) = D_80176490;
        index = ((global[0x64] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
        table_value = D_80176490[index];
        func_80047784(arg2, table_value, 0);
        FIELD(arg2, u16, 0x1E) = 0x800;
        FIELD(arg2, u16, 0x1C) = 0x800;
    }
    goto advance_8;

L3:
    timer = FIELD(arg0, u16, 0xAE) - 1;
    FIELD(arg0, u16, 0xAE) = timer;
    if ((s16)timer >= 0) {
        u16 scale;

        scale = FIELD(arg2, u16, 0x1E) + 0x100;
        FIELD(arg2, u16, 0x1E) = scale;
        FIELD(arg2, u16, 0x1C) = scale;
        FIELD(arg0, u16, 0x92) += (s16)FIELD(arg0, u16, 0xB2) >> 4;
        return;
    }
    FIELD(arg0, u16, 0xAE) = 4;
    FIELD(arg0, u16, 0x98) |= 0x80;
    FIELD(arg0, u8, 0x9B)++;
    return;

L4:
    timer = FIELD(arg0, u16, 0xAE) - 1;
    FIELD(arg0, u16, 0xAE) = timer;
    if ((s16)timer >= 0) {
        return;
    }
    timer = 9;
    FIELD(arg0, s32, 0xB4) = FIELD(arg2, s32, 0xC);
    FIELD(arg0, u16, 0xBA) = FIELD(arg2, u16, 0x10);
    FIELD(arg0, u16, 0xB8) = FIELD(arg2, u16, 0x12);
    FIELD(arg2, u16, 0x12) -= 0x80;
    {
        u8 next_state;

        next_state = FIELD(arg0, u8, 0x9B);
        FIELD(arg0, u16, 0xAE) = timer;
        next_state++;
        FIELD(arg0, u8, 0x9B) = next_state;
        return;
    }

L5:
    timer = FIELD(arg0, u16, 0xAE) - 1;
    FIELD(arg0, u16, 0xAE) = timer;
    if ((s16)timer <= 0) {
        return;
    }
    FIELD(arg3, u32, 0x1C) |= 0x10000000;
    FIELD(arg2, u16, 0x14) |= 0xC;
    FIELD(arg2, u16, 0x10) |= 0x20;
    FIELD(arg2, u8, 0xC) -= FIELD(arg2, u8, 0xC) / (s16)FIELD(arg0, u16, 0xAE);
    FIELD(arg2, u8, 0xD) -= FIELD(arg2, u8, 0xD) / (s16)FIELD(arg0, u16, 0xAE);
    FIELD(arg2, u8, 0xE) -= FIELD(arg2, u8, 0xE) / (s16)FIELD(arg0, u16, 0xAE);
    if (FIELD(arg0, s16, 0xAE) != 1) {
        return;
    }
    {
        u8 next_state;

advance_8:
        next_state = FIELD(arg0, u8, 0x9B);
        timer = 8;
        FIELD(arg0, u16, 0xAE) = timer;
        next_state++;
        FIELD(arg0, u8, 0x9B) = next_state;
        return;
    }

L6:
    timer = FIELD(arg0, u16, 0xAE) - 1;
    FIELD(arg0, u16, 0xAE) = timer;
    if ((s16)timer > 0 && !(FIELD(arg2, u16, 0x14) & 0x8000)) {
        return;
    }
    child = FIELD(arg0, void *, 0xA0);
    ASM_KEEP(child);
    if (child != 0) {
        register void *active_child ASM_REG("$5");
        register s32 used_flags ASM_REG("$2");
        register u16 child_flags ASM_REG("$3");
        register u8 *used_page ASM_REG("$4");

        used_page = (u8 *)0x80080000;
        ASM_KEEP(used_page);
        active_child = child;
        ASM_KEEP(active_child);
        used_flags = *(volatile s32 *)(used_page + 0x14A0);
        ASM_KEEP(used_flags);
        FIELD(arg0, s16, 0xAC) = 0;
        FIELD(arg0, s32, 0xA4) = 0;
        FIELD(arg0, s32, 0x90) = 0;
        child_flags = FIELD(active_child, u16, 0x1E);
        ASM_KEEP(child_flags);
        used_flags |= 0x8000;
        child_flags |= 0x8000;
        *(volatile s32 *)(used_page + 0x14A0) = used_flags;
        FIELD(active_child, u16, 0x1E) = child_flags;
        FIELD(arg0, void *, 0xA0) = 0;
    }
    FIELD(arg3, u32, 0x1C) &= 0xEFFFFFFF;
    FIELD(arg2, u16, 0x12) = FIELD(arg0, u16, 0xB8);
    FIELD(arg2, s32, 0xC) = FIELD(arg0, s32, 0xB4);
    FIELD(arg2, u16, 0x10) = FIELD(arg0, u16, 0xBA);
    FIELD(arg1_s4, s32, 0x14) = 0;
    FIELD(arg1_s4, s32, 0x10) = 0;
    FIELD(arg1_s4, s32, 0xC) = 0;
    func_800A2B04(arg1_s4, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    FIELD(arg0, u16, 0x98) &= 0xFFF7;
    FIELD(arg3, u32, 0x1C) |= 0x40000000;
    if (FIELD(arg2, void *, 0x2C) != D_80176460) {
        s32 index;

        FIELD(arg2, void *, 0x2C) = D_80176460;
        index = ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
        func_80047784(arg2, D_80176460[index], 0);
    }
    {
        u8 *global;

        global = D_80083460;
        if (FIELD(global, s32, 0xC) != 0) {
            return;
        }
        FIELD(global, u16, 0xA)--;
    }
    FIELD(arg0, void *, 0x8C) = D_80171094;
    FIELD(arg2, u16, 0x1E) = 0x1000;
    FIELD(arg2, u16, 0x1C) = 0x1000;
    func_800A4ACC(arg3);
    FIELD(arg3, s8, 0x73) = 0;
    FIELD(arg3, s8, 0x72) = 0;
    FIELD(arg3, u8, 0x6D)--;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    func_800A56E0(0xB4);
}
