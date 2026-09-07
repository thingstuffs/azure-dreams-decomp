#include "common.h"
#include "records/Rec_D_80016000.h"

typedef struct S_80170F6C_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0xA];
    u16 unk_A6;
    union { s16 s; u16 u; } unk_A8;   /* accessed as both */
    u16 unk_AA;
} S_80170F6C_0;   /* arg0 in func_80170F6C */

typedef struct S_80170F6C_1 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x4];
    u16 unk_6A;
    u8 pad_6C[0x1];
    s8 unk_6D;
} S_80170F6C_1;   /* arg3 in func_80170F6C */

typedef struct S_80170F6C_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80170F6C_2;   /* arg2 in func_80170F6C */

typedef struct S_80170F6C_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    u32 unk_08;
    s32 unk_0C;
    s32 unk_10;
} S_80170F6C_3;   /* arg1 in func_80170F6C */

typedef struct S_80170F6C_4 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xA6];
    u8 unk_BA;
} S_80170F6C_4;   /* object in func_80170F6C */

typedef struct S_80170F6C_5 {
    s32 unk_00;
    s32 unk_04;
    u32 unk_08;
} S_80170F6C_5;   /* payload in func_80170F6C */

typedef struct S_80170F6C_6 {
    void * unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x2];
    u32 unk_08;
    u32 unk_0C;
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_80170F6C_6;   /* part in func_80170F6C */


typedef struct S_80170F6C_8 {
    u8 pad_00[0x58];
    void * unk_58;
} S_80170F6C_8;   /* D_800814A8[0] in func_80170F6C */

typedef struct S_80170F6C_9 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80170F6C_9;   /* map_base in func_80170F6C */

typedef struct S_80170F6C_10 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80170F6C_10;   /* status_object in func_80170F6C */



typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A1C58(void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern s32 func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);

extern void func_80171434(void) __attribute__((noreturn));
extern void func_8017143C(void) __attribute__((noreturn));
extern void func_80171704(void) __attribute__((noreturn));
extern void func_801718B4(void) __attribute__((noreturn));
extern void func_801718EC(void) __attribute__((noreturn));
extern void func_80171910(void);
extern void func_80171B68(void *, void *, void *, void *);
extern s32 func_80172314(void *, void *, void *, void *);
extern void func_80172514(void *, void *, void *, void *);
extern s32 func_80172658(void *, void *, void *, s32);
extern void func_80174250(void *, void *, void *, void *);

extern u8 D_80045340[];
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern void *D_800814A8[3];
extern u8 D_80082E80[];
extern s8 D_80082EA4[16];
extern s16 D_80083228[5];
extern u16 D_80083460[];
extern u16 D_80083462[5];
extern u8 D_80083498[];
extern u8 D_800DEA68[];
extern DungeonRecord D_800E2970[];
extern u8 D_80175174[];
extern u8 D_80175258[];
extern u8 D_80175260[];
extern u8 D_80175290[];
extern u8 D_80175298[];
extern u8 D_801752A0[];
extern void *D_80170808[];
extern void *D_80170820[];

