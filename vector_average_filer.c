//
//  vector_average_filer.c
//  send
//
//  Created by Yosacy on 2021/11/09.
//

//#include "vector_average_filer.h"
#include <stdio.h>
#include <math.h>

#define d_1 100
#define d_2 100
#define d_3 100
#define d_4 100

void vector_average_filter(int row_mvs[d_1][d_2][d_3][d_4], int filtered_mvs[d_1][d_2][d_3][d_4])
{
#pragma HLS INTERFACE s_axilite port=row_mvs
#pragma HLS INTERFACE s_axilite port=filtered_mvs
#pragma HLS INTERFACE s_axilite port=return
    for(int t = 0; t < d_1; t++)
    {
        for(int y = 0; y < d_2; y++)
        {
            for(int x =0; x < d_3; x++)
            {
                int ave_vector[2] = {0, 0};
                int cnti = 0;
                for(int ti = -1; ti <= 1; ti++)
                {
                    for(int yi = -2; yi <= 2; yi++)
                    {
                        for(int xi = -2; xi <= 2; xi++)
                        {
                            if(y+yi >= 0 && y+yi < d_2 && x+xi >= 0 && x+xi < d_3 && t+ti < d_1 && t+ti >= 0)
                            {
                                cnti += 1;
                                ave_vector[0] += row_mvs[t + ti][y + yi][x + xi][2] - row_mvs[t + ti][y + yi][x + xi][0];
                                ave_vector[1] += row_mvs[t + ti][y + yi][x + xi][3] - row_mvs[t + ti][y + yi][x + xi][1];
                            }
                        }
                    }
                }
                filtered_mvs[t][y][x][0] = row_mvs[t][y][x][0];
                filtered_mvs[t][y][x][1] = row_mvs[t][y][x][1];
                filtered_mvs[t][y][x][2] = row_mvs[t][y][x][0] + ave_vector[0];
                filtered_mvs[t][y][x][3] = row_mvs[t][y][x][1] + ave_vector[1];
                filtered_mvs[t][y][x][4] = pow((filtered_mvs[t][y][x][0] - filtered_mvs[t][y][x][2]), 2) + pow((filtered_mvs[t][y][x][1] - filtered_mvs[t][y][x][3]), 2);
            }
        }
    }
}
