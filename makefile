TOP_DIR		 = .

include		$(TOP_DIR)/incs.mk


TGT			 = $(TOP_DIR)/dumpsym

SRCS		 =
SRCS		+= main.c
SRCS		+= elf.c
SRCS		+= process.c
SRCS		+= addr2line.c
SRCS		+= dwarf.c
SRCS		+= hist.c
SRCS		+= util.c

OBJS		 = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

all : $(TGT)

$(TGT) : $(OBJS)
	@$(CCDV) $(CC) -o $@ $(OBJS) -lz

clean :
	@rm -f $(OBJ_DIR)/*.o
	@rm -f $(TGT)

clobber : clean
	@rm -rf $(OBJ_DIR)

tags :
	@ctags -R

include		$(TOP_DIR)/rules.mk
