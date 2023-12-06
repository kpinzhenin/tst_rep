#include <stdio.h>
#include "ttype.h"


// current status of shaft
#define ROTATION_STOP 0x2
#define ROTATION_CLOCKWISE 0x3
#define ROTATION_COUNTERCLOCKWISE 0x1

#define INIT_ANGLE_VALUE 17000
#define ROTATION_SIGN_TO_SHIFT(RS) ( (RS) - 2 )

//global var
struct phase_t sequence[6] = {
    {.phase_name = ST1G, .i2c_pair = 1},
    {.phase_name = ST2G, .i2c_pair = 1},
    {.phase_name = ST1Y, .i2c_pair = 1},
    {.phase_name = ST2Y, .i2c_pair = 1},
    {.phase_name = ST1R, .i2c_pair = 1},
    {.phase_name = ST2R, .i2c_pair = 1}   
};

// use git to look changes !!!!!
int main(int argc, char **argv)
{

    union aligned_pos aligned_tbl[72];
    // init tbl
    Tmp_aligned_tbl_Init(&aligned_tbl[0], sizeof(aligned_tbl) / 8 );
    
    //union aligned_pos *ptr_tbl = &aligned_tbl[4];
    /*
    for(int i = 0; i < 10; i++)
    {
        // mean clockwise rotation
        union aligned_pos *ptr_prev = (union aligned_pos*)NextShiftedElement(ROTATION_SIGN_TO_SHIFT(ROTATION_COUNTERCLOCKWISE) * 2,
                                                            (unsigned*)ptr_tbl,
                                                            (unsigned*)aligned_tbl,
                                                            sizeof(aligned_tbl) / 8 ); 
        
        union aligned_pos *ptr_next = (union aligned_pos*)NextShiftedElement(ROTATION_SIGN_TO_SHIFT(ROTATION_CLOCKWISE) * 2,
                                                            (unsigned*)ptr_tbl,
                                                            (unsigned*)aligned_tbl,
                                                            sizeof(aligned_tbl) / 8 ); 
                                                                
        printf("[%d]->[%d]->[%d] \n", ptr_prev->bit.phase_name, ptr_tbl->bit.phase_name, ptr_next->bit.phase_name);
        
        ptr_tbl = ptr_next;
    }
    */
    
    int arr[3] = {0, 1, 2};
    void *p_arr = &arr[0];
    printf("{0} =%d, +1 = %d \n", *((int*)p_arr), *((int*)p_arr + 1) );
    struct phase_t *ptr_phase = &sequence[1];
    struct phase_t *ptr_cw_phase = NextSwitchedPhase(ROTATION_SIGN_TO_SHIFT(ROTATION_CLOCKWISE) * 1,
                                    ptr_phase, sequence,
                                    sizeof(sequence) / sizeof(sequence[0]) );
    printf("next CW phase = %d \n", ptr_cw_phase->phase_name);
    for (int i = 0; i < 13; i++)
    {
        printf("phase_name {%d} \n", ptr_phase->phase_name);
        ptr_phase = NextSwitchedPhase(ROTATION_SIGN_TO_SHIFT(ROTATION_CLOCKWISE) * 2,
                                    ptr_phase, sequence,
                                    sizeof(sequence) / sizeof(sequence[0]) );
    }
	printf("hello world\n");
	return 0;
}

unsigned* NextShiftedElement(int shift, unsigned *ptr_a, unsigned a[], int size)
{
    // check next and preious element
    if (shift > 0)
    {
        for(int i = 0; i < shift; i++)
            if (ptr_a++ == &a[size - 1])
                ptr_a = &a[0];
    }
    else
    {
        for (int i = 0; i > shift; i--)
            if(ptr_a-- == &a[0])
                ptr_a =&a[71];
    }
    return ptr_a;
}

struct phase_t* NextSwitchedPhase(int shift, struct phase_t *p_ph, struct phase_t arr_ph[], int size)
{
    // return pointer to next phase swithes
        if (shift > 0)
    {
        for(int i = 0; i < shift; i++)
            if (p_ph++ == &arr_ph[size - 1])
                p_ph = &arr_ph[0];
    }
    else
    {
        for (int i = 0; i > shift; i--)
            if(p_ph-- == &arr_ph[0])
                p_ph =&arr_ph[size-1];
    }
    return p_ph;
}

void Tmp_aligned_tbl_Init(union aligned_pos *tbl, unsigned tbl_size)
{
	for (int i = 0; i < tbl_size; i++)
	{
		//*tbl++ = INIT_ANGLE_VALUE;
		tbl->bit.phase_name = i;
		tbl++->bit.val = INIT_ANGLE_VALUE;

	}
}
