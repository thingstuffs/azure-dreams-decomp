#include "common.h"
#include "frontend/card.h"

typedef struct { u8 pad[0x10]; void *callback; u8 pad14[0x2C]; void *first, *second; } Owner;
extern void func_80400948(void);
extern u8 frontend_action_resume_address[];
/*
 * Creates the card background and slot objects, saves their handles, runs the screen setup, and
 * installs frontend_action_resume_address.
 */
void card_dev_create_slot_screen_objects(u8 *work) {
    Owner *owner = (Owner *)(work - 0x20);
    *(s32 *)(work + 0x20) = init_card_background_object((s32)owner, (s32)(work + 0xC));
    *(void **)(work + 0x24) = init_card_slot_object((s32)owner);
    func_80400948();
    owner->callback = frontend_action_resume_address;
}
