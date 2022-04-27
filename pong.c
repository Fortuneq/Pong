
#include <stdio.h>
#include "./pong.h"

struct Ball_str    Ball;
struct Pleer_2_str Pleer_2;
struct Pleer_1_str Pleer_1;

int get_shot = 0;

int allow_up_pleer_1 = 1;
int allow_down_pleer_1 = 1;

int allow_up_pleer_2 = 1;
int allow_down_pleer_2 = 1;

void initialization(void);
int print_a_simbol(int x, int y);
void ininitial_state(void);
int end_pattern(const int * src, int pleer);
void choice_direction(void);

int main(void) {
    char mv;

    initialization();

    while (1) {
        for (int y = 0; y <= BUTTOM; y++) {
            for (int x = 0; x <= RIGHT_WALL; x++) {
                Ball.ball_x = 40 + Ball.add_ball_x;
                Ball.ball_y = 12 + Ball.add_ball_y;

                Pleer_2.pleer_2_y1 = 10 - Pleer_2.add_pleer_2;
                Pleer_2.pleer_2_y2 = 12 - Pleer_2.add_pleer_2;

                Pleer_1.pleer_1_y1 = 10 - Pleer_1.add_pleer_1;
                Pleer_1.pleer_1_y2 = 12 - Pleer_1.add_pleer_1;

                int to_do = print_a_simbol(x, y);
                if (to_do == 1) continue;
                if (to_do == -1) return 0;
            }

            printf("\n");
        }

        if (scanf("%c", &mv)) {
            switch (mv) {
                case 97:
                    if (allow_up_pleer_1) {
                        Pleer_1.add_pleer_1++;
                        allow_down_pleer_1 = 1;
                    }
                    break;
                case 122:
                    if (allow_down_pleer_1) {
                        Pleer_1.add_pleer_1--;
                        allow_up_pleer_1 = 1;
                    }
                    break;
                case 107:
                    if (allow_up_pleer_2) {
                        Pleer_2.add_pleer_2++;
                        allow_down_pleer_2 = 1;
                    }
                    break;
                case 109:
                    if (allow_down_pleer_2) {
                        Pleer_2.add_pleer_2--;
                        allow_up_pleer_2 = 1;
                    }
                    break;
                default:
                    break;
            }

            if (Ball.allow_y_offsets) {
                if (Ball.offset_y_direction) {
                    Ball.add_ball_y--;
                } else {
                    Ball.add_ball_y++;
                }
            }

            if (Ball.offset_x_direction) {
                Ball.add_ball_x--;
            } else {
                Ball.add_ball_x++;
            }
            get_shot = 0;
            printf("\033[0d\033[2J");
        }
    }
}


int print_a_simbol(int x, int y) {
    static int scr1 = 0, scr2 = 0;

    // Для счёта
    if (Ball.ball_x == 80 && !get_shot) {
        ++scr1;

        if (end_pattern(&scr1, 1)) return -1;
        ininitial_state();
        get_shot = 1;
    }

    if (Ball.ball_x == 0 && !get_shot) {
        ++scr2;

        if (end_pattern(&scr2, 0)) return -1;
        ininitial_state();
        get_shot = 1;
    }

    // Табло для левого игрока
    if (y == 3 && x == 15) {
        printf("%d", scr1);
        return 1;
    }

    // Табло для правого игрока
    if (y == 3 && x == 65) {
        printf("%d", scr2);
        return 1;
    }

    choice_direction();

    if (Ball.ball_y == TOP + 1) {
        Ball.offset_y_direction = 0;
    }

    if (Ball.ball_y == BUTTOM - 1) {
        Ball.offset_y_direction = 1;
    }

    if (Pleer_1.pleer_1_y1 == TOP) {
        allow_up_pleer_1 = 0;
    }
    if (Pleer_2.pleer_2_y1 == TOP) {
        allow_up_pleer_2 = 0;
    }
    if (Pleer_1.pleer_1_y2 == BUTTOM) {
        allow_down_pleer_1 = 0;
    }
    if (Pleer_2.pleer_2_y2 == BUTTOM) {
        allow_down_pleer_2 = 0;
    }

    if (x == 0 && (y >= Pleer_1.pleer_1_y1 && y <= Pleer_1.pleer_1_y2)) {
        printf("|");
        return 1;
    }

    if (x == Ball.ball_x && y == Ball.ball_y) {
        printf(".");
        return 1;
    }

    if (x == 40) {
        printf("|");
        return 1;
    }
    if (x == 80 && (y >= Pleer_2.pleer_2_y1 && y <= Pleer_2.pleer_2_y2)) {
        printf("|");
        return 1;
    }

    printf(" ");
    return 0;
}

