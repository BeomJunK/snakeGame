#include "GamePch.h"
#include "Snake.h"
#include "GameManager.h"


void ClearScreen();
void Initalize();
void StartUI();
void InGame();
void EndUI();



int main()
{
    Initalize();

    GameManager& manager = GameManager::getInstance();

    while (true)
    {
        switch (manager.GetCurrentGameState())
        {
            case GameState::Ready:
                StartUI();
                break;
            case GameState::Play:
                InGame();
                break;
            case GameState::End:
                EndUI();
                break;
        }
    }
}
void ClearScreen()
{
    COORD cursorPosition;
    cursorPosition.X = cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void Initalize()
{
    DWORD consolModePrev;
    HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(handle, &consolModePrev);
    SetConsoleMode(handle, consolModePrev & ~ENABLE_QUICK_EDIT_MODE);
}

void StartUI()
{
    GameManager& mgr = GameManager::getInstance();

    gInput->ClearBind();
    gInput->BindAction(KEY_TYPE::ENTER, [&mgr]() { mgr.SetCurrentGameState(GameState::Play); });

    while (true)
    {
        ClearScreen();

        cout << "Let's Play Snake Game!" << endl;

        cout << endl;
        cout << endl;
        cout << "엔터를 눌러 시작하기" << endl;

        gInput->Update();

        if ( mgr.GetCurrentGameState()!= GameState::Ready)
            break;
    }
}
void InGame()
{
    int score = 0;
    GameManager& mgr = GameManager::getInstance();
    unique_ptr<Snake> snake = make_unique<Snake>();

    gInput->BindAction(KEY_TYPE::LEFT, [&snake]() {snake->ChangeDirection(Direction::LEFT); });
    gInput->BindAction(KEY_TYPE::RIGHT, [&snake]() {snake->ChangeDirection(Direction::RIGHT); });
    gInput->BindAction(KEY_TYPE::UP, [&snake]() {snake->ChangeDirection(Direction::UP); });
    gInput->BindAction(KEY_TYPE::DOWN, [&snake]() {snake->ChangeDirection(Direction::DOWN); });

    mgr.Reset();

    clock_t startTime = clock();
    clock_t elapsedTime;
    while (true)
    {
        ClearScreen();

        clock_t updateTime = clock();
        elapsedTime = updateTime - startTime;
        string str = format("Score : {0}", mgr.GetCurrentGameScore());
        wstring temp = wstring(str.begin(), str.end());
        SetConsoleTitle(temp.c_str());

        gInput->Update();
        snake->Update(elapsedTime);
        gMap->Draw();

        if (mgr.GetCurrentGameState() != GameState::Play)
            break;
    }
    system("cls");
}
void EndUI()
{
    GameManager& mgr = GameManager::getInstance();
    gInput->ClearBind();
    gInput->BindAction(KEY_TYPE::ENTER, [&mgr]() {mgr.SetCurrentGameState(GameState::Play); });

    while (true)
    {
        ClearScreen();

        cout << "Game Over!!!" << endl;

        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << "엔터를 눌러 다시 시작합니다." << endl;

        gInput->Update();

        if (mgr.GetCurrentGameState() != GameState::End)
            break;
    }
}