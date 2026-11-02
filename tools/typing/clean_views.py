#!/usr/bin/env python3
"""Remove pointer-only view chains from arguments already accepted without them.

Only complete-record pointer bases and compatible final argument conversions are
handled. Byte arithmetic, integer casts, macros and qualified views are retained.
The enclosing batch still requires native and production byte proof.
"""
import sys
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2]
sys.path[:0]=[str(ROOT/'tools/typing'),str(ROOT/'tools'),str(ROOT/'tools/lint'),str(ROOT)]
import cast_ast as A
import cast_fold as F
import param_retype as P
import field_census as C

def clean(root, touched):
    texts={};physical,_=F.physical_for(root,list(touched))
    for tu,recipe in physical.items():
        unit,err=A.clang_unit(root,tu,recipe)
        if unit is None:raise ValueError('parse:'+tu)
        edits={}
        for file,fn in unit.functions(set(touched)):
            if fn['name'] not in touched[file]:continue
            text=unit.text(file)
            for call,parent in A.walk(fn):
                if call.get('kind')!='CallExpr':continue
                for arg in A.kids(call)[1:]:
                    expected=P.decay(unit.canon(C.qtype(arg)))
                    node=arg;casts=0;unsafe=False
                    while node.get('kind') in ('ParenExpr','ImplicitCastExpr','CStyleCastExpr') and A.kids(node):
                        if A.in_macro(node):unsafe=True;break
                        if node['kind']=='CStyleCastExpr':
                            ty=C.qtype(node)
                            if '*' not in ty or any(q in ty for q in ('const','volatile','(*')):
                                unsafe=True;break
                            casts+=1
                        node=A.kids(node)[0]
                    if unsafe or not casts or not A.pure(node) or A.in_macro(arg):continue
                    ty=C.qtype(node)
                    if any(q in ty for q in ('const','volatile')) or not unit.record_of_pointer(ty):continue
                    source=P.decay(unit.canon(ty))
                    if expected!='void*' and expected!=source:continue
                    span=A.node_range(arg,text);inner=A.node_range(node,text)
                    if span is None or inner is None:continue
                    edits.setdefault(file,[]).append((span[0],span[1],text[inner[0]:inner[1]]))
        for file,changes in edits.items():
            texts[file]=P.apply_text_edits(unit.text(file),changes)
    return texts
