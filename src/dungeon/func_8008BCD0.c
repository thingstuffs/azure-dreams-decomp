#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082EB0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_800E296C[3];
extern void *D_8008ACDC[];
extern void *D_8008EAC8[];
struct S_8003E2D8; typedef struct S_8003E2D8 S_8003E2D8;
extern struct S_8003E2D8 D_80083160;
extern volatile s32 D_80082EB0[];
extern s16 D_800DCE66[5];
extern s32 D_800E4940[];
extern u8 D_8004F5F4[];
M2C_UNK func_8004DD2C();                     /* extern */
s32 func_8009074C();                /* extern */
M2C_UNK func_80091500();                   /* extern */
M2C_UNK func_80091628();                            /* extern */
M2C_UNK func_80091708(); /* extern */
M2C_UNK func_80091714(); /* extern */
M2C_UNK func_80091778();                            /* extern */
M2C_UNK func_80091860();                            /* extern */
M2C_UNK func_800918A0();                       /* extern */
M2C_UNK func_800918F8();                       /* extern */
M2C_UNK func_800918FC();                       /* extern */
s32 func_8009402C(); /* extern */
s32 func_80094208();                         /* extern */
M2C_UNK func_800997FC();                   /* extern */
M2C_UNK func_8009F644();   /* extern */
M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_800B0F50();                      /* extern */
s32 func_800B9964();                          /* extern */
M2C_UNK func_800BA810();                 /* extern */
M2C_UNK func_800C77D0();   /* extern */
extern u8 D_80012D6D;
extern M2C_UNK D_8001EF2C;
extern M2C_UNK D_80023C58;
extern M2C_UNK D_80088904;
extern M2C_UNK D_80088934;
extern M2C_UNK D_80088970;
extern M2C_UNK D_800E0040;
extern M2C_UNK D_800E2004;


typedef struct S_80091430_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_80091430_0;   /* dungeon_state in func_80091430 */

typedef struct S_80091430_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x6A];
    s16 unk_8A;
} S_80091430_1;   /* actor in func_80091430 */

typedef struct S_80091430_2_pre {
    s32 unk_00;
    u8 pad_04[0x14];
} S_80091430_2_pre;   /* the 0x18 bytes before temp_t0 in func_80091430, addressed as temp_t0[-1] */


typedef struct S_80091430_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_80091430_4;   /* temp_a0 in func_80091430 */

typedef struct S_80091430_5 {
    u8 pad_00[0x46];
    u16 unk_46;
} S_80091430_5;   /* temp_a0_2 in func_80091430 */

typedef struct S_80091430_6 {
    u8 pad_00[0x46];
    u16 unk_46;
} S_80091430_6;   /* temp_v1_2 in func_80091430 */

typedef struct S_80091430_7 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80091430_7;   /* (*(void **)((u8 *)arg0 + 0x104)) in func_80091430 */

