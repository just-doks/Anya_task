#old
#########################################################################################
																						#
OLD_MAIN_SRC:=$(wildcard srcs/old_main.c) 
OLD_MAIN_OBJ:=$(addprefix obj/, $(notdir $(OLD_MAIN_SRC:.c=.o)))
OLD_OBJ_DIR = obj
OLD_SRC_DIR = srcs

OLD_DRIVE_SRCS:=$(wildcard srcs/old/dataManagment/drive_d/*.c) 
OLD_DRIVE_OBJS:=$(addprefix obj/old/dataManagment/drive_d/, $(notdir $(OLD_DRIVE_SRCS:.c=.o)))
OLD_DRIVE_OBJDIR = obj/old/dataManagment/drive_d
OLD_DRIVE_SRCDIR = srcs/old/dataManagment/drive_d

OLD_DOREP_SRCS:=$(wildcard srcs/old/doReport/*.c)
OLD_DOREP_OBJS:=$(addprefix obj/old/doReport/, $(notdir $(OLD_DOREP_SRCS:.c=.o)))
OLD_DOREP_OBJDIR = obj/old/doReport
OLD_DOREP_SRCDIR = srcs/old/doReport
																						#
#########################################################################################

#final
#########################################################################################
																						#
FDP_SRCS:=$(wildcard srcs/fdp/*.c srcs/fdp/linux/*.c)
FDP_OBJS:=$(addprefix obj/fdp/, $(notdir $(FDP_SRCS:.c=.o)))
FDP_OBJDIR = obj/fdp
FDP_SRCDIR = srcs/fdp

BASE_SRCS:=$(wildcard srcs/dataManagment/base_d/*.c)
BASE_OBJS:=$(addprefix obj/dataManagment/base_d/, $(notdir $(BASE_SRCS:.c=.o)))
BASE_OBJDIR = obj/dataManagment/base_d
BASE_SRCDIR = srcs/dataManagment/base_d
																						#
#########################################################################################

MAC_FDP_SRCS:=$(wildcard srcs/fdp/*.c srcs/fdp/macos/*.c)
MAC_FDP_OBJS:=$(addprefix obj/fdp/, $(notdir $(MAC_FDP_SRCS:.c=.o)))
MAC_FDP_OBJDIR = obj/fdp
MAC_FDP_SRCDIR = srcs/fdp

MAIN_SRC:=$(wildcard srcs/main.c) 
MAIN_OBJ:=$(addprefix obj/, $(notdir $(MAIN_SRC:.c=.o)))
OBJ_DIR = obj
SRC_DIR = srcs

DRIVE_SRCS:=$(wildcard srcs/dataManagment/drive_d/*.c) 
DRIVE_OBJS:=$(addprefix obj/dataManagment/drive_d/, $(notdir $(DRIVE_SRCS:.c=.o)))
DRIVE_OBJDIR = obj/dataManagment/drive_d
DRIVE_SRCDIR = srcs/dataManagment/drive_d

DOREP_SRCS:=$(wildcard srcs/doReport/*.c)
DOREP_OBJS:=$(addprefix obj/doReport/, $(notdir $(DOREP_SRCS:.c=.o)))
DOREP_OBJDIR = obj/doReport
DOREP_SRCDIR = srcs/doReport

FDATA_SRCS:=$(wildcard srcs/dataManagment/fdata_d/*.c) 
FDATA_OBJS:=$(addprefix obj/dataManagment/fdata_d/, $(notdir $(FDATA_SRCS:.c=.o)))
FDATA_OBJDIR = obj/dataManagment/fdata_d
FDATA_SRCDIR = srcs/dataManagment/fdata_d

$(info $(MAC_FDP_OBJS))

all: default

demo: $(FDP_OBJS) $(BASE_OBJS) $(DRIVE_OBJS) $(MAIN_OBJ)
	gcc -o $@ $(FDP_OBJS) $(BASE_OBJS) $(DRIVE_OBJS) $(MAIN_OBJ)

#rules for compiling %.c files to %.o files
#####################################################
													#	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)/
	gcc -c $< -o $@ 

$(FDP_OBJDIR)/%.o: $(FDP_SRCDIR)/%.c 
	@mkdir -p $(FDP_OBJDIR)/
	gcc -c $< -o $@ 

$(FDP_OBJDIR)/%.o: $(FDP_SRCDIR)/linux/%.c
	@mkdir -p $(FDP_OBJDIR)/
	gcc -c $< -o $@ 

$(BASE_OBJDIR)/%.o: $(BASE_SRCDIR)/%.c
	@mkdir -p $(BASE_OBJDIR)/
	gcc -c $< -o $@ 

$(DRIVE_OBJDIR)/%.o: $(DRIVE_SRCDIR)/%.c
	@mkdir -p $(DRIVE_OBJDIR)/
	gcc -c $< -o $@ 

$(FDATA_OBJDIR)/%.o: $(FDATA_SRCDIR)/%.c
	@mkdir -p $(FDATA_OBJDIR)/
	gcc -c $< -o $@ 
													#
#####################################################													

full: $(FDP_OBJS) $(BASE_OBJS) $(DRIVE_OBJS) $(DOREP_OBJS) $(FDATA_OBJS) $(MAIN_OBJ)
	gcc -o Launch $(FDP_OBJS) $(BASE_OBJS) $(DRIVE_OBJS) $(DOREP_OBJS) $(FDATA_OBJS) $(MAIN_OBJ)

$(DOREP_OBJDIR)/%.o: $(DOREP_SRCDIR)/%.c
	@mkdir -p $(DOREP_OBJDIR)/
	gcc -c $< -o $@ 


old_full: $(FDP_OBJS) $(BASE_OBJS) $(OLD_DRIVE_OBJS) $(OLD_DOREP_OBJS) $(OLD_MAIN_OBJ)
	gcc -o oldLaunch $(FDP_OBJS) $(BASE_OBJS) $(OLD_DRIVE_OBJS) $(OLD_DOREP_OBJS) $(OLD_MAIN_OBJ)

$(OLD_OBJ_DIR)/%.o: $(OLD_SRC_DIR)/%.c
	@mkdir -p $(OLD_OBJ_DIR)/
	gcc -c $< -o $@ 

$(OLD_DRIVE_OBJDIR)/%.o: $(OLD_DRIVE_SRCDIR)/%.c
	@mkdir -p $(OLD_DRIVE_OBJDIR)/
	gcc -c $< -o $@ 

$(OLD_DOREP_OBJDIR)/%.o: $(OLD_DOREP_SRCDIR)/%.c
	@mkdir -p $(OLD_DOREP_OBJDIR)/
	gcc -c $< -o $@ 



$(MAC_FDP_OBJDIR)/%.o: $(MAC_FDP_SRCDIR)/%.c 
	mkdir -p $(MAC_FDP_OBJDIR)/
	gcc -c $< -o $@ 

$(MAC_FDP_OBJDIR)/%.o: $(MAC_FDP_SRCDIR)/macos/%.c
	mkdir -p $(MAC_FDP_OBJDIR)/
	gcc -c $< -o $@ 

macos: $(MAC_FDP_OBJS) $(BASE_OBJS) $(DRIVE_OBJS) $(DOREP_OBJS) $(FDATA_OBJS) $(MAIN_OBJ)
	gcc -o Launch $(MAC_FDP_OBJS) $(BASE_OBJS) $(DRIVE_OBJS) $(DOREP_OBJS) $(FDATA_OBJS) $(MAIN_OBJ)


default: 
	@echo "print: make -f makefile full"
clean:
	rm -rf Launch oldLaunch demo test report.txt filelist.txt obj/ 