
DUMP_TARGET_RULES := 1
DUMP_RULES_FILE   := rulesdump.txt

USE_LIBRARY		   := 1
IS_STATIC_LIBRARY  := 0
IS_DYNAMIC_LIBRARY := 1
LIB_NAME       	   := echo_server
LIB_DYN_LDFLAGS	   := --shared
LIB_DIR			   := lib

USE_TARGET		:= 1

CC  			:= gcc
CXX 			:= g++
LNK				:= ld
ARCHIVE			:= ar

CFLAGS   		:= -g -Wall -fpic
CXXFLAGS 		:= 
LDFLAGS  		:=
LDLIBS   		:= 

INCLUDE_FOLDER  := include ../include/api
SOURCE_FOLDER   := src
PROGRAMS_FOLDER := programs

OBJECTS_DIR 	:= .objects
BIN_DIR			:= .

SOURCE_FILES_CXX:= $(shell find $(SOURCE_FOLDER) -type f -name "*.cpp") 
SOURCE_FILES_C  := $(shell find $(SOURCE_FOLDER) -type f -name "*.c")
INCLUDE_DIRS 	:= $(shell find $(INCLUDE_FOLDER) -type d)

OBJECTS_C		:= $(patsubst $(SOURCE_FOLDER)/%.c,$(OBJECTS_DIR)/%.o,$(SOURCE_FILES_C))
OBJECTS_CXX 	:= $(patsubst $(SOURCE_FOLDER)/%.cpp,$(OBJECTS_DIR)/%.o,$(SOURCE_FILES_CXX)) $(OBJECTS_C)

INCLUDE_DIR_FLAGS = $(foreach HEADER_,$(INCLUDE_DIRS),-I$(HEADER_)) 
CFLAGS += $(INCLUDE_DIR_FLAGS)
CXXFLAGS += $(INCLUDE_DIR_FLAGS)

$(info ------ found project files)
$(info C SOURCES    : $(SOURCE_FILES_C))
$(info CXX SOURCES  : $(SOURCE_FILES_CXX))
$(info INCLUDE DIRS : $(INCLUDE_DIRS))
$(info ------ using environment)
$(info SOURCE FOLDER: $(SOURCE_FOLDER))
$(info BIN    FOLDER: $(BIN_DIR))
$(info OBJECT FOLDER: $(OBJECTS_DIR))
$(info ------ using compiler flags)
$(info CXXFLAGS     : $(CXXFLAGS))
$(info CFLAGS		: $(CFLAGS))
$(info INCLUDE_DIRS : $(INCLUDE_DIR_FLAGS))
$(info LDFLAGS		: $(LDFLAGS))
$(info LDLIBS		: $(LDLIBS))

TARGETS_C   := $(shell find $(PROGRAMS_FOLDER) -type f -name "*.c")
TARGETS_CXX := $(shell find $(PROGRAMS_FOLDER) -type f -name "*.cpp")

FILE_TARGETS += \
	$(foreach T_,$(notdir $(basename $(TARGETS_C))), $(BIN_DIR)/$(T_)) \
	$(foreach T_,$(notdir $(basename $(TARGETS_CXX))), $(BIN_DIR)/$(T_)) 

$(info ------ found targets)
$(info $(TARGETS_C))
$(info $(TARGETS_CXX))
$(info ------ generating executables)
$(info EXECUTABLES : $(FILE_TARGETS))

define __LINK_STATIC_EXPANSION_C__
$(LIB)/$(notdir $(basename $(1))).a : $(OBJECTS_C) 
	$(ARCHIVE) rcs $(LIB)/$(notdir $(basename $(1))).a $(OBJECTS_C)
endef

define __LINK_DYNAMIC_EXPANSION_C__
$(LIB_DIR)/$(notdir $(basename $(1))).so : $(OBJECTS_C)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIB_DYN_LDFLAGS) -o $(LIB_DIR)/$(notdir $(basename $(1))).so $(OBJECTS_C) $(LDLIBS)
endef

define __SOURCE_EXPANSION_CXX__
$(OBJECTS_DIR)/$(notdir $(basename $(1))).o : $(1)
	$(CXX) $(CXXFLAGS) -c $(1) -o $(OBJECTS_DIR)/$(notdir $(basename $(1))).o
endef

define __SOURCE_EXPANSION_C__
$(OBJECTS_DIR)/$(notdir $(basename $(1))).o : $(1)
	$(CC) $(CFLAGS) -c $(1) -o $(OBJECTS_DIR)/$(notdir $(basename $(1))).o
endef

