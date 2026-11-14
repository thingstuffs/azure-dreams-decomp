#ifndef TOWN_PERSON_CALLBACKS_API_H
#define TOWN_PERSON_CALLBACKS_API_H

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct SpriteFrameState;
struct TownObjectRecord;
struct town_gray_fade_color;
struct town_gray_fade_state;
struct town_rising_reaction_object;
void finish_selfy_magic_fade(struct town_gray_fade_state *state, int unused_arg, struct town_gray_fade_color *color);
void dispatch_record_handler(struct TownObjectRecord *record, void *dispatch_arg, void *dispatch_data, int check_arg);
void raise_reaction_output_until_expiry(struct town_rising_reaction_object *obj, int update_input_1, struct SpriteFrameState *update_input_2);

#endif
