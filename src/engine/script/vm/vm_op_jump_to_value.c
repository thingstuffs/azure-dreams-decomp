#include "common.h"
#include "engine/script/vm.h"

typedef struct Func8003A9B8Table {
    u8 pad_00[0x48];
    u8 *values[256];
} Func8003A9B8Table;

typedef struct Func8003A9B8State {
    u8 pad_00[0x1c];
    u8 *stream;
    u8 pad_20[0x60];
    Func8003A9B8Table *table;
} Func8003A9B8State;

/* Opcode 0x48: Jump to the script address held in v[var]. */
void script_jump_to_variable(Func8003A9B8State *vm) {
    u8 index = *vm->stream;
    vm->stream++;
    vm->stream = vm->table->values[index];
}
