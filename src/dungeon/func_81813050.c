#include "modules/dungeon_ovl_1831cd8.h"

void dungeonInitializeMenuHeaderRecords(void *unused, ovl_1831cd8_81813050_Header *header, ovl_1831cd8_81813050_Template0 *record_a, ovl_1831cd8_81813050_Record1 *record_b) {
    ovl_1831cd8_81813050_Template0 *defaults_a = &D_8002E5D8;
    ovl_1831cd8_81813050_Template1 *defaults_b = &D_8002E5E8;
    s32 *first_word;

    record_a->unk0 = defaults_a->unk0;
    first_word = &defaults_b->unk0;
    record_a->unk4 = defaults_a->unk4;
    record_a->unk8 = defaults_a->unk8;
    record_a->unkC = defaults_a->unkC;

    ((ovl_1831cd8_81813050_Template1 *)record_b)->unk0 = *first_word;
    ((ovl_1831cd8_81813050_Template1 *)record_b)->unk4 = defaults_b->unk4;
    ((ovl_1831cd8_81813050_Template1 *)record_b)->unk8 = defaults_b->unk8;

    header->unk4 = (ovl_1831cd8_81813050_Record0 *)record_a;
    header->unk8 = record_b;
    header->unk0 = 0;

    header->unk4->unk8 = -0x58;
    header->unk4->unkA = -0x40;
    header->unk4->unkC = 0x200;
    header->unk8->unk2 = 0x400;
    header->unk8->unk6 = -0x50;
    header->unk4->unkF = 4;
}
