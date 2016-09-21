for i in `seq 1 20`; do
	echo -e "Rodando Teste: $i"
	./main < in/$i.in > $i.out
	rm -f doubleHashing.bin
done
for i in `seq 1 20`; do
    echo -e "Comparing: $i"
    diff $i.out out/$i.out
done
