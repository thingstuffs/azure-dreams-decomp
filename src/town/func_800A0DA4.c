#include "modules/town_town_windows.h"

/* Sets object type fields and selects the corresponding resource. */
void townSetObjectTypesAndResource(void *object, s32 index, void *output)
{
    u32 resource;
    u8 mode;
    u8 type;

    mode = BU(object, 0x94);
    if (mode == 0) {
        townConfigureTheSetModeN4(object, index, D_800D073C);
        townInitializeOptionalObjectState(object, index, output, D_800D076C);
        BU(object, 0x4C) = BU(object, 0x95);
        BU(object, 0x4D) = BU(object, 0x96);
    } else
    if ((s8)mode == -1) {
        townConfigureTheSetModeN3(object, index, D_800D073C);
        townInitializeOptionalObjectState(object, index, output, 0);
        BU(object, 0x4C) = BU(object, 0x95);
        BU(object, 0x4D) = BU(object, 0x96);
    } else {
        townConfigureTheSetModeN4(object, index, D_800D073C);
        townInitializeOptionalObjectState(object, index, output, D_800D0788);
        {
            u8 *type_table;

            type_table = (u8 *)0x80010000;
            BU(object, 0x4C) = type_table[BU(object, 0x95) * 4 + 0x980];
            BU(object, 0x4D) = type_table[BU(object, 0x95) * 4 + 0x981];
            BU(object, 0x4E) = type_table[BU(object, 0x95) * 4 + 0x982];
            BU(object, 0x4F) = type_table[BU(object, 0x95) * 4 + 0x983];
        }
        townInitializeEntityFlagsTransformTypeDependentVariant(object, object, index, output);
    }

    if (townIsUnk18N12Unk1ABetweenN37N41() == 0) {
        resource = (u32)&townCleanupOrDispatchObject;
        PP(object, -0x10) = (u8 *)resource;
    } else {
        resource = (u32)townDispatchObjectOrSwitchAlternateState;
        PP(object, -0x10) = (u8 *)resource;
    }
    if ((u32)(BU(object, 0x4D) - 0x12) < 2U) {
        PP(object, 0xC) = D_800D0754;
    }

    type = BU(object, 0x4D);
    if (type == 0x12) {
        resource = (u32)&D_8006E240;
    } else if (type == 0x13) {
        u8 *data_base = (u8 *)0x80010000;

        townSetObjectStateForMode(
            object,
            output,
            BU(object, 0x4C),
            *(s32 *)&data_base[
                ((data_base[BU(object, 0x95) * 4 + 0x983] & 0x3F) * 0x54)
                    + 0xA94]);
        return;
    } else {
        resource = lookupItemCategoryMappedValue(BU(object, 0x4D), BU(object, 0x4C));
    }
    WD(output, 8) = resource;
}
