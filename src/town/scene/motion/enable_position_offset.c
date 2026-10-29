#include "common.h"
#include "shared/town_delta_words.h"
#include "town/scene/motion.h"

/* Stores 1 in D_80017B98. */
void enable_position_offset(void) { D_80017B98 = 1; }
