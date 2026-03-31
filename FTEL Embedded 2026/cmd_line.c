

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

	uint8_t     cmd[MAX_CMD_SIZE];// biến quy định kích thước tối đa của tên lệnh (ví dụ "led") là 12 ký tự. Nếu người dùng nhập lệnh dài hơn, hàm sẽ trả về lỗi CMD_TOO_LONG.
	uint8_t* p_command = command; // con trỏ dùng để duyệt qua chuỗi lệnh người dùng nhập vào. Ban đầu, nó trỏ tới ký tự đầu tiên của chuỗi command.
	uint8_t     cmd_index = 0; // biến đếm số ký tự đã đọc vào mảng cmd[]. Nó bắt đầu từ 0 và sẽ tăng lên mỗi khi một ký tự hợp lệ được thêm vào cmd[].
	uint8_t     index_check = 0; // biến dùng để duyệt qua bảng lệnh cmd_table. Nó bắt đầu từ 0 và sẽ tăng lên mỗi lần kiểm tra một mục trong bảng lệnh.

	if (cmd_table == (cmd_line_t*)0) 
	{
		return CMD_TBL_NOT_FOUND;
		/*
		code này có nghĩa là kiểm tra xem con trỏ cmd_table có bằng NULL hay không.
		(cmd_line_t*)0 chính là cách viết “ép kiểu” số 0 thành con trỏ kiểu cmd_line_t*.
		Trong C, con trỏ bằng 0 (NULL) nghĩa là nó không trỏ tới vùng nhớ hợp lệ nào.
		Nếu cmd_table bằng NULL, tức là bạn chưa truyền vào bảng lệnh hợp lệ, thì hàm sẽ trả về CMD_TBL_NOT_FOUND.
		*/
	}

	/* get cmd */
	//while (*p_command) nghĩa là lặp cho đến khi ký tự mà con trỏ p_command đang trỏ tới bằng 0 (null terminator '\0' của chuỗi C). → Nói cách khác, vòng lặp sẽ dừng khi đến cuối chuỗi lệnh.
	while (*p_command) 
	{
		//Nếu gặp khoảng trắng ' ', hoặc ký tự xuống dòng '\r', '\n' thì coi như đã hết phần tên lệnh → đặt cmd[cmd_index] = 0 để kết thúc chuỗi, rồi break ra khỏi vòng lặp.
		if (*p_command == ' ' || *p_command == '\r' || *p_command == '\n') 
		{
			cmd[cmd_index] = 0;
			break;
		}

		//Nếu không, thì copy ký tự hiện tại vào mảng cmd[] và tăng p_command sang ký tự tiếp theo.
		else 
		{
			//cmd_index++: nghĩa là dùng giá trị hiện tại của cmd_index để truy cập mảng cmd[], sau đó mới tăng cmd_index lên 1.
			//p_command++: nghĩa là lấy ký tự mà p_command đang trỏ tới, rồi sau đó dịch con trỏ p_command sang vị trí tiếp theo trong chuỗi.
			cmd[cmd_index++] = *(p_command++);

			/* ví dụ: nếu command là "led on", thì quá trình sẽ diễn ra như sau:
						uint8_t command[] = "led on";
						uint8_t cmd[12];
						uint8_t* p_command = command;
						int cmd_index = 0;

							Lần đầu chạy:
							cmd[0] = *p_command → 'l' được gán vào cmd[0].
							cmd_index tăng thành 1.
							p_command trỏ sang 'e'.

								Lần sau:
								cmd[1] = *p_command → 'e' vào cmd[1].
								cmd_index tăng thành 2.
								p_command trỏ sang 'd'.

				Cứ thế cho đến khi gặp khoảng trắng hoặc hết chuỗi.

			*/

			//Nếu số ký tự vượt quá MAX_CMD_SIZE (12) thì trả về lỗi CMD_TOO_LONG.
			if (cmd_index >= MAX_CMD_SIZE) 
			{
				return CMD_TOO_LONG;
			}
		}
	}

	/* find respective command in command table */
	while (cmd_table[index_check].cmd) // nghĩa là lặp cho đến khi gặp mục trong cmd_table mà trường cmd bằng NULL (điều này đánh dấu kết thúc bảng lệnh).
	{

		if (strcmp((const char*)cmd_table[index_check].cmd, (const char*)cmd) == 0) // strcmp so sánh chuỗi cmd_table[index_check].cmd với chuỗi cmd đã tách ra từ lệnh người dùng. Nếu chúng giống nhau, strcmp sẽ trả về 0.
		{

			/* perform respective function */
			cmd_table[index_check].func(command);// gọi hàm xử lý tương ứng với lệnh đã tìm thấy. Hàm này sẽ nhận toàn bộ chuỗi lệnh người dùng (command) để có thể xử lý các tham số nếu cần.

			/* return success */
			return CMD_SUCCESS;// trả về mã trạng thái CMD_SUCCESS để báo hiệu rằng lệnh đã được xử lý thành công.
		}

		index_check++;// tăng index_check để kiểm tra mục tiếp theo trong bảng lệnh.
	}

	return CMD_NOT_FOUND;  /* command not found */
}