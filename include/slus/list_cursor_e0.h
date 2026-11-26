#ifndef SLUS_LIST_CURSOR_E0_H
#define SLUS_LIST_CURSOR_E0_H

#include "common.h"

/* Word view of external storage; its complete extent is not established. */
extern void (*runtime_callback_entries[16])(void);
extern void (**runtime_callback_write_cursor)(void);

#endif
