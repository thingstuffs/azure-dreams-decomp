#include "common.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"
#include "slus.h"

typedef struct S_80026CF0_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80026CF0_1;

typedef struct S_80026CF0_2 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80026CF0_2;

typedef struct S_80026CF0_3 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_80026CF0_3;

typedef struct S_80026CF0_4 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_80026CF0_4;
struct S8004CBFC_a0;
struct S8004CBFC_a1;
struct S8004CBFC_a1; extern struct S8004CBFC_a1 D_80027E68;

typedef struct S_80026CF0_0 {
    u8 pad_00[0x68];
    void * unk_68;
    void * unk_6C;
} S_80026CF0_0;   /* arg0 in set_entry_destination_and_value */

/* Position and initialize the left and right items. */
void set_entry_destination_and_value(void *state) {
    S_80026CF0_1 *left_item;
    S_80026CF0_2 *right_item;

    left_item = ((S_80026CF0_0 *)state)->unk_68;
    ((S_80026CF0_3 *)(left_item->unk_04))->unk_08 = 0x40;
    ((S_80026CF0_3 *)(left_item->unk_04))->unk_0A = 0x20;
    initialize_scaled_entry_cursor(state + 4, &D_80027E68, left_item);
    right_item = ((S_80026CF0_0 *)state)->unk_6C;
    ((S_80026CF0_4 *)(right_item->unk_04))->unk_08 = 0xC0;
    ((S_80026CF0_4 *)(right_item->unk_04))->unk_0A = 0x20;
    initialize_scaled_entry_cursor(state + 0x10, &D_80027E68, right_item);
}
