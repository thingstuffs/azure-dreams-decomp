#include "common.h"
#include "engine/script.h"
#include "town/map/resource.h"

extern s8 town_resource_command[];

/* Pack a value in little-endian order and a code into the shared buffer and submit it. */
void write_resource_command(s32 value, s8 code) {
    s8 *buffer = town_resource_command;

    buffer[3] = value >> 8;
    buffer[2] = value;
    buffer[4] = value >> 16;
    buffer[5] = value >> 24;
    buffer[6] = code;
    call_script(buffer);
}
