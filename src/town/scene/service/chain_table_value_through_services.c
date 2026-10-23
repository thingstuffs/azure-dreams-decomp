#include "common.h"
#include "shared/record_ptrs.h"
typedef struct Data20 {
    u8 pad0[0x3C];
    void (*callback3C)(void *, s32);
    u8 pad40[8];
    s32 (*callback48)(u8, void *);
} Data20;

typedef struct State {
    u8 pad0[0x20];
    Data20 *data20;
} State;

extern u8 D_80018348[];
extern s32 D_800183D0;
extern s32 D_800183D4;
extern u8 scene_service_arguments[];

/* Stores the selected table value and chains the state's callbacks on the shared buffer. */
void chain_table_value_through_services(void) {
    u8 selected_value;
    u8 *value_table;
    State **state_slot;

    value_table = D_80018348;
    selected_value = value_table[D_800183D4 * 4];
    state_slot = ((State * *)(&town_scene_root));
    D_800183D0 = (s32)selected_value;
    (*state_slot)->data20->callback3C(scene_service_arguments, (*state_slot)->data20->callback48(selected_value, scene_service_arguments));
}