define __TARGET_EXPANSION_CXX__
$(BIN_DIR)/$(notdir $(basename $(1))) : $(OBJECTS_C) $(OBJECTS_CXX) $(OBJECTS_DIR)/$(notdir $(basename $(1))).o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(BIN_DIR)/$(notdir $(basename $(1))) $(OBJECTS_DIR)/$(notdir $(basename $(1))).o $(OBJECTS_C) $(OBJECTS_CXX) $(LDLIBS)
$(OBJECTS_DIR)/$(notdir $(basename $(1))).o : $(1)
	$(CXX) $(CXXFLAGS) -c $(1) -o $(OBJECTS_DIR)/$(notdir $(basename $(1))).o
endef

define __TARGET_EXPANSION_C__
$(BIN_DIR)/$(notdir $(basename $(1))) : $(OBJECTS_C) $(OBJECTS_DIR)/$(notdir $(basename $(1))).o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/$(notdir $(basename $(1)))  $(OBJECTS_DIR)/$(notdir $(basename $(1))).o $(OBJECTS_C) $(LDLIBS)
$(OBJECTS_DIR)/$(notdir $(basename $(1))).o : $(1)
	$(CC) $(CFLAGS) -c $(1) -o $(OBJECTS_DIR)/$(notdir $(basename $(1))).o
endef


# Generate the Source Rules
ifeq ($(DUMP_TARGET_RULES),1)
$(info ----- Dumping Rules to file: $(DUMP_RULES_FILE))
$(foreach SOURCE_,$(SOURCE_FILES_C),$(file >$(DUMP_RULES_FILE),$(call __SOURCE_EXPANSION_C__, $(SOURCE_))))
$(foreach SOURCE_,$(SOURCE_FILES_CXX),$(file >>$(DUMP_RULES_FILE),$(call __SOURCE_EXPANSION_CXX__, $(SOURCE_))))
endif
$(foreach SOURCE_,$(SOURCE_FILES_C),$(eval $(call __SOURCE_EXPANSION_C__, $(SOURCE_))))
$(foreach SOURCE_,$(SOURCE_FILES_CXX),$(eval $(call __SOURCE_EXPANSION_CXX__, $(SOURCE_))))


# Generate the Executable Target Rules
ifeq ($(USE_TARGET),1)
ifeq ($(DUMP_TARGET_RULES),1)
$(info ----- Dumping Rules to file: $(DUMP_RULES_FILE))
$(foreach TARGET_,$(TARGETS_C),$(file >>$(DUMP_RULES_FILE),$(call __TARGET_EXPANSION_C__, $(TARGET_))))
$(foreach TARGET_,$(TARGETS_CXX),$(file >>$(DUMP_RULES_FILE),$(call __TARGET_EXPANSION_CXX__, $(TARGET_))))
endif
$(foreach TARGET_,$(TARGETS_C),$(eval $(call __TARGET_EXPANSION_C__, $(TARGET_))))
$(foreach TARGET_,$(TARGETS_CXX),$(eval $(call __TARGET_EXPANSION_CXX__, $(TARGET_))))
endif

# Generate the Library Target Rules
ifeq ($(USE_LIBRARY),1)
ifeq ($(IS_DYNAMIC_LIBRARY),1)
ifeq ($(DUMP_TARGET_RULES),1)
$(file >$(DUMP_RULES_FILE),$(call __LINK_DYNAMIC_EXPANSION_C__, $(LIB_NAME)))
endif
$(eval $(call __LINK_DYNAMIC_EXPANSION_C__, $(LIB_NAME)))
$(info ---- Generated Rules For Dynamic Lib $(LIB_NAME).so)
FILE_TARGETS += $(LIB_DIR)/$(LIB_NAME).so
endif
ifeq ($(IS_STATIC_LIBRARY),1)
ifeq ($(DUMP_TARGET_RULES),1)
$(file >$(DUMP_RULES_FILE),$(call __LINK_STATIC_EXPANSION_C__, $(LIB_NAME)))
endif
$(eval $(call __LINK_STATIC_EXPANSION_C__, $(LIB_NAME)))
$(info ---- Generated Rules For Static Lib $(LIB_NAME).a)
FILE_TARGETS += $(LIB_DIR)/$(LIB_NAME).a
endif
endif

directories:
	$(info Setting up build directories)
	@mkdir -pv $(OBJECTS_DIR)
	@mkdir -pv $(BIN_DIR)
	@mkdir -pv $(LIB_DIR)

all: directories $(FILE_TARGETS) 

clean:
	@rm -rf $(OBJECTS_DIR)
	@rm -rf $(LIB_DIR)
	@rm $(FILE_TARGETS)
	@rm $(DUMP_RULES_FILE)

tests:
	
.PHONY: all clean directories tests