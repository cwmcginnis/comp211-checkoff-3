CC ?= cc
CFLAGS ?= -O3 -std=c11 -Wall -Wextra -Wpedantic

N ?= 1024
T ?= 64

SIZES ?= 1024
TILES ?= 64

OBJS = matmul.o ijk.o ikj.o tiled.o

.PHONY: all run test test-ijk test-ikj test-tiled clean

all: matmul

matmul: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

$(OBJS): matmul.h

run: matmul
	@echo "N=$(N)"
	@./matmul ijk $(N)
	@./matmul ikj $(N)
	@./matmul tiled $(N) $(T)

test-ijk: matmul
	@for n in $(SIZES); do \
		echo "N=$$n"; \
		./matmul ijk $$n; \
	done

test-ikj: matmul
	@for n in $(SIZES); do \
		echo "N=$$n"; \
		./matmul ikj $$n; \
	done

test-tiled: matmul
	@for n in $(SIZES); do \
		echo "N=$$n"; \
		for t in $(TILES); do \
			./matmul tiled $$n $$t; \
		done; \
	done

test: test-ijk test-ikj test-tiled

clean:
	rm -f matmul $(OBJS)

