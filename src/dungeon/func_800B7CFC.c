#include "common.h"
#include "m2c_compat.h"

typedef struct S_800BD45C_0 {
    s32 unk_00;
    u8 pad_04[0x27];
    u8 unk_2B;
    s32 unk_2C;
    u8 pad_30[0x4];
    s32 unk_34;
    u8 pad_38[0xF0];
    s32 unk_128;
} S_800BD45C_0;   /* arg0 in func_800BD45C; pointer addresses record offset 0x18 */

typedef struct S_800BD45C_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800BD45C_1;   /* counter in func_800BD45C */


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
void func_800BD5A8(void);                          /* extern */
M2C_UNK func_800C4AFC();            /* extern */
extern M2C_UNK D_80082E80;
extern extern M2C_UNK D_80083460[3];
extern M2C_UNK D_80083780;
extern u16 D_800DDE84[];
extern M2C_UNK D_800E0E69;
extern void *D_800E3D7C[];

s32 func_800BD45C(void *arg0, s32 arg1, s16 arg2) {
    u16 *table;
    M2C_UNK *counter;

    if (arg0 == D_800E3D7C[0]) {
        ((S_800BD45C_0 *)((u8 *)arg0 - 0x18))->unk_128 = arg1;
        func_8008D330(arg0, &D_80083780, &D_80082E80, arg0);
        return 0;
    }
    if ((u32) arg0 <= 0x9FFFFFFFU) {
        register void *call_obj ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
        register u8 *table_page ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
        u8 table_index;

        func_800A63B8(arg0, arg1, arg2);
        call_obj = arg0;
        table_page = (u8 *)0x800E0000;
        ASM_KEEP(table_page);   /* MATCH pin: load-bearing for the whole function shape */
        table_index = ((S_800BD45C_0 *)((u8 *)arg0 - 0x18))->unk_2B;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
        table = (u16 *)(table_page - 0x217C);
        ASM_KEEP(table);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        if (func_800AD6FC(call_obj, (table[table_index] >> 6) & 3, 0) == 0) {
            func_800A5F38(arg0, arg1);
            return 1;
        }
        goto block_8;
    }
block_8:
    func_800C4AFC(((S_800BD45C_0 *)((u8 *)arg0 - 0x18))->unk_00, 0x802080, arg0);
    if ((((S_800BD45C_0 *)((u8 *)arg0 - 0x18))->unk_2C & 0x4000) && !(((S_800BD45C_0 *)((u8 *)arg0 - 0x18))->unk_34 & 0x40)) {
        M2C_UNK *format_obj;
        register s32 format_arg ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
        register s32 saved_result ASM_REG("$16");   /* MATCH pin: keeps a statement from moving across a call/branch */
        s32 raw_result;
        s32 format_result;

        raw_result = func_800990FC();
        format_obj = &D_800E0E69;
        ASM_USE(format_obj);   /* MATCH pin: retail schedule: same instructions, different order without it */
        format_arg = raw_result;
        saved_result = format_arg;
        format_result = func_80099194(format_obj, format_arg);
        func_80099290(format_result);
        func_800A5720(saved_result);
    }
    func_80042B68(arg0, 5);
    func_80098B38(arg1);
    counter = D_80083460;
    ASM_KEEP(counter);   /* MATCH pin: load-bearing for the whole function shape */
    ((S_800BD45C_1 *)counter)->unk_0A = (u16) (((S_800BD45C_1 *)counter)->unk_0A - 1);
    return 1;
}

/* MECHANISM: The natural 0x20 frame holds arg0/arg1 in s1/s2 and the saved formatter input in s0.
   LEAD-22 void calls plus explicit returns place 0/1 in both dispatcher jump delay slots.
   A held v1 page, fenced lbu, and low-half addiu reproduce the split table address sequence.
   Scoped a0/a1 carriers order the formatter result v0 -> a1 -> s0 exactly. */
