
DUMP_TARGET_RULES := 1
DUMP_RULES_FILE   := rulesdump.txt

CC  			:= gcc
CXX 			:= g++

CFLAGS   		:= 
CXXFLAGS 		:=
LDFLAGS  		:=
LDLIBS   		:= 

INCLUDE_FOLDER  := include
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

TARGETS := $(TARGETS_C) $(TARGETS_CXX)

TARGETS_EXE += \
	$(foreach T_,$(notdir $(basename $(TARGETS_C))), $(BIN_DIR)/$(T_)) \
	$(foreach T_,$(notdir $(basename $(TARGETS_CXX))), $(BIN_DIR)/$(T_)) 

$(info ------ found targets)
$(info $(TARGETS_C))
$(info $(TARGETS_CXX))
$(info ------ generating executables)
$(info EXECUTABLES : $(TARGETS_EXE))

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

ifeq ($(DUMP_TARGET_RULES),1)
$(info ----- Dumping Rules to file: $(DUMP_RULES_FILE))
$(foreach SOURCE_,$(SOURCE_FILES_C),$(file >$(DUMP_RULES_FILE),$(call __SOURCE_EXPANSION_C__, $(SOURCE_))))
$(foreach SOURCE_,$(SOURCE_FILES_CXX),$(file >>$(DUMP_RULES_FILE),$(call __SOURCE_EXPANSION_CXX__, $(SOURCE_))))
$(foreach TARGET_,$(TARGETS_C),$(file >>$(DUMP_RULES_FILE),$(call __TARGET_EXPANSION_C__, $(TARGET_))))
$(foreach TARGET_,$(TARGETS_CXX),$(file >>$(DUMP_RULES_FILE),$(call __TARGET_EXPANSION_CXX__, $(TARGET_))))
endif

$(foreach SOURCE_,$(SOURCE_FILES_C),$(eval $(call __SOURCE_EXPANSION_C__, $(SOURCE_))))
$(foreach SOURCE_,$(SOURCE_FILES_CXX),$(eval $(call __SOURCE_EXPANSION_CXX__, $(SOURCE_))))
$(foreach TARGET_,$(TARGETS_C),$(eval $(call __TARGET_EXPANSION_C__, $(TARGET_))))
$(foreach TARGET_,$(TARGETS_CXX),$(eval $(call __TARGET_EXPANSION_CXX__, $(TARGET_))))


directories:
	$(info Setting up build directories)
	@mkdir -pv $(OBJECTS_DIR)
	@mkdir -pv $(BIN_DIR)

all: directories $(TARGETS_EXE) 

clean:
	@rm -rf $(OBJECTS_DIR)
	@rm $(TARGETS_EXE)
	@rm $(DUMP_RULES_FILE)

tests:
	
.PHONY: all clean directories tests

