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

void ft_error(char *str_err)
{
	size_t len;
	len = ft_strlen(str_err);
	write(2, str_err, len);
	exit(1);
}