void func_80091430(void *arg0, M2C_UNK arg1, M2C_UNK arg2, void *arg3) {
    S_80091430_1 *actor = arg3;
    S_8003E2D8 *dungeon_state = &D_80083160;
    s16 sp18;
    s16 sp1A;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s32 temp_a2;
    s32 temp_v0;
    s32 temp_v1_3;
    s32 temp_v1;
    void **var_a0;
    S_80091430_4 *temp_a0;
    S_80091430_5 *temp_a0_2;
    void *temp_t0;
    S_80091430_6 *temp_v1_2;

    temp_v1 = (*(u8 *)((u8 *)arg0 + 0x9B));
    if (temp_v1 == 1) {
        goto block_16;
    }
    if (temp_v1 < 2) {
        if (temp_v1 != 0) {
            func_800918FC();
            return;
        }
    } else {
        s32 dispatch_v0;

        ASM_USE(arg0);   /* MATCH pin: retail delay-slot fill depends on it */
        dispatch_v0 = 2;
        if (temp_v1 == dispatch_v0) {
            goto block_case_2;
        }
        func_800918FC();
        return;
    }
    {
        temp_v0 = func_800B9964(arg0 + 0x104);
        (*(s32 *)((u8 *)arg0 + 0xC8)) = temp_v0;
        if (temp_v0 != 0) {
            func_8004DCE0(2);
            func_8004DCEC();
            if ((*(s16 *)((u8 *)arg0 + 0x120)) == 0) {
                if (D_80012D6D == 0) {
                    ASM_USE(arg0);   /* MATCH pin: retail delay-slot fill depends on it */
                    func_80091500(&D_80088904);
                    return;
                }
                ASM_USE(arg0);   /* MATCH pin: retail delay-slot fill depends on it */
                func_80091500(&D_80088934);
                return;
            }
            {
                register void *call_a0 ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */

                call_a0 = &D_80088970;
                ASM_KEEP(call_a0);   /* MATCH pin: retail basic-block layout depends on it */
                func_8004DD2C();
            }
            (*(u8 *)((u8 *)arg0 + 0x9B)) = (u8) ((*(u8 *)((u8 *)arg0 + 0x9B)) + 1);
            goto block_16;
        }
    }
    return;

block_16:
        temp_a2 = func_8009074C((*(s16 *)((u8 *)arg0 + 0x9E)), arg0 + 0xA2, (*(void **)((u8 *)arg0 + 0x104)) + 0x2A);
        temp_v0_2 = (s16) temp_a2;
        if (temp_v0_2 != 0xFFF) {
            ((S_80091430_7 *)((*(void **)((u8 *)arg0 + 0x104))))->unk_2A = temp_a2;
            func_8009F644(actor, 0x70, (s32) (*(void **)((u8 *)arg0 + 0x104)) == (*(s32 *)((u8 *)arg0 + 0xB0)), (temp_a2 << 0x10 >> 0x19) & 7);
        }
        if ((*(s16 *)((u8 *)arg0 + 0x120)) == 0) {
            temp_t0 = (*(void **)((u8 *)arg0 + 0x104));
            if (temp_t0 != NULL) {
                if (((S_80091430_0 *)dungeon_state)->unk_10 & 0x80) {
                    if ((func_80094208(0) == 0) && !(actor->unk_1C & 0x100000)) {
                        actor->unk_8A = (s16) ((s32) (*(void **)((u8 *)arg0 + 0x104)) != (*(s32 *)((u8 *)arg0 + 0xAC)));
                        D_80082EB0[0] = 0;
                        if ((func_8009402C(arg0, arg1, arg2, &sp18, &sp1A, D_80082EB0[0]) << 0x10) != 0) {
                            func_800997FC(&D_800E2004);
                            func_80091628(arg0);
                            return;
                        }
                        func_8004E130();
                        (*(s32 *)((u8 *)arg0 + 0xC8)) = 0;
                        func_8008DB0C(arg0, arg1, arg2, sp18, (s32) sp1A);
                        {
                            s32 tail_flags = D_800E296C[0];

                            (*(void **)((u8 *)arg0 + 0x104)) = NULL;
                            D_800E296C[0] = tail_flags & ~0x2000;
                        }
                        func_800918FC();
                    }
                } else {
                    if (((S_80091430_0 *)dungeon_state)->unk_10 & 0x10) {
                        register void *internal_a0 ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
                        register M2C_UNK internal_a1 ASM_REG("$5");   /* MATCH pin: retail immediate-load split depends on it */
                        register M2C_UNK internal_a2 ASM_REG("$6");   /* MATCH pin: retail immediate-load split depends on it */
                        void *internal_a3;
                        register void *internal_v0 ASM_REG("$2");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
                        register void *internal_v1 ASM_REG("$3");   /* MATCH pin: retail callee-saved set / frame layout depends on it */

                        func_800C77D0(temp_t0 - 0x20, ((S_80091430_2_pre *)temp_t0)[-1].unk_00, 8, *D_800DCE66);
                        internal_a0 = arg0;
                        internal_a1 = arg1;
                        internal_a2 = arg2;
                        internal_a3 = (void *) 0x80020000;
                        ASM_KEEP4(internal_a0, internal_a1, internal_a2, internal_a3);   /* MATCH pin: keeps a constant in a register as retail does */
                        internal_v0 = (*(void **)((u8 *)arg0 + 0x104));
                        internal_v1 = (*(void **)((u8 *)arg0 + 0xAC));
                        ASM_USE2(internal_v0, internal_v1);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                        internal_a3 = (u8 *) internal_a3 - 0x10D4;
                        ASM_TAILSLOT_PIN(internal_a3);   /* MATCH pin: load-bearing for the whole function shape */
                        func_80091708();
                        return;
                    }
                    if (((S_80091430_0 *)dungeon_state)->unk_10 & 0x20) {
                        register void *internal_a0 ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
                        register M2C_UNK internal_a1 ASM_REG("$5");   /* MATCH pin: retail immediate-load split depends on it */
                        register M2C_UNK internal_a2 ASM_REG("$6");   /* MATCH pin: retail immediate-load split depends on it */
                        register void *internal_a3 ASM_REG("$7");   /* MATCH pin: load-bearing for the whole function shape */
                        s32 internal_v0;
                        register void *internal_v1 ASM_REG("$3");   /* MATCH pin: retail callee-saved set / frame layout depends on it */

                        internal_a0 = arg0;
                        internal_a1 = arg1;
                        internal_a2 = arg2;
                        internal_a3 = &D_80023C58;
                        ASM_KEEP4(internal_a0, internal_a1, internal_a2, internal_a3);   /* MATCH pin: keeps a constant in a register as retail does */
                        internal_v0 = (s32) temp_t0 != (*(s32 *)((u8 *)arg0 + 0xAC));
                        internal_v1 = (void *) 0x800E0000;
                        ASM_USE(internal_v1);   /* MATCH pin: load-bearing for the whole function shape */
                        ASM_TAILSLOT_PIN(internal_v0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                        func_80091714();
                        return;
                    }
                    if (((S_80091430_0 *)dungeon_state)->unk_10 & 0x40) {
                        func_800C77D0(temp_t0 - 0x20, ((S_80091430_2_pre *)temp_t0)[-1].unk_00, 8, *D_800DCE66);
                        temp_v0_3 = (s32) (*(void **)((u8 *)arg0 + 0x104)) != (*(s32 *)((u8 *)arg0 + 0xAC));
                        actor->unk_8A = temp_v0_3;
                        *D_800E4940 = (s32) temp_v0_3;
                        func_8008CF6C(arg0, arg1, arg2, D_8004F5F4);
                        ((Rec_D_80082EB0 *)D_80082EB0)->unk_00.as_s32 = 0;
                        (*(s32 *)((u8 *)arg0 + 0xC8)) = 0;
                        (*(void **)((u8 *)arg0 + 0x104)) = NULL;
                        func_8004E130();
                        func_800918FC();
                        return;
                    }
                    goto block_37;
                }
            } else {
block_37:
                temp_v1_2 = (*(void **)((u8 *)arg0 + 0x104));
                if (temp_v1_2 == (*(s32 *)((u8 *)arg0 + 0xAC))) {
                    s32 internal_v0;

                    internal_v0 = ((S_80091430_0 *)dungeon_state)->unk_08 & 2;
                    ASM_TAILSLOT_PIN(internal_v0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                    func_80091778();
                    return;
                }
                if ((temp_v1_2 != (*(s32 *)((u8 *)arg0 + 0xB0))) || !(((S_80091430_0 *)dungeon_state)->unk_08 & 1)) {
                    if (((S_80091430_0 *)dungeon_state)->unk_08 & 3) {
                        var_a0 = arg0 + 0xAC;
                        if (!(((S_80091430_0 *)dungeon_state)->unk_08 & 2)) {
                            var_a0 = arg0 + 0xB0;
                        }
                        temp_a0 = *var_a0;
                        if ((temp_a0 != NULL) && ((*(void *volatile *)((u8 *)arg0 + 0x104)) != temp_a0)) {
                            temp_v1_3 = temp_a0->unk_1C;
                            if (temp_v1_3 & 0x20000) {
                                if (!(temp_v1_3 & 0x80000)) {
                                    (*(void **)((u8 *)arg0 + 0x104)) = temp_a0;
                                    func_800B0F50(temp_a0);
                                    func_800918FC();
                                }
                            }
                        }
                    } else {
                        (*(void **)((u8 *)arg0 + 0x104)) = NULL;
                        (*(u8 *)((u8 *)arg0 + 0x9B)) = (u8) ((*(u8 *)((u8 *)arg0 + 0x9B)) + 1);
                        func_800918FC();
                    }
                }
            }
        } else {
            temp_a0_2 = (*(void **)((u8 *)arg0 + 0x104));
            func_800BA810(temp_a0_2, temp_a0_2->unk_46);
            if (((S_80091430_0 *)dungeon_state)->unk_10 & 0x60) {
                if (((S_80091430_0 *)dungeon_state)->unk_10 & 0x20) {
                    func_800A56E0(0x515);
                    temp_v1_2 = (*(void **)((u8 *)arg0 + 0x104));
                    temp_v1_2->unk_46 &= 0x7FFF;
                    func_80091860();
                    return;
                }
                func_800A56E0(0x503);
                (*(void **)((u8 *)arg0 + 0x104)) = NULL;
                func_8004E130();
                D_800E296C[0] &= ~0x2000;
                if (actor->unk_1C & 0x100000) {
                    void *callback;

                    callback = D_8008EAC8;
                    ASM_TAILSLOT_PIN(callback);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                    func_800918A0();
                    return;
                } else {
                    (*(void **)((u8 *)arg0 + 0x8C)) = D_8008ACDC;
                }
                func_800BA810(NULL, 0U);
                func_800918FC();
            }
        }
    return;

block_case_2:
    (*(s32 *)((u8 *)arg0 + 0xC8)) = 0;
    func_8004E130();
    D_800E296C[0] &= ~0x2000;
    if (actor->unk_1C & 0x100000) {
        void *callback;

        callback = D_8008EAC8;
        ASM_TAILSLOT_PIN(callback);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_800918F8();
        return;
    } else {
        (*(void **)((u8 *)arg0 + 0x8C)) = D_8008ACDC;
    }
}
/* Warning: struct S_8003E2D8 is not defined (only forward-declared) */
