#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Template0;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Template1;

extern Template0 D_8002E5D8;
extern Template1 D_8002E5E8;

typedef struct {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 unkF;
} Record0;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s32 unk8;
} Record1;

typedef struct {
    s32 unk0;
    Record0 *unk4;
    Record1 *unk8;
} Header;

/* Initialize the header and its two records from default templates. */
void func_8012656C(Header *header, Template0 *primary_record, Record1 *secondary_record) {
    Template0 *primary_defaults = &D_8002E5D8;
    Template1 *secondary_defaults = &D_8002E5E8;
    s32 *default_word;

    primary_record->unk0 = primary_defaults->unk0;
    default_word = &secondary_defaults->unk0;
    primary_record->unk4 = primary_defaults->unk4;
    primary_record->unk8 = primary_defaults->unk8;
    primary_record->unkC = primary_defaults->unkC;

    ((Template1 *)secondary_record)->unk0 = *default_word;
    ((Template1 *)secondary_record)->unk4 = secondary_defaults->unk4;
    ((Template1 *)secondary_record)->unk8 = secondary_defaults->unk8;

    header->unk4 = (Record0 *)primary_record;
    header->unk8 = secondary_record;
    header->unk0 = 0;

    header->unk4->unk8 = -0xA0;
    header->unk4->unkA = -0x78;
    header->unk4->unkC = 0x200;
    header->unk4->unkF = 8;
    header->unk8->unk0 = 0;
    header->unk8->unk2 = 0;
    header->unk8->unk4 = 0;
}
