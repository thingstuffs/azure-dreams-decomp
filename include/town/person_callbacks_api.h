#ifndef TOWN_PERSON_CALLBACKS_API_H
#define TOWN_PERSON_CALLBACKS_API_H

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct ObjectPosition;
struct SpriteFrameState;
struct TownObjectRecord;
void finish_selfy_magic_fade(struct TownObjectRecord *state, struct ObjectPosition *unused_position, struct SpriteFrameState *sprite);
void dispatch_record_handler(struct TownObjectRecord *record, struct ObjectPosition *dispatch_arg, struct SpriteFrameState *dispatch_data, int check_arg);
void raise_reaction_output_until_expiry(struct TownObjectRecord *object, struct ObjectPosition *position, struct SpriteFrameState *sprite);

#endif
