#include "common.h"
#include "shared/widget_views.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"
#include "main/data.h"

typedef struct S_80026C94_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80026C94_3;

typedef struct S_80026C94_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80026C94_4;

typedef struct S_80026C94_5 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_80026C94_5;

typedef struct S_80026C94_6 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_80026C94_6;

typedef struct S_80026C94_0 {
    u8 pad_00[0x60];
    void * unk_60;
    void * unk_64;
} S_80026C94_0;   /* arg0 in card_boot_layout_left_right_labels */

/* Set the positions and data pointers for the left and right entries. */
void card_boot_layout_left_right_labels(S_80026C94_0 *owner) {
    CardCallbackState *left_entry;

    left_entry = owner->unk_60;
    ((S_80026C94_5 *)(((S_80026C94_3 *)left_entry)->unk_04))->unk_08 = 0x40;
    ((S_80026C94_5 *)(((S_80026C94_3 *)left_entry)->unk_04))->unk_0A = 0x20;
    left_entry->callback = &D_80028418;
    left_entry = (owner->unk_64);
    ((S_80026C94_6 *)(((S_80026C94_4 *)left_entry)->unk_04))->unk_08 = 0xC0;
    ((S_80026C94_6 *)(((S_80026C94_4 *)left_entry)->unk_04))->unk_0A = 0x20;
    left_entry->callback = &D_80028430;
}
