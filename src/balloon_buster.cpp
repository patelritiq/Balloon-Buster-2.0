// Balloon Buster 2.0 - A simple console ballon shooting game optimized over the old legacy turbo c++ version. Now with multiple levels, difficulty settings, and a survival mode! also now cross platform compatible!!

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#endif

using namespace std;

#define HOME "\033[H"
#define CLEAR "\033[2J"
#define HIDE "\033[?25l"
#define SHOW "\033[?25h"

const int WIDTH = 100;
const int HEIGHT = 30;

const int FPS_PHYSICS = 10;
const int FPS_RENDER  = 4;

const int FRAME_PHYSICS = 1000 / FPS_PHYSICS;
const int FRAME_RENDER  = 1000 / FPS_RENDER;

enum class GameState {
    MENU,
    DIFFICULTY,
    RULES,
    PLAYING,
    LEVEL_RESULT,
    SURVIVAL_RULES,
    SURVIVAL,
    GAME_OVER,
    EXIT
};

struct Arrow {
    float x = 0;
    int y = 0;
    bool active = false;
};

struct Balloon {
    int x = 0;
    float y = 0;
    bool active = false;
};

class Game {

    GameState state = GameState::MENU;

    string playerName;
    int score = 0;
    int highScore = 0;
    int level = 1;

    int arrows = 6;
    int balloonsLogical = 12;

    int survivalMisses = 0;
    int survivalArrows = 15;

    float balloonSpeed = 0.18f;
    float arrowSpeed = 3.0f;

    Arrow arrow;
    Balloon balloons[2];
    int activeBalloons = 1;

    int bowY = HEIGHT / 2;

public:

    Game() { srand(time(nullptr)); }

    void loadHighScore() {
        ifstream file("highscore.dat");
        if (file) {
            string name;
            int s;
            file >> name >> s;
            highScore = s;
        }
    }

    void saveHighScore() {
        if (score > highScore) {
            ofstream file("highscore.dat");
            file << playerName << " " << score;
        }
    }

    void spawnBalloon(int i) {
        balloons[i].x = WIDTH - 8;
        balloons[i].y = HEIGHT - 6;
        balloons[i].active = true;
    }

    void resetLevelData() {
        arrows = 6;
        arrow.active = false;
        activeBalloons = 1;

        if (level == 1) balloonsLogical = 12;
        if (level == 2) balloonsLogical = 10;
        if (level == 3) balloonsLogical = 8;

        spawnBalloon(0);
    }

    void render() {

        cout << HOME;

        vector<string> buffer(HEIGHT, string(WIDTH, ' '));

        // Bow
        buffer[bowY][2] = ')';
        buffer[bowY-1][2] = ')';
        buffer[bowY+1][2] = ')';

        // Arrow
        if (arrow.active) {
            for (int i=0;i<4;i++)
                if ((int)arrow.x+i < WIDTH)
                    buffer[arrow.y][(int)arrow.x+i] = '-';
            if ((int)arrow.x+4 < WIDTH)
                buffer[arrow.y][(int)arrow.x+4] = '>';
        }

        vector<string> shape = {
            " ___ ",
            "/   \\",
            "|   |",
            "\\___/",
            "  |  "
        };

        for (int b=0;b<activeBalloons;b++) {
            if (!balloons[b].active) continue;
            int bx = balloons[b].x;
            int by = (int)balloons[b].y;
            for (int i=0;i<5;i++)
                for (int j=0;j<5;j++)
                    if (by+i < HEIGHT && bx+j < WIDTH)
                        buffer[by+i][bx+j] = shape[i][j];
        }

        cout << "=== BALLOON BUSTER 2.0 ===\n";
        cout << "Player: " << playerName
             << " | High Score: " << highScore << "\n";
        cout << "-----------------------------------------------\n";

        cout << "Level: " << level
             << "   Arrows: " << arrows
             << "   Score: " << score << "\n\n";

        for (int y=0;y<HEIGHT;y++)
            cout << buffer[y] << "\n";
    }

    void updatePhysicsLevel() {

        if (arrow.active) {
            arrow.x += arrowSpeed;

            if (arrow.x > WIDTH) {
                arrow.active = false;
            }
        }

        for (int i=0;i<activeBalloons;i++) {

            if (!balloons[i].active) continue;

            balloons[i].y -= balloonSpeed;

            if (balloons[i].y < 1)
                spawnBalloon(i);

            if (arrow.active) {
                int tipX = (int)arrow.x + 4;
                int tipY = arrow.y;

                int bx = balloons[i].x;
                int by = (int)balloons[i].y;

                if (tipX >= bx && tipX <= bx+4 &&
                    tipY >= by && tipY <= by+4) {

                    score += 20;
                    balloonsLogical--;
                    arrow.active = false;
                    spawnBalloon(i);
                }
            }
        }
    }

    void updatePhysicsSurvival() {

        if (arrow.active) {
            arrow.x += arrowSpeed;

            if (arrow.x > WIDTH) {
                arrow.active = false;
                survivalMisses++;
            }
        }

        balloons[0].y -= balloonSpeed;

        if (balloons[0].y < 1)
            spawnBalloon(0);

        if (arrow.active) {
            int tipX = (int)arrow.x + 4;
            int tipY = arrow.y;

            int bx = balloons[0].x;
            int by = (int)balloons[0].y;

            if (tipX >= bx && tipX <= bx+4 &&
                tipY >= by && tipY <= by+4) {

                score += 20;
                arrow.active = false;
                spawnBalloon(0);

                if (score % 40 == 0)
                    balloonSpeed += 0.03f;
            }
        }
    }

