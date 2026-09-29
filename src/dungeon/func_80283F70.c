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
    s16 next_count;
    s16 count;
    s8 *record;
    s8 *id_ptr;
    s16 record_id;
    s8 record_type;

    record = &D_800E3DB0;
    count = 0;
    record_id = count;
    record_type = 1;
    id_ptr = record + 3;
    do {
        next_count = count + 1;
        count = next_count;
        *record = record_type;
        ((S_80016F70_0 *)((u8 *)id_ptr - 0x2))->unk_02 = record_id;
        record_id += 1;
        ((S_80016F70_0 *)((u8 *)id_ptr - 0x2))->unk_00 = 0;
        ((S_80016F70_0 *)((u8 *)id_ptr - 0x2))->unk_01 = 0;
        id_ptr += 8;
        record += 8;
    } while (next_count < 4);
    count = 0;
    record_type = 3;
    id_ptr = record + 3;
    do {
        next_count = count + 1;
        count = next_count;
        *record = record_type;
        ((S_80016F70_1 *)((u8 *)id_ptr - 0x2))->unk_02 = record_id;
        record_id += 1;
        ((S_80016F70_1 *)((u8 *)id_ptr - 0x2))->unk_00 = 0;
        ((S_80016F70_1 *)((u8 *)id_ptr - 0x2))->unk_01 = 0;
        id_ptr += 8;
        record += 8;
    } while (next_count < 2);
    ((S_80016F70_2 *)record)->unk_00 = 2;
    ((S_80016F70_2 *)record)->unk_01 = 0;
    ((S_80016F70_2 *)record)->unk_02 = 0;
    ((S_80016F70_2 *)record)->unk_03 = record_id;
    ((S_80016F70_2 *)record)->unk_04 = 0;
}
