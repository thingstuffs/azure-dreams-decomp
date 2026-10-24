#include "frontend/libcard.h"

extern void func_80024D10(void *, s32);
extern void func_80024BB4(void *, void *, void *);
extern void func_80024ACC(void *);

/* Store the selection, link the panel's templates, and lay out its display. */
void init_card_file_list_panel(void *record, s32 selection)
{
    func_80024D10(record, selection);
    func_80024BB4(record + 0xB2C, record + 0xB04, record + 0xB14);
    func_80024ACC(record);
}
