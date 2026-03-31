
#ifndef __CMD_LINE_H__
#define __CMD_LINE_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

//các define code bên dưới vai trò giống như một enum
#define MAX_CMD_SIZE			12  // hằng số: độ dài tối đa của tên lệnh

#define CMD_TBL_NOT_FOUND		0 // mã lỗi: không tìm thấy bảng lệnh
#define CMD_SUCCESS				1 // mã trả về: thực thi thành công
#define CMD_NOT_FOUND			2 // mã lỗi: không tìm thấy lệnh trong bảng
#define CMD_TOO_LONG			3 // mã lỗi: lệnh quá dài



	/*================================================
	typedef: tạo một tên kiểu mới.

	int32_t: kiểu trả về của hàm (số nguyên 32-bit có dấu).

	(*pf_cmd_func): định nghĩa một con trỏ tới hàm.

	(uint8_t* argv): tham số đầu vào của hàm, là một con trỏ tới chuỗi lệnh gốc mà người dùng nhập.

	→ Nói ngắn gọn: pf_cmd_func là một kiểu dữ liệu đại diện cho hàm xử lý lệnh, với dạng: int32_t function_name(uint8_t* argv);
	*/
	typedef int32_t(*pf_cmd_func)(uint8_t* argv);//có vai trò định nghĩa một kiểu con trỏ hàm để dùng trong bảng lệnh (cmd_line_t)

	typedef struct {
		const int8_t* cmd; // tên lệnh (ví dụ "led")
		pf_cmd_func func; // con trỏ tới hàm xử lý lệnh
		const int8_t* info; // mô tả lệnh (ví dụ "bật/tắt LED")
	} cmd_line_t;

	/*
	 Giả sử bạn muốn tạo lệnh "led" để bật/tắt LED:

	int32_t led_handler(uint8_t* argv) 
	{
		xprintf("LED command received: %s\n", argv);
		return 0; 
	};

	cmd_line_t table[] = 
	{
		{"led", led_handler, "Điều khiển LED"},
		{"reset", reset_handler, "Khởi động lại hệ thống"},
		{0, 0, 0} // kết thúc bảng
	};
	
	*/


	/*================================================
	extern có vai trò khai báo nguyên mẫu hàm (function prototype) để các file khác khi #include "cmd_line.h" sẽ biết rằng có một hàm tên là cmd_line_parser tồn tại ở đâu đó (trong file .c).
	extern: báo cho compiler rằng hàm này được định nghĩa ở một nơi khác (không phải trong file .h), thường là trong file .c.
	*/
	extern uint8_t cmd_line_parser(cmd_line_t* cmd_table, uint8_t* command);
	

#ifdef __cplusplus
}
#endif

#endif //__CMD_LINE_H__