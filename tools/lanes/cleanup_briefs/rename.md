
## Your task: meaningful names for decompiler locals and parameters

Rename `temp_*`, `var_*`, `phi_*` locals and `argN` parameters (and `spXX` stack locals) to honest names. Renaming a
local or a parameter never changes the compiled bytes - but SCORE every row anyway.
Naming rule (owner, binding): **never a false name.** Name only what the code makes obvious:
- loop counters `i`, `j`, `k`; counts `count`; indices `index`/`slot`; coordinates `x`, `y`, `z`, `dx`, `dy`;
- a pointer from a known shared type in `include/` (EntityRec, GameWork, MapGrid ...) -> `entity`, `work`, `grid`;
- a value read from a named struct field -> the field's name (`flags = e->flags1C;` -> `flags`);
- the return value collected before `return x;` -> `result`;
- a parameter passed straight to a named function's named parameter -> that name.
If you cannot tell what a variable is from the row and the definitions it touches, use a NEUTRAL descriptive name
from its role (`value`, `ptr`, `mask`, `offset`, `tmp`) rather than a guess - never invent a game meaning (no
"hp", "monster", "gold" unless a named field/function in the code says so). Do not rename globals (D_*), functions
(func_*), struct fields (unk_*), or anything in a header. Keep one name per variable (no reuse across roles you
create). Do not change declarations' types, order or scope. Rename consistently across the K&R parameter list and its
declarations if the row is K&R style. In the report, give each new name with its one-line evidence.
