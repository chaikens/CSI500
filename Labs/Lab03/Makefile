# IDEA OF MAKE:
# "make TARGET" is supposed to make the TARGET file up-to-date.
# Algorithm outline for "make TARGET"
# (1) (recursively) make each of the dependencies (listed after the :)
#     This will check the up-to-dateness of each dependency.
#     Those that are updated are recorded as YOUNGER than the TARGET.
# (2) If the TARGET file is missing or one or more dependency is 
#     YOUNGER than the TARGET, then the COMMANDS (on tabbed lines below)
#     are performed.
# (3) Often, the COMMANDS recreate the TARGET.  $@ within a command
#     evaluates to the TARGET (name).  
# (4) Sometime, the COMMANDS don't recreate the TARGET.  Makefile
#     programmers write such commands so "make TARGET" executes the
#     commands ALWAYS.  Examples: make config and make help
#

ifneq ($(MAKECMDGOALS),clean)
include dot.config
endif


CONF=${CONFIG_VOLATILE}${CONFIG_OPT}

raceDriver-${CONF} : racer.h config.h raceDriver.c \
racer-${CONF}.o Makefile
	gcc -o $@ -pthread -include config.h raceDriver.c \
            racer-${CONF}.o

racer-${CONF}.o : racer-${CONF}.s Makefile
	gcc -c  racer-${CONF}.s

racer-${CONF}.s : config.h racer.c racer.h Makefile
	gcc -c -S ${CONFIG_OPT} -include config.h         \
             racer.c -o racer-${CONF}.s

dot.config:  WasConfigured
	touch WasConfigured
	nano dot.config
	touch dot.config

WasConfigured:

config:
	rm WasConfigured
	$(MAKE) dot.config

config.h: dot.config
	sed -e '{/^CONFIG_.*=.*/!d}'                      \
            -e '{s/^CONFIG_\(.*\)=\(.*\)/#define CONFIG_\1 \2/}' \
             dot.config > config.h

help:
	@echo
	@echo 'make to build a raceDriver'
	@echo 'make config to edit the configuration file to specify'
	@echo '    (1) whether the shared variable is declared volatile'
	@echo '    (2) whether the racer is compiled with optimization'
	@echo 'We force you to edit the configuration file initially.'
	@echo '    This technology is similar to configuration of '
	@echo '    Linux kernel builds, roughly.'
	@echo 'make clean to remove machine built and backup files'

.phony: clean help config 

clean:
	rm -f *.o *.s *~ raceDriver raceDriver-* *.bak config.h WasConfigured

