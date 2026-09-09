#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern int D_800814A8[4];
extern u8 D_80083498[];
extern u8 D_80082E80[];
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern u16 D_80082E94;
extern s32 D_80083460[3];
extern s32 D_800814A0[3];
extern void *D_80024008[];
s32 func_8003DE58();     /* extern */
u8 *func_8003FD64();                   /* extern */
M2C_UNK func_8004491C();             /* extern */
M2C_UNK func_8009CE1C(); /* extern */
void *func_800A3F28();           /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern M2C_UNK D_80024440;
extern M2C_UNK D_8002466C;
extern M2C_UNK D_80024B48;
extern M2C_UNK D_80024C14;

typedef struct S_func_819B2800_0 {
    void *unk_00;
    u16 *unk_04;
    u8 unk_08;
    u8 unk_09;
    union { s16 unk_0A; u16 unk_A; } unk_0A;
    u8 pad_0C[0x44];
    u16 unk_50;
    union { s16 unk_052; u16 unk_52; } unk_52;
} S_func_819B2800_0;

typedef struct S_func_819B2800_1 {
    s32 unk_00;
    s32 unk_04;
    union {
        s32 unk_08;
        struct { u8 pad_08[2]; u16 unk_0A; } unk_0A;
    } unk_08;
} S_func_819B2800_1;

typedef struct S_func_819B2800_2 {
    u8 pad_00[0x10];
    M2C_UNK *unk_10;
    u8 pad_14[0xC];
    void *unk_20;
    u8 pad_24[6];
    s16 unk_2A;
} S_func_819B2800_2;

typedef struct S_func_819B2800_3 {
    u8 pad_00[8];
    void *unk_08;
    void *unk_0C;
    u8 pad_10[0x14];
    u8 unk_24;
    u8 unk_25;
} S_func_819B2800_3;

typedef struct S_func_819B2800_4 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
    u16 unk_10;
    u8 pad_12[0xA];
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
} S_func_819B2800_4;

typedef struct S_func_819B2800_5 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x7A];
    u16 unk_A6;
    u8 unk_A8;
    u8 pad_A9[0x4B];
    s32 unk_F4;
    u8 pad_F8[0xA];
    s8 unk_102;
} S_func_819B2800_5;

typedef struct S_func_819B2800_6 {
    u8 pad_00[8];
    s32 unk_08;
} S_func_819B2800_6;

typedef struct S_func_819B2800_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_func_819B2800_7;

typedef struct S_func_819B2800_8 {
    u16 unk_00;
} S_func_819B2800_8;

#ifdef __mips__
/* Existing-identity DATA-BANK composite: the row owns these seven retail words;
 * the C body begins at the true interior entry 0x819B281C. */
static const u32 bank_words[] __asm__("func_80024000")
    __attribute__((section(".text.func_80024000"), aligned(4))) = {
    0x8002401C, 0x00000000, 0x80024080, 0x800240E8,
    0x800241E8, 0x80024224, 0x80024310
};
__asm__(".globl func_80024000\n.type func_80024000,@function\n.size func_80024000,1088\n");
#define BODY_NAME composite_body
#define BODY_STORAGE static
#define BODY_ATTR __attribute__((used, section(".text.func_80024000")))
#else
#define BODY_NAME func_80024000
#define BODY_STORAGE
#define BODY_ATTR
#endif

BODY_STORAGE void BODY_NAME(S_func_819B2800_0 *arg0, S_func_819B2800_1 *arg1) BODY_ATTR;
BODY_STORAGE void BODY_NAME(S_func_819B2800_0 *arg0, S_func_819B2800_1 *arg1) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    s16 sp20[3];
    u16 temp_counter;
    u16 temp_state;
    M2C_UNK var_a0;
    s16 temp_v0_3;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 var_s0;
    S_func_819B2800_4 *temp_s0;
    u8 *var_a0_2;
    S_func_819B2800_6 *temp_a1;
    S_func_819B2800_5 *global_obj;
    S_func_819B2800_7 *global_state;
    S_func_819B2800_2 *temp_s1;
    S_func_819B2800_3 *temp_s2;

    temp_state = ((volatile S_func_819B2800_0 *) arg0)->unk_50;
    temp_s1 = ((volatile S_func_819B2800_0 *) arg0)->unk_00;
    temp_v1 = arg0->unk_0A.unk_0A;
    arg0->unk_50 = (u16) (temp_state - 1);
    temp_s2 = (S_func_819B2800_3 *) ((u8 *) temp_s1 - 0x20);
    if ((u32) temp_v1 >= 5U) {
        goto block_36;
    }
    (void)jt_keep; goto *D_80024008[(u32)(temp_v1)];
jt_c0:
    ((S_func_819B2800_5 *) ((s32*)&D_800814A8)[0])->unk_102 = 1;
    ((S_func_819B2800_5 *) ((s32*)&D_800814A8)[0])->unk_F4 = 0;
    arg1->unk_00 = (s32) ((S_func_819B2800_1 *) temp_s2->unk_08)->unk_00;
    arg1->unk_04 = (s32) ((S_func_819B2800_1 *) temp_s2->unk_08)->unk_04;
    arg1->unk_08.unk_08 = (s32) ((S_func_819B2800_1 *) temp_s2->unk_08)->unk_08.unk_08;
    arg0->unk_0A.unk_0A = (s16) ((u16) arg0->unk_0A.unk_0A + 1);
