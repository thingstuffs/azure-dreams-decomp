# Directional tile flag processing



4 functions (foff 0xEB680-0xEBEE8) of one original translation unit. Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00301 - CL:dungeon/func_800CB680, CL:dungeon/func_800CB9CC, CL:dungeon/func_800CBBD8, CL:dungeon/func_800CBF3C, CL:dungeon/func_800CBFFC.

Definitions retain retail order; declarations are reconciled in `include/dungeon/effect/mesh.h` to one true prototype, with explicit caller/data-view casts and parameter or live-argument corrections where required (decision 72(d)), preserving object bytes and relocations (proved by tools/tu/tu_merge.py). String literals stay retail imports until the whole TU and its pool extent are recovered (decision 72(f)).
