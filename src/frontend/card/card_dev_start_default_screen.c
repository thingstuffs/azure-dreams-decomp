#include "common.h"
#include "frontend/card.h"
#include "frontend/card/server_imports.h"
#include "frontend/card/effect_mode_data.h"

/* Set the global mode to 2 and invoke the transition routines. */
void card_dev_start_default_screen(void) {
    card_dev_effect_mode = 2;
    card_dev_close_events();
    func_8003D548(3);
}
