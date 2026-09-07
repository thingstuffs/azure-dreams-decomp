#include "common.h"
#include "m2c_compat.h"

typedef struct S_800BD5C4_0 {
    s32 unk_00;
    u8 pad_04[0x27];
    u8 unk_2B;
    s32 unk_2C;
    u8 pad_30[0x4];
    s32 unk_34;
    u8 pad_38[0xF0];
    s32 unk_128;
} S_800BD5C4_0;   /* arg0 in func_800BD5C4; pointer addresses record offset 0x18 */


M2C_UNK func_80042B68();             /* extern */
M2C_UNK func_8008D330(); /* extern */
M2C_UNK func_80098B38();                         /* extern */
s32 func_800990FC(void);                          /* extern */
s32 func_80099194();                  /* extern */
M2C_UNK func_80099290();                         /* extern */
M2C_UNK func_800A5720();                         /* extern */
M2C_UNK func_800A5F38();                 /* extern */
M2C_UNK func_800A63B8();            /* extern */
s32 func_800AD6FC();            /* extern */
void func_800BD710();                                /* extern */
M2C_UNK func_800C4AFC();            /* extern */
typedef struct {
    u8 pad[0xA];
    u16 fieldA;
} D_80083460_t;
extern M2C_UNK D_80082E80;
extern D_80083460_t D_80083460;
extern M2C_UNK D_80083780;
extern u16 D_800DDE84[];
extern M2C_UNK D_800E0E82;
extern void *D_800E3D7C[];

s32 func_800BD5C4(void *arg0, s32 arg1, s16 arg2) {
    u16 *table;
    register void *call_arg ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s32 pass_value ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    register s32 saved_value ASM_REG("$16");   /* MATCH pin: retail register colouring depends on it */
    D_80083460_t *state;
    s32 table_index;
    s32 temp_v0;
    s32 result;

    if (arg0 == D_800E3D7C[0]) {
        ((S_800BD5C4_0 *)((u8 *)arg0 - 0x18))->unk_128 = arg1;
        func_8008D330(arg0, &D_80083780, &D_80082E80, arg0);
        return 0;
    }
    if ((u32) arg0 <= 0x9FFFFFFFU) {
        func_800A63B8(arg0, arg1, arg2);
        call_arg = arg0;
        table = (u16 *)0x800E0000;
        ASM_KEEP(table);   /* MATCH pin: retail immediate-load split depends on it */
        table_index = ((S_800BD5C4_0 *)((u8 *)arg0 - 0x18))->unk_2B;
        ASM_KEEP(table_index);   /* MATCH pin: retail immediate-load split depends on it */
        table = (u16 *)((u8 *)table - 0x217C);
        ASM_KEEP(table);   /* MATCH pin: retail immediate-load split depends on it */
        if (func_800AD6FC(call_arg, (table[table_index] >> 6) & 3, 0) == 0) {
            func_800A5F38(arg0, arg1);
            return 1;
        }
        goto block_8;
    }
block_8:
    func_800C4AFC(((S_800BD5C4_0 *)((u8 *)arg0 - 0x18))->unk_00, 0xC02020, arg0);
    if ((((S_800BD5C4_0 *)((u8 *)arg0 - 0x18))->unk_2C & 0x4000) && !(((S_800BD5C4_0 *)((u8 *)arg0 - 0x18))->unk_34 & 0x400)) {
        temp_v0 = func_800990FC();
        call_arg = &D_800E0E82;
        ASM_KEEP(call_arg);   /* MATCH pin: retail schedule: same instructions, different order without it */
        pass_value = temp_v0;
        saved_value = pass_value;
        result = func_80099194(call_arg, pass_value);
        func_80099290(result);
        func_800A5720(saved_value);
    }
    func_80042B68(arg0, 2);
    func_80098B38(arg1);
    state = &D_80083460;
    state->fieldA = (u16) (state->fieldA - 1);
    return 1;
}

/* MECHANISM: The measured pins retain the exact 0x20 frame, s1/s2 argument holds, and s0 call result.
   A short-lived state=&D_80083460 makes cdk-G0 hold the symbol base and use lhu/sh 10(a0).
   Plain 2.7.2 folds to D_80083460+10 with offset 0; rerouting to 2.7.2-cdk-G0 closes all 3 tail subs. */
