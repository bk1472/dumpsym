.PHONY : tags ccdv

OBJ_DIR		 = $(TOP_DIR)/objs
INC_DIR		 = $(TOP_DIR)/include
MKD_ERR		 = $(TOP_DIR)/.d.err
SCRPT_DIR	 = $(TOP_DIR)/script
CCDV_DIR	 = $(SCRPT_DIR)/ccdv.src

CC			 = gcc
CCDV_OPTS	?= -v0 -p -x 1000
CCDV		 = $(SCRPT_DIR)/ccdv $(CCDV_OPTS)

CFLAGS		 =
CFLAGS		+= -O2
CFLAGS		+= -I$(INC_DIR) -I.
CFLAGS		+= -DUNIX
CFLAGS		+= -DMKSYM
CFLAGS		+= -Wno-format
CFLAGS		+= -Wno-unused-result

all : $(SCRPT_DIR)/ccdv
