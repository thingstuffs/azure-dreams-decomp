#include "modules/town_town_windows.h"

/* Creates an object with the supplied data, position, and callback mode. */
void *townCreateConfiguredObject(void *object_data, void *source_position, s32 alternate_callback)
{
    void *created;
    void *render_state;
    void *position;
    void *object;
    u8 type;

    created = func_8003FD64(0x136, ((u8 *)(&D_80083498)));
    if (created == 0) {
        return 0;
    }

    position = POINTER_AT(created, 8);
    render_state = POINTER_AT(created, 0xC);
    HALF_AT(position, 2) = HALF_AT(source_position, 2);
    HALF_AT(position, 6) = HALF_AT(source_position, 6);
    HALF_AT(position, 0xA) = HALF_AT(source_position, 0xA);

    object = (u8 *)created + 0x20;
    HALF_AT(render_state, 0x1E) = 0x1000;
    HALF_AT(render_state, 0x1C) = 0x1000;
    WORD_AT(render_state, 0xC) = 0x00808080;
    WORD_AT(object, 0x48) = 0;
    WORD_AT(object, 0x98) = 0;
    BYTE_AT(object, 0x93) = 0;

    BYTE_AT(object, 0x4C) = BYTE_AT(object_data, 0);
    BYTE_AT(object, 0x4D) = BYTE_AT(object_data, 1);
    BYTE_AT(object, 0x4E) = BYTE_AT(object_data, 2);
    BYTE_AT(object, 0x4F) = BYTE_AT(object_data, 3);
    type = BYTE_AT(object, 0x4D);

    if (type == 0x13) {
        func_800A0878_Copy84 *copy_table = COPY_TABLE_ADDRESS;
        func_800A0878_Copy84 *copy_src;

        copy_src = (func_800A0878_Copy84 *)((u32)(BYTE_AT(object, 0x4F) & 0x1F) * 84U
                              + (u32)copy_table);
        D_80100AF8 = *copy_src;
    }

    townConfigureTheSetModeN4(object, position, D_800D073C);
    if (alternate_callback != 0) {
        townInitializeOptionalObjectState(object, position, render_state, D_800D0788);
    } else {
        townInitializeOptionalObjectState(object, position, render_state, D_800D076C);
    }

    if ((u32)(BYTE_AT(object, 0x4D) - 0x12) < 2) {
        POINTER_AT(object, 0xC) = D_800D0754;
    }
    type = BYTE_AT(object, 0x4D);

    if (type == 0x12) {
        POINTER_AT(render_state, 8) = &D_8006E240;
    } else if (type == 0x13) {
        townSetObjectStateForMode(object, render_state, BYTE_AT(object, 0x4C), D_80100B0C);
    } else {
        POINTER_AT(render_state, 8) = (void *)lookupItemCategoryMappedValue(
            BYTE_AT(object, 0x4D), BYTE_AT(object, 0x4C));
    }

    POINTER_AT(created, 0x10) = townDispatchObjectOrSwitchAlternateState;
    townInitializeObjectAndMaybePlaySound(object, object, position, render_state);
    del_t_item_w_ptr(object_data);
    return created;
}
