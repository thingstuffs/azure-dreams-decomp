#include "common.h"
typedef struct FuncArg FuncArg;
void release_item_menu_object(FuncArg *parameters);

typedef struct S_800AE484_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
} S_800AE484_0;   /* arg0 in set_item_menu_data_pointer */

/* Sets the object's data pointer to start_item_menu_object_processing. */
void set_item_menu_data_pointer(S_800AE484_0 *object) {
    object->unk_10 = &release_item_menu_object;
}
