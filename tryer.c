#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct	s_data {
  void	*img;
  char	*addr;
  int bits_per_pixel;
  int line_length;
  int endian;
}				t_data;

typedef struct  s_vars {
  void *mlx;
  void *win;
}               t_vars;

typedef struct  s_given {
  void  *mlx;
  void  *win;
  int x;
  int y;
  int x_len;
  int y_len;
  t_data  *img;
}             t_given;
  

void  my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
  char	*dst;

  dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
  *(unsigned int*)dst = color;
}

int get_blue(int color, int shade)
{
  unsigned char maker[4];
  
  maker[0] = ((unsigned char *)&color)[0] + shade;
  maker[1] = ((unsigned char *)&color)[1];
  maker[2] = ((unsigned char *)&color)[2];
  maker[3] = ((unsigned char *)&color)[3];
  return ((*(int *)maker));
}

int get_green(int color, int shade)
{
  unsigned char maker[4];
  
  maker[0] = ((unsigned char *)&color)[0];
  maker[1] = ((unsigned char *)&color)[1] + shade;
  maker[2] = ((unsigned char *)&color)[2];
  maker[3] = ((unsigned char *)&color)[3];
  return ((*(int *)maker));
}

int get_red(int color, int shade)
{
  unsigned char maker[4];
  
  maker[0] = ((unsigned char *)&color)[0];
  maker[1] = ((unsigned char *)&color)[1];
  maker[2] = ((unsigned char *)&color)[2] + shade;
  maker[3] = ((unsigned char *)&color)[3];
  return ((*(int *)maker));
}

void  gradient_line(t_data *data, int x, int y, int len, int color)
{
  int shade;
  int i;
  int buf;

  shade = 255 / len;
  buf = 1;
  while (!shade)
  {
    buf++;
    shade = 255 / (len / buf);
  }
  shade = 255 / len;
  i = 0;
  while (i < len)
  {
    my_mlx_pixel_put(data, x + i, y, color);
    i++;
    color = get_blue(color, shade);
    if (buf != 1 && !(i % buf))
      color = get_blue(color, shade + 1);
  }
}

void  rectangle(t_data *data, int x, int y, int color, int hor, int vert)
{
  int i;
  int j;
  i = 0;
  while (i < hor)
  {
    if (i == 0 || i == hor-1)
    {
      j = 0;
      while (j < vert)
      {
        my_mlx_pixel_put(data, x + i, y + j, color);
        j++;
      }
    }
    else
    {
      my_mlx_pixel_put(data, x + i, y + 0, color);
      my_mlx_pixel_put(data, x + i, y + vert-1, color);
    }
    i++;
  }
}

void  shader(t_data *data, int x, int y, int len, int color)
{
  int i;
  int shade;
  int buf;
  
  i = 0;
  shade = 255 / len;
  buf = 1;
  while (!shade)
  {
    buf++;
    shade = 255 / (len / buf);
  }
  shade = 255 / len;
  while (i < len)
  {
    gradient_line(data, x, y + i, len, color);
    i++;
    color = get_green(color, shade);
    if (buf != 1 && !(i % buf))
      color = get_green(color, shade + 1);
  }
}

int close(int keycode, t_vars *vars)
{
  if (keycode == 0xff1b)
  {
    mlx_loop_end(vars->mlx);
  }
  return (0);
}

int close_x(int button, int x, int y, t_vars *vars)
{
  printf("here the coordinates of the click :: %d, %d\n", x, y);
  if (button == 0)
  {
    mlx_destroy_window(vars->mlx, vars->win);
  }
  return (0);
}

int in_win(void)
{
  printf("Hello !\n");
  return (0);
}

int out_win(void)
{
  printf("Bye-bye !\n");
  return (0);
}

int move_square(t_given *given)
{
  t_data  tmp;
  
  tmp.img = mlx_new_image(given->mlx, given->x_len, given->y_len);
  tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bits_per_pixel, &tmp.line_length, &tmp.endian);
  rectangle(&tmp, given->x, given->y, 0x00FF0000, 300, 300);
  mlx_put_image_to_window(given->mlx, given->win, tmp.img, 0, 0);
  if (given->img)
    mlx_destroy_image(given->mlx, given->img);
  given->img = tmp.img;
  given->x++;
  given->y++;
  if (given->x > given->x_len - 300)
    given->x = 0;
  if (given->y > given->y_len - 300)
    given->y = 0;
  return (0);
}

int main(void)
{
  void  *mlx;
  t_vars vars;
  void  *mlx_win;
  t_data  img;
  t_given given;

  mlx = mlx_init();
  mlx_win = mlx_new_window(mlx, 920, 980, "Hi world");
  vars.win = mlx_win;
  vars.mlx = mlx;
  img.img = mlx_new_image(mlx, 920, 980);
  img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
  rectangle(&img, 0, 0, 0x00FF0000, 300, 300);
  /*rectangle(&img, 247, 360, 0x00FF0000, 200, 100);
  rectangle(&img, 786, 70, 0x00FF0000, 50, 20);
  rectangle(&img, 80, 750, 0x00FF0000, 700, 35);
  rectangle(&img, 500, 5, 0x00FF0000, 600, 300);
  shader(&img, 250, 400, 400, 0x00FF0000);*/
  given.win = mlx_win;
  given.mlx = mlx;
  given.x = 0;
  given.y = 0;
  given.x_len = 920;
  given.y_len = 980;
  given.img = img.img;
  mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
  mlx_loop_hook(vars.mlx, &move_square, &given);
  mlx_hook(vars.win, 2, 1L<<0, close, &vars);
  mlx_hook(vars.win, 7, 1L<<4, in_win, NULL);
  mlx_hook(vars.win, 8, 1L<<5, out_win, NULL);
  mlx_hook(vars.win, 4, 1L<<2, close_x, &vars);
  mlx_loop(vars.mlx);
  mlx_destroy_window(vars.mlx, vars.win);
  mlx_destroy_display(vars.mlx);
  //free(mlx);
}

//seemingly core dumps from a timing issue :: win is freed/destroyed before the loop ends, so the loop attempts to go on and print an image into a non-existant window. segfault, coredump. shoudl try to protect the put_image with a more flexible window pointer - preferably, a component that points to the referred vars struct so we can swtch it to NULL and check it before proceeding.

//other issue :: no mlx_sync ? i've resorted to img by img buffering, but it's not exactly ideal here. also, is there maybe a way to halt a loop at all ? seems necessary.
