AUTEURS := BERNARD_CADIC
INC_DIR := include
MAIN := emul-mips
SRC_C := $(wildcard src/*.c)

$(MAIN): $(SRC_C)
	gcc $^ -o $@ -Og -g -Wall -Wextra -I$(INC_DIR) -D__DEBUG__ 
# -D__NO_CRASH_ON_ERROR__ pour interdire le crash lors des erreurs d'assemblages et d'exécution (peut générer un comportement indéfini)

CLITMP := /tmp/emul-mips-test

test-cli: $(MAIN)
	@ [ -e ./$(MAIN) ] \
	  || echo "error: emul-mips does not exist!"; \
	touch $(CLITMP).in; \
	rm -f $(CLITMP).out1 $(CLITMP).out2; \
	./$(MAIN) $(CLITMP).in $(CLITMP).out1 $(CLITMP).out2 \
	  || echo "error: emul-mips in automatic mode returned $$?!"; \
	[ -e $(CLITMP).out1 ] \
	  || echo "error: assembled output file does not exist!"; \
	[ -e $(CLITMP).out2 ] \
	  || echo "error: final state output file does not exist!"; \
	rm -f $(CLITMP).out1 $(CLITMP).out2

clean:
	rm -f $(MAIN) src/*~ src/*.swap tests/*~ tests/*.swap
	rm -rf __pycache__ .pytest_cache tests/*.hex tests/*.state

tests: $(MAIN)
	@ python3 test.py -v

tar: clean
	@ dir=$$(basename "$$PWD") && cd .. && tar cvfz $(AUTEURS).tgz  "$$dir"
	@ echo "==="; echo "Created ../$(AUTEURS).tgz"

.PHONY: test-cli clean tests tar
