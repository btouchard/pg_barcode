all:
	gcc -Wall -Wmissing-prototypes -Wpointer-arith -Wdeclaration-after-statement -Werror=vla -Wendif-labels -Wmissing-format-attribute -Wimplicit-fallthrough=3 -Wcast-function-type -Wformat-security -fno-strict-aliasing -fwrapv -fexcess-precision=standard -Wno-format-truncation -Wno-stringop-truncation -g -g -O2 -fstack-protector-strong -Wformat -Werror=format-security -fno-omit-frame-pointer -fPIC -shared -o pg_barcode.so pg_barcode.o -L/lib/x86_64-linux-gnu -lqrencode -ldmtx

CFLAGS += -std=c99 -O

MODULES 	= pg_barcode
EXTENSION 	= pg_barcode
DATA 		= pg_barcode--1.1.sql
PG_CONFIG 	= pg_config
PGXS 		:= $(shell $(PG_CONFIG) --pgxs)

include $(PGXS)
SHLIB_LINK = -L/lib/x86_64-linux-gnu -lqrencode -ldmtx
