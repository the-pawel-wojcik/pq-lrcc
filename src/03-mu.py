import pdaggerq
from pdaggerq.parser import contracted_strings_to_tensor_terms
from pdaggerq.algebra import TensorTerm

pq = pdaggerq.pq_helper('fermi')

# Let's pretend that h is the untouched mu
pq.add_operator_product(1.0, ['a*(i)', 'a(a)', 'h'])
pq.add_operator_product(-1.0, ['h', 'a*(a)', 'a(i)'])

# Let's pretend that h is the untouched mu
# pq.add_st_operator(1.0, ['a*(i)', 'a(a)', 'h'], ['t1', 't2'])
pq.simplify()

strings = pq.strings()
print('Strings:')
padding = '  '
for string in strings:
    print(f'{padding}{string}')
print()

tensor_terms: list[TensorTerm] = contracted_strings_to_tensor_terms(strings)
print('Tensor terms:')
for term in tensor_terms:
    print(f'{padding}{term=}')
print()

print('Numpy terms:')
for my_term in tensor_terms:
    einsum_terms = my_term.einsum_string(
        output_variables=('i', 'a'),
        update_val='test',
    )
    print(f"{einsum_terms}")

