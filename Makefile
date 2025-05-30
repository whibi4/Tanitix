TARGET = Tanitix
BUILD_DIR = build
all: $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ../src && make
debug: $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=Debug ../src && make

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
run:
	GDK_BACKEND=x11 CODE_PATH=./simpleCode.tx ./$(BUILD_DIR)/$(TARGET)
run_gdb:
	GDK_BACKEND=x11 CODE_PATH=./simpleCode.tx gdb ./$(BUILD_DIR)/$(TARGET)
clean:
	rm -rf $(BUILD_DIR)
