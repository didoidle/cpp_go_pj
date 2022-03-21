#include "CheckWinner.h"

CheckWinner::CheckWinner() {}

CheckWinner::~CheckWinner() {}

void CheckWinner::direct(int x, int y)
{
    directX = x;
    directY = y;
}

bool CheckWinner::checkOver(int xPos, int yPos, int color, float mat[15][15][3])
{

    int count[8] = { 0, }; // [0 0 0 0 0 0 0 0]

    for (int i = 0; i < 8; i++)
    {
        int x = xPos;
        int y = yPos;

        while (0 <= x && x <= 14 && 0 <= y && y <= 14)
        {

            switch (i)
            {
            case 0:
                direct(-1, -1); //왼 아래 대각
                break;
            case 1:
                direct(0, -1); // 아래
                break;
            case 2:
                direct(1, -1);
                break;
            case 3:
                direct(1, 0);
                break;
            case 4:
                direct(1, 1);
                break;
            case 5:
                direct(0, 1);
                break;
            case 6:
                direct(-1, 1);
                break;
            case 7:
                direct(-1, 0);
                break;
            default:
                break;
            }

            x = x + directX;
            y = y + directY;

            if (x >= 0 && y >= 0 && x <= 14 && y <= 14) {

                if (mat[y][x][2] == color)
                {
                    count[i]++;
                }
                else
                    break;
            }
            else
                break;

        }

        if ((count[0] + count[4]) == 4) {
            cout << (color == 1 ? "흑돌 승리" : "백돌 승리") << endl;
            return true;
            break;
        }
        else if ((count[1] + count[5]) == 4) {

            cout << (color == 1 ? "흑돌 승리" : "백돌 승리") << endl;
            return true;
            break;
        }
        else if ((count[2] + count[6]) == 4) {
            cout << (color == 1 ? "흑돌 승리" : "백돌 승리") << endl;
            return true;
            break;
        }
        else if ((count[3] + count[7]) == 4) {
            cout << (color == 1 ? "흑돌 승리" : "백돌 승리") << endl;
            return true;
            break;
        }
        else
            continue;
    }

    return false;
}
