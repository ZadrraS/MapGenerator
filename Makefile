all: feudo_sim
	make all -C src
	mv src/feudo_sim ./
feudo_sim:
	make $@ -C src
	mv src/feudo_sim ./
clean:
	make clean -C src
	rm feudo_sim
.PHONY: feudo_sim