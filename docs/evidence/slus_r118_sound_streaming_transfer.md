# Sound streaming transfer: bounded integration and interface review

Reviewer: pending. This is a one-function present integration point within the
established stock-2.7.2 sound TU, not an original source filename or TU-boundary
claim. The actual logical recipe is stock 2.7.2 with empty compiler/assembler
flags. The complete func_8005E7E0 streams bounded chunks and waits on the event;
all its calls, loops, state save/restore and return values are retained.

The actual ten-word table replaces its redundant record wrapper. Three accessed
state/shift/event words become scalar s32. The sample buffer is declared as an
extent-free byte array because only its address is passed; no buffer allocation
or extent is added. The command prototype matches func_8005D1D0(s32, ...), and
the range predicate matches its canonical u32 value parameter. The existing
argument widths/promotions are preserved. An exact frozen-raw control and exact
whole-object identity preceded staging at the unchanged recipe.

The neighboring-symbol aliases and existing volatile local/alias accesses are
retained, not justified as historical source. They remain source-quality debt
for a future concrete C-shape investigation. This input package does not add
an alias, qualifier, padding or accessed extent, and certification alone grants
no L4/L5 source-quality promotion. The independent transfer helper cluster
uses different present views of those symbols and is not silently merged here.

Delivery requires the unchanged fresh full retail-image build and complete
module/member direct genuine ASPSX 2.79 proof with zero masked retail relocations.
No allocated data, logical split record, collector part, rowbase, recipe
exception, gate tool, window value or noreturn census is changed. Membership
review and real --write remain orchestrator actions after final landed inputs.

Rebase receipt at 97f105e7f: this input uses the committed code/code2 parent recipes (both 2.7.2-cdk) and preserves the seven-function stock-2.7.2 sound_tu_code partition. Any earlier production proof is historical; this delivery requires fresh unchanged full-image, member/physical-owner genuine and relevant production-window checks at this HEAD. No old collector recipe, asm alias, compiler flag, pin-census implementation or parked-container setting is restored. Reviewer remains pending.
