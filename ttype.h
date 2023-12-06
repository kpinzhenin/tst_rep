#ifndef TTYPE_H_
#define TTYPE_H_

// phase name
#define ST1G 0
#define ST2G 1
#define ST1Y 2
#define ST2Y 3
#define ST1R 4
#define ST2R 5

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

struct phase_t
{
    const unsigned phase_name;
    unsigned i2c_pair;
};

void Tmp_aligned_tbl_Init(union aligned_pos *tbl, unsigned tbl_size);

unsigned * NextShiftedElement(int shift, unsigned *ptr_a, unsigned a[], int size);
struct phase_t* NextSwitchedPhase(int shift, struct phase_t *p_ph, struct phase_t arr_ph[], int size);

#endif