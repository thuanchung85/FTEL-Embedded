#include <stdio.h>
#include <stdint.h>
#include "cmd_line.h"
#include "xprintf.h"

// Hàm xử lý lệnh "led"
int32_t led_handler(uint8_t* argv) {
    xprintf("LED handler called with: %s\n", argv);
    return 0;
}

// Hàm xử lý lệnh "reset"
int32_t reset_handler(uint8_t* argv) {
    xprintf("RESET handler called with: %s\n", argv);
    return 0;
}

// Bảng lệnh
cmd_line_t cmd_table[] = {
    {"led",   led_handler,   "Điều khiển LED"},
    {"reset", reset_handler, "Khởi động lại hệ thống"},
    {0, 0, 0} // kết thúc bảng
};

int main(void) {
    uint8_t command1[] = "led on";
    uint8_t command2[] = "reset now";
    uint8_t command3[] = "abc";

    uint8_t result;

    // Test lệnh "led"
    result = cmd_line_parser(cmd_table, command1);
    printf("Result for 'led on': %d\n", result);

    // Test lệnh "reset"
    result = cmd_line_parser(cmd_table, command2);
    printf("Result for 'reset now': %d\n", result);

    // Test lệnh không tồn tại
    result = cmd_line_parser(cmd_table, command3);
    printf("Result for 'abc': %d\n", result);

    return 0;
}