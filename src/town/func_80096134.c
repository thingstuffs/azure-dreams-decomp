#include "common.h"
#include "shared/object_node.h"
#include "shared/types3a_types.h"


typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
} Unk96134Bytes;


typedef struct {
    IntVector3 pos;
    u8 padC[0xC];
    Unk96134Bytes bytes;
} Unk96134Work;

typedef struct {
    u8 pad0[0x10];
    void *unk10;
    u8 pad14[4];
    s32 unk18;
} Unk96134State;

extern void write_resource_command(void *ptr, s32 value);
extern s32 is_town_state_pair_accepted(void);
extern void initialize_scene_action_record(void *object, void *position, void *callback_data);
extern void initialize_actor_movement_interaction_action(void *object, void *position, void *callback_data);
extern void set_item_selection_data_pointer(void *object, void *position, void *callback_data);
extern void *create_configured_object(void *context, IntVector3 *position, s32 mode);
extern s32 get_first_free_four_byte_entry_index_n_1_none_available(void *ptr, s32 value);
extern s32 is_unk_18_n_12_unk_1_a_between_n_37_n_41(s32 state_index);
extern s32 count_type_n_4_links_whose_state_not_n_1(void);
extern s32 find_target_byte_index_in_list(void);

extern u8 D_80088C0C[];
extern u8 D_80088C48[];
extern u8 D_80088C8C[];
extern u8 D_80088CCC[];
extern u8 D_80088D04[];
extern s32 D_80093D48;
extern u8 D_800CFCB4[];
extern s32 D_800D0428;
extern s32 D_800D0728[];
extern s32 D_800FE518;
extern void (*D_800FE5D8)(void *object, void *position, void *callback_data);
extern u8 D_80110EB8[];


typedef struct S_80093894_1 {
    Unk96134Bytes * unk_00;
    u8 pad_04[0x4];
    s32 unk_08;
} S_80093894_1;   /* context in handle_selection_and_create_object */

   /* arg1 in handle_selection_and_create_object */

typedef struct S_80093894_3 {
    void * unk_00;
} S_80093894_3;   /* &D_80110EB8 in handle_selection_and_create_object */

typedef struct S_80093894_4 {
    u8 pad_00[0x2C];
    void * unk_2C;
} S_80093894_4;   /* object in handle_selection_and_create_object */

/* Checks the current selection, displays rejection messages, or creates and selects an object. */
void handle_selection_and_create_object(void) {
    Unk96134Work work;
    ObjectNodeHeader *data;
    u8 *context;
    u8 *object;
    IntVector3 *position;
    void *callback_data;
    void *created_entry;
    u32 state_code;
    s32 state_index;
    s32 state_is_12_or_13;
    s32 is_available;
    s32 mode;

    data = &D_80083498;
    object = (u8 *)data + 0x20;
    context = D_80110EB8;
    position = data->unk_08;
    callback_data = data->unk_0C;

    if (((S_80093894_1 *)context)->unk_08 == 3) {
        Unk96134Bytes *source = ((S_80093894_1 *)context)->unk_00;

        work.bytes.unk0 = source->unk0;
        state_code = source->unk1;
        work.bytes.unk1 = state_code;
        work.bytes.unk2 = source->unk2;
        work.bytes.unk3 = source->unk3;
        state_index = state_code - 0x12;
        state_is_12_or_13 = (u32)state_index < 2;
        is_available = is_unk_18_n_12_unk_1_a_between_n_37_n_41(state_index) == 1;

        switch (is_available) {
        case 0: {
            if (is_town_state_pair_accepted() != 0) {
                write_resource_command(D_80088C0C, 0x11);
            } else if (count_type_n_4_links_whose_state_not_n_1() >= 0x12) {
                write_resource_command(D_80088C48, 0x11);
            } else if (work.bytes.unk1 == 0x13) {
                write_resource_command(D_80088C8C, 0x11);
            } else {
                break;
            }
            set_item_selection_data_pointer(object, position, callback_data);
            D_800FE5D8 = (void (*)(void *, void *, void *))&D_80093D48;
            D_800FE518 = 0;
            return;
        }
        default: {
            if (work.bytes.unk1 != 0x13) {
                if (work.bytes.unk1 == 0x12) {
                    mode = find_target_byte_index_in_list();
                    if (get_first_free_four_byte_entry_index_n_1_none_available((void *)0x80010980, D_800D0728[mode]) == -1) {
                        write_resource_command(D_80088CCC, 0x11);
                        set_item_selection_data_pointer(object, position, callback_data);
                        D_800FE5D8 = (void (*)(void *, void *, void *))&D_80093D48;
                        D_800FE518 = 0;
                        return;
                    }
                } else {
                    write_resource_command(D_80088D04, 0x11);
                    set_item_selection_data_pointer(object, position, callback_data);
                    D_800FE5D8 = (void (*)(void *, void *, void *))&D_80093D48;
                    D_800FE518 = 0;
                    return;
                }
            }
            break;
        }
        }

        work.pos.x = position->x;
        work.pos.y = position->y;
        work.pos.z = position->z + D_800D0428;
        mode = 0;
        if (state_is_12_or_13) {
            mode = is_available != 0;
        }
        created_entry = create_configured_object(((S_80093894_3 *)(&D_80110EB8))->unk_00, &work.pos, mode);
        if (created_entry != 0) {
            Unk96134State *state = (Unk96134State *)D_800CFCB4;
            void *next_object;

            next_object = (u8 *)created_entry + 0x20;
            ((S_80093894_4 *)object)->unk_2C = next_object;
            state->unk10 = next_object;
            state->unk18 = 0;
            initialize_actor_movement_interaction_action(object, position, callback_data);
            return;
        }
        initialize_scene_action_record(object, position, callback_data);
        return;
    }

    D_800FE5D8(object, position, callback_data);
}
