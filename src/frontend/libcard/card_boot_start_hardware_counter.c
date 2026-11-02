#include "common.h"
#include "frontend/libcard.h"
#include "sdk/libapi.h"

/* Bracket command 0xF2000002 with setup and completion calls. */
void card_boot_start_hardware_counter(void) {
    EnterCriticalSection();
    StartRCnt(0xF2000002);
    ExitCriticalSection();
}
