#include <stdio.h>
#include <stdint.h>
#include "cmd_line.h"
#include "xprintf.h"
#include <assert.h>

// Hàm xử lý mẫu
int32_t dummy_handler(uint8_t* argv) {
    xprintf("Handler called with: %s\n", argv);
    return 0;
}

// Bảng lệnh mẫu
cmd_line_t cmd_table[] = {
    {"led",   dummy_handler, "Điều khiển LED"},
    {"reset", dummy_handler, "Khởi động lại hệ thống"},
    {0, 0, 0} // kết thúc bảng
};

//====MAIN====//
int main(void) 
{
    /*
     hàm cmd_line_parser có thể trả về. Như bạn thấy trong code, có 4 giá trị trả về:
    CMD_TBL_NOT_FOUND (0)
    CMD_SUCCESS (1)
    CMD_NOT_FOUND (2)
    CMD_TOO_LONG (3)
    */
    uint8_t result;

    // Case 1: CMD_TBL_NOT_FOUND
    result = cmd_line_parser(NULL, (uint8_t*)"led on");
    assert(result == CMD_TBL_NOT_FOUND); //assert trong C hoạt động giống như một cổng kiểm tra hay một “chốt chặn” trong chương trình,Nếu điều_kiện đúng (true) → chương trình chạy tiếp bình thường.Nếu điều_kiện sai (false) → chương trình sẽ dừng ngay lập tức 
    printf("Test CMD_TBL_NOT_FOUND passed\n");

    // Case 2: CMD_SUCCESS (lệnh hợp lệ)
    result = cmd_line_parser(cmd_table, (uint8_t*)"led on");
    assert(result == CMD_SUCCESS);
    printf("Test CMD_SUCCESS passed\n");

    // Case 3: CMD_NOT_FOUND (lệnh không tồn tại)
    result = cmd_line_parser(cmd_table, (uint8_t*)"abc");
    assert(result == CMD_NOT_FOUND);
    printf("Test CMD_NOT_FOUND passed\n");

    // Case 4: CMD_TOO_LONG (lệnh dài hơn MAX_CMD_SIZE)
    char long_cmd[20];
    memset(long_cmd, 'A', sizeof(long_cmd));
    long_cmd[sizeof(long_cmd) - 1] = '\0'; // kết thúc chuỗi
    result = cmd_line_parser(cmd_table, (uint8_t*)long_cmd);
    assert(result == CMD_TOO_LONG);
    printf("Test CMD_TOO_LONG passed\n");

    printf("Tất cả unit test đã chạy thành công!\n");
    return 0;
}