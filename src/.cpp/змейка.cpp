
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <vector>


using namespace std;

string Game(int SizeFiedGame, char frameOther) {

    string base;
    string field;
    string BuildField;

    for (int i = 0; i < SizeFiedGame-1; i++) {                  // строим низ верх
        base.push_back(frameOther);
        base.push_back(frameOther);
    }
    base.push_back(frameOther);

    field.push_back('\n');
    field.push_back(frameOther);                                      // строим середину
    for (int i = 0; i < SizeFiedGame*2-3; i++) {
        field.push_back(' ');
    }
    field.push_back(frameOther);

    BuildField.append(base);                                   // складываем все
    for (int i = 0; i < SizeFiedGame - 2; i++) {   
        BuildField.append(field);
    }
    BuildField.push_back('\n');
    BuildField.append(base);

    return BuildField;
}

int main() {
    setlocale(LC_ALL, "ru");
    srand(time(NULL));

    HWND hwnd = GetConsoleWindow();
    if (hwnd != NULL) {                                                         
        MoveWindow(hwnd, 300, 300, 800, 800, TRUE);
    }

    string FieldGame{};

    int DirectionMove = 119;
    int SizeFiedGame = 0;
    int Duration;                                                               // спим
    
    char frame = '0';
    char TailSnake = '#';
    char HeadShanke = '@';
    char BodySnake = 'x';
    char Point = '+';

    cout << "укажите предпочтительный размер игрового поля от 10 до 40" << endl;

    for (; !(SizeFiedGame >= 10 && SizeFiedGame <= 40); ) {
        cin >> SizeFiedGame;
    }
    if (SizeFiedGame % 2 == 0) {
        SizeFiedGame--;
    }

    FieldGame = Game(SizeFiedGame, frame);

    int Head = (SizeFiedGame / 2) * (SizeFiedGame * 2) - SizeFiedGame;
    int Tail = (SizeFiedGame / 2) * (SizeFiedGame * 2) + SizeFiedGame;          //корды хвоста

    FieldGame[Tail] = TailSnake;
    FieldGame[Head] = HeadShanke;

    vector<int> lehgtnSnake;
    bool Lose = false;
    int ConstantTransition = SizeFiedGame * 2;                                  //постоянная перехода вверх вниз


    lehgtnSnake.push_back(Tail);
    lehgtnSnake.push_back(Head);

    cout << "а теперь введи скорость змейки в милисекундах от 0 до 50 (по желанию)" << endl << "чем меньше - тем быстрее" << endl;
    cin >> Duration;

    cout << FieldGame << endl;
    cout << "готов? управление WASD" << endl;

    system("pause");            

    if (hwnd != NULL) {                                 
        MoveWindow(hwnd, 300, 300, 700, 700, TRUE);
    }

    for (int DurationRef = 0; Lose == false ; DurationRef++) {                  // игра
        
        Sleep(Duration);                                                        // спим?

        if (DurationRef == 80) {                                              //спавн очков
            DurationRef -= 80;

            for ( ; ; ) {
                int randomPoint = rand() % (SizeFiedGame * SizeFiedGame * 2);

                if (FieldGame[randomPoint] == ' ' && randomPoint % 2 != 0) {
                    FieldGame[randomPoint] = Point;
                }
                break;
            }

        }

        if (_kbhit()) {                                                                                 // чекаем кнопки 97 и 228 ... 119 и 230 ...  115 и 235 .. 100 и 162
            int DirectionMoveCheck = _getch();
            if ((DirectionMoveCheck == 97 || DirectionMoveCheck == 228) && (DirectionMove == 100 || DirectionMove == 162)) {
                //cout << " невозможно повернуть " << endl;
            }
            else if ((DirectionMoveCheck == 100 || DirectionMoveCheck == 162) && (DirectionMove == 97 || DirectionMove == 228)) {
                //cout << " невозможно повернуть " << endl;
            }
            else if ((DirectionMoveCheck == 119 || DirectionMoveCheck == 230) && (DirectionMove == 115 || DirectionMove == 235)) {
                cout << " невозможно повернуть " << endl;
            }
            else if ((DirectionMoveCheck == 115 || DirectionMoveCheck == 235) && (DirectionMove == 119 || DirectionMove == 230)) {
                //cout << " невозможно повернуть " << endl;
            }
            else {
                DirectionMove = DirectionMoveCheck;
                //cout << " " << endl;
            }
        }

        if (DurationRef%10 == 1 ) {

            switch (DirectionMove) {
            case 97:
            case 228:                               // влево

                if (FieldGame[Head - 1] == frame || FieldGame[Head - 1] == TailSnake || FieldGame[Head - 1] == BodySnake ) {
                    Lose = true;
                }
                if (FieldGame[Head - 2] == Point) {
                    Head -= 2;
                    lehgtnSnake.push_back(Head);
                }
                else if (FieldGame[Head - 2] == ' ') {
                    FieldGame[*(lehgtnSnake.begin())] = ' ';
                    lehgtnSnake.erase(lehgtnSnake.begin());
                    Head -= 2;
                    lehgtnSnake.push_back(Head);
                }
                else {
                    cout << "erorr 1 case97" << endl;
                }

                break;
            
            case 119:               // вверх
            case 230:

                if (FieldGame[Head - ConstantTransition] == frame || FieldGame[Head - ConstantTransition] == TailSnake || FieldGame[Head - ConstantTransition] == BodySnake) {
                    Lose = true;
                }
                else if (FieldGame[Head - ConstantTransition] == Point) {
                    Head -= ConstantTransition;
                    lehgtnSnake.push_back(Head);
                }
                else if (FieldGame[Head - ConstantTransition] == ' ') {
                    FieldGame[*(lehgtnSnake.begin())] = ' ';
                    lehgtnSnake.erase(lehgtnSnake.begin());
                    Head -= ConstantTransition;
                    lehgtnSnake.push_back(Head);
                }
                else {
                    cout << "erorr 2 case119" << endl;
                }
                break;

            case 115:                       // вниз
            case 235:

                if (FieldGame[Head + ConstantTransition] == frame || FieldGame[Head + ConstantTransition] == TailSnake || FieldGame[Head + ConstantTransition] == BodySnake) {
                    Lose = true;
                }
                if (FieldGame[Head + ConstantTransition] == Point) {
                    Head += ConstantTransition;
                    lehgtnSnake.push_back(Head);
                }
                else if (FieldGame[Head + ConstantTransition] == ' ') {
                    FieldGame[*(lehgtnSnake.begin())] = ' ';
                    lehgtnSnake.erase(lehgtnSnake.begin());
                    Head += ConstantTransition;
                    lehgtnSnake.push_back(Head);
                }
                else {
                    cout << "erorr 3 case115" << endl;
                }
                break;
            
            case 100:                   // вправо
            case 162:

                if (FieldGame[Head + 1] == frame || FieldGame[Head + 1] == TailSnake || FieldGame[Head + 1] == BodySnake ) {
                    Lose = true;
                }
                else if (FieldGame[Head + 2] == Point) {
                    Head += 2;
                    lehgtnSnake.push_back(Head);
                }
                else if (FieldGame[Head + 2] == ' ') {
                    FieldGame[*(lehgtnSnake.begin())] = ' ';
                    lehgtnSnake.erase(lehgtnSnake.begin());
                    Head += 2;
                    lehgtnSnake.push_back(Head);
                }
                else {
                    cout << "erorr 4 case100" << endl;
                }
                break;

            default:
                cout << "erorr 00000 case 0000" << endl;
            }

            for (int i = 0; i < lehgtnSnake.size(); i++) {
                if (i == 0) {
                    FieldGame[*(lehgtnSnake.begin())] = TailSnake;
                }
                else if (i == lehgtnSnake.size()-1) {
                    FieldGame[lehgtnSnake[i]] = HeadShanke;
                }
                else {
                    FieldGame[lehgtnSnake[i]] = BodySnake;
                }
            }

            COORD pos = { 0, 0 };
            HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleCursorPosition(output, pos);

            cout << FieldGame << endl;
            cout << "набрано очков: \t\t" << lehgtnSnake.size() - 2;
        }
    }

    cout << "You've lost" << endl;
}
