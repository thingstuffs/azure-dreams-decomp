#include "common.h"
#include "town/devkit.h"

extern void _new_card_804086CC(void);
extern s32 _card_write_804086BC(s32, s32, s32);

/* Prepare state and process the target with fixed parameters 63 and 0. */
void reinit_card_and_write_sector(s32 target) {
    s32 saved_target = target;

    _new_card_804086CC();
    _card_write_804086BC(saved_target, 63, 0);
}
