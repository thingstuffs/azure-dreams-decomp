## THE CLASS QUESTION (read before the rows)

<!-- TEMPLATE.  Copy this file, fill the four <<...>> slots by hand and pass the copy to
     build_class_pack.py --paragraphs <name>.  It is deliberately NOT a substitution engine: the
     census numbers and the mechanism list are the orchestrator's reading of the round, and a
     generated sentence would say less than a read one.  The filled examples this was taken from:
     work/native_lane/r63_astra_movemove/BRIEF.md (a residue class) and
     work/native_lane/r64_astra_bivhide/BRIEF.md (a census-derived class, with the pass's own
     source lines quoted). -->

These rows were chosen as clean representatives of ONE class, <<CLASS: the residue class label or
the census property, e.g. `MOVED|1-2|-move +move`>>: <<CENSUS: how many pin sites in how many rows,
and what erasing the pin does to the listing - the measured fact, not the story>>. <<WHAT IS ALREADY
KNOWN about the pass that decides it: the source rule and where it was read (file:line), and which
generators already took the easy rows of the class>>.

Your job is the MECHANISM, not only these rows: find the ordinary C shape that makes the pin
unnecessary on as many of them as you can, and state it as a generator rule (APPEARS / RESOLVES /
RECOGNISE THE POPULATION) precise enough to be implemented and swept over the whole class. A rule
that solves three rows of one kind beats five unrelated fixes. Mechanisms found so far, for
orientation (do not assume they apply): <<MECHANISMS: the current short list - the scheduler tie rule
(source order decides among equal priorities; statements written after a call are hoisted above it),
lifetime merge (one variable carrying two consecutive values inherits the register and the ordering
dependence), the allocation-order rule (work/native_lane/r61_alloc_study/NOTE.md), narrow parameter
types (assign_parms), symbol-named addresses at a splitting cell, a store placed next to its
producer (cse), statements sunk into or hoisted out of if-arms, a recovered static __inline__ helper
with narrow parameters>>. "Impossible in C" has been wrong every time in this project: if nothing
works, say exactly what you measured and what you would need to know.
