.PHONY : tags ccdv

OBJ_DIR		 = $(SRC_DIR)/objs
INC_DIR		 = $(SRC_DIR)/include
MKD_ERR		 = $(SRC_DIR)/.d.err
SCRPT_DIR	 = $(SRC_DIR)/script
CCDV_DIR	 = $(SCRPT_DIR)/ccdv.src

CC			 = gcc
CCDV_OPTS	?= -v0 -p -x 1000
CCDV		 = $(SCRPT_DIR)/ccdv $(CCDV_OPTS)

CFLAGS		 =
CFLAGS		+= -O2
CFLAGS		+= -I$(INC_DIR) -I.
CFLAGS		+= -DUNIX
CFLAGS		+= -DMKSYM
CFLAGS		+= -DBIT_WIDTH=$(BIT_SZ)
CFLAGS		+= -Wno-format
CFLAGS		+= -Wno-unused-result
CFLAGS		+= -Wno-incompatible-pointer-types
CFLAGS		+= -Wno-pointer-to-int-cast

all : $(SCRPT_DIR)/ccdv
