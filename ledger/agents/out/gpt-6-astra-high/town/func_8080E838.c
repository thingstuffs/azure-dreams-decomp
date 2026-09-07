#include "common.h"

typedef struct S_8080E838_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_8080E838_0;   /* copy_src in func_8080E838 */

typedef struct S_8080E838_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_8080E838_1;   /* copy_dst in func_8080E838 */

typedef struct S_8080E838_2 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    s32 unk_10;
} S_8080E838_2;   /* obj in func_8080E838 */

typedef struct S_8080E838_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8080E838_3;   /* initial in func_8080E838 */

typedef struct S_8080E838_4 {
    s32 unk_00;
    union { struct { s32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_04;   /* overlapping accesses */
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    union { s32 s32; u16 u16; } unk_14;   /* accessed as both */
    u8 pad_18[0x4];
    s16 unk_1C;
    s16 unk_1E;
} S_8080E838_4;   /* part in func_8080E838 */

typedef struct S_8080E838_5 {
    u8 pad_00[0x54];
    s16 unk_54;
} S_8080E838_5;   /* source in func_8080E838 */

typedef struct S_8080E838_6 {
    u8 pad_00[0x130];
    s32 unk_130;
} S_8080E838_6;   /* table_base in func_8080E838 */

typedef struct S_8080E838_7 {
    u8 pad_00[0x50];
    void * unk_50;
} S_8080E838_7;   /* payload in func_8080E838 */


typedef struct {
    s32 words[4];
} Copy16;

extern void *func_800373DC(s32);
extern void func_8003BC18(void *, void *);
extern void func_8023FA58(void *, void *, void *);

extern u8 D_8003C558[];
extern u8 D_8052643C[];
extern u8 D_80529594[];
extern s32 D_805300F4[];


/* Allocates an object, copies its source data, and initializes its components. */
void func_8080E838(void *source_data, void *initial_data) {
    void *obj;
    void *allocated_obj;
    register void *source ASM_REG("$17");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register void *initial ASM_REG("$19");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register u8 *payload ASM_REG("$18");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    u8 *part;
    register u8 *payload_table ASM_REG("$20");   /* MATCH pin: retail register colouring depends on it */
    Copy16 *copy_src;
    Copy16 *copy_dst;
    Copy16 *copy_end;
    s32 copy_word_0;
    register s32 copy_word_1 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 copy_or_obj;
    register s32 copy_or_entry ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    s32 field_value;
    register s32 field_or_table ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
    register s32 init_word_2 ASM_REG("$7");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 init_word_3 ASM_REG("$8");   /* MATCH pin: load-bearing for the whole function shape */
    register u8 *setup_data ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 *table_base ASM_REG("$1");   /* MATCH pin: keeps a constant in a register as retail does */

    source = source_data;
    ASM_KEEP_NV(source);   /* MATCH pin: retail schedule: same instructions, different order without it */
    initial = initial_data;
    ASM_KEEP_NV(initial);   /* MATCH pin: retail schedule: same instructions, different order without it */
    allocated_obj = func_800373DC(0x136);
    payload_table = D_8052643C;
    ASM_KEEP_NV(payload_table);   /* MATCH pin: retail schedule: same instructions, different order without it */
    obj = allocated_obj;
    payload = (u8 *)obj + 0x20;
    if (obj != 0) {
        copy_dst = (Copy16 *)payload;
        copy_src = (Copy16 *)source;
        copy_end = (Copy16 *)((u8 *)source + 0x50);
        do {
            copy_word_0 = ((S_8080E838_0 *)copy_src)->unk_00;
            copy_word_1 = ((S_8080E838_0 *)copy_src)->unk_04;
            copy_or_obj = ((S_8080E838_0 *)copy_src)->unk_08;
            copy_or_entry = ((S_8080E838_0 *)copy_src)->unk_0C;
            ((S_8080E838_1 *)copy_dst)->unk_00 = copy_word_0;
            ((S_8080E838_1 *)copy_dst)->unk_04 = copy_word_1;
            ((S_8080E838_1 *)copy_dst)->unk_08 = copy_or_obj;
            ((S_8080E838_1 *)copy_dst)->unk_0C = copy_or_entry;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
            copy_src++;
            copy_dst++;
        } while (copy_src != copy_end);
        field_value = ((S_8080E838_0 *)copy_src)->unk_00;
        copy_word_1 = ((S_8080E838_0 *)copy_src)->unk_04;
        ((S_8080E838_1 *)copy_dst)->unk_00 = field_value;
        ((S_8080E838_1 *)copy_dst)->unk_04 = copy_word_1;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        copy_or_obj = (s32)obj;
        ASM_KEEP(copy_or_obj);   /* MATCH pin: retail schedule: same instructions, different order without it */
        setup_data = D_8003C558;
        part = ((S_8080E838_2 *)obj)->unk_08;
        ASM_KEEP(part);   /* MATCH pin: retail schedule: same instructions, different order without it */
        field_value = (s32)D_80529594;
        ((S_8080E838_2 *)obj)->unk_10 = field_value;
        field_value = ((S_8080E838_3 *)initial)->unk_00;
        field_or_table = ((S_8080E838_3 *)initial)->unk_04;
        init_word_2 = ((S_8080E838_3 *)initial)->unk_08;
        init_word_3 = ((S_8080E838_3 *)initial)->unk_0C;
        ((S_8080E838_4 *)part)->unk_00 = field_value;
        ((S_8080E838_4 *)part)->unk_04.at00.v = field_or_table;
        ((S_8080E838_4 *)part)->unk_08 = init_word_2;
        ((S_8080E838_4 *)part)->unk_0C = init_word_3;
        field_value = ((S_8080E838_3 *)initial)->unk_10;
        field_or_table = ((S_8080E838_3 *)initial)->unk_14;
        ((S_8080E838_4 *)part)->unk_10 = field_value;
        ((S_8080E838_4 *)part)->unk_14.s32 = field_or_table;
        func_8003BC18((void *)copy_or_obj, setup_data);

        field_or_table = 0x800000;
        ASM_KEEP(field_or_table);   /* MATCH pin: retail schedule: same instructions, different order without it */
        part = ((S_8080E838_2 *)obj)->unk_0C;
        field_value = 0x1000;
        ((S_8080E838_4 *)part)->unk_1E = field_value;
        ((S_8080E838_4 *)part)->unk_1C = field_value;
        field_value = ((S_8080E838_5 *)source)->unk_54;
        ASM_KEEP(field_value);   /* MATCH pin: retail schedule: same instructions, different order without it */
        field_or_table |= 0x8080;
        field_value <<= 2;
        table_base = (s32 *)0x80530000;
        table_base = (s32 *)((s32)table_base - -field_value);
        copy_or_entry = ((S_8080E838_6 *)table_base)->unk_130;
        ASM_KEEP(copy_or_entry);   /* MATCH pin: keeps a statement from moving across a call/branch */
        field_value = ((S_8080E838_4 *)part)->unk_14.u16;
        ((S_8080E838_4 *)part)->unk_04.at00u.v = 0;
        ((S_8080E838_4 *)part)->unk_04.at01.v = 0;
        ((S_8080E838_4 *)part)->unk_0C = field_or_table;
        field_value |= 0x80;
        ((S_8080E838_4 *)part)->unk_14.u16 = field_value;
        ASM_KEEP(field_value);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ((S_8080E838_4 *)part)->unk_08 = copy_or_entry;
        ((S_8080E838_7 *)payload)->unk_50 = payload_table;
        ASM_KEEP_NV(payload);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        setup_data = ((S_8080E838_2 *)obj)->unk_08;
        ASM_KEEP(setup_data);   /* MATCH pin: retail schedule: same instructions, different order without it */
        field_or_table = (s32)D_805300F4;
        ASM_KEEP(field_or_table);   /* MATCH pin: retail schedule: same instructions, different order without it */
        func_8023FA58(payload + 8, setup_data, (void *)field_or_table);
    }
}
