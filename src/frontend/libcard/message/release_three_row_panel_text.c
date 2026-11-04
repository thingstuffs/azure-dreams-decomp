#include "frontend/libcard/save_heading.h"
#include "common.h"
#include "frontend/libcard/message.h"
#include "slus.h"

/* Passes the referenced panel entry to noop_release_notification. */
void release_three_row_panel_text(CardSaveHeadingDisplayPrefix *object) {
    noop_release_notification(object->heading->payload.word);
}
