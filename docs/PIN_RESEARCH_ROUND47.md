# Round 47: recover local returns, then transfer the repair

Two constructors become pin-free, removing **ten pins**. The new census is
**6,039 pins in 1,273 rows**, 64 removed since the reopened baseline.
The unchanged stock recipe is `2.8.1-G0`. Publication gates are recorded in
[the durable receipt](evidence/pin_research_round47_20260917.json).

## The useful mechanical unit is a complete repair

The direct-table audit covers all 96 remaining DUNGEON files containing the
allocator/render-helper pair outside round 46's fifteen-member image cluster.
Thirty-eight have pins. Three static-address transfers were selected before
compilation. Table replacement alone leaves two constructors at distance 3;
direct arguments leave them at distance 5. Stock CDK reproduces that residue.
Compiler diagnosis found an existing callback keep blocking the branch-slot
scheduler's scan, but the more consequential problem was the source's CFG.

`818A4A64` and `818A4948` pretend their allocation failure jumps call external
noreturn functions. At their already-solved runtime bases, these jumps land on
their own epilogues and return zero. Nearby proven functions, contiguous
callbacks and the bank's pointer header corroborate the mapping. The repair
uses ordinary `if (object != NULL) { ...; return object; } return NULL;`, direct
static callback/table addresses and the actual resident helper contracts.
All four and six pins disappear together, including the global v0 bindings
and the final coordinate-use fences. Full linked bytes match 55/55 and 58/58.

The first normal-return form had only a branch-layout residue; expressing the
positive allocation arm closes it. Applying that same pattern to the sibling
also matches. This is a demonstrated transfer, without a compiler change,
replacement constraint or a broad search through C spellings. The row-local
base records are promoted with fresh strict recompiles; no region is widened.
See [the independent review](evidence/pin_research_constructor_review_20260917.md).

The generic arm-collapse lander correctly refuses this semantic correction:
the old port arm also contains the false noreturn call, so its generated code
must change. The reviewed whole-C route proves the actual local return and
new port compilation instead of claiming old/new port identity. No recipe
transition is needed.

Other bounded controls remain negative: `8092192C`'s table-only repair misses
by 13, and all seven isolated erasures in the changed caller `81338C4C` miss
(distances 5, 33, 3, 3, 2, 14, 2). None establishes a minimum pin count.

## Snapshot140: allocation is now explained quantitatively

The 140-byte prefix/longer record relationship is real: the source accesses a
byte at +0xA8 outside the copied prefix. Giving it a named prefix and fields still
produces the same 13 register substitutions in the 17-pin partial candidate.
A pointer registry plus indexed buffer only commutes two additions; it does
not fix the roles. A zero-offset prefix does not prevent the compiler from
merging its pointer back into the containing record's pointer.

Bindings in later regions also affect the first loop. GCC first prefers hard
registers already marked used, including those bound later in the function.
Removing the second-loop index/destination bindings sends the selected record
to the remaining bound page register. Removing all four saved-register bindings
and then the old flags/page keeps remains nonexact (15/13/11 pins, distances
37/38/38). These controls remove existing constraints; they add no replacements.

The ordinary zero-pin candidate's input/HIGH swap has a distinct, measured
cause. Removing dead old cursor setup changes the HIGH from three to four
references. GCC's `floor_log2(refs)` factor doubles at that boundary. Input's
priority is 1147, HIGH's 1176, so HIGH gets s6 and input gets s7. The earlier
candidate had priorities 1138/428 and the retail order, but also dead setup.
The exact compiler executable, dump counts, conflicts and allocation order
corroborate the explanation. Dead setup is not retained as a solution.

Using the input's actual two-element reference array improves distance 35 to 30
at 181 words. Strength reduction recreates a separate cursor, so input still
has seven references and priority 1157, below HIGH's 1176. The improvement is
third-loop scheduling, not a recovered register assignment. Further priority
experiments require genuine source relationships, rather than extra uses or
changes to compiler costs.

## Scale through bounded whole-function batches

The post-landing mechanical join identifies **32 remaining DUNGEON functions
with 328 pins** whose scored C calls an alleged noreturn target that retail
jumps to inside that same row at a solved/proven base. Eleven of these contain
an allocator call and carry 143 pins. These are routing counts, not promised
removals: some targets are interior blocks and some pins have unrelated causes.
A nearby `jr ra` alone does not prove that the target is an epilogue. The scan
is a bounded subset of the remaining tree, not a count of distinct patterns.

Historical evidence supports discovery followed by automation: the shape
sweep in `PIN_PATTERNS.md` removed 121 pins and its follow-up erasure removed
44; the same-register merge generator in `LANE_KIT.md` removed 238 pins after
small-pack discoveries. These are historical, overlapping campaign stages;
do not add them to this round's ten or call them current opportunities.
Gemini's two base-address examples also generalized to 29 rows. Broad old
Gemini REG lanes had only a 6% recorded exact-row rate, so repeat that model
on a newly evidenced mechanism rather than rerun that spent pool.

Use one complete function per cheap-model task, with the current source hash,
full retail/site map, correct base and stock recipe, a solved family example,
known failures and local verification commands. Begin with one Gemini pilot
through the installed `agy` CLI: `818B15F4`, 112 bytes, one pin, two jumps to
its own epilogue. It differs from the constructors by a switch dispatch, so
its table must be decoded before restructuring it. Limit the task to six
meaningful candidate compiles and four minutes, scratch output only.

Then compare a small Luna/Sol/Gemini batch by accepted pins, exact rows,
compiles, elapsed time and available usage statistics. Escalate shared
blockers only; record failures so resets do not repeat them. Mechanize a
repair after a second independent match, rerun erasure on changed functions,
and perform independent semantics/caller and full publication gates locally.
Pause the open-ended Snapshot allocation lane while measuring this transfer
route. The zero-pin goal remains active; no architectural minimum is proved.

Gemini pilot completed in 242.6 seconds and produced five candidates. It
correctly decoded the eight-entry table (states 4/5/6 call the three helpers;
others take the local return) and produced an independently exact 28/28 local
return reconstruction. That candidate retains the existing one table keep.
The ordinary address variant misses by five substitutions. No pilot source
was published and no additional pin removal is claimed. The CLI text output
provides no token usage; elapsed time and candidates are recorded, not an
invented cost estimate. This establishes a usable delegation path, not its
population success rate. Keep the result for a separately attributed compiler
address-lowering experiment; do not repeat the five source spellings.