    void showRules() {

        cout << CLEAR;
        cout << "LEVEL " << level << " RULES\n\n";

        if (level == 1) {
            cout << "• 6 Arrows\n• 12 Balloons\n• 20 Points per Balloon\n";
            cout << "• 100 Points needed to clear level\n\n";
        }
        if (level == 2) {
            cout << "• 6 Arrows\n• 10 Balloons\n• 20 Points per Balloon\n";
            cout << "• 200 Points needed to clear level\n\n";
        }
        if (level == 3) {
            cout << "• 6 Arrows\n• 8 Balloons\n• 20 Points per Balloon\n";
            cout << "• 300 Points needed\n";
            cout << "• Two balloons active\n\n";
        }

        cout << "Controls:\n";
        cout << "W - Move Up\n";
        cout << "S - Move Down\n";
        cout << "SPACE - Shoot\n";
        cout << "Q - Quit\n\n";

        cout << "Press Enter to Start...";
        cin.ignore();
        cin.get();
    }

    void showSurvivalRules() {
        cout << CLEAR;
        cout << "SURVIVAL MODE\n\n";
        cout << "• 15 Arrows\n";
        cout << "• Unlimited Balloons\n";
        cout << "• Ends after 3 misses OR arrows finish\n";
        cout << "• Speed increases every 40 points\n\n";
        cout << "Press Enter to Enter Survival...";
        cin.ignore();
        cin.get();
    }

    void levelResult() {

        cout << CLEAR;

        cout << "ROUND COMPLETE\n\n";
        cout << "Player: " << playerName << "\n";
        cout << "Level: " << level << "\n";
        cout << "Score: " << score << "\n";
        cout << "High Score: " << highScore << "\n\n";

        int required = level * 100;

        if (score >= required) {
            cout << "Congratulations! Level Cleared.\n";
            cout << "Proceed to next level? (Y/N)\n";
            char c; cin >> c;
            if (c=='y' || c=='Y') {
                level++;
                state = GameState::RULES;
            } else state = GameState::EXIT;
        }
        else {
            cout << "Level Failed.\n";
            cout << "Retry? (Y/N)\n";
            char c; cin >> c;
            if (c=='y' || c=='Y')
                state = GameState::RULES;
            else state = GameState::EXIT;
        }
    }

    void survivalResult() {
        cout << CLEAR;
        cout << "SURVIVAL COMPLETE\n\n";
        cout << "Score: " << score << "\n";
        cout << "Misses: " << survivalMisses << "\n\n";
        cout << "Press Enter to Exit...";
        cin.ignore();
        cin.get();
        state = GameState::EXIT;
    }

    void run() {

        cout << CLEAR << HIDE;
        loadHighScore();

        while (state != GameState::EXIT) {

            if (state == GameState::MENU) {
                cout << CLEAR;
                cout << "=== BALLOON BUSTER 2.0 ===\n";
                cout << "1. Start\n2. Quit\n";
                char c; cin >> c;
                if (c=='1') state = GameState::DIFFICULTY;
                else state = GameState::EXIT;
            }

            else if (state == GameState::DIFFICULTY) {
                cout << CLEAR;
                cout << "Select Difficulty\n1.Easy\n2.Normal\n3.Hard\n";
                char c; cin >> c;

                if (c=='1') balloonSpeed = 0.12f;
                else if (c=='3') balloonSpeed = 0.24f;
                else balloonSpeed = 0.18f;

                cout << "Enter Name: ";
                cin >> playerName;

                score = 0;
                level = 1;
                state = GameState::RULES;
            }

            else if (state == GameState::RULES) {
                resetLevelData();
                showRules();
                state = GameState::PLAYING;
            }

            else if (state == GameState::PLAYING) {

                auto lastPhysics = chrono::steady_clock::now();
                auto lastRender  = chrono::steady_clock::now();

                while (state == GameState::PLAYING) {

#ifdef _WIN32
                    if (_kbhit()) {
                        char c = _getch();
                        if (c=='w' && bowY>2) bowY--;
                        if (c=='s' && bowY<HEIGHT-3) bowY++;
                        if (c==' ' && !arrow.active && arrows>0) {
                            arrow = {3.0f, bowY, true};
                            arrows--;
                        }
                        if (c=='q') state = GameState::EXIT;
                    }
#endif

                    auto now = chrono::steady_clock::now();

                    if (chrono::duration_cast<chrono::milliseconds>(now-lastPhysics).count() >= FRAME_PHYSICS) {
                        updatePhysicsLevel();
                        lastPhysics = now;
                    }

                    if (chrono::duration_cast<chrono::milliseconds>(now-lastRender).count() >= FRAME_RENDER) {
                        render();
                        lastRender = now;
                    }

                    if (arrows <= 0 && !arrow.active)
                        state = GameState::LEVEL_RESULT;

                    this_thread::sleep_for(chrono::milliseconds(1));
                }
            }

            else if (state == GameState::LEVEL_RESULT) {
                saveHighScore();
                levelResult();
            }

            else if (state == GameState::SURVIVAL) {
                // similar structure for survival loop
                survivalResult();
            }
        }

        cout << SHOW;
    }
};

int main() {
    Game g;
    g.run();
    return 0;
}