//
// обработка ошибок
// заменить на обработку кодов ошибки
//
#include "cub3D.h"

void	ft_puterror(void)
{
	write(2, "Error map\n", 10);
}

void	ft_puterror_mem(void)
{
	write(2, "Error memory allocation\n", 24);
	exit(1);
}

void	ft_puterr_clean(char *arr)
{
	write(2, "Error map\n", 10);
	if (arr != 0)
		free(arr);
}

int ft_error(void *ptr1, void *ptr2)
{
	if (ptr1 != NULL)
		free(ptr1);
	if (ptr2 != NULL)
		free(ptr2);
	write(2, "Error map\n", 10);
	return (-1);
}
