#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} TownStruct80110EB8;

extern TownStruct80110EB8 D_80110EB8;

/* Stores a value in the town record and sets its final field to 5. */
s32 set_item_menu_record_state_five(s32 value) {
    D_80110EB8.unk0 = value;
    D_80110EB8.unk8 = 5;
    return 1;
}
