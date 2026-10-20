#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"

typedef struct {
    s8 type;
    s8 value;
} Slot;
typedef struct {
    u8 pad[0x2C];
    Slot slots[4];
} SlotOwner;

extern void clear_slots_of_type(SlotOwner *owner, s8 match_type);             /* extern */
void begin_deferred_item_action(); /* extern */
void clear_slot_and_update_linked_state();                         /* extern */
s32 get_unused_text_buffer(void);                          /* extern */
s32 expand_text_control_codes();                  /* extern */
void *func_80099290();                         /* extern */
s32 display_text_with_fullwidth_adjustment();                         /* extern */
void apply_item_effect_at_entity_position();                 /* extern */
void display_item_status_message();            /* extern */
s32 apply_actor_food_preference();            /* extern */
void create_timed_paired_particle_emitter();            /* extern */
extern extern M2C_UNK D_80083460[3];
extern M2C_UNK D_800E0E69;


typedef struct S_800BD45C_0_pre {
    s32 unk_00;
    u8 pad_04[0x14];
} S_800BD45C_0_pre;   /* the 0x18 bytes before arg0 in use_item_to_cure_poison, addressed as arg0[-1] */


typedef struct S_800BD45C_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800BD45C_1;   /* counter in use_item_to_cure_poison */

/* Applies an item's effect to an entity and consumes the processed item. */
s32 use_item_to_cure_poison(void *entity, s32 item, s16 action) {
    u16 *type_flags;
    s32 *item_counts;

    if (entity == D_800E3D7C) {
        ((EntityRec *)entity)->unk_110 = item;
        begin_deferred_item_action(entity, &D_80083780.x.v, &D_80082E80.unk_000, entity);
        return 0;
    }
    if ((u32) entity <= 0x9FFFFFFFU) {
        void *call_entity;
        u8 type_id;

        display_item_status_message(entity, item, action);
        call_entity = entity;
        type_id = (*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3));
        if (apply_actor_food_preference(call_entity, (entity_action_selectors[type_id] >> 6) & 3, 0) == 0) {
            apply_item_effect_at_entity_position(entity, item);
            return 1;
        }
    }
    create_timed_paired_particle_emitter(((S_800BD45C_0_pre *)entity)[-1].unk_00, 0x802080, entity);
    if ((((EntityRec *)entity)->flags14 & 0x4000) && !(((EntityRec *)entity)->flags1C & 0x40)) {
        void *message_text;
        s32 message_pos;
        s32 message_start;
        s32 message_end;

        message_end = get_unused_text_buffer();
        message_text = &D_800E0E69;
        message_pos = message_end;
        message_start = message_pos;
        message_end = expand_text_control_codes(message_text, message_pos);
        func_80099290(message_end);
        display_text_with_fullwidth_adjustment(message_start);
    }
    clear_slots_of_type(entity, 5);
    clear_slot_and_update_linked_state(item);
    item_counts = D_80083460;
    ((S_800BD45C_1 *)item_counts)->unk_0A = (u16) (((S_800BD45C_1 *)item_counts)->unk_0A - 1);
    return 1;
}
