# cub3d

create a “realistic” 3D graphical representation using ray-casting

-  허용 함수

    <img width="275" alt="Screen Shot 2024-05-08 at 5 14 04 PM" src="https://github.com/Eunryong/cub/assets/86572427/0fb42907-5b63-4416-be93-350ed0e2f866">
    
-  MinilibX

    X-Window 및 Cocoa에 대한 지식 없이 기본적인 렌더링을 위한 가장 기본적인 작업을 수행할 수 있는 작은 그래픽 라이브러리

    [MinilibX](https://harm-smits.github.io/42docs/libs/minilibx)

## Ray Casting

  #### 레이캐스팅
    2차원 맵에서 3차원의 원근감을 구현하기 위한 렌더링 기술
    가상의 공간에 보이지 않는 빛(Ray)을 투사해 빛에 닿는 표면을 파악하는 기술
    빛을 투사해 벽을 만나면 거리를 얻고, 거리를 통해 세로줄의 길이를 정한다.
    
  #### 구현

  
  - 구조체
  
    ```c
      typedef struct s_ray
      {
        double	camera;
        double	raydir_x;
        double	raydir_y;
        int		map_x;
        int		map_y;
        double	sidedist_x;
        double	sidedist_y;
        double	deltadist_x;
        double	deltadist_y;
        double	walldist;
        int		step_x;
        int		step_y;
        int		hit;
        int		side;
        int		line_height;
        int		draw_start;
        int		draw_end;
        int		texture_num;
        double	wall_x;
        int		texture_x;
      }	t_ray;
    ```
    
  - 거리계산(dda 알고리즘)
    ```c
    void	dda(t_game *game, t_ray *ray)
    {
    	t_map	*map;
    
    	map = game->map;
    	while (ray->hit == 0)
    	{
    		if (ray->sidedist_x < ray->sidedist_y)
    		{
    			ray->sidedist_x += ray->deltadist_x;
    			ray->map_x += ray->step_x;
    			ray->side = 0;
    		}
    		else
    		{
    			ray->sidedist_y += ray->deltadist_y;
    			ray->map_y += ray->step_y;
    			ray->side = 1;
    		}
    		if (map->map[ray->map_y][ray->map_x] > 0)
    			ray->hit = 1;
    	}
    }
    
    void	calculate_distance(t_game *game, t_ray *ray)
    {
    	t_player	*player;
    
    	player = game->player;
    	if (ray->side == 0)
    		ray->walldist = ray->sidedist_x - ray->deltadist_x;
    	else
    		ray->walldist = ray->sidedist_y - ray->deltadist_y;
    	ray->line_height = (int)(WIN_HEIGHT / ray->walldist);
    	ray->draw_start = WIN_HEIGHT / 2 - ray->line_height / 2;
    	if (ray->draw_start < 0)
    		ray->draw_start = 0;
    	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
    	if (ray->draw_end >= WIN_HEIGHT)
    		ray->draw_end = WIN_HEIGHT - 1;
    }
    ```


## Map Parsing
  #### example:


  <img width="228" alt="Screen Shot 2024-05-08 at 7 11 14 PM" src="https://github.com/Eunryong/cub/assets/86572427/81ac2483-9058-44bd-86bd-4b86c9e5d57b">
    
  #### 순서
  
  1. 한줄씩 타입 지정(texture: 0 ~ 3, bg-color: 4 ~ 5, map: 6)
  2. 데이터 유효성 체크 및 파싱
