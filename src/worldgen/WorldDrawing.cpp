//
//  WorldDrawing.cpp
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/4/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//

#include "WorldDrawing.h"
#include "../mapping/Tile.h"
#include "../mapping/TileMap.h"
#include "../mapping/WorldMap.h"
#include "../mapping/GeometryFunctions.h"
#include "../utils/FileLogger.h"

#include <string>
#include <algorithm>



void drawLineOnTileMap(int x1, int y1, int x2, int y2, TileMap *output, std::string symbol){
    Bresenham2D(x1, y1, x2, y2, output, symbol);
}



void drawLineOnWorldMap(int x1, int y1, int z1, int x2, int y2, int z2, WorldMap *output, std::string symbol){
    Bresenham3D(x1, y1, z1, x2, y2, z2, output, symbol);
}



// Original Author Unknown
// A slightly modified version of the code found at
// http://roguebasin.roguelikedevelopment.org/index.php?title=Bresenham%27s_Line_Algorithm

void Bresenham2D(int x1, int y1, int const x2, int const y2, TileMap *output, std::string symbol){
    int delta_x(x2 - x1);
    // if x1 == x2, then it does not matter what we set here
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = std::abs(delta_x) << 1;
    
    int delta_y(y2 - y1);
    // if y1 == y2, then it does not matter what we set here
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = std::abs(delta_y) << 1;
    
    //plot(x1, y1);
    output->setTileSymbol(x1, y1, symbol);
    
    if (delta_x >= delta_y)
    {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));
        
        while (x1 != x2)
        {
            if ((error >= 0) && (error || (ix > 0)))
            {
                error -= delta_x;
                y1 += iy;
            }
            // else do nothing
            
            error += delta_y;
            x1 += ix;
            
            //plot(x1, y1);
            output->setTileSymbol(x1, y1, symbol);
        }
    }
    else
    {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));
        
        while (y1 != y2)
        {
            if ((error >= 0) && (error || (iy > 0)))
            {
                error -= delta_y;
                x1 += ix;
            }
            // else do nothing
            
            error += delta_x;
            y1 += iy;
            
            //plot(x1, y1);
            output->setTileSymbol(x1, y1, symbol);
        }
    }
}



// Original Author Unknown
// A slightly modified version of the source found at
// http://www.ict.griffith.edu.au/anthony/info/graphics/bresenham.procs
// Provided by Anthony Thyssen, though he does not take credit for the original implementation
//
// We can confirm that it does work, however at the time he didn't see a purpose for its use.
//
// "3d Bresenham Line Drawing  (Why I don't know)
// Note I have NOT tested this, just include it from a news groups."
// 


void Bresenham3D(int x1, int y1, int z1, const int x2, const int y2, const int z2, WorldMap *output, std::string symbol){
    
   // if( (std::max(x1,x2) > output->getX()) || (std::max(y1,y2) > output->getY()) || std::max(z1,z2) > output->getZ() )
   //     return;
    
    int i, dx, dy, dz, l, m, n, x_inc, y_inc, z_inc, err_1, err_2, dx2, dy2, dz2;
    int point[3];
    
    point[0] = x1;
    point[1] = y1;
    point[2] = z1;
    dx = x2 - x1;
    dy = y2 - y1;
    dz = z2 - z1;
    x_inc = (dx < 0) ? -1 : 1;
    l = abs(dx);
    y_inc = (dy < 0) ? -1 : 1;
    m = abs(dy);
    z_inc = (dz < 0) ? -1 : 1;
    n = abs(dz);
    dx2 = l << 1;
    dy2 = m << 1;
    dz2 = n << 1;
    
    if ((l >= m) && (l >= n)) {
        err_1 = dy2 - l;
        err_2 = dz2 - l;
        for (i = 0; i < l; i++) {
            output->getTileAt(point[0], point[1], point[2])->setSymbol(symbol);
            if (err_1 > 0) {
                point[1] += y_inc;
                err_1 -= dx2;
            }
            if (err_2 > 0) {
                point[2] += z_inc;
                err_2 -= dx2;
            }
            err_1 += dy2;
            err_2 += dz2;
            point[0] += x_inc;
        }
    } else if ((m >= l) && (m >= n)) {
        err_1 = dx2 - m;
        err_2 = dz2 - m;
        for (i = 0; i < m; i++) {
            output->getTileAt(point[0], point[1], point[2])->setSymbol(symbol);
            if (err_1 > 0) {
                point[0] += x_inc;
                err_1 -= dy2;
            }
            if (err_2 > 0) {
                point[2] += z_inc;
                err_2 -= dy2;
            }
            err_1 += dx2;
            err_2 += dz2;
            point[1] += y_inc;
        }
    } else {
        err_1 = dy2 - n;
        err_2 = dx2 - n;
        for (i = 0; i < n; i++) {
            output->getTileAt(point[0], point[1], point[2])->setSymbol(symbol);
            if (err_1 > 0) {
                point[1] += y_inc;
                err_1 -= dz2;
            }
            if (err_2 > 0) {
                point[0] += x_inc;
                err_2 -= dz2;
            }
            err_1 += dy2;
            err_2 += dx2;
            point[2] += z_inc;
        }
    }
    output->getTileAt(point[0], point[1], point[2])->setSymbol(symbol);
}
