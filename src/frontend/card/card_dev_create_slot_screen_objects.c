#include "common.h"

typedef struct { u8 pad[0x10]; void *callback; u8 pad14[0x2C]; void *first, *second; } Owner;
extern s32 init_card_background_object(s32, s32);
extern void *init_card_slot_object(s32);
extern void func_80400948(void);
extern u8 D_804081AC[];
void card_dev_create_slot_screen_objects(u8 *work) {
    Owner *owner = (Owner *)(work - 0x20);
    *(s32 *)(work + 0x20) = init_card_background_object((s32)owner, (s32)(work + 0xC));
    *(void **)(work + 0x24) = init_card_slot_object((s32)owner);
    func_80400948();
    owner->callback = D_804081AC;
}
