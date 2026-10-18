#include "modules/dungeon_ovl_1831370.h"

void initialize_object_phase_data(void *recordFields, s32 recordValue2C, s32 typeCode, s32 recordValue24) {
    s32 isType13;

    ((ovl_1831370_8181192C_S_8002692C_0 *)((u8 *)recordFields - 0x10))->unk_1C = typeCode;
    isType13 = typeCode == 0x13;
    ((ovl_1831370_8181192C_S_8002692C_0 *)((u8 *)recordFields - 0x10))->unk_20 = isType13;
    initialize_variant_packet(recordFields + 0x20, isType13);
    set_descriptor_fields_and_flag(recordFields + 0x2C);
    ((ovl_1831370_8181192C_S_8002692C_0 *)((u8 *)recordFields - 0x10))->unk_24 = recordValue24;
    ((ovl_1831370_8181192C_S_8002692C_0 *)((u8 *)recordFields - 0x10))->unk_2C = recordValue2C;
    ((ovl_1831370_8181192C_S_8002692C_0 *)((u8 *)recordFields - 0x10))->unk_00 = (void *)apply_step_and_reset_after_five;
}
