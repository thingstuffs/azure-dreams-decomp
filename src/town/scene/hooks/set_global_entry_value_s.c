#include "common.h"
extern u8 D_80016094[];
extern void *D_80016DC8;
void capture_global_entry_value(void) { D_80016DC8 = D_80016094; }
