#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8002290C_arg0.h"
#include "frontend/libcard/message.h"

typedef struct S_8002290C_2 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8002290C_2;

typedef struct S_8002290C_3 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_8002290C_3;


typedef struct S_8002290C_1 {
    void * unk_00;
} S_8002290C_1;

/* Set the linked coordinates to (160, 120) and bind the object's data. */
void card_boot_center_message_dialog_display(void *object) {
    S_8002290C_1 *linked_state;

    linked_state = ((Rec_func_8002290C_arg0 *)object)->unk_8E0;
    ((S_8002290C_3 *)(((S_8002290C_2 *)linked_state)->unk_04))->unk_08 = 0xA0;
    ((S_8002290C_3 *)(((S_8002290C_2 *)linked_state)->unk_04))->unk_0A = 0x78;
    linked_state->unk_00 = (object + 0x24);
}
