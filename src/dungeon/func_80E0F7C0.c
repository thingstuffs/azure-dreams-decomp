#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80172FC0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_90;   /* overlapping accesses */
    u8 pad_94[0x4];
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    void * unk_A0;
    s32 unk_A4;
    u8 pad_A8[0x4];
    s16 unk_AC;
    union { u16 u; s16 s; } unk_AE;   /* accessed as both */
    u8 pad_B0[0x2];
    u16 unk_B2;
    s32 unk_B4;
    u16 unk_B8;
    u16 unk_BA;
} S_80172FC0_0;   /* arg0 in func_80172FC0 */


typedef struct S_80172FC0_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172FC0_2_pre;   /* the 0x14 bytes before effect in func_80172FC0, addressed as effect[-1] */

typedef struct S_80172FC0_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172FC0_3;   /* owner in func_80172FC0 */

typedef struct S_80172FC0_4 {
    void * unk_00;
    u8 pad_04[0x4];
    s32 unk_08;
    union { struct { s32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x2];
    void * unk_28;
    void * unk_2C;
} S_80172FC0_4;   /* arg2 in func_80172FC0 */

typedef struct S_80172FC0_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172FC0_5;   /* arg1_s4 in func_80172FC0 */

typedef struct S_80172FC0_6 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80172FC0_6;   /* selected_model in func_80172FC0 */

typedef struct S_80172FC0_7 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_80172FC0_7;   /* active_child in func_80172FC0 */

typedef struct S_80172FC0_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172FC0_8;   /* global in func_80172FC0 */



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
    register void *arg1_s4 ASM_REG("$20") = arg1;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 special;
    u8 *selector;
    u8 state;
    u16 timer;
    void *main_obj;
    register void *child ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    ASM_KEEP(arg1_s4);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    state = ((S_80172FC0_0 *)arg0)->unk_9B;
    special = 0;
    if (state >= 7U) {
        return;
    }
    (void)keepalive;
    goto *D_80170850[state];

L0:
    if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x2000) {
        s32 kind;
        u32 index;

        kind = ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x3FFF;
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

        kind = ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x3FFF;
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
            s32 special_test;

            do {
                special_test = special;
            } while (0);
            ASM_KEEP(special_test);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            if (special_test != 0) {
                effect = D_800814A8[0];
                ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv = effect;
                goto copy_effect;
            }
        }
        if (D_8006DE24[*selector * 0x14 + 0x12] == 2) {
            effect = ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv;
            if (effect != 0) {
                register void *owner ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
copy_effect:
                owner = ((S_80172FC0_2_pre *)effect)[-1].unk_00;
                ((Rec_D_800E3D7C *)arg3)->unk_72.as_s8 = ((S_80172FC0_3 *)owner)->unk_24;
                ((Rec_D_800E3D7C *)arg3)->unk_73.as_s8 = ((S_80172FC0_3 *)owner)->unk_25;
            }
        } else {
            s32 x;
            s32 y;

            (*(void *volatile *)((u8 *)arg3 + 0x60)) = func_800A05A4(
                arg3,
                ((S_80172FC0_4 *)arg2)->unk_24,
                ((S_80172FC0_4 *)arg2)->unk_25,
                ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16,
                0x10);
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            x = ((Rec_D_800E3D7C *)arg3)->unk_72.as_s8;
            y = ((Rec_D_800E3D7C *)arg3)->unk_73.as_s8;
            if (x < 0) {
                x = -x;
            }
            if (y < 0) {
                y = -y;
            }
            ((Rec_D_800E3D7C *)arg3)->unk_72.as_s8 = x;
            ((Rec_D_800E3D7C *)arg3)->unk_73.as_s8 = y;
        }
        if (func_800A94A0(arg3, selector, special, (u8 *)arg0 + 0x98) == 0) {
            return;
        }
        func_800BB044(arg3);
        {
            u8 next_state;

            next_state = ((S_80172FC0_0 *)arg0)->unk_9B;
            next_state++;
            ((S_80172FC0_0 *)arg0)->unk_9B = next_state;
            return;
        }
    }

    ((S_80172FC0_5 *)arg1_s4)->unk_14 = 0;
    ((S_80172FC0_5 *)arg1_s4)->unk_10 = 0;
    ((S_80172FC0_5 *)arg1_s4)->unk_0C = 0;
    func_800A2B04(arg1_s4, ((S_80172FC0_4 *)arg2)->unk_24, ((S_80172FC0_4 *)arg2)->unk_25);
    main_obj = D_800814A8[0];
    D_8008346C = 0;
    (*(u16 *)((u8 *)main_obj + 0xA6))--;
    func_800A4ACC(arg3);
    ((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8--;
    ((S_80172FC0_0 *)arg0)->unk_8C = D_80171094;
    ((Rec_D_800E3D7C *)arg3)->unk_73.as_s8 = 0;
    ((Rec_D_800E3D7C *)arg3)->unk_72.as_s8 = 0;
    ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v &= 0x7FFF;
    return;

L1:
    if (func_8003F270() != 0) {
        ((S_80172FC0_4 *)arg2)->unk_14 |= 0x800;
        return;
    }
    ((S_80172FC0_4 *)arg2)->unk_14 &= 0xF7FF;
    ((S_80172FC0_0 *)arg0)->unk_AE.u = 8;
    ((S_80172FC0_0 *)arg0)->unk_9B++;

L2:
    timer = ((S_80172FC0_0 *)arg0)->unk_AE.u - 1;
    ((S_80172FC0_0 *)arg0)->unk_AE.u = timer;
    if ((s16)timer > 0) {
        u16 scale;

        scale = ((S_80172FC0_4 *)arg2)->unk_1E - 0x100;
        ((S_80172FC0_4 *)arg2)->unk_1E = scale;
        ((S_80172FC0_4 *)arg2)->unk_1C = scale;
        return;
    }

    ((S_80172FC0_0 *)arg0)->unk_A0 = func_80175858(arg0, arg1_s4, arg2);
    do {
    } while (0);
    {
        s16 *global;
#ifndef NON_MATCHING
        u8 *global_page;
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
        ASM_KEEP(global_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        global = (s16 *)(global_page + 0x3160);
#endif
        {
            s32 first_index;
            s32 first_base;
            s32 first_angle;

            first_base = global[0x64];
            first_angle = ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16;
            model_root = ((S_80172FC0_4 *)arg2)->unk_28;
            do {
                first_index =
                    ((first_base + first_angle + 0x100) >> 9) & 7;
            } while (0);
            ASM_KEEP_NV(first_index);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            model = *(void **)model_root;
            model_table = *(void **)model;
            selected_model =
                ((void **)model_table)[D_80176498[first_index]];
        }
        {
            void *call_obj;
            s32 model_word;

            do {
                call_obj = arg2;
            } while (0);
            ASM_KEEP(call_obj);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            ((S_80172FC0_4 *)arg2)->unk_00 = selected_model;
            model_word = ((S_80172FC0_6 *)selected_model)->unk_04;
            {
                u16 *call_vec;

                do {
                    call_vec = vec;
                } while (0);
                ASM_KEEP(call_vec);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                ((S_80172FC0_4 *)arg2)->unk_08 = model_word;
                vec[2] = 0;
                vec[1] = 0;
                vec[0] = 0;
                if (func_8003DE58(
                        ((S_80172FC0_4 *)arg2)->unk_08, call_obj, call_vec, 0) != 0) {
                    u16 vec_z;

                    ((S_80172FC0_5 *)arg1_s4)->unk_02 += vec[0];
                    ((S_80172FC0_5 *)arg1_s4)->unk_06 += vec[1];
                    vec_z = vec[2];
                    ((S_80172FC0_0 *)arg0)->unk_B2 = vec_z;
                    ((S_80172FC0_0 *)arg0)->unk_90.at02.v =
                        ((S_80172FC0_5 *)arg1_s4)->unk_0A - ((Rec_D_800E3D7C *)arg3)->unk_88.as_u16 +
                        (s16)vec_z / 2;
                }
            }
        }
        ((S_80172FC0_0 *)arg0)->unk_98 |= 8;
        ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 &= 0xBFFFFFFF;
        ((S_80172FC0_4 *)arg2)->unk_2C = D_80176490;
        index = ((global[0x64] + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7;
        table_value = D_80176490[index];
        func_80047784(arg2, table_value, 0);
        ((S_80172FC0_4 *)arg2)->unk_1E = 0x800;
        ((S_80172FC0_4 *)arg2)->unk_1C = 0x800;
    }
    goto advance_8;

L3:
    timer = ((S_80172FC0_0 *)arg0)->unk_AE.u - 1;
    ((S_80172FC0_0 *)arg0)->unk_AE.u = timer;
    if ((s16)timer >= 0) {
        u16 scale;

        scale = ((S_80172FC0_4 *)arg2)->unk_1E + 0x100;
        ((S_80172FC0_4 *)arg2)->unk_1E = scale;
        ((S_80172FC0_4 *)arg2)->unk_1C = scale;
        ((S_80172FC0_0 *)arg0)->unk_90.at02.v += (s16)((S_80172FC0_0 *)arg0)->unk_B2 >> 4;
        return;
    }
    ((S_80172FC0_0 *)arg0)->unk_AE.u = 4;
    ((S_80172FC0_0 *)arg0)->unk_98 |= 0x80;
    ((S_80172FC0_0 *)arg0)->unk_9B++;
    return;

L4:
    timer = ((S_80172FC0_0 *)arg0)->unk_AE.u - 1;
    ((S_80172FC0_0 *)arg0)->unk_AE.u = timer;
    if ((s16)timer >= 0) {
        return;
    }
    timer = 9;
    ((S_80172FC0_0 *)arg0)->unk_B4 = ((S_80172FC0_4 *)arg2)->unk_0C.at00.v;
    ((S_80172FC0_0 *)arg0)->unk_BA = ((S_80172FC0_4 *)arg2)->unk_10;
    ((S_80172FC0_0 *)arg0)->unk_B8 = ((S_80172FC0_4 *)arg2)->unk_12;
    ((S_80172FC0_4 *)arg2)->unk_12 -= 0x80;
    {
        u8 next_state;

        next_state = ((S_80172FC0_0 *)arg0)->unk_9B;
        ((S_80172FC0_0 *)arg0)->unk_AE.u = timer;
        next_state++;
        ((S_80172FC0_0 *)arg0)->unk_9B = next_state;
        return;
    }

L5:
    timer = ((S_80172FC0_0 *)arg0)->unk_AE.u - 1;
    ((S_80172FC0_0 *)arg0)->unk_AE.u = timer;
    if ((s16)timer <= 0) {
        return;
    }
    ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 |= 0x10000000;
    ((S_80172FC0_4 *)arg2)->unk_14 |= 0xC;
    ((S_80172FC0_4 *)arg2)->unk_10 |= 0x20;
    ((S_80172FC0_4 *)arg2)->unk_0C.at00u.v -= ((S_80172FC0_4 *)arg2)->unk_0C.at00u.v / (s16)((S_80172FC0_0 *)arg0)->unk_AE.u;
    ((S_80172FC0_4 *)arg2)->unk_0C.at01.v -= ((S_80172FC0_4 *)arg2)->unk_0C.at01.v / (s16)((S_80172FC0_0 *)arg0)->unk_AE.u;
    ((S_80172FC0_4 *)arg2)->unk_0C.at02.v -= ((S_80172FC0_4 *)arg2)->unk_0C.at02.v / (s16)((S_80172FC0_0 *)arg0)->unk_AE.u;
    if (((S_80172FC0_0 *)arg0)->unk_AE.s != 1) {
        return;
    }
    {
        u8 next_state;

advance_8:
        next_state = ((S_80172FC0_0 *)arg0)->unk_9B;
        timer = 8;
        ((S_80172FC0_0 *)arg0)->unk_AE.u = timer;
        next_state++;
        ((S_80172FC0_0 *)arg0)->unk_9B = next_state;
        return;
    }

L6:
    timer = ((S_80172FC0_0 *)arg0)->unk_AE.u - 1;
    ((S_80172FC0_0 *)arg0)->unk_AE.u = timer;
    if ((s16)timer > 0 && !(((S_80172FC0_4 *)arg2)->unk_14 & 0x8000)) {
        return;
    }
    child = ((S_80172FC0_0 *)arg0)->unk_A0;
    if (child != 0) {
        void *active_child;
        s32 used_flags;
        register u16 child_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        u8 *used_page;

        used_page = (u8 *)0x80080000;
        ASM_KEEP(used_page);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        active_child = child;
        ASM_KEEP(active_child);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        used_flags = *(volatile s32 *)(used_page + 0x14A0);
        ASM_KEEP(used_flags);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ((S_80172FC0_0 *)arg0)->unk_AC = 0;
        ((S_80172FC0_0 *)arg0)->unk_A4 = 0;
        ((S_80172FC0_0 *)arg0)->unk_90.at00.v = 0;
        child_flags = ((S_80172FC0_7 *)active_child)->unk_1E;
        ASM_KEEP(child_flags);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        used_flags |= 0x8000;
        child_flags |= 0x8000;
        *(volatile s32 *)(used_page + 0x14A0) = used_flags;
        ((S_80172FC0_7 *)active_child)->unk_1E = child_flags;
        ((S_80172FC0_0 *)arg0)->unk_A0 = 0;
    }
    ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 &= 0xEFFFFFFF;
    ((S_80172FC0_4 *)arg2)->unk_12 = ((S_80172FC0_0 *)arg0)->unk_B8;
    ((S_80172FC0_4 *)arg2)->unk_0C.at00.v = ((S_80172FC0_0 *)arg0)->unk_B4;
    ((S_80172FC0_4 *)arg2)->unk_10 = ((S_80172FC0_0 *)arg0)->unk_BA;
    ((S_80172FC0_5 *)arg1_s4)->unk_14 = 0;
    ((S_80172FC0_5 *)arg1_s4)->unk_10 = 0;
    ((S_80172FC0_5 *)arg1_s4)->unk_0C = 0;
    func_800A2B04(arg1_s4, ((S_80172FC0_4 *)arg2)->unk_24, ((S_80172FC0_4 *)arg2)->unk_25);
    ((S_80172FC0_0 *)arg0)->unk_98 &= 0xFFF7;
    ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 |= 0x40000000;
    if (((S_80172FC0_4 *)arg2)->unk_2C != D_80176460) {
        s32 index;

        (*(void * *)((u8 *)arg2 + 0x2C)) = D_80176460;
        index = ((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7;
        func_80047784(arg2, D_80176460[index], 0);
    }
    {
        u8 *global;

        global = D_80083460;
        if (((S_80172FC0_8 *)global)->unk_0C != 0) {
            return;
        }
        ((S_80172FC0_8 *)global)->unk_0A--;
    }
    ((S_80172FC0_0 *)arg0)->unk_8C = D_80171094;
    ((S_80172FC0_4 *)arg2)->unk_1E = 0x1000;
    ((S_80172FC0_4 *)arg2)->unk_1C = 0x1000;
    func_800A4ACC(arg3);
    ((Rec_D_800E3D7C *)arg3)->unk_73.as_s8 = 0;
    ((Rec_D_800E3D7C *)arg3)->unk_72.as_s8 = 0;
    ((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8--;
    ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v &= 0x7FFF;
    func_800A56E0(0xB4);
}
