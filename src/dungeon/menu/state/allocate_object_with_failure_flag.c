#include "shared/object_node.h"
#include "common.h"
#include "shared/object_flags.h"

typedef struct {
    u8 pad_00[0x38];
    s32 *field_38;
    u8 field_3C[1];
} ObjectHeader;

extern s32 create_callback_pair_default(s32);
extern void register_node(void *, void *);
extern void initialize_complemented_state(void *);
extern s32 run_object_setup_and_finalize(void *, s32);
extern void initialize_object_tables_2(void *, s32);
extern u8 D_8004CAA0[];
extern u8 D_800DC8F8[];
extern void *D_800E5910[];

/* Allocate and initialize an object, marking allocation failure in the status flags. */
void *allocate_object_with_failure_flag(void) {
    s32 allocation;
    register ObjectHeader *header;
    s32 *status_page;
    s32 *source_table;
    u8 *data;
    u8 *object;

    object = func_8003FC64(0);
    if (object != 0) {
        D_800E5910[0] = object;
        allocation = create_callback_pair_default(0x100);
        header = (ObjectHeader *)(object + 0x20);
        if (allocation != 0) {
            data = object + 0x5C;
            initialize_object_tables_2(data, allocation);
            source_table = (s32 *)0x800133A0;
            header->field_38 = source_table;
            *(s32 *)(object + 0xC) = run_object_setup_and_finalize(data, source_table[0]);
            initialize_complemented_state(object);
            *(u8 **)(object + 0x10) = D_800DC8F8;
            register_node(object, D_8004CAA0);
            return object;
        }
        *(u16 *)(object + 0x1E) |= 0x8000;
        status_page = (s32 *)0x80080000;
        object = 0;
        status_page[0x528] |= 0x8000;
    }
    return object;
}
