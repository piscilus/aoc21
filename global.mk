.PHONY: all debug release clean
.DEFAULT_GOAL = debug

OBJECTDIR = ./objects
OBJECTDIR_RELEASE = ./$(OBJECTDIR)/release
OBJECTDIR_DEBUG = ./$(OBJECTDIR)/debug


#COMPILER
CC=gcc

CFLAGS =\
	-c\
	-std=c99\
	-Wall\
	-Wextra\
	-Wpedantic
CFLAGS_RELEASE = -DNDEBUG
CFLAGS_DEBUG =


#LINKER
LD=gcc

LDFLAGS =
LDFLAGS_RELEASE = -Wl,-Map -Wl,release/$(TARGET_NAME).map
LDFLAGS_DEBUG = -Wl,-Map -Wl,debug/$(TARGET_NAME).map


OBJECTS_RELEASE = $(addprefix $(OBJECTDIR_RELEASE)/, $(SOURCES:.c=.o) )
OBJECTS_DEBUG = $(addprefix $(OBJECTDIR_DEBUG)/, $(SOURCES:.c=.o) )


$(OBJECTDIR_RELEASE)/%.o: %.c
	@echo 'Building file: $*.c in $(@D)'
	-mkdir  -p $(@D)
	$(CC) $(INCLUDES) $(CFLAGS) $(CFLAGS_RELEASE) $(DEFINES) -o $@ -l $(@D) $<
	@echo ' '

$(OBJECTDIR_DEBUG)/%.o: %.c
	@echo 'Building file: $*.c in $(@D)'
	-mkdir  -p $(@D)
	$(CC) $(INCLUDES) $(CFLAGS) $(CFLAGS_DEBUG) $(DEFINES) -o $@ -l $(@D) $<
	@echo ' '

release/$(TARGET_NAME).exe: $(OBJECTS_RELEASE)
	@echo 'Building target: $@'
	mkdir -p release
	$(LD) $(OBJECTS_DEBUG) $(LDFLAGS) $(LDFLAGS_RELEASE) -o $@
	@echo 'Finished building target: $@'
	@echo ' '

debug/$(TARGET_NAME).exe: $(OBJECTS_DEBUG)
	@echo 'Building target: $@'
	mkdir -p debug
	$(LD) $(OBJECTS_DEBUG) $(LDFLAGS) $(LDFLAGS_DEBUG) -o $@
	@echo 'Finished building target: $@'
	@echo ' '

debug: debug/$(TARGET_NAME).exe
release: release/$(TARGET_NAME).exe
all: clean debug

clean:
	rm -rfd $(OBJECTDIR)
	rm -rfd release
	rm -rfd debug
