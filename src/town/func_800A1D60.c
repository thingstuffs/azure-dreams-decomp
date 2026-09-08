#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

typedef struct S_8009F4C0_3 {
    u8 pad_00[0xAC3];
    u8 unk_AC3;
} S_8009F4C0_3;   /* (temp_s0 + (u8 *)baseD) in func_8009F4C0 */

typedef struct S_8009F4C0_4 {
    u8 pad_00[0x983];
    u8 unk_983;
} S_8009F4C0_4;   /* ((arg0->unk_95 * 4) + (u8 *)baseD) in func_8009F4C0 */

typedef struct S_8009F4C0_5 {
    u8 pad_00[0xA94];
    s32 unk_A94;
} S_8009F4C0_5;   /* ((temp_s3 * 0x54) + (u8 *)baseD) in func_8009F4C0 */




struct PackedTownEntry {
    s32 word0;
    s32 word4;
    s8 byte8;
    s8 byte9;
} __attribute__((packed));

struct TownCopy84 {
    s32 words[21];
};

M2C_UNK func_80033CD8();                   /* extern */
void *func_8003C06C();               /* extern */
M2C_UNK func_8003E188();        /* extern */
M2C_UNK func_800422DC();            /* extern */
M2C_UNK func_800423C0();      /* extern */
M2C_UNK func_80042640();               /* extern */
M2C_UNK memset(); /* extern */
M2C_UNK func_8009DC8C();    /* extern */
extern M2C_UNK D_80010A80;
extern M2C_UNK D_80010AB4;
extern M2C_UNK D_80045340;
extern M2C_UNK D_8009F374;
extern M2C_UNK D_80100A10;
extern struct TownCopy84 D_80100AF8;
extern u8 D_80010000[];


typedef struct S_8009F4C0_1 {
    u8 pad_00[0x981];
    s8 unk_981;
} S_8009F4C0_1;   /* temp_v2 in func_8009F4C0 */

typedef struct S_8009F4C0_2 {
    u8 pad_00[0x981];
    u8 unk_981;
    u8 pad_982[0x1];
    u8 unk_983;
} S_8009F4C0_2;   /* temp_v1 in func_8009F4C0 */

/* Initialize the town entity record and synchronize its slot state. */
void func_8009F4C0(Rec_func_80094268_arg0 *entity, M2C_UNK unused_arg1, M2C_UNK unused_arg2, M2C_UNK context) {
    void *stored_entry;
    s32 unused_value;
    s32 record_offset;
    s32 record_value;
    s32 slot_index;
    register s32 record_index;
    void *source_entry;
    S_8009F4C0_2 *slot_flags;
    S_8009F4C0_1 *slot_state;
    register void *data_base ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    slot_index = entity->unk_95;
    func_80033CD8(entity, &D_80045340);
    slot_state = (slot_index * 4) + 0x80010000;
    slot_state->unk_981 = 0x13;
    memset(&D_80100A10, 0, 0x54);
    func_80042640(&D_80100A10, entity->unk_4C);
    record_index = slot_index;
    func_800423C0(&D_80100A10, entity->unk_4C, 0);
    func_800422DC(&D_80100AF8, &D_80100A10);
    *(struct TownCopy84 *)((u8 *)0x80010A80 + (record_index * 0x54)) = D_80100AF8;
    stored_entry = (void *) 0x80010AB4;
    record_offset = record_index * 0x54;
    stored_entry = (u8 *)stored_entry + record_offset;
    source_entry = func_8003C06C(entity->unk_4C);
    *(struct PackedTownEntry *)stored_entry = *(struct PackedTownEntry *)source_entry;
    data_base = (void *) 0x80010000;
    slot_flags = (slot_index * 4) + (u8 *)data_base;
    slot_flags->unk_983 = (u8) ((slot_flags->unk_983 & 0xC0) | record_index);
    ((S_8009F4C0_3 *)((record_offset + (u8 *)data_base)))->unk_AC3 = slot_index;
    entity->unk_4D = (u8) slot_flags->unk_981;
    entity->unk_4F = (u8) slot_flags->unk_983;
    record_index = (u8) (((S_8009F4C0_4 *)(((entity->unk_95 * 4) + (u8 *)data_base)))->unk_983 & 0x3F);
    record_value = ((S_8009F4C0_5 *)(((record_index * 0x54) + (u8 *)data_base)))->unk_A94;
    func_8003E188(entity->unk_4C, 1, data_base);
    func_8009DC8C(entity, context, entity->unk_4C, record_value);
    entity->unk_50.as_pm = &D_8009F374;
    entity->unk_6C.as_s16 = 0xA;
}