void func_80170F6C(void *in_arg0, void *in_arg1, void *in_arg2, void *in_arg3)
{
    static void *const sw_keep[] = {
        &&sw_case123, &&sw_generic, &&sw_case89,
        &&sw_case567, &&sw_case12
    };
    static void *const sw1_keep[] = {
        &&sw1_case0, &&sw1_case1, &&sw1_case2,
        &&sw1_case3, &&sw1_case4
    };
    u16 initial_flags = D_80083462[0];
    s32 scratch;
    s8 result;
    void *arg0 = in_arg0;
    void *arg1 = in_arg1;
    void *arg2 = in_arg2;
    void *arg3 = in_arg3;

    if (initial_flags & 0x1000) {
        ((S_80170F6C_0 *)arg0)->unk_9A = 0xE;
        func_80171910();
        func_801718EC();
    }

    ASM_KEEP(arg0);   /* MATCH pin: load-bearing for the whole function shape */
       /* MATCH pin: retail schedule: same instructions, different order without it */
       /* MATCH pin: load-bearing for the whole function shape */

    if (((S_80170F6C_1 *)arg3)->unk_25 == 0) {
        func_800AA79C(arg0, arg1, arg2, arg3);
        {
            register void *current ASM_REG("$3") =
                ((S_80170F6C_2 *)arg2)->unk_2C;
            register u8 *page ASM_REG("$2") = (u8 *)0x80170000;   /* MATCH pin: keeps a constant in a register as retail does */
            register void *table ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
            ASM_KEEP(current);   /* MATCH pin: retail basic-block layout depends on it */
            ASM_KEEP(page);   /* MATCH pin: keeps a constant in a register as retail does */
            table = page + 0x5298;
            ASM_TAILSLOT_PIN(table);   /* MATCH pin: retail delay-slot contents depend on it */
            func_801718B4();
        }
    }

    if (((S_80170F6C_1 *)arg3)->unk_1C & 0x200) {
        if (((S_80170F6C_2 *)arg2)->unk_2C == D_80175298) {
            ((S_80170F6C_0 *)arg0)->unk_9A = 0xD;
            ((S_80170F6C_0 *)arg0)->unk_9B = 1;
            ((S_80170F6C_0 *)arg0)->unk_8C = 0;
            ((S_80170F6C_1 *)arg3)->unk_1C &= ~0x40000;
            func_801718EC();
        }
        if (func_800AA924(arg0, arg1, arg2, D_80175298) != 0) {
            return;
        }
    }

    if (!(D_80083462[0] & 0x2000)) {
        if (((S_80170F6C_1 *)arg3)->unk_1C & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            func_801718EC();
        }

        {
            register u32 state ASM_REG("$16");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
            u32 current_state = ((S_80170F6C_0 *)arg0)->unk_9A;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
            state = 0xE;
            if (current_state != state) {
                if (((S_80170F6C_2 *)arg2)->unk_2C != D_80175258) {
                    ((S_80170F6C_2 *)arg2)->unk_2C = D_80175258;
                    func_80047784(arg2,
                        D_80175258[((D_80083228[0] + ((S_80170F6C_1 *)arg3)->unk_2A.s + 0x100) >> 9) & 7],
                        0);
                }
                ((S_80170F6C_0 *)arg0)->unk_9A = state;
            }
        }

        if (((S_80170F6C_1 *)arg3)->unk_14 & 0x20000) {
            {
                s32 switch_index = ((S_80170F6C_0 *)arg0)->unk_A8.s;
                if ((u32)switch_index >= 5) {
                    goto epilogue;
                }
                (void)sw1_keep;
                {
                    void **switch_table = D_80170808;
                    goto *switch_table[switch_index];
                }
            }
sw1_case0:
                if (((S_80170F6C_2 *)arg2)->unk_2C != D_801752A0) {
                    D_80083460[5]++;
                    ((S_80170F6C_0 *)arg0)->unk_AA = ((S_80170F6C_1 *)arg3)->unk_2A.u;
                    ((S_80170F6C_1 *)arg3)->unk_2A.s =
                        (((S_80170F6C_1 *)arg3)->unk_6A + 0x800) & 0xFFF;
                    ((S_80170F6C_2 *)arg2)->unk_14 &= 0x9FFF;
                    ((S_80170F6C_0 *)arg0)->unk_A6 = 300;
                }
                {
                    u32 tail_state =
                        ((S_80170F6C_0 *)arg0)->unk_A8.u;
                    tail_state += 1;
                    ASM_TAILSLOT_PIN_TIED(tail_state);   /* MATCH pin: retail delay-slot fill depends on it */
                    func_8017143C();
                }

sw1_case1: {
                u16 timer = ((S_80170F6C_0 *)arg0)->unk_A6 - 1;

                ((S_80170F6C_0 *)arg0)->unk_A6 = timer;
                if (((s32)timer << 16) <= 0 ||
                    ((S_80170F6C_1 *)arg3)->unk_64 != 0) {
                    D_80083460[5]--;
                    ((S_80170F6C_3 *)arg1)->unk_10 = 0;
                    ((S_80170F6C_3 *)arg1)->unk_0C = 0;
                    func_800A2B04(arg1,
                        ((S_80170F6C_2 *)arg2)->unk_24.at00.v, ((S_80170F6C_2 *)arg2)->unk_24.at01.v);
                    ((S_80170F6C_1 *)arg3)->unk_14 &= ~0x20000;
                    ((S_80170F6C_0 *)arg0)->unk_A8.u = 0;
                    func_801718EC();
                }
                if (((S_80170F6C_1 *)arg3)->unk_14 & 0x1000000) {
                    ((S_80170F6C_0 *)arg0)->unk_A8.u++;
                    ((S_80170F6C_2 *)arg2)->unk_2C = D_801752A0;
                    func_80047784(arg2,
                        D_801752A0[((D_80083228[0] + ((S_80170F6C_1 *)arg3)->unk_2A.s + 0x100) >> 9) & 7],
                        0);
                    ((S_80170F6C_0 *)arg0)->unk_A6 = 0;
                    func_801718EC();
                }
                goto epilogue;
            }

sw1_case2: {
                s32 scale;
                S_80170F6C_4 *object;
                void *part;
                void *payload;
                u32 color;
                u32 payload_word;
                u32 texture_word;

                ((S_80170F6C_3 *)arg1)->unk_0C =
                    D_8006CCD8[((s32)(((S_80170F6C_1 *)arg3)->unk_6A << 16)) >> 25] << 16;
                ((S_80170F6C_3 *)arg1)->unk_10 =
                    D_8006CCE8[((s32)(((S_80170F6C_1 *)arg3)->unk_6A << 16)) >> 25] << 16;
                scale = func_800644B8((s16)((S_80170F6C_0 *)arg0)->unk_A6 << 8);
                ((S_80170F6C_3 *)arg1)->unk_0C = ((S_80170F6C_3 *)arg1)->unk_0C +
                    (((S_80170F6C_3 *)arg1)->unk_0C * scale >> 9);
                scale = func_800644B8((s16)((S_80170F6C_0 *)arg0)->unk_A6 << 8);
                ((S_80170F6C_3 *)arg1)->unk_10 = ((S_80170F6C_3 *)arg1)->unk_10 +
                    (((S_80170F6C_3 *)arg1)->unk_10 * scale >> 9);

                object = func_8003FD64(0x312, D_80083498);
                if (object != 0) {
                    func_8004491C(object, D_80045340);
                    payload = object->unk_08;
                    object->unk_10 = D_80175174;
                    part = object->unk_0C;
                    ((S_80170F6C_5 *)payload)->unk_00 = ((S_80170F6C_3 *)arg1)->unk_00.at00.v;
                    payload = object->unk_08;
                    ((S_80170F6C_5 *)payload)->unk_04 = ((S_80170F6C_3 *)arg1)->unk_04.at00.v;
                    payload = object->unk_08;
                    payload_word = ((S_80170F6C_3 *)arg1)->unk_08;
                    ASM_KEEP(payload_word);   /* MATCH pin: retail schedule: same instructions, different order without it */
                    color = 0x00800000;
                    ASM_KEEP(color);   /* MATCH pin: keeps a statement from moving across a call/branch */
                    ((S_80170F6C_5 *)payload)->unk_08 = payload_word;
                    ((S_80170F6C_6 *)part)->unk_1E = 0x1000;
                    ((S_80170F6C_6 *)part)->unk_1C = 0x1000;
                    ((S_80170F6C_6 *)part)->unk_10 = 0;
                    ((S_80170F6C_6 *)part)->unk_00 = D_800DEA68;
                    ((S_80170F6C_6 *)part)->unk_14 |= 0xC;
                    texture_word = ((Rec_D_80016000 *)D_800DEA68)->unk_04.at00_u32.v;
                    color |= 0x8080;
                    ((S_80170F6C_6 *)part)->unk_04 = 0;
                    ((S_80170F6C_6 *)part)->unk_05 = 0;
                    ((S_80170F6C_6 *)part)->unk_0C = color;
                    ((S_80170F6C_6 *)part)->unk_08 = texture_word;
                    object->unk_BA = 0;
                }

                {
                    u16 old_timer = ((S_80170F6C_0 *)arg0)->unk_A6;
                    ((S_80170F6C_0 *)arg0)->unk_A6 = old_timer + 1;
                    if ((s16)old_timer >= 3) {
                    ((S_80170F6C_2 *)arg2)->unk_14 &= 0xF7FF;
                    ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
                    ((S_80170F6C_3 *)arg1)->unk_10 = 0;
                    ((S_80170F6C_3 *)arg1)->unk_0C = 0;
                    {
                        u32 tail_value =
                            ((S_80170F6C_0 *)arg0)->unk_A8.u;
                        u32 tail_code = 4;
                        ASM_KEEP(tail_value);   /* MATCH pin: retail delay-slot fill depends on it */
                        ASM_TAILSLOT_PIN_TIED(tail_code);   /* MATCH pin: retail delay-slot contents depend on it */
                        func_80171434();
                    }
                }
                }
                goto epilogue;
            }

sw1_case3: {
                u16 timer = ((S_80170F6C_0 *)arg0)->unk_A6 - 1;

                ((S_80170F6C_0 *)arg0)->unk_A6 = timer;
                if (((s32)timer << 16) <= 0) {
                    ((S_80170F6C_2 *)arg2)->unk_14 &= 0xF7FF;
                    ((S_80170F6C_3 *)arg1)->unk_10 = 0;
                    ((S_80170F6C_3 *)arg1)->unk_0C = 0;
                    ((S_80170F6C_0 *)arg0)->unk_A6 = 3;
                    ((S_80170F6C_0 *)arg0)->unk_A8.u++;
                    func_801718EC();
                }
                goto epilogue;
            }

sw1_case4: {
                s32 x;
                s32 y;
                s32 coord;
                s32 delta;
                u16 timer;

                coord = ((S_80170F6C_2 *)arg2)->unk_24.at00.v << 6;
                delta = ((S_80170F6C_3 *)arg1)->unk_00.at02.v - 0x20;
                ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
                x = coord - delta;
                ((S_80170F6C_3 *)arg1)->unk_0C = (s32)((u32)x << 15) >> 1;
                coord = ((S_80170F6C_2 *)arg2)->unk_24.at01.v << 6;
                delta = ((S_80170F6C_3 *)arg1)->unk_04.at02.v - 0x20;
                y = coord - delta;
                ((S_80170F6C_3 *)arg1)->unk_10 = (s32)((u32)y << 15) >> 1;
                timer = ((S_80170F6C_0 *)arg0)->unk_A6 - 1;
                ((S_80170F6C_0 *)arg0)->unk_A6 = timer;
                if (((s32)timer << 16) <= 0) {
                    D_80083460[5]--;
                    ((S_80170F6C_3 *)arg1)->unk_10 = 0;
                    ((S_80170F6C_3 *)arg1)->unk_0C = 0;
                    func_800A2B04(arg1,
                        ((S_80170F6C_2 *)arg2)->unk_24.at00.v, ((S_80170F6C_2 *)arg2)->unk_24.at01.v);
                    ((S_80170F6C_1 *)arg3)->unk_14 &= ~0x20000;
                    ((S_80170F6C_1 *)arg3)->unk_2A.s = ((S_80170F6C_0 *)arg0)->unk_AA;
                    ((S_80170F6C_2 *)arg2)->unk_2C = D_80175258;
                    func_80047784(arg2,
                        D_80175258[((D_80083228[0] + ((S_80170F6C_1 *)arg3)->unk_2A.s + 0x100) >> 9) & 7],
                        0);
                    ((S_80170F6C_0 *)arg0)->unk_A8.u = 0;
                    func_801718EC();
                }
                goto epilogue;
            }
        } else {
            ((S_80170F6C_0 *)arg0)->unk_98 &= 0xFFF3;
            if (((S_80170F6C_1 *)arg3)->unk_64 == 0 ||
                func_800AA6B4(arg0, arg1, arg2, D_80175260) == 0) {
                if (((S_80170F6C_1 *)arg3)->unk_1C & 0x80000) {
                    func_800AA888(arg0, arg1, arg2, arg3);
                    func_80174250(arg0, arg1, arg2, arg3);
                    func_801718EC();
                }
                if ((func_800A1C58(arg3) << 16) != 0) {
                    func_800AAB10(arg0, arg1, arg2, arg3);
                }
            } else {
                return;
            }
        }
    }

    result = func_8009FB34(((S_80170F6C_2 *)arg2)->unk_24.at00.v, ((S_80170F6C_2 *)arg2)->unk_24.at01.v);
    ((S_80170F6C_2 *)arg2)->unk_26 = result;

    if (((S_80170F6C_1 *)arg3)->unk_6D > 0) {
        if (((S_80170F6C_1 *)arg3)->unk_1C & 0x20) {
            goto sw_case12;
        }
        if (((S_80170F6C_2 *)arg2)->unk_24.at00u.v == *(u16 *)&D_80082EA4[0]) {
            goto sw_generic;
        }
        if (!(((S_80170F6C_1 *)arg3)->unk_46 & 0x8000)) {
            if ((D_80083462[0] & 0x2000) &&
                ((func_8009A180(arg3,
                    (u8 *)((S_80170F6C_8 *)(D_800814A8[0]))->unk_58 + 0x20) << 16) != 0)) {
                return;
            }
            if ((func_80172658(arg0, arg1, arg2, 0) << 16) == 0) {
                return;
            }
            ((S_80170F6C_1 *)arg3)->unk_46 |= 0x4000;
            if (!(((S_80170F6C_1 *)arg3)->unk_46 & 0x8000)) {
                goto sw_generic;
            }
        }

        {
            u32 swi = (((S_80170F6C_1 *)arg3)->unk_46 & 0x3FFF) - 1;

            if (swi >= 12) {
                goto sw_generic;
            }
            (void)sw_keep;
            {
                void **switch_table = D_80170820;
                goto *switch_table[swi];
            }
        }

sw_case89:
        if ((((S_80170F6C_1 *)arg3)->unk_46 & 0x3FFF) == 9) {
            u32 case_flags;

            case_flags = ((S_80170F6C_0 *)arg0)->unk_98;
            case_flags |= 0x8000;
            ASM_TAILSLOT_PIN_TIED(case_flags);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            func_80171704();
        }
        ((S_80170F6C_0 *)arg0)->unk_98 &= 0x7FFF;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
        if ((func_80172314(arg0, arg1, arg2, arg3) << 16) != 0) {
            return;
        }
        func_80172514(arg0, arg1, arg2, arg3);
        func_801718EC();

sw_case567:
        {
            s16 next_position;
            void *status_object;
            u8 *map_base = D_80082E80;

            next_position = func_800A0818(
            ((S_80170F6C_2 *)arg2)->unk_24.at00.v, ((S_80170F6C_2 *)arg2)->unk_24.at01.v,
            ((S_80170F6C_9 *)map_base)->unk_24, ((S_80170F6C_9 *)map_base)->unk_25,
            &scratch);
            status_object = D_800814A8[0];
            ((S_80170F6C_1 *)arg3)->unk_2A.s = next_position;
            if (((S_80170F6C_10 *)status_object)->unk_9A == 0x11) {
                goto sw_case123;
            }
        }
sw_case12:
        func_800A9A0C(arg3);
        func_801718EC();

sw_case123:
        func_800AAF00(arg0, arg1, arg2, D_80175290, func_80170F6C);
        func_801718EC();

sw_generic:
        func_80171B68(arg0, arg1, arg2, arg3);
        func_801718EC();
    }

    {
        u32 final_flags =
            ((S_80170F6C_1 *)arg3)->unk_1C;
        if (!(final_flags & 0x2000)) {
            if ((result < 0) || !(D_800E2970[result].flags & 2)) {
                u32 final_mask =
                    final_flags & 0x430;
                if (!final_mask) {
                u8 *map_base = D_80082E80;

                if ((func_8009FD7C(
                        ((S_80170F6C_2 *)arg2)->unk_24.at00.v, ((S_80170F6C_2 *)arg2)->unk_24.at01.v,
                        ((S_80170F6C_9 *)map_base)->unk_24, ((S_80170F6C_9 *)map_base)->unk_25) << 16) != 0) {
                    ((S_80170F6C_1 *)arg3)->unk_2A.s = func_800A0818(
                        ((S_80170F6C_2 *)arg2)->unk_24.at00.v, ((S_80170F6C_2 *)arg2)->unk_24.at01.v,
                        ((S_80170F6C_9 *)map_base)->unk_24, ((S_80170F6C_9 *)map_base)->unk_25,
                        &scratch);
                }
            }
        }
    }
    }

    if (!(D_80083462[0] & 0x2000) &&
        !(((S_80170F6C_2 *)arg2)->unk_14 & 0x40)) {
        void *post_current =
            ((S_80170F6C_2 *)arg2)->unk_2C;
        u8 *post_page = (u8 *)0x80170000;
        u8 *post_table;
        ASM_KEEP(post_page);   /* MATCH pin: keeps a constant in a register as retail does */
        post_table = post_page + 0x5258;
        if (post_current != post_table) {
            u32 post_index;

            ((S_80170F6C_2 *)arg2)->unk_2C = post_table;
            post_index = ((D_80083228[0] +
                ((S_80170F6C_1 *)arg3)->unk_2A.s + 0x100) >> 9) & 7;
            func_80047784(arg2,
                *(u8 *)((unsigned long)post_index +
                    (unsigned long)post_table),
                0);
        }
    }

epilogue:
    return;
}
