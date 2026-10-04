#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

void func_8009539C();                      /* extern */
extern void *D_8009BC44;

typedef struct S_800A022C_0 {
    u8 pad_00[0x15];
    s8 unk_15;
} S_800A022C_0;   /* arg1 in func_800A022C */


typedef struct S_800A022C_2 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
} S_800A022C_2;   /* arg0 in func_800A022C */

/* Initialize the record and active flag, then install the object handler. */
void func_800A022C(S_800A022C_2 *object, S_800A022C_0 *state, EntityRec *record) {
    state->unk_15 = 1;
    record->unk_0C = 0;
    record->unk_10 = 0;
    record->flags14 = 0xFFF20000;
    func_8009539C(record);
    object->unk_50 = &D_8009BC44;
}
