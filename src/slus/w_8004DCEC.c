#include "slus/message_mode_81550.h"
#include "slus.h"

typedef void (*FuncPtr_8004DCEC)(char *);
extern char message_mode_work_buffer[2];

/* Calls the selected mode handler with the shared work buffer. */
void runtime_call_selected_mode_handler(void)
{
    FuncPtr_8004DCEC handler;
    handler = message_mode_handlers[message_handler_mode];
    handler(message_mode_work_buffer);
}
