
#include "cub3D.h"

//void	ft_puterror_mem(void)
//{
//	write(2, "Error memory allocation\n", 24);
//	exit(1);
//}

void ft_error(char *str_err)
{
	size_t len;
	len = ft_strlen(str_err);
	write(2, str_err, len);
	exit(1);
}
