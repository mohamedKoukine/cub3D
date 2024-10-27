  
  
  
  
  
  
  
  
  
  
  
  
  
  if (ray->hv == 1)
        ofsetX = (int)ray->dx % PIXELS;
    else
        ofsetX = (int)ray->dy % PIXELS;
    while((int)x++ < wall_heigh && x < (int)exec->info.win_hei)
    { 
        int top = y + (wall_heigh / 2) - (exec->info.win_hei / 2);
        int ofsetY = top * ((double)PIXELS / wall_heigh);
        o = ((PIXELS * ofsetY) + ofsetX) * 4;
        // if (ray->d == 2)
        // {
        //     color = (int)ft_pixel(exec->d->pixels[o], exec->d->pixels[o + 1], exec->d->pixels[o + 2], exec->d->pixels[o + 3]);
        //     // printf("==> %c\n", exec->info.map[(int)floor(ray->dy / PIXELS)][(int)floor(ray->dx / PIXELS)]);
        //     mlx_put_pixel(exec->wind_image, rx, y++, color);
        // }
        if (ray->hv == 0 && ((angle >= 0 && angle < M_PI_2) || (angle >= 3 * M_PI_2 && angle < 2 * M_PI)))
            color = (int)ft_pixel(exec->we->pixels[o], exec->we->pixels[o + 1], exec->we->pixels[o + 2], exec->we->pixels[o + 3]);
        else if (ray->hv == 0 && angle >= M_PI_2 && angle < 3 * M_PI_2)
            color = (int)ft_pixel(exec->ea->pixels[o], exec->ea->pixels[o + 1], exec->ea->pixels[o + 2], exec->ea->pixels[o + 3]);
        else if (ray->hv == 1 && angle >= 0 && angle < M_PI)
            color = (int)ft_pixel(exec->so->pixels[o], exec->so->pixels[o + 1], exec->so->pixels[o + 2], exec->so->pixels[o + 3]);
        else if (ray->hv == 1 && angle >= M_PI && angle < 2 * M_PI)
            color = (int)ft_pixel(exec->no->pixels[o], exec->no->pixels[o + 1], exec->no->pixels[o + 2], exec->no->pixels[o + 3]);
        // if (ray->hv)
        //     color = 0xff0000ff;
        // else
        //     color = 0x00ff00ff;
        mlx_put_pixel(exec->wind_image, rx, y++, color);


        while (y < end_y && y < data->map.map_hight * data->map.tile_size)
    {
        int distance = y - ((data->map.map_hight * data->map.tile_size) / 2) + (wall_proj / 2);
        float tex_y_ratio = (float)distance / (float)wall_proj;
        int tex_y = (int)(tex_y_ratio * texture_height);
        unsigned int pixel = texture_data[(tex_y * texture_width) + tex_x];
       int32_t

        mlx_put_pixel(data->mlx_img, i, y, apply_shadow(color, 0x000000FF, dis, 1500.0f));
        y++;
    }

    void    init_xindex(t_data *data, int *xindex)
{
    *xindex = (((int)data->rays->wall_hit_x % TILE_SIZE) * \
            data->texture[data->rays->flag]->width) / TILE_SIZE;
    if (data->rays->flag == 1 || data->rays->flag == 2)
        *xindex = data->texture[data->rays->flag]->width - *xindex - 1;
}

void    draw_wall(t_data *data, int x, int y, int ydes)
{
    int    i;
    int    yi;
    int    xindex;
    int    xi;

    init_xindex(data, &xindex);
    i = 0;
    while (i < y && i < HEIGHT)
        mlx_put_pixel(data->image, x, i++, \
        ft_pixel(data->c[0], data->c[1], data->c[2], 255));
    while (i < ydes && i < HEIGHT)
    {
        yi = (i - y) * data->texture[data->rays->flag]->height / (ydes - y);
        xi = (xindex + yi * data->texture[data->rays->flag]->width) * \
        data->texture[data->rays->flag]->bytes_per_pixel;
        mlx_put_pixel(data->image, x, i++,
            ft_pixel(data->texture[data->rays->flag]->pixels[xi], \
                data->texture[data->rays->flag]->pixels[xi + 1],
                data->texture[data->rays->flag]->pixels[xi + 2],
                data->texture[data->rays->flag]->pixels[xi + 3]));
    }
    while (i < HEIGHT)
        mlx_put_pixel(data->image, x, i++, ft_pixel(data->f[0],
                data->f[1], data->f[2], 255));
}

int32_t    ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}