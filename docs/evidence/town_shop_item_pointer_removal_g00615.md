# Item pointer removal (G00615).



2 functions (foff 0x34AB4-0x34B20) of one original translation unit. Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B4A30, CL:town/func_800B4AB4.

Definitions retain retail order; declarations are reconciled in `include/town/shop/item_pointer_removal_g00615.h` to one true prototype, with explicit caller/data-view casts and parameter or live-argument corrections where required (decision 72(d)), preserving object bytes and relocations (proved by tools/tu/tu_merge.py). String literals stay retail imports until the whole TU and its pool extent are recovered (decision 72(f)).
