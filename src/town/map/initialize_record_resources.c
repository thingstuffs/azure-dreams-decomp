#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

typedef struct S_800BC840_0 {
    s32 * unk_00;
    u8 pad_04[0x54];
    s32 unk_58;
    u8 pad_5C[0x4];
    s32 unk_60;
} S_800BC840_0;   /* arg0 in initialize_record_resources; pointer addresses record offset 0x10 */


void func_8003DB94(struct Dst *state, struct Elem *entries, short index);
s32 register_node();              /* extern */
void configure_the_set_mode_n_1();  /* extern */
extern M2C_UNK D_800BC764;
extern M2C_UNK D_800D20CC;
extern s32 D_800D20E4;
extern M2C_UNK D_800F15E4;

/* Initializes the record and its associated resources. */
void initialize_record_resources(void *record, s32 init_context, s32 resource_target) {
    ((S_800BC840_0 *)((u8 *)record - 0x10))->unk_00 = &D_800BC764;
    ((S_800BC840_0 *)((u8 *)record - 0x10))->unk_60 = 0;
    register_node(record - 0x20, project_sprite_chain);
    ((S_800BC840_0 *)((u8 *)record - 0x10))->unk_58 = (s32) D_800D20E4;
    func_8003DB94(resource_target, &D_800F15E4, 0);
    configure_the_set_mode_n_1(record, init_context, &D_800D20CC);
}