void initialization(void) {
    Pleer_1.add_pleer_1 = 0;
    Pleer_2.add_pleer_2 = 0;

    Ball.add_ball_x = 0;
    Ball.add_ball_y = 0;

    Pleer_1.pleer_1_x = 0;
    Pleer_2.pleer_2_x = 80;

    Ball.allow_y_offsets = 0;
    Ball.offset_x_direction = 0;
    Ball.offset_y_direction = 0;
}

void ininitial_state(void) {
    Ball.add_ball_x = 0;
    Ball.add_ball_y = 0;
    Ball.allow_y_offsets = 0;
}

int end_pattern(const int * src, int pleer) {
    if (*src == FINAL_SCORE) {
        printf("\033[0d\033[2J");
        for (int y = 0; y <= BUTTOM; y++) {
            for (int x = 0; x <= RIGHT_WALL; x++) {
                if (pleer) {
                    if (x == 47 && y == 11) {
                        printf("/");
                        continue;
                    }

                    if (x == 48 && (y >= 11 && y <= 14)) {
                        printf("|");
                        continue;
                    }

                    if (x == 46  && y == 12) {
                        printf("/");
                        continue;
                    }
                } else {
                    if (x == 45 && y == 11) {
                        printf("|");
                        continue;
                    }

                    if ((x == 46 || x == 47) && y == 11) {
                        printf("-");
                        continue;
                    }

                    if (x ==48 && (y == 11 || y == 12)) {
                        printf("|");
                        continue;
                    }
                    if (x == 47 && y == 13) {
                        printf("/");
                        continue;
                    }

                    if (x == 46 && y == 14) {
                        printf("/");
                        continue;
                    }

                    if ((x >= 46 && x <= 48) && y == 15) {
                        printf("-");
                        continue;
                    }
                }

                    if ((x == 35 || x == 60) && y == 9) {
                        printf("|");
                        continue;
                    }
                    if ((x > 35 && x < 60) && y == 9) {
                        printf("~");
                        continue;
                    }

                    if ((x == 35 || x == 60) && (y >= 10 && y<= 16)) {
                        printf("|");
                        continue;
                    }

                    if ((x == 35 || x == 60) && y == 17) {
                        printf("|");
                        continue;
                    }
                    if ((x > 35 && x < 60) && y == 17) {
                        printf("_");
                        continue;
                    }

                    printf(" ");
            }
            printf("\n");
        }
        return 1;
    }
    return 0;
}

void choice_direction(void) {
    if (Ball.ball_x == (Pleer_1.pleer_1_x + 1)) {
        if (Ball.ball_y == Pleer_1.pleer_1_y1) {
            Ball.allow_y_offsets = 1;
            Ball.offset_x_direction = 0;
            Ball.offset_y_direction = 0;
        }

        if (Ball.ball_y == Pleer_1.pleer_1_y1 + 1) {
            Ball.allow_y_offsets = 0;
            Ball.offset_x_direction = 0;
            Ball.offset_y_direction = 0;
        }

        if (Ball.ball_y == Pleer_1.pleer_1_y2) {
            Ball.allow_y_offsets = 1;
            Ball.offset_x_direction = 0;
            Ball.offset_y_direction = 1;
        }
    }

    if (Ball.ball_x == (Pleer_2.pleer_2_x - 1)) {
        if (Ball.ball_y == Pleer_2.pleer_2_y1) {
            Ball.allow_y_offsets = 1;
            Ball.offset_x_direction = 1;
            Ball.offset_y_direction = 1;
        }

        if (Ball.ball_y == Pleer_2.pleer_2_y1 + 1) {
            Ball.allow_y_offsets = 0;
            Ball.offset_x_direction = 1;
            Ball.offset_y_direction = 1;
        }

        if (Ball.ball_y == Pleer_2.pleer_2_y2) {
            Ball.allow_y_offsets = 1;
            Ball.offset_x_direction = 1;
            Ball.offset_y_direction = 0;
        }
    }
}
