#include <stdio.h>
#include "ttype.h"


// current status of shaft
#define ROTATION_STOP 0x2
#define ROTATION_CLOCKWISE 0x3
#define ROTATION_COUNTERCLOCKWISE 0x1

#define INIT_ANGLE_VALUE 17000
#define ROTATION_SIGN_TO_SHIFT(RS) ( (RS) - 2 )


// use git to look changes !!!!!
int main(int argc, char **argv)
{

    union aligned_pos aligned_tbl[72];
    // init tbl
    Tmp_aligned_tbl_Init(&aligned_tbl[0], sizeof(aligned_tbl) / 8 );
    
    union aligned_pos *ptr_tbl = &aligned_tbl[4];
    
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

void Tmp_aligned_tbl_Init(union aligned_pos *tbl, unsigned tbl_size)
{
	for (int i = 0; i < tbl_size; i++)
	{
		//*tbl++ = INIT_ANGLE_VALUE;
		tbl->bit.phase_name = i;
		tbl++->bit.val = INIT_ANGLE_VALUE;

	}
}
