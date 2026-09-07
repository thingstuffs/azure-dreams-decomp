#include "common.h"
#include "m2c_compat.h"

typedef struct S_80016F70_0 {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
} S_80016F70_0;   /* var_v1 in func_80016F70; pointer addresses record offset 0x2 */

typedef struct S_80016F70_1 {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
} S_80016F70_1;   /* var_v1_2 in func_80016F70; pointer addresses record offset 0x2 */

typedef struct S_80016F70_2 {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
    s8 unk_03;
    s32 unk_04;
} S_80016F70_2;   /* var_a0 in func_80016F70 */


extern s8 D_800E3DB0;

/* Initialize seven records with sequential IDs and types 1, 3, and 2. */
void func_80016F70(void) {
    register u32 page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s16 next_type1_count;
    s16 next_type3_count;
    register s16 type1_count ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
    s16 type3_count;
    s8 *record;
    s8 *type1_id_ptr;
    s8 *type3_id_ptr;
    s8 record_id;
    s8 record_type;

    page = 0x800E0000;
    ASM_KEEP(page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    record = (s8 *)(page + 0x3DB0);
    ASM_CLOBBER("$2");   /* MATCH pin: load-bearing for the whole function shape */
    type1_count = 0;
    record_id = type1_count;
    record_type = 1;
    type1_id_ptr = record + 3;
    do {
        next_type1_count = type1_count + 1;
        type1_count = next_type1_count;
        *record = record_type;
        ((S_80016F70_0 *)((u8 *)type1_id_ptr - 0x2))->unk_02 = record_id;
        record_id += 1;
        ((S_80016F70_0 *)((u8 *)type1_id_ptr - 0x2))->unk_00 = 0;
        ((S_80016F70_0 *)((u8 *)type1_id_ptr - 0x2))->unk_01 = 0;
        type1_id_ptr += 8;
        record += 8;
    } while (next_type1_count < 4);
    type3_count = 0;
    record_type = 3;
    type3_id_ptr = record + 3;
    do {
        next_type3_count = type3_count + 1;
        type3_count = next_type3_count;
        *record = record_type;
        ((S_80016F70_1 *)((u8 *)type3_id_ptr - 0x2))->unk_02 = record_id;
        record_id += 1;
        ((S_80016F70_1 *)((u8 *)type3_id_ptr - 0x2))->unk_00 = 0;
        ((S_80016F70_1 *)((u8 *)type3_id_ptr - 0x2))->unk_01 = 0;
        type3_id_ptr += 8;
        record += 8;
    } while (next_type3_count < 2);
    ((S_80016F70_2 *)record)->unk_00 = 2;
    ((S_80016F70_2 *)record)->unk_01 = 0;
    ((S_80016F70_2 *)record)->unk_02 = 0;
    ((S_80016F70_2 *)record)->unk_03 = record_id;
    ((S_80016F70_2 *)record)->unk_04 = 0;
}
/* MECHANISM: Frameless leaf; a pinned 0x800E0000 page in v0 forms the advancing a0 base.
   Clobbering v0 after base formation prevents the +3 pointer from folding through the page.
   Named a3 loop constants place each li before the derived v1 pointer.
   An a2 counter pin plus seam keep preserves retail's move a1,a2. */
