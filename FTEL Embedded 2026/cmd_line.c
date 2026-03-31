

#include <string.h>
#include "cmd_line.h"
#include "xprintf.h"

/*
cmd_line.c là một command line parser – tức là bộ phân tích lệnh. 
Nó nhận chuỗi lệnh từ người dùng (qua UART chẳng hạn), tách phần tên lệnh ra, rồi so khớp với bảng lệnh (cmd_table). Nếu tìm thấy thì gọi hàm xử lý tương ứng.
*/

//Tham số:
//cmd_table: bảng lệnh(mảng các cmd_line_t).
//command : chuỗi lệnh người dùng nhập(ví dụ "led on").

//uint8_t chạy từ 0 - 255  được dùng vì Lưu ký tự lệnh (cmd[]) vì mỗi ký tự chỉ cần 1 byte. 
//Trả về mã trạng thái(CMD_SUCCESS, CMD_NOT_FOUND, …) vì các giá trị này đều nhỏ hơn 255. 
//Giúp code nhúng chạy ổn định trên nhiều vi điều khiển, không phụ thuộc vào việc char hay int có kích thước khác nhau trên từng compiler.
uint8_t cmd_line_parser(cmd_line_t* cmd_table, uint8_t* command) 
{

	uint8_t     cmd[MAX_CMD_SIZE];
	uint8_t* p_command = command;
	uint8_t     cmd_index = 0;
	uint8_t     index_check = 0;

	if (cmd_table == (cmd_line_t*)0) {
		return CMD_TBL_NOT_FOUND;
	}

	/* get cmd */
	while (*p_command) {
		if (*p_command == ' ' || *p_command == '\r' || *p_command == '\n') {
			cmd[cmd_index] = 0;
			break;
		}
		else {
			cmd[cmd_index++] = *(p_command++);
			if (cmd_index >= MAX_CMD_SIZE) {
				return CMD_TOO_LONG;
			}
		}
	}

	/* find respective command in command table */
	while (cmd_table[index_check].cmd) {

		if (strcmp((const char*)cmd_table[index_check].cmd, (const char*)cmd) == 0) {

			/* perform respective function */
			cmd_table[index_check].func(command);

			/* return success */
			return CMD_SUCCESS;
		}

		index_check++;
	}

	return CMD_NOT_FOUND;  /* command not found */
}