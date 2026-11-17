# Return declaration holds

## `check_directional_move_and_terrain` in Hikewne movement

The definition in `src/dungeon/level/tile.c` returns `s32`. The Hikewne
movement caller in `src/dungeon/monster/hikewne/choose_hikewne_move.c`
declares an `s16` return and tests the result against zero at two sites.
Changing only that declaration to `s32` compiled, but the scoped production
link rejected the changed object with `source/import extent 6` for
`dungeon/bank_995000`. The original declaration was restored.

The return width is therefore byte sensitive at this caller. A future
correction needs an explicit source and code generation explanation for the
postcall sign extension and a scoped image match. Do not treat this as a
declaration only correction or change the definition's parameter types to
make the census agree.
