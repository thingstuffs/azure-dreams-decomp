/* Object table initialization (G00375). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800D7228, CL:dungeon/func_800D7484, CL:dungeon/func_800D74DC, CL:dungeon/func_800D7594. */
#include "dungeon/menu/object_table_initialization_g00375.h"
#include "shared/object_node.h"

/* Initialize nine records and vectors from templates, setting each record's last byte to 4. */
void initialize_nine_records_and_vectors(u8 *object) {
    s32 i;

    for (i = 0; i < 9; i++) {
        *(s32 *)(i * 0x10 + *(s32 *)(object + 4)) = display_block_defaults.unk0;
        *(s32 *)(i * 0x10 + *(s32 *)(object + 4) + 4) = display_block_defaults.unk4;
        *(s32 *)(i * 0x10 + *(s32 *)(object + 4) + 8) = display_block_defaults.unk8;
        *(s32 *)(i * 0x10 + *(s32 *)(object + 4) + 0xC) = display_block_defaults.unkC;
        *(u8 *)(i * 0x10 + *(s32 *)(object + 4) + 0xF) = 4;
        *(s32 *)(i * 0xC + *(s32 *)(object + 8)) = display_vector_defaults.x;
        *(s32 *)(i * 0xC + *(s32 *)(object + 8) + 4) = display_vector_defaults.y;
        *(s32 *)(i * 0xC + *(s32 *)(object + 8) + 8) = display_vector_defaults.z;
    }
}

/* Assign the object tables and mode, then initialize the object. */
s32 initialize_object_tables_2(S_800DCCF4_0 *object, s32 mode) {
    object->unk_04 = &D_800E2828;
    object->unk_08 = &D_800E28B8;
    object->unk_00 = mode;
    object->unk_0C = &D_800E2804;
    initialize_nine_records_and_vectors(object);
    return 1;
}

/* Allocate and initialize an object, marking allocation failure in the status flags. */
void *allocate_object_with_failure_flag(void) {
    s32 allocation;
    register ObjectHeader *header;
    s32 *status_page;
    s32 *source_table;
    u8 *data;
    ObjectNodeHeader *object;

    object = allocate_flagged_object_node(0);
    if (object != 0) {
        dungeon_menu_object[0] = object;
        allocation = create_callback_pair_default(0x100);
        header = (ObjectHeader *)(((u8 *)object) + 0x20);
        if (allocation != 0) {
            data = ((u8 *)object) + 0x5C;
            initialize_object_tables_2(data, allocation);
            source_table = (s32 *)0x800133A0;
            header->field_38 = source_table;
            object->sprite = run_object_setup_and_finalize(data, source_table[0]);
            initialize_complemented_state(object);
            object->unk_10 = D_800DC8F8;
            register_node(object, dungeon_menu_tag);
            return object;
        }
        object->flags |= 0x8000;
        status_page = (s32 *)0x80080000;
        object = 0;
        status_page[0x528] |= 0x8000;
    }
    return object;
}
