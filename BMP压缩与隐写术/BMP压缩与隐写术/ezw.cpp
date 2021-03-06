#include "stdafx.h"
#define debug

#include "ezw.h"
//#include "fifo.h"
//#include "list.h"
//#include "matrix2d.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


Ezw::Ezw(){
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			
		}
	}
	header.height = 8;
	header.width = 8;
}


matrix_2d *Ezw::matrix_2d_create(int r, int c)
{
	int row;
	matrix_2d *m;

	m = (matrix_2d *)malloc(sizeof(matrix_2d));

	if (m != NULL) {
		m->row = r;
		m->col = c;
		m->m = (element_type **)malloc(r*sizeof(element_type*));
		if (m->m == NULL) return NULL;
		for (row = 0; row<r; row++) {
			m->m[row] = (element_type *)malloc(c*sizeof(element_type));
			if (m->m[row] == NULL) return NULL;
		}
	}

	return m;
}


/*
* Destroy a matrix.
*/
void Ezw::matrix_2d_destroy(matrix_2d *m)
{
	int row;
	for (row = 0; row<m->row; row++) {
		free(m->m[row]);
	}
	free(m);
}


/*
* Set all matrix elements to zero.
*/
void Ezw::matrix_2d_clear(matrix_2d *m)
{
	int row, col;

	for (row = 0; row<m->row; row++) {
		for (col = 0; col<m->col; col++) {
			m->m[row][col] = 0;
		}
	}
}

/*
* Display a matrix.
*/
void Ezw::matrix_2d_write(matrix_2d *m)
{
	int row, col;
	for (row = 0; row<m->row; row++) {
		for (col = 0; col<m->col; col++) {
			printf("%3d", m->m[row][col]);
		}
		printf("\n");
	}
}


/*
* Returns max(abs(matrix)), the absolute maximum value of a matrix.
*/
element_type Ezw::matrix_2d_abs_max(matrix_2d *m)
{
	int row, col;
	element_type max = 0;

	for (row = 0; row<m->row; row++) {
		for (col = 0; col<m->col; col++) {
			if (abs(m->m[row][col])>max) max = abs(m->m[row][col]);
		}
	}

	return max;
}


//--------------listfunc
void Ezw::append_to_list(list_type d)
{
	list_element *p;
	p = (list_element *)malloc(sizeof(list_element));
	if (p != NULL) {
		p->data = d;
		p->next = NULL;
		if (list_root == NULL) list_root = p;
		if (list_end != NULL) list_end->next = p;
		list_end = p;
		list_length++;
	}
}

void Ezw::destroy_list(void)
{
	list_element *p;

	p = list_root;
	while (p != NULL) {
		list_root = p->next;
		free(p);
		p = list_root;
	}
	list_root = NULL;
	list_current = NULL;
	list_end = NULL;
	list_length = 0;
}

void Ezw::display_list(void)
{
	list_element *p;
	p = list_root;
	while (p != NULL) {
		printf("(%d,%d)", p->data.x, p->data.y);
		p = p->next;
	}
}

list_type Ezw::get_list_element(int pos, char *found)
{
	list_element *p;
	list_type d;
	int i;

	i = 0;
	p = list_root;
	while ((i<pos) && (p != NULL)) {
		i++;
		p = p->next;
	}
	if ((i<pos) || (p == NULL)) *found = 0;
	else {
		d = p->data;
		*found = 1;
	}
	return d;
}

void Ezw::put_list_element(list_type d, int pos, char *found)
{
	list_element *p;
	int i;

	i = 0;
	p = list_root;
	while ((i<pos) && (p != NULL)) {
		i++;
		p = p->next;
	}
	if ((i<pos) || (p == NULL)) *found = 0;
	else {
		p->data = d;
		*found = 1;
	}
}

void Ezw::reset_list(void)
{
	list_current = list_root;
}

list_type Ezw::get_next_list_element(char *found)
{
	list_type d;

	if (list_current == NULL) *found = 0;
	else {
		d = list_current->data;
		*found = 1;
		list_current = list_current->next;
	}
	return d;
}

void Ezw::write_list_info(void)
{
	printf("\n");
	printf("element size: %ld, length: %d\n", sizeof(list_type), list_length);
}

void Ezw::initialize_list(void)
{
	list_root = NULL;
	list_current = NULL;
	list_end = NULL;
	list_length = 0;
}

//--------------fifofunc
void Ezw::put_in_fifo(ezw_element d)
{
	fifo_element *p;

	p = (fifo_element *)malloc(sizeof(fifo_element));
	if (p != NULL) {
		p->data = d;
		p->previous = NULL;
		if (fifo_last != NULL) fifo_last->previous = p;
		fifo_last = p;
		if (fifo_first == NULL) fifo_first = p;
		fifo_empty = 0;
	}
}

