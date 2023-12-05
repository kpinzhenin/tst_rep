#ifndef TTYPE_H_
#define TTYPE_H_
typedef struct
{
	unsigned val :16; 				   // aligned position val
	unsigned phase_delta :10; 		   // delta between previous phase
	unsigned phase_name :6;			   // aligned phase name

}angle_aligned; // aligned_pos

union aligned_pos
{
	angle_aligned bit;
	unsigned all;
};

void Tmp_aligned_tbl_Init(union aligned_pos *tbl, unsigned tbl_size);

unsigned * NextShiftedElement(int shift, unsigned *ptr_a, unsigned a[], int size);

#endif