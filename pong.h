#define TOP        0
#define BUTTOM     25
#define RIGHT_WALL 80
#define LEFT_WALL  0

#define FINAL_SCORE 21

struct Pleer_1_str {
    int pleer_1_x;

    int pleer_1_y1;
    int pleer_1_y2;

    int add_pleer_1;
};

struct Pleer_2_str {
    int pleer_2_x;

    int pleer_2_y1;
    int pleer_2_y2;

    int add_pleer_2;
};

struct Ball_str {
    int allow_y_offsets;
    int offset_x_direction;
    int offset_y_direction;

    int add_ball_x;
    int add_ball_y;

    int ball_x;
    int ball_y;
};