ezw_element Ezw::get_from_fifo(void)
{
	ezw_element d = {0};
	fifo_element *p;

	p = fifo_first;
	if (p != NULL) {
		d = p->data;
		fifo_first = p->previous;
		free(p);
	}
	else {
		fifo_last = NULL;
		fifo_empty = 1;
	}
	return d;
}

void Ezw::destroy_fifo(void)
{
	fifo_element *p;
	while (fifo_first != NULL) {
		p = fifo_first;
		fifo_first = p->previous;
		free(p);
	}
	fifo_last = NULL;
	fifo_empty = 1;
}

void Ezw::initialize_fifo(void)
{
	fifo_first = NULL;
	fifo_last = NULL;
	fifo_empty = 1;
}

//--------------ezwfunc

void Ezw::load_data(matrix_2d *m)
{
	int row, col;
	for (row = 0; row<8; row++) {
		for (col = 0; col<8; col++) {
			m->m[row][col] = example[row][col];
		}
	}
}


/*
* Puts a bit in the output stream.
*/
void Ezw::put_bit(char bit)
{
	if (bit == '1') {
		output_byte |= mask;
		ones++;
	}
	else zeroes++;

	mask >>= 1;
	if (mask == 0) {
		fwrite(&output_byte, sizeof(output_byte), 1, ezw_file);
		output_byte = 0;
		mask = 0x80;
	}
}


/*
* Puts dominant-pass and subordinate-pass codes in the output stream.
*/
void Ezw::output_code(int code)
{
	switch (code) {

	case ZERO:
		put_bit('0');

#ifdef debug
		printf("0");
#endif

		break;

	case ONE:
		put_bit('1');

#ifdef debug
		printf("1");
#endif

		break;

	case POS:
		put_bit('0');
		put_bit('1');

#ifdef debug
		printf("p");
#endif

		break;

	case NEG:
		put_bit('1');
		put_bit('1');

#ifdef debug
		printf("n");
#endif

		break;

	case ZTR:
		put_bit('0');
		put_bit('0');

#ifdef debug
		printf("t");
#endif

		break;

	case IZ:
		put_bit('1');
		put_bit('0');

#ifdef debug
		printf("z");
#endif

		break;
	}
}


/*
* Returns the largest value in a descendance tree.
*/
element_type Ezw::max_descendant(matrix_2d *m, int x, int y)
{
	int i, j, min_x, max_x, min_y, max_y;
	element_type temp, max;

	if ((x == 0) && (y == 0)) {
		temp = m->m[0][0];
		m->m[0][0] = min_element_type;
		max = matrix_2d_abs_max(m);
		m->m[0][0] = temp;
	}
	else {
		min_x = x << 1;
		min_y = y << 1;
		max_x = (x + 1) << 1;
		max_y = (y + 1) << 1;
		if ((min_x == m->col) || (min_y == m->row)) {
			return (0);
		}

		max = 0;
		while ((max_y <= m->row) && (max_x <= m->col)) {
			for (i = min_y; i<max_y; i++) {
				for (j = min_x; j<max_x; j++) {
					temp = abs(m->m[i][j]);
					if (temp>max) max = temp;
				}
			}
			min_x <<= 1;
			max_x <<= 1;
			min_y <<= 1;
			max_y <<= 1;
		}

	}

	return (max);
}


/*
* Returns 1 if descendance tree is a zerotree.
*/
char Ezw::zerotree(matrix_2d *m, int x, int y, int threshold)
{
	int i, j, min_x, max_x, min_y, max_y;
	element_type temp, max;
	char stop;

	stop = 0;
	if ((x == 0) && (y == 0)) {
		temp = m->m[0][0];
		m->m[0][0] = min_element_type;
		max = matrix_2d_abs_max(m);
		m->m[0][0] = temp;
		if (max >= threshold) stop = 1;
	}
	else {
		min_x = x << 1;
		min_y = y << 1;
		max_x = (x + 1) << 1;
		max_y = (y + 1) << 1;
		if ((min_x == m->col) || (min_y == m->row)) {
			return (1);
		}

		max = 0;
		while ((max_y <= m->row) && (max_x <= m->col)) {
			for (i = min_y; i<max_y; i++) {
				for (j = min_x; j<max_x; j++) {
					temp = abs(m->m[i][j]);
					if (temp >= threshold) {
						stop = 1;
						break;
					}
				}
				if (stop == 1) break;
			}
			if (stop == 1) break;
			min_x <<= 1;
			max_x <<= 1;
			min_y <<= 1;
			max_y <<= 1;
		}
	}
	if (stop == 1) return (0);
	return (1);
}


/*
* Returns a dominant-pass code from the alphabet [POS,NEG,ZTR,IZ].
*/
int Ezw::code(matrix_2d *m, int x, int y, element_type threshold)
{
	element_type temp;
	temp = m->m[y][x];
	if (abs(temp) >= threshold) {
		if (temp >= 0) return (POS);
		else return (NEG);
	}
	else {
		/*    if ((max_descendant(m,x,y)<threshold)) code = ZTR*/
		if (zerotree(m, x, y, threshold) == 1) return (ZTR);
		else return (IZ);
	}
}


