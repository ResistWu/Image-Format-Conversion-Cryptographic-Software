#ifndef __EZW_H__
#define __EZW_H__
#include "afxwin.h"
#define min_element_type -32768
#define max_element_type  32767

#define ZERO  0 /* binary 0 */
#define ONE   1 /* binary 1 */
#define ZTR   2 /* binary 00 */
#define POS   3 /* binary 01 */
#define NEG   4 /* binary 11 */
#define IZ    5 /* binary 10 */

typedef int element_type;
typedef struct __ezw_file_header {
	int height;
	int width;
	element_type threshold;
} ezw_file_header;

typedef struct __ezw_element {
	int x;
	int y;
	int code;
} ezw_element;

typedef struct __list_type {
	int x;
	int y;
} list_type;

typedef struct __matrix_2d {
	int row;
	int col;
	element_type **m;
} matrix_2d;

typedef struct __fifo_element {
	ezw_element data;
	struct __fifo_element *previous;
} fifo_element;

typedef struct __list_element {
	list_type data;
	struct __list_element *next;
} list_element;
 /*= {
	{ 427, 19, 256, -6, 4, 0, 4, 6 },
	{ -57, 10, 342, -3, 2, 0, 0, 2 },
	{ 316, 306, 422, -6, 0, 0, 0, 3 },
	{ -4, -2, 6, -6, 0, 2, 0, 2 },
	{ 251, 3, -7, 8, 0, -6, -1, 6 },
	{ -307, 3, 8, -4, 1, 1, -2, 0 },
	{ 263, -10, -5, 7, 0, -3, 0, 4 },
	{ -302, -9, 1, 8, 0, -1, 0, 5 },
	//{  5, 11,  5,  6,  0,  3, -4,  4 }
};*/

class Ezw{
public:
	Ezw();
	int example[8][8];
	void ezwencode();
	//char fifo_empty;
	void put_in_fifo(ezw_element d);
	ezw_element get_from_fifo(void);
	void destroy_fifo(void);
	void initialize_fifo(void);

	//--------list
	//int list_length;
	void append_to_list(list_type d);
	void destroy_list(void);
	void display_list(void);
	list_type get_list_element(int pos, char *found);
	void put_list_element(list_type d, int pos, char *found);
	void reset_list(void);
	list_type get_next_list_element(char *found);
	void write_list_info(void);
	void initialize_list(void);

	matrix_2d *matrix_2d_create(int r, int c);
	void matrix_2d_destroy(matrix_2d *m);
	void matrix_2d_clear(matrix_2d *m);
	void matrix_2d_write(matrix_2d *m);
	element_type matrix_2d_abs_max(matrix_2d *m);

	matrix_2d *M;
	char error;
	int zeroes, ones;
	FILE *ezw_file;
	unsigned char output_byte, mask;
	ezw_file_header header;

	fifo_element *fifo_first = NULL;
	fifo_element *fifo_last = NULL;
	char fifo_empty = 1;

	list_element *list_root = NULL;
	list_element *list_current = NULL;
	list_element *list_end = NULL;
	int list_length = 0;

	void load_data(matrix_2d *m);
	void put_bit(char bit);
	void output_code(int code);
	element_type max_descendant(matrix_2d *m, int x, int y);
	char zerotree(matrix_2d *m, int x, int y, int threshold);
	int code(matrix_2d *m, int x, int y, element_type threshold);
	void to_sub_list(element_type value);
	void process_element(matrix_2d *m, element_type threshold, ezw_element *s);
	void dominant_pass(matrix_2d *m, element_type threshold);
	void subordinate_pass(element_type threshold);
	void EZW_code(matrix_2d *m, element_type threshold);
	
};


#endif