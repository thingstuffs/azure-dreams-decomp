#include "common.h"
#include "shared/object_node.h"
#include "shared/entity_objects.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x2];
    u16 field_02;
    u8 pad_04[0x2];
    u16 field_06;
} RecordFieldView_8133879C;



typedef s32 M2C_UNK;
extern u8 *D_80175D50[3];
extern s16 func_8016F428(void *arg);


typedef struct S_8016F79C_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_8016F79C_0;   /* s0 in dungeonApplyScriptDirectionRecord */

typedef struct S_8016F79C_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_8016F79C_1;   /* s2 in dungeonApplyScriptDirectionRecord */

/* Sets the target field from the record or source field and restores two record words. */
void dungeonApplyScriptDirectionRecord(void *unused_0, u8 *record, void *unused_2) {
    u8 *source_base = (u8 *)(&D_80083498.next);
    register u8 *source_data = (u8 *)(source_base + 0x20);
    u8 *target_base = D_80175D50[1];
    u8 *target_data = target_base + 0x20;
    s16 raw_value = func_8016F428(record);
    s32 decoded_value = raw_value;

    if (decoded_value == 9) {
        ((S_8016F79C_0 *)target_data)->unk_2A = ((S_8016F79C_1 *)source_data)->unk_2A;
    } else {
        ((S_8016F79C_0 *)target_data)->unk_2A = (u16)(decoded_value << 9);
    }
    {
        register u16 *default_words = (u16 *)((u8 *)(&D_80083780));
        ((RecordFieldView_8133879C *)record)->field_02 = default_words[1];
        ((RecordFieldView_8133879C *)record)->field_06 = default_words[3];
    }
}
