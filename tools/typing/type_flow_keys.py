"""File-aware identities for cached type-flow facts.

Only a name defined in several files is qualified here. Existing static keys and
unique external names keep their spelling. An unresolved cross-file reference
keeps its ambiguous key so the solver can hold it rather than guess a definition.
"""
from __future__ import annotations

import collections
import re


class FunctionKeys:
    def __init__(self, units):
        self.files = collections.defaultdict(set)
        for unit in units:
            for definition in unit['functions']:
                self.files[definition['key']].add(definition['file'])
        self.collisions = {key for key, files in self.files.items() if len(files) > 1}

    def qualify(self, key, file):
        if key in self.collisions and file in self.files[key]:
            return key + '@' + file
        return key

    def rewrite(self, unit):
        """Re-key the bodies in one TU, including parameters, returns and callbacks."""
        local = collections.defaultdict(set)
        for definition in unit['functions']:
            local[definition['key']].add(definition['file'])

        def function(key, file=''):
            if key not in self.collisions:
                return key
            if file in local[key]:
                return self.qualify(key, file)
            if len(local[key]) == 1:
                return self.qualify(key, next(iter(local[key])))
            return key

        def node(value, file=''):
            if not value:
                return value
            match = re.match(r'^(&?(?:P:|R:|FN:|L:))([^#:*\[\]]+)(.*)$', value)
            if not match:
                return value
            return match[1] + function(match[2], file) + (match[3] or '')

        for definition in unit['functions']:
            definition['key'] = self.qualify(definition['key'], definition['file'])
        for group in ('edges', 'uses', 'int_uses'):
            for fact in unit[group]:
                file = fact.get('file', '')
                for key in ('src', 'dst', 'node', 'root'):
                    if key in fact:
                        fact[key] = node(fact[key], file)
                if 'fn' in fact:
                    fact['fn'] = function(fact['fn'], file)
        for call in unit['calls']:
            file = call.get('file', '')
            call['caller'] = function(call['caller'], file)
            call['callee'] = (function(call['callee'], file) if call['mode'] == 'direct'
                              else node(call['callee'], file))
        declarations = collections.defaultdict(collections.Counter)
        for key, types in unit['decl_types'].items():
            declarations[node(key)].update(types)
        unit['decl_types'] = dict(declarations)
        unit['protos'] = {function(key): value for key, value in unit['protos'].items()}
        return unit
