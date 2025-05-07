import pdaggerq as rome


pq = rome.pq_helper('fermi')

pq.add_operator_product(1.0, ['f'])  # add the Fock operator
pq.add_operator_product(1.0, ['v'])  # add the fluctuation operator

pq.simplify()

terms = pq.strings()
print('<0|H|0>')
for string in terms:
    print(string)

pq.clear()
