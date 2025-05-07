import pdaggerq as rome

vacuum_type = 'fermi'
pq = pq_helper(vacuum_type) # vacuum_type = ‘fermi’/‘true’

num = 1.0

# arbitrary operators 
a = 'a1'
b = 'a2'
c = 'a3'
d = 'a4'
e = 'e1(p,q)'  # one body transition operator = a _p ^† a _q
f = 'f' # Fock's operator
g = 'g' # general two-body operator
h = 'h' # general one-body operator = sum _{pq} h _{pq} a _p ^† a _q

# Products of as many operators as you wish
ab = [a, b]
cd = [c, d]
ef = [e, f]
gh = [g, h]
prod = ['a7', 'a9']

# <bra| = <0|(a + b)
pq.set_left_operators(ab)

# |ket> = (a + b)|0>
pq.set_right_operators(ab)


# num * <bra|ab|ket>
pq.add_operator_product(num, ab)

# num * <bra|[ab, cd]|ket>
pq.add_commutator(num, ab, cd)

#  num * <bra| [[ab, cd], ef] |ket>
pq.add_double_commutator(num, ab, cd, ef)

pq.add_triple_commutator(num, ab, cd, ef, gh)
pq.add_quadruple_commutator(num, ab, cd, ef, gh, prod)
pq.add_st_operator(num, ab, cd)

pq.print()

strings = pq.strings()
pq.simplify()
pq.print_fully_contracted()
strings = pq.fully_contracted_strings()
