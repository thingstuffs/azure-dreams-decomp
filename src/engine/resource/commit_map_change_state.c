#include "engine/resource.h"
#include "slus/map_state.h"

void commit_map_change_state(void) {
    map_runtime_state = map_change_state;
}