/*
* Appends a value to the subordinate list.
*/
void Ezw::to_sub_list(element_type value)
{
	list_type d;
	/*
	* Put only coefficient magnitude in list, sign is allready coded.
	*/
	d.x = abs(value);
	d.y = 0;
	append_to_list(d);
}


/*
* Builds a dominant pass EZW-element from a matrix element and a threshold.
*/
void Ezw::process_element(matrix_2d *m, element_type threshold, ezw_element *s)
{
	s->code = code(m, s->x, s->y, threshold);
	if ((s->code == POS) || (s->code == NEG)) {
		to_sub_list(m->m[s->y][s->x]);
		m->m[s->y][s->x] = 0;
	}
}


/*
* Performs one complete dominant pass. Dominant-pass-codes are sent to the
* output stream and the subordinate list is updated.
*/
//主扫描
void Ezw::dominant_pass(matrix_2d *m, element_type threshold)
{
	ezw_element s;
	int min_x, max_x, min_y, max_y;
	/*  int level;*/

	s.x = 0;
	s.y = 0;
	process_element(m, threshold, &s);
	output_code(s.code);

	s.x = 1;
	s.y = 0;
	process_element(m, threshold, &s);
	put_in_fifo(s);
	s.x = 0;
	s.y = 1;
	process_element(m, threshold, &s);
	put_in_fifo(s);
	s.x = 1;
	s.y = 1;
	process_element(m, threshold, &s);
	put_in_fifo(s);

	s = get_from_fifo();
	if (fifo_empty == 0) output_code(s.code);

	while (fifo_empty == 0) {
		if (s.code != ZTR) {
			min_x = s.x << 1;
			max_x = min_x + 1;
			min_y = s.y << 1;
			max_y = min_y + 1;
			if ((max_x <= m->col) && (max_y <= m->row)) {
				for (s.y = min_y; s.y<max_y + 1; s.y++) {
					for (s.x = min_x; s.x<max_x + 1; s.x++) {
						process_element(m, threshold, &s);
						put_in_fifo(s);
					}
				}
			}
		}
		s = get_from_fifo();
		if (fifo_empty == 0) output_code(s.code);
	}
}


//辅扫描
void Ezw::subordinate_pass(element_type threshold)
{
	list_type d;
	int i;
	char found;

	if (threshold>0) {
		for (i = 0; i<list_length; i++) {
			d = get_list_element(i, &found);
			if (found == 1) {
				if ((d.x&threshold) != 0) output_code(ONE);
				else output_code(ZERO);
			}
		}
	}
}


/*
* EZW-codes matrix m, returns initial threshold.
*/
void Ezw::EZW_code(matrix_2d *m, element_type threshold)
{
	while (threshold != 0) {
		dominant_pass(m, threshold);

#ifdef debug
		printf("\n");
#endif

		subordinate_pass(threshold >> 1);

#ifdef debug
		printf("\n");
#endif

		threshold >>= 1;
	}
}

void Ezw::ezwencode()
{
	/*
	//printf("\n");
	//建立矩阵
	header.height = 8;
	header.width = 8;
	M = matrix_2d_create(header.height, header.width);
	if (M == NULL) exit(1);
	load_data(M);

#ifdef debug
	//matrix_2d_write(M);
#endif

	/*
	* Prepare output file.
	*/
	//header.threshold = 256;//1 << (int)(floor(log10(matrix_2d_abs_max(M)) / log10(2)));
	//向下取整log2(matrix_2d_abs_max(M)；对最大尺度的LLN计算出均值，确定阈值T。

//	if (fopen_s(&ezw_file,"out.ezw", "wb") != NULL) {
//		printf("Could not open output file.\n");
//		exit(1);
//	};
//	fwrite(&header, sizeof(header), 1, ezw_file);
//
//
//	//EZW coding.
//	zeroes = 0;
//	ones = 0;
//	output_byte = 0;
//	mask = 0x80;//1000 0000
//	EZW_code(M, header.threshold);
//
//	/*
//	* Flush output.
//	*/
//	if (mask != 0) {
//		fwrite(&output_byte, sizeof(output_byte), 1, ezw_file);
//	}
//
//#ifdef debug
//	printf("\n");
//	printf(" bits: %d, %d zeroes, %d ones.\n", zeroes + ones, zeroes, ones);
//#endif
//
//	/*
//	* Cleanup.
//	*/
//	fclose(ezw_file);
//	//matrix_2d_destroy(M);
//	//destroy_fifo();
//	//destroy_list();
//
//	/*
//	* Clean exit.
//	*/
//
//	//return 0;*/
	Sleep(500);
}