#include "engine/message.h"
#include "engine/message/data.h"
#include "engine/script/vm.h"

/* Set the current text column and row. */
void store_script_state_pair(s16 column, s16 row) {
    runtime_script_state.window.column = column;
    runtime_script_state.window.row = row;
}
