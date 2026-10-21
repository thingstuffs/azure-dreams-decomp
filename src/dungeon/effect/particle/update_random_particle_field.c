#include "dungeon/effect/particle/update_random_particle_field.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/effect/particle/update_random_particle_field.h"

/* Selector bank entry calls the complete native initialization member. */
void (*const D_80024000)(void *, void *) = update_random_particle_field;
s32 decrement_flagged_item_parameters(DungeonObject *object) {
    s32 changed_count;
    DungeonObjectEntry *entry;
    u8 group;
    u8 column;

    changed_count = 0;
    if (is_linked_object_flagged_10000() != 0) {
        return changed_count;
    }
    entry = object->entry4C;
    if (entry != 0) {
        group = entry->group;
        column = entry->column;
        if ((item_category_groups[group].cells[column].flags & 0x8000) != 0 &&
            entry->amount >= -0x62) {
            entry->amount = (u8)entry->amount - 1;
            changed_count = 1;
        }
    }
    entry = object->entry50;
    if (entry != 0) {
        group = entry->group;
        column = entry->column;
        if ((item_category_groups[group].cells[column].flags & 0x8000) != 0) {
            if (entry->amount >= -0x62) {
                entry->amount = (u8)entry->amount - 1;
                changed_count += 1;
            }
        }
    }
    return changed_count;
}
void update_random_particle_field(void *self, void *output)
{
    Copy24 *copy_src;
    void *effect;
    void *output_data;
    void *search_origin;
    void *target;
    void *particle;
    s32 rand_quotient;
    s16 state;
    s32 spawn_index;
    s32 origin_component;
    s32 random_value;
    s32 value;
    s16 countdown;
    s32 page_value;

    state = ((S_81934928_0 *)self)->unk_0A.s;
    effect = ((S_81934928_0 *)self)->unk_00;
    output_data = output;
    switch (state) {
    case 0:
    {
        if ((((S_81934928_6 *)(((S_81934928_0 *)self)->unk_04))->unk_00 & 0x80) == 0) {
            return;
        }
        {
            ObjectPosition *copy_page;
            *(Copy24 *)output_data = *(Copy24 *)&view_reference_entity;
            copy_page = &view_reference_entity;
            ((S_81934928_0 *)self)->unk_10.s = ((u16)copy_page->x.w.i);
            ((S_81934928_0 *)self)->unk_12.s = ((u16)copy_page->y.w.i);
            page_value = ((u16)copy_page->z.w.i);
        }
        ((S_81934928_0 *)self)->unk_0C.s = 0x3C;
        ((S_81934928_0 *)self)->unk_0A.u++;
        ((S_81934928_0 *)self)->unk_14 = page_value;
        play_sound_if_enabled(0x300);
    }
        /* fallthrough */
    case 1:
    spawn_index = 0x3C - ((S_81934928_0 *)self)->unk_0C.u;
    if (spawn_index >= 8) {
        spawn_index = 8;
    }
    if (spawn_index >= 0) {
        do {
            particle = allocate_list_node(0x202, ((s32 *)(&scene_object_list_anchor)));
            if (particle != NULL) {
                ((S_81934928_2 *)particle)->unk_10 = D_8002445C;
                register_node(particle, D_80024740);
                search_origin = (u8 *)particle + 0x20;

                rand_quotient = rand();
                random_value = rand_quotient;
                origin_component = ((S_81934928_0 *)self)->unk_10.u;
                rand_quotient = random_value / 512;
                value = origin_component + ((random_value % 512)) - 0x100;
                if (value < 0) {
                    value = 0;
                }
                ((S_81934928_3 *)search_origin)->unk_0C = value;
                ((S_81934928_3 *)search_origin)->unk_1E = value;

                rand_quotient = rand();
                random_value = rand_quotient;
                origin_component = ((S_81934928_0 *)self)->unk_12.u;
                rand_quotient = random_value / 512;
                value = origin_component + ((random_value % 512)) - 0x100;
                if (value < 0) {
                    value = 0;
                }
                ((S_81934928_3 *)search_origin)->unk_0E = value;
                ((S_81934928_3 *)search_origin)->unk_22 = value;

                value = ((S_81934928_0 *)self)->unk_14 - 0x100;
                ((S_81934928_3 *)search_origin)->unk_10 = value;
                ((S_81934928_3 *)search_origin)->unk_26 = value;
                ((S_81934928_2 *)particle)->unk_20 = self;
            }
            spawn_index--;
        } while (spawn_index >= 0);
    }

    if (((S_81934928_0 *)self)->unk_0C.u == 0x1E) {
        target = (void *)primary_actor_record;
        if (target != NULL) {
            void *lookup_origin = target;
            while ((target = find_eligible_nearby_entry(reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, lookup_origin, target)) != NULL) {
                if ((((S_81934928_4 *)target)->unk_1C & 0x2000) == 0) {
                    copy_src = (Copy24 *)(u32)((S_81934928_0 *)self)->unk_09;
                    apply_attack_power_and_element_effects(target, 0x20, (s32)copy_src, 0xA,
                                  ((S_81934928_5 *)effect)->unk_2A, effect, 2);
                }
                decrement_flagged_item_parameters(target);
            }
        }
    }

    countdown = ((S_81934928_0 *)self)->unk_0C.s - 1;
    ((S_81934928_0 *)self)->unk_0C.s = countdown;
    if (countdown > 0) {
        return;
    }
    ((S_81934928_0 *)self)->unk_0C.s = 8;
    ((S_81934928_0 *)self)->unk_0A.u = 0xFF;
    return;

    case 0xFF:
    countdown = ((S_81934928_0 *)self)->unk_0C.s - 1;
    ((S_81934928_0 *)self)->unk_0C.s = countdown;
    if (countdown > 0) {
        return;
    }
    {
        u16 effect_flags;
        value = ((S_81934928_0 *)self)->unk_0E.s;
        effect_flags = ((S_81934928_0 *)self)->unk_0E.u;
        if ((value & 0x8000) != 0) {
            value = effect_flags & 0x7FFF;
            ((S_81934928_0 *)self)->unk_0E.u = value;
            return;
        }
    }
    g_dungeon_status.active_actor = 0;
    (*(u16 *)((u8 *)self + -2)) |= 0x8000;
    object_flag_block.flags |= 0x8000;

        return;
    default:
        return;
    }
}
void draw_red(void *effect) {
    s32 ticks_left;
    s32 surface_height;
    s16 state;
    u16 final_display_y;
    SpriteFrameState *impact_sprite;
    S_81934C5C_2 *impact_effect;
    S_81934C5C_1 *owner;

    owner = ((S_81934C5C_0 *)effect)->unk_00;
    ((S_81934C5C_0 *)effect)->unk_48.s = (u16) (((S_81934C5C_0 *)effect)->unk_48.s - 1);
    owner->unk_0E = (u16) (owner->unk_0E | 0x8000);
    state = ((S_81934C5C_0 *)effect)->unk_4C;
    switch (state) {
    case 0:
        ((S_81934C5C_0 *)effect)->unk_48.s = 3U;
        ((S_81934C5C_0 *)effect)->unk_28.at02.v = -4;
        ((S_81934C5C_0 *)effect)->unk_30.at02.v = 0x10;
        ((S_81934C5C_0 *)effect)->unk_4C = (s16) ((u16) ((S_81934C5C_0 *)effect)->unk_4C + 1);

                        /* fallthrough */
    case 1:
        ((S_81934C5C_0 *)effect)->unk_1C.at00.v = (s32) (((S_81934C5C_0 *)effect)->unk_1C.at00.v
            + ((S_81934C5C_0 *)effect)->unk_28.at00.v);
        ticks_left = ((S_81934C5C_0 *)effect)->unk_48.u;
        ((S_81934C5C_0 *)effect)->unk_24.at00.v = (s32) (((S_81934C5C_0 *)effect)->unk_24.at00.v
            + ((S_81934C5C_0 *)effect)->unk_30.at00.v);
        if (ticks_left > 0) {
            return;
        }
        ((S_81934C5C_0 *)effect)->unk_4C = (s16) ((u16) ((S_81934C5C_0 *)effect)->unk_4C + 1);
        return;
    case 2:
        ((S_81934C5C_0 *)effect)->unk_1C.at00.v += ((S_81934C5C_0 *)effect)->unk_28.at00.v;
        ((S_81934C5C_0 *)effect)->unk_0C += (((S_81934C5C_0 *)effect)->unk_28.at02.v * 3) >> 2;
        ((S_81934C5C_0 *)effect)->unk_10 += (((S_81934C5C_0 *)effect)->unk_30.at02.v * 3) >> 2;
        ((S_81934C5C_0 *)effect)->unk_24.at00.v += ((S_81934C5C_0 *)effect)->unk_30.at00.v;
        surface_height = sample_terrain_surface_height(((S_81934C5C_0 *)effect)->unk_1C.at02.v,
            ((S_81934C5C_0 *)effect)->unk_20.at02.v, -0x400);
        if (surface_height >= 0x201) {
            if (((S_81934C5C_0 *)effect)->unk_24.at02.v > 0) {
                ((S_81934C5C_0 *)effect)->unk_4C = 0xFF;
                return;
            }
        }
        if (surface_height >= ((S_81934C5C_0 *)effect)->unk_24.at02.v) {
            return;
        }
        ((S_81934C5C_0 *)effect)->unk_24.at02.v = surface_height;
        impact_effect = allocate_list_node(0x312, ((s32 *)&scene_object_list_anchor.next));
        if (impact_effect != 0) {
            impact_effect->unk_10 = &D_80024928;
            impact_effect->unk_20 = (void *) ((S_81934C5C_0 *)effect)->unk_00;
            register_node(impact_effect, project_sprite_chain);
            impact_sprite = impact_effect->unk_0C;
            ((S_81934C5C_5 *)(impact_effect->unk_08))->unk_00 = (s32) ((S_81934C5C_0 *)effect)->unk_1C.at00.v;
            ((S_81934C5C_5 *)(impact_effect->unk_08))->unk_04 = (s32) ((S_81934C5C_0 *)effect)->unk_20.at00.v;
            ((S_81934C5C_5 *)(impact_effect->unk_08))->unk_08 = (s32) ((S_81934C5C_0 *)effect)->unk_24.at00.v;
            impact_sprite->scale_y = 0x500;
            impact_sprite->scale_x = 0x500;
            impact_sprite->flags = (u16) (impact_sprite->flags | 0xC);
            {
                s32 *animation;

                if (func_80069EF8() & 1) {
                    animation = &D_800DEDB0;
                } else {
                    animation = &D_800DEE38;
                }
                impact_sprite->unk_00 = animation;
                impact_sprite->source = (s32) ((S_81934C5C_4 *)animation)->unk_04;
                impact_sprite->unk_04 = 0;
                impact_sprite->unk_05 = 0;
            }
        }
        ((S_81934C5C_0 *)effect)->unk_4C = (s16) ((u16) ((S_81934C5C_0 *)effect)->unk_4C + 1);
        return;
    case 3:
        ((S_81934C5C_0 *)effect)->unk_0C = (u16) (((S_81934C5C_0 *)effect)->unk_0C
            + ((s32) (((S_81934C5C_0 *)effect)->unk_28.at02.v * 3) >> 2));
        final_display_y = ((S_81934C5C_0 *)effect)->unk_10 + ((s32) (((S_81934C5C_0 *)effect)->unk_30.at02.v * 3) >> 2);
        ((S_81934C5C_0 *)effect)->unk_10 = final_display_y;
        if (((S_81934C5C_0 *)effect)->unk_24.at02.v < (s16) final_display_y) {
            ((S_81934C5C_0 *)effect)->unk_10 = (u16) ((S_81934C5C_0 *)effect)->unk_24.at02.v;
            ((S_81934C5C_0 *)effect)->unk_4C = 0xFF;
        }
        return;
    case 0xFF:
        ((S_81934C5C_0_pre *)effect)[-1].unk_00 = (u16) (((S_81934C5C_0_pre *)effect)[-1].unk_00 | 0x8000);
        object_flag_block.flags |= 0x8000;
        return;
    default:
        return;
    }
}
