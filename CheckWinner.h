//#pragma once
//#include <stdio.h>
//
//class CheckWinner
//{
//
//private :
//    int direct_x;
//    int direct_y;
//    float matrix[15][15][3]; 
//
//public: 
//
//	void direct(int x, int y) {
//		direct_x = x;
//		direct_y = y;
//	}
//
//	void checkOver(int px, int py, float mat[15][15][3]) {
//		int count[8] = { 0, };
//
//		for (int i = 0; i < 8; i++) {
//
//			int x = px;  int y = py;
//
//			while (0 <= x && x < 15 && 0 <= y && y < 15) {
//
//				switch (i)
//				{
//                case 0:
//                    direct(-1, -1);
//                    break;
//                case 1:
//                    direct(0, -1);
//                    break;
//                case 2:
//                    direct(1, -1);
//                    break;
//                case 3:
//                    direct(1, 0);
//                    break;
//                case 4:
//                    direct(1, 1);
//                    break;
//                case 5:
//                    direct(0, 1);
//                    break;
//                case 6:
//                    direct(-1, 1);
//                    break;
//                case 7:
//                    direct(-1, 0);
//				default:
//					break;
//				}
//
//                x = x + direct_x;
//                y = y + direct_y;
//
//                if (x >= 0 && y >= 0 && x <= 14 && y <= 14) {
//                    if (mat[y][x][2] == mat[py][px][2]) {
//                        count[i] ++;
//                    }
//                    else break;
//                }
//                else break;
//
//			}
//
//            if ((count[0] + count[4]) == 4) {
//                over();
//                break;
//            }
//            else if ((count[1] + count[5]) == 4) {
//                over();
//                break;
//            }
//            else if ((count[2] + count[6]) == 4) {
//                over();
//                break;
//            }
//            else if ((count[3] + count[7]) == 4) {
//                over();
//                break;
//            }
//            else
//                continue;
//		}
//	}
//
//
//};
//
