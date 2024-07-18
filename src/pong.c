#include <math.h>
#include <stdio.h>

int count(int racket1_X, int racket1_Y, int racket2_X, int racket2_Y, int ball_X, int ball_Y, int sc1,
          int sc2, int game);
int render(int racket1_X, int racket1_Y, int racket2_X, int racket2_Y, int ball_X, int ball_Y, int sc1,
           int sc2);

int main() {
    int height = 25;
    int width = 80;
    int racket1_X = 3;
    int racket1_Y = (height / 2) - 1;
    int racket2_X = width - 4;
    int racket2_Y = (height / 2) - 1;
    int ball_X = width / 2;
    int ball_Y = height / 2;
    int sc1 = 0;
    int sc2 = 0;
    int game = 1;

    count(racket1_X, racket1_Y, racket2_X, racket2_Y, ball_X, ball_Y, sc1, sc2, game);
}

int count(int racket1_X, int racket1_Y, int racket2_X, int racket2_Y, int ball_X, int ball_Y, int sc1,
          int sc2, int game) {
    int height = 25;
    int width = 80;
    int ballSpawn_X = width / 2;
    int ballSpawn_Y = height / 2;
    int ball_moveUp = 0;
    int ball_moveRight = 0;
    int ball_moveDown = 1;
    int ball_moveLeft = 1;

    while (game) {
        render(racket1_X, racket1_Y, racket2_X, racket2_Y, ball_X, ball_Y, sc1, sc2);
        // Управление
        char keyMove;
        char q;
        if (scanf("%c%c", &keyMove, &q) == 2 && q == '\n') {
            switch (keyMove) {
                case 'a':
                    (racket1_Y - 1) != 0 ? (racket1_Y -= 1) : racket1_Y;
                    break;
                case 'z':
                    (racket1_Y + 3) != (height - 1) ? (racket1_Y += 1) : racket1_Y;
                    break;
                case 'k':
                    (racket2_Y - 1) != 0 ? (racket2_Y -= 1) : racket2_Y;
                    break;
                case 'm':
                    (racket2_Y + 3) != (height - 1) ? (racket2_Y += 1) : racket2_Y;
                    break;
                case ' ':
                    break;
            }
        } else
            printf("Control: A/Z and K/M");
        // Движение мяча
        if (ball_moveUp) ball_Y--;
        if (ball_moveRight) ball_X++;
        if (ball_moveDown) ball_Y++;
        if (ball_moveLeft) ball_X--;
        // Столкневения
        if (ball_Y == 1) {  // Вверхняя стенка
            ball_moveDown = 1;
            ball_moveUp = 0;
        } else if (ball_Y == (height - 2)) {  // Нижняя стенка
            ball_moveUp = 1;
            ball_moveDown = 0;
        } else if (ball_X == 0) {  // Гол первому игроку
            sc2 += 1;
            ball_moveLeft = 0;
            ball_moveRight = 1;
            ball_X = ballSpawn_X;
            ball_Y = ballSpawn_Y;
        } else if (ball_X == (width - 1)) {  //  Гол второму игркоку
            sc1 += 1;
            ball_moveLeft = 1;
            ball_moveRight = 0;
            ball_X = ballSpawn_X;
            ball_Y = ballSpawn_Y;
        } else if (ball_X == 4) {  // Столкневение с первой ракеткой
            for (int i = 0; i < 3; i++) {
                if (ball_Y == racket1_Y + i) {
                    ball_moveRight = 1;
                    ball_moveLeft = 0;
                }
            }
        } else if (ball_X == (width - 5)) {  // Столкневение со второй ракеткой
            for (int i = 0; i < 3; i++) {
                if (ball_Y == racket2_Y + i) {
                    ball_moveLeft = 1;
                    ball_moveRight = 0;
                }
            }
        }
        render(racket1_X, racket1_Y, racket2_X, racket2_Y, ball_X, ball_Y, sc1, sc2);
        if (sc1 == 10) {
            game = 0;
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\nGAME OVER! WIN'S PLAYER #2!");
        } else if (sc2 == 10) {
            game = 0;
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\nGAME OVER! WIN'S PLAYER #1!");
        }
    }
    return 0;
}

int render(int racket1_X, int racket1_Y, int racket2_X, int racket2_Y, int ball_X, int ball_Y, int sc1,
           int sc2) {  // Отрисовка интерфейса

    int width = 80;
    int height = 25;
    char wall_c = '#';
    char ball_c = 'o';
    char racket1_c = ']';
    char racket2_c = '[';

    printf("\n\t\t\t\t   SCORE %d:%d\n\n", sc1, sc2);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
                printf("%c", wall_c);  // стены
            else if (j == ball_X && i == ball_Y)
                printf("%c", ball_c);  // мяч
            else if (j == racket1_X && (i == racket1_Y || i == racket1_Y + 1 || i == racket1_Y + 2))
                printf("%c", racket1_c);  // ракетка 1
            else if (j == racket2_X && (i == racket2_Y || i == racket2_Y + 1 || i == racket2_Y + 2))
                printf("%c", racket2_c);  // ракетка 2
            else
                printf(" ");
        }
        printf("\n");
    }
    return 0;
}