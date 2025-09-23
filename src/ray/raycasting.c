/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:27:16 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/09/23 14:03:48 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//calculamos la distancia a la muralla con un rayo, usamos dos rayos uno que mide la primera colision con el grid en el eje x y otro con misma dirección y sentido pero revisando la colision con el grid y
//usamos el tamaño de cada tile para revisar colisión solo en ese punto pero sumandole el valor del tile en x e y



//pintamos en un buffer el rayo
//calculamos el siguiente rayo y pintamos en el buffer hasta tener toda la pantalla del buffer pintada, entonces lo cargamos en la pantalla de la MLX para que se pueda ver


/*
* BUCLE DDA
while (hit == 0) {
    // Avanzar al siguiente lado del grid más cercano
    if (sideDistX < sideDistY) {
        sideDistX += deltaDistX;
        mapX += stepX;
        side = 0; // golpeamos un lado vertical
    } else {
        sideDistY += deltaDistY;
        mapY += stepY;
        side = 1; // golpeamos un lado horizontal
    }
    
    // Verificar si golpeamos una pared
    if (map[mapX][mapY] == '1') {
        hit = 1;
    }
}
*/

/**
 * CALCULO DISTANCIA FINAL
 if (side == 0) // golpe en lado vertical
    perpWallDist = (mapX - rayPosX + (1 - stepX) / 2) / rayDirX;
else // golpe en lado horizontal
    perpWallDist = (mapY - rayPosY + (1 - stepY) / 2) / rayDirY;
 */