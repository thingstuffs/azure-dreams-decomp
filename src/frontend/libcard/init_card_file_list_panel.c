#include "frontend/libcard.h"
#include "frontend/libcard/message.h"

/* func_80024BB4 is a second placed copy of init_card_choice_templates (same
 * bytes, entry, block, vector); that name binds to the copy at its home, so the
 * call keeps the address.  func_80024ACC is an unregistered code region. */
extern void func_80024BB4(CardDisplayNode *entry, CardDisplayBlock *block, DisplayPositionWords *vector);

/* Store the selection, link the panel's heading templates, and lay out its display. */
void init_card_file_list_panel(CardFileListPanel *panel, s32 selection)
{
    set_file_list_selection(&panel->selection, selection);
    func_80024BB4(&panel->list_heading, &panel->heading_block, &panel->heading_vector);
    configure_card_file_list_windows(panel);
}