jt_c1:
    if (!(*arg0->unk_04 & 0x80)) {
        goto block_36;
    }
    global_obj = (void *) ((s32*)&D_800814A8)[0];
    arg0->unk_50 = 0xAU;
    global_obj->unk_A6 = (u16) (global_obj->unk_A6 - 1);
    global_obj->unk_A8 = (u8) arg0->unk_08;
    temp_s1 = (S_func_819B2800_2 *) func_8003FD64(0x302, D_80083498);
    if (temp_s1 == NULL) {
        goto block_8;
    }
    temp_a1 = temp_s2->unk_0C;
    if (func_8003DE58(temp_a1->unk_08, temp_a1, sp20, 0) != 0) {
        goto block_7;
    }
    sp20[2] = 0;
    sp20[1] = 0;
    sp20[0] = 0;
block_7:
    temp_s0 = (S_func_819B2800_4 *) ((u8 *) temp_s1 + 0x20);
    temp_s1->unk_10 = &D_8002466C;
    func_8004491C(temp_s1, &D_80024440);
    temp_v1_2 = ((S_func_819B2800_1 *) temp_s2->unk_08)->unk_00 + (sp20[0] << 0x10);
    arg1->unk_00 = temp_v1_2;
    temp_s0->unk_1C = temp_v1_2;
    temp_v1_3 = ((S_func_819B2800_1 *) temp_s2->unk_08)->unk_04 + (sp20[1] << 0x10);
    arg1->unk_04 = temp_v1_3;
    temp_s0->unk_20 = temp_v1_3;
    temp_v1_4 = ((S_func_819B2800_1 *) temp_s2->unk_08)->unk_08.unk_08 + (sp20[2] << 0x10);
    arg1->unk_08.unk_08 = temp_v1_4;
    temp_s0->unk_24 = temp_v1_4;
    temp_s1->unk_20 = arg0;
block_8:
    temp_counter = arg0->unk_0A.unk_A;
    temp_counter++;
    goto block_store_counter;
jt_c2:
    if ((s16) arg0->unk_50 > 0) {
        goto block_36;
    }
    if (func_80053EF0(4) != 2) {
        var_a0 = 0x300;
    } else {
        var_a0 = 0x4300;
    }
    func_800A56E0(var_a0);
    temp_counter = arg0->unk_0A.unk_A;
    temp_v1 = 0xD;
    goto block_state_increment;
jt_c3:
    if ((s16) arg0->unk_50 != 2) {
        goto block_17;
    }
    func_800419EC(0x18, 0x10);
block_17:
    if ((s16) arg0->unk_50 > 0) {
        goto block_36;
    }
    temp_s1 = (S_func_819B2800_2 *) func_8003FD64(0x302, D_80083498);
    var_a0_2 = (u8 *) temp_s1;
    if (temp_s1 == NULL) {
        goto block_20;
    }
    temp_s0 = (S_func_819B2800_4 *) ((u8 *) temp_s1 + 0x20);
    temp_s1->unk_10 = &D_80024B48;
    func_8004491C(var_a0_2, &D_80024C14);
    var_a0_2 = D_80082E80;
    temp_v0_3 = ((u16) ((S_func_819B2800_5 *) ((s32*)&D_800814A8)[0])->unk_2A >> 9) & 7;
    sp20[0] = temp_v0_3;
    temp_s0->unk_0C = (s16) (((S_func_819B2800_3 *) D_80082E80)->unk_24 + D_8006CCD8[temp_v0_3]);
    temp_s0->unk_0E = (s16) (((S_func_819B2800_3 *) D_80082E80)->unk_25 + D_8006CCE8[sp20[0]]);
    temp_s0->unk_10 = (u16) arg1->unk_08.unk_0A.unk_0A;
    temp_s1->unk_20 = arg0;
block_20:
    temp_counter = arg0->unk_0A.unk_A;
    temp_v1 = 0x10;
block_state_increment:
    arg0->unk_50 = temp_v1;
    temp_counter++;
block_store_counter:
    arg0->unk_0A.unk_A = temp_counter;
    goto block_36;
jt_c4:
    if ((s16) arg0->unk_50 != 8) {
        goto block_30;
    }
    var_s0 = ((s32*)&D_800814A8)[0];
    arg1 = (void *) var_s0;
    if (var_s0 == 0) {
        goto block_30;
    }
    temp_s2 = (S_func_819B2800_3 *) D_80082E80;
loop_25:
    var_s0 = func_800A3F28(temp_s2->unk_24, temp_s2->unk_25, arg1, (void *) var_s0);
    if (var_s0 == 0) {
        goto block_30;
    }
    if (((S_func_819B2800_5 *) var_s0)->unk_1C & 0x2000) {
        goto loop_25;
    }
    func_8009CE1C((void *) var_s0, 0x10, arg0->unk_09, 0xC, (s32) temp_s1->unk_2A, temp_s1, 2);
    goto loop_25;
block_30:
    if (D_80082E94 & 0x8000) {
        goto block_32;
    }
    if ((s16) arg0->unk_50 >= 0) {
        goto block_36;
    }
block_32:
    if (!(arg0->unk_52.unk_052 & 0x8000)) {
        goto block_35;
    }
    arg0->unk_52.unk_52 = (u16) (arg0->unk_52.unk_52 & 0x7FFF);
    goto block_36;
block_35:
    global_state = (S_func_819B2800_7 *) D_80083460;
    global_state->unk_0C = 0;
    global_state->unk_0A = (u16) (global_state->unk_0A - 1);
    ((S_func_819B2800_8 *) ((u8 *) arg0 - 2))->unk_00 = (u16) (((S_func_819B2800_8 *) ((u8 *) arg0 - 2))->unk_00 | 0x8000);
    D_800814A0[0] |= 0x8000;
block_36:
    return;
}
