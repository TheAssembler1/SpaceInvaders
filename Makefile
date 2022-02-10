TARGET_EXEC ?= a.out

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

CFLAGS = -DLOG_USE_COLOR
PARAMS = log/log.txt false log_trace
HEADERS = ./src/headers/

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -I$(HEADERS) -c $< -o $@

.PHONY: clean run

clean:
	$(RM) -r $(BUILD_DIR)

run:
	./build/$(TARGET_EXEC) $(PARAMS)

-include $(DEPS)

MKDIR_P ?= mkdir -p

