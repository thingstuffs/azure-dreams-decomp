#include "modules/town_player_init.h"

/* Initialize the town scene and configure its object for the current mode. */
void initialize_scene_for_mode(void)
{
    EntityRec *scene;
    TileObject *render;
    func_80092868_TownState *state;
    func_80092868_TownObject *object;
    func_80092868_TownWork *work;
    void *shared_data;
    s32 neutral_color;
    u16 x_offset;
    u16 x_coord;
    u16 y_offset;
    u16 y_coord;
    u16 frame;

    scene = &D_80083780;
    D_80100E18[0] = 0;
    D_80100DB0[0] = 0;
    zero_words(scene, 6);
    render = &D_80082E80;
    zero_words(render, 0xC);
    render->unk_028 = D_80080A80;
    initialize_circular_list_head();

    shared_data = D_800D0420;
    handle_insert_initialize_two_values_status_flags(D_800CFCB4, scene, shared_data);
    initialize_pointer_table_self_links();
    initialize_the_store_two_values_set_state_flags(D_800FE490, scene, shared_data);

    state = &D_8006ADBC;
    if (state->mode == 0x37000C) {
        initialize_object_at_current_position();
        return;
    }

    object = initialize_scene_object_in_buffer(0, ((u8 *)(&D_80083498)), 0x22);
    object->scene = scene;
    object->render = render;

    if (state->alternate != 0) {
        u16 *coords;

        object->callback = D_8008FFC0;
        coords = state->coords;
        scene->x.w.i = state->x_offset + coords[0];
        scene->y.w.i = state->y_offset + coords[1];
        scene->z.w.i = 0;
        copy_entity_record_fields(D_80100D98, scene);
        return;
    }

    {
        u16 *coords;

        object->callback = rebuild_menu_node_list;
        func_8004491C(object, D_800970FC);
        neutral_color = 0x808080;
        render->unk_01E = 0x1000;
        render->unk_01C = 0x1000;

        coords = state->coords;
        x_offset = state->x_offset;
        x_coord = coords[0];
        *(s32 *)(&render->unk_00C) = neutral_color;
        scene->x.w.i = x_offset + x_coord;
        y_offset = state->y_offset;
        y_coord = coords[1];
        scene->z.w.i = -0x80;
        scene->y.w.i = y_offset + y_coord;
        scene->z.w.i = query_lowered_transform_position(scene);
        initialize_six_global_pointers_corresponding_storage_blocks();
        run_the_three_update_routines_context(scene);

        work = (func_80092868_TownWork *)((u8 *)object + 0x20);
        work->field12 = -1;
        frame = state->frame;
        work->frame0 = frame;
        work->frame1 = frame;
        clear_resident_bitmap_bit(0xA4);

        if (test_resident_bitmap_bit(0x1202) == 0) {
            work->active = 0;
        } else {
            work->active = 1;
        }

        render->unk_028 = D_80080A80;
        if ((D_8006ADD4[0] != 0xC) && (find_item_by_kind_and_type(2, 0x13) != 0)) {
            create_person_object();
        }
    }
}
