import pdaggerq as rome

vacuum_type = 'fermi'
pq = rome.pq_helper(vacuum_type)  # vacuum_type = ‘fermi’/‘true’


# indices convention
# occupied spin-orbitals: i, j, k, l, m, and n
# virtual spin-orbitals: a, b, c, d, e, and f
# general spin-orbitals: s, p, q, r

# Predefined operators
identity = '1'

cc1 = 't1'  # t^a_i a_a^† a_i
cc2 = 't2'  # 1/2 t^ab_ij a_a^† a_b^† a_j a_i
cc3 = 't3'
cc4 = 't4'

sub1 = 'e1(p,q)'  # a _p ^† a_q
sub2 = 'e2(s,p,q,r)'  # a _s ^† a _p ^† a_q a_r
sub3 = 'e3(t,s,p,q,r,u)'  # a _t ^† a _s ^† a _p ^† a_q a_r a_u
sub4 = 'e4(v,t,s,p,q,r,u,w)'

f = 'f'  # Fock's operator
f = 'v'  # fluctuation potential

h = 'h'  # general one-body operator = sum _{pq} h _{pq} a _p ^† a _q
g = 'g'  # general two-body operator

# arbitrary operators
virtual_creator = 'a1'
virtual_annihilator = 'a1*'
occupied_creator = 'i1'
occupied_annihilator = 'i1*'

a = 'a1'
b = 'a2'
c = 'a3'
d = 'a4'
e = 'e1(p,q)'  # one body transition operator = a _p ^† a _q

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


num = 1.0
# num * <bra|ab|ket>
pq.add_operator_product(num, ab)

# num * <bra|[ab, cd]|ket>
pq.add_commutator(num, ab, cd)

#  num * <bra| [[ab, cd], ef] |ket>
pq.add_double_commutator(num, ab, cd, ef)

pq.add_triple_commutator(num, ab, cd, ef, gh)
pq.add_quadruple_commutator(num, ab, cd, ef, gh, prod)
pq.add_st_operator(num, ab, ['t1', 't2'])


""" Printing """
# pq.print()  # seem like it's deprecated in the newer version
# pq.print_fully_contracted()  # also look like it's gone
# strings = pq.fully_contracted_strings()  # also looks like it's gone
strings = pq.strings()
pq.simplify()

from pdaggerq.parser import contracted_strings_to_tensor_terms
from pdaggerq.algebra import TensorTerm
tensor_terms: list[TensorTerm] = contracted_strings_to_tensor_terms(strings)
for term in tensor_terms:
    einsum_terms = term.einsum_string(
        output_variables=('a', 'i'),
        update_val='matrix_name',
    )
    print(f"{einsum_terms}")
