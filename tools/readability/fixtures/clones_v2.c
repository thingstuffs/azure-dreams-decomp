/* Two exact loop copies and a third with a different stopping condition. */
void corridor_copy(void) {
    for (;;) {
        s32 iy;
        s32 ix;
        s32 tile;
        Cell *cell;
        s32 distance;
        tile = walker->tile & 0xFFE0;
        iy = cy;
        cell = &cells[(iy << shift) + (ix = cx)];
        if (cell->value != 16384) {
            distance = abs(cell->value - (s16)tile);
            if (distance >= 33) {
                return;
            }
        }
        cell->value = tile;
        if (ix == wx && iy == wy) {
            break;
        }
        *(s32 *)walker += *cost;
        count++;
        cx += step_x[direction];
        cy += step_y[direction];
    }
    for (;;) {
        s32 iy;
        s32 ix;
        s32 tile;
        Cell *cell;
        s32 distance;
        tile = walker->tile & 0xFFE0;
        iy = cy;
        cell = &cells[(iy << shift) + (ix = cx)];
        if (cell->value != 16384) {
            distance = abs(cell->value - (s16)tile);
            if (distance >= 33) {
                return;
            }
        }
        cell->value = tile;
        if (ix == wx && iy == wy) {
            break;
        }
        *(s32 *)walker += *cost;
        count++;
        cx += step_x[direction];
        cy += step_y[direction];
    }
    for (;;) {
        s32 iy;
        s32 ix;
        s32 tile;
        Cell *cell;
        s32 distance;
        tile = walker->tile & 0xFFE0;
        iy = cy;
        cell = &cells[(iy << shift) + (ix = cx)];
        if (cell->value != 16384) {
            distance = abs(cell->value - (s16)tile);
            if (distance >= 33) {
                return;
            }
        }
        cell->value = tile;
        if (ix == destination_x && iy == destination_y) {
            break;
        }
        *(s32 *)walker += *cost;
        count++;
        cx += step_x[direction];
        cy += step_y[direction];
    }
}
