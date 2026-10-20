#include "common.h"

#include "common.h"
#include "records/Rec_D_80082D58.h"

typedef struct S_8003C2B8_0_pre {
    s32 unk_00;
    u8 pad_04[0x10];
} S_8003C2B8_0_pre;   /* the 0x14 bytes before &D_80082D58 in clear_fade_manager, addressed as &D_80082D58[-1] */
void unlink_node_if_registered(void *block_data);                   /* extern */
void runtime_clear_record_field_04();              /* extern */
extern u8 D_80082D58[];

/* Clears D_80082D58 and processes it using the preceding block's value. */
void clear_fade_manager(void) {
    ((Rec_D_80082D58 *)(&D_80082D58))->unk_00 = 0;
    runtime_clear_record_field_04(&D_80082D58, ((S_8003C2B8_0_pre *)(&D_80082D58))[-1].unk_00);
    unlink_node_if_registered(&D_80082D58);
}
