#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8002290C_arg0.h"

typedef struct S_8002290C_2 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8002290C_2;   /* temp_v1 in func_8002290C */

typedef struct S_8002290C_3 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_8002290C_3;   /* ((S_8002290C_2 *)temp_v1)->unk_04 in func_8002290C */





typedef struct S_8002290C_1 {
    void * unk_00;
} S_8002290C_1;   /* temp_v1 in func_8002290C */

/* Set the linked coordinates to (160, 120) and bind the object's data. */
void func_8002290C(void *object) {
    S_8002290C_1 *linked_state;

    linked_state = ((Rec_func_8002290C_arg0 *)object)->unk_8E0;
    ((S_8002290C_3 *)(((S_8002290C_2 *)linked_state)->unk_04))->unk_08 = 0xA0;
    ((S_8002290C_3 *)(((S_8002290C_2 *)linked_state)->unk_04))->unk_0A = 0x78;
    linked_state->unk_00 = (void *) (object + 0x24);
}
