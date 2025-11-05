# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
DEBUG_FLAGS = -g
RELEASE_FLAGS = -O2

# Папки
SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build
INCLUDE_DIR = include

# Исходные файлы
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
TEST_FILES = $(wildcard $(TEST_DIR)/*.c)

# Объектные файлы
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))
TEST_OBJ_FILES = $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/%.o,$(TEST_FILES))

# Исполняемые файлы
TARGET = prufer_test
DEBUG_TARGET = prufer_test_debug

# Основная цель по умолчанию
all: test

# Релизная сборка
release: CFLAGS += $(RELEASE_FLAGS)
release: $(TARGET)

# Отладочная сборка
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(DEBUG_TARGET)

# Сборка и запуск тестов
test: $(TARGET)
	@echo "=== Запуск тестов ==="
	./$(TARGET)

test-debug: $(DEBUG_TARGET)
	@echo "=== Запуск тестов (отладочная версия) ==="
	./$(DEBUG_TARGET)

# Сборка релизной версии
$(TARGET): $(OBJ_FILES) $(TEST_OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Сборка отладочной версии
$(DEBUG_TARGET): $(OBJ_FILES) $(TEST_OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Компиляция объектных файлов из исходников
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Создание папки build
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Очистка
clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(DEBUG_TARGET)

# Запуск тестов (альтернативные команды)
run: test
run-debug: test-debug

# Отладочная информация
info:
	@echo "Source files: $(SRC_FILES)"
	@echo "Test files: $(TEST_FILES)"
	@echo "Object files: $(OBJ_FILES)"
	@echo "Test object files: $(TEST_OBJ_FILES)"

# Помощь
help:
	@echo "Доступные цели:"
	@echo "  all         - сборка и запуск тестов (по умолчанию)"
	@echo "  release     - только сборка релизной версии"
	@echo "  debug       - только сборка отладочной версии"
	@echo "  test        - сборка и запуск тестов (релиз)"
	@echo "  test-debug  - сборка и запуск тестов (отладка)"
	@echo "  clean       - очистка собранных файлов"
	@echo "  run         - синоним для test"
	@echo "  run-debug   - синоним для test-debug"
	@echo "  info        - информация о файлах проекта"
	@echo "  help        - эта справка"

.PHONY: all release debug test test-debug clean run run-debug info help
