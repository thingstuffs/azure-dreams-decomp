#include "frontend/libcard.h"
#include "frontend/libcard/message.h"

/* func_80024BB4 is a second placed copy of init_card_choice_templates (same
 * bytes, entry, block, vector); that name binds to the copy at its home, so the
 * call keeps the address.  func_80024ACC is an unregistered code region.
 * advance_timed_visual is the name bound to 0x80024D10; this copy only stores
 * one word (the name came from a dungeon function at the same address). */
extern void func_80024BB4(CardDisplayNode *entry, CardDisplayBlock *block, DisplayPositionWords *vector);
extern void func_80024ACC(CardFileListPanel *panel);

/* Store the selection, link the panel's heading templates, and lay out its display. */
void init_card_file_list_panel(CardFileListPanel *panel, s32 selection)
{
    advance_timed_visual(&panel->selection, selection);
    func_80024BB4(&panel->heading, &panel->heading_block, &panel->heading_vector);
    func_80024ACC(panel);
}
