#include "modules/dungeon_ovl_1830850.h"

void inventoryInitializeOwnerPointersAndOffsets(ovl_1830850_81810E3C_Source *source, ovl_1830850_81810E3C_Owner **owners)
{
    s32 owner_idx;

    owners[0]->unk0 = D_80078C10;
    owners[0]->unk4->unkA = 0;

    owners[1]->unk0 = D_800789B8;
    owners[1]->unk4->unk8 = -20;

    owners[2]->unk0 = source->unk74 + 12;
    owners[2]->unk4->unk8 = -20;
    inventorySetPairedIndexOffset(owners, 0);

    owners[3]->unk0 = source->unk74;
    owners[3]->unk4->unkA = -64;
    inventoryInitializeFiveSharedEntries(source->unk74 + 24);

    owners[4]->unk0 = source->unk74 + 24;
    owners[4]->unk4->unk8 = -20;
    owners[4]->unk4->unkA = 8;

    owners[5]->unk0 = func_8004DC14(D_80029474, 0);
    owners[5]->unk4->unk8 = 124;
    owners[5]->unk4->unkA = 72;

    for (owner_idx = 6; owner_idx < 11; owner_idx++) {
        owners[owner_idx]->unk0 = D_8007795C;
        owners[owner_idx]->unk4->unk8 = -12;
        owners[owner_idx]->unk4->unkA = (owner_idx * 16) - 137;
    }

    inventorySelectNullOrDefaultData(source);
    owners[12]->unk4->unk8 = -12;
    owners[12]->unk4->unkA = 23;
}
