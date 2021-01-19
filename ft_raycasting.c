#/*include "cub3D.h"
#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

int worldMap [mapWidth] [mapHeight] =
		{
				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
				{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
				{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		};

double 	ft_abs(double num)
{
	if (num < 0)
		return (-num);
	return (num);
}

typedef struct t_data {
	double	pos_x;
	double	pos_y;
	double	dir_x;
	...
}

void	set_dir(char c)
{
	if (c == 'N')
		dir_x = 0;
		dir_y = -1;
}

int		ft_raycasting(void) {
	double posX = 22, posY = 12;  // начальная позиция x и y
	double dirX = -1, dirY = 0; // начальный вектор направления
	double planeX = 0, planeY = 0.66; // 2d raycaster версия плоскости камеры

	double time = 0; // время текущего кадра
	double oldTime = 0; // время предыдущего кадра

	for (int x = 0; x < w; x ++)
	{
		// вычисляем положение и направление
												 // x-координата в пространстве камеры
		double cameraX = 2 * x / double(w) - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;

//		deltaDistX = abs (1 / rayDirX)
//		deltaDistY = abs (1 / rayDirY)

		//which box of the map we're in
		// в каком блоке карты мы находимся
		int mapX = int(posX);
		int mapY = int(posY);

		//length of ray from current position to next x or y-side
		// длина луча от текущей позиции до следующей стороны x или y
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		// длина луча от одной стороны x или y до следующей стороны x или y
//		ПРИМЕЧАНИЕ. Если rayDirX или rayDirY равны 0, то выше происходит деление на 0,
//		в результате чего значение deltaDistX или deltaDistY становится бесконечным
		double deltaDistX = ft_abs(1 / rayDirX); // добавить проверку перед вычислением
		double deltaDistY = ft_abs(1 / rayDirY); // если rDX == 0, rDY == 0, то просто подавать 1
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		// в каком направлении делать шаг по       оси x или y (+1 или -1)
		int stepX;
		int stepY;

//		// там была стена?
//      // Был ли удар по стене NS или EW?
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?


//		вычислить первый stepX, stepY и начальные sideDistX и sideDistY.
		if (rayDirX <0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY <0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}

		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0) hit = 1;
		}

		// Вычислить расстояние, проецируемое в направлении камеры (евклидово расстояние даст эффект       рыбьего глаза !)
		if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		// Вычислить расстояние, проецируемое в направлении камеры (евклидово расстояние даст эффект       рыбьего глаза !)
		if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		// Рассчитываем высоту линии для рисования на экране
		int lineHeight = (int) (h / perpWallDist); // вычисляем самый низкий и самый высокий пиксели для заполнения текущей полосы
		int drawStart = -lineHeight / 2 + h / 2;
		else (drawStart <0) drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		else (drawEnd> = h) drawEnd = h - 1;


	}
*/