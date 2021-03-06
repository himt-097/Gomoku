#include <StateManager.hpp>
#include <Helpers/Utils.hpp>
#include <EngineGlobals.hpp>
#include <GameStateMainMenu.hpp>
#include <Input.hpp>
#include <GameState.hpp>
#include <LoadGame.hpp>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

int main() {
		EngineGlobals::init();
		// Phần khởi tạo

		srand(static_cast<unsigned int>(time(0))); // random seed

		// khởi tạo thư viện ncurses
		initscr();
		cbreak();
		curs_set(0);
		noecho();
		nodelay(stdscr, TRUE);
		keypad(stdscr, TRUE);
		ESCDELAY = 25;
		refresh();

		Colors::init();

		// Quản lí trạng thái của game bằng StateManager
		StateManager states;

		// trạng thái đầu tiên của game là màn hình menu
		GameState* initialState = new GameStateMainMenu();

		states.currentState = initialState;
		states.currentState->load();


		// vòng lặp : GetInput --> Update --> render --> GetInput
		// vòng lặp chính của game
		// Dùng try catch exception để đổi trạng thái, thoát game.
		while (true) {
			try {
				// luôn luôn nhận input từ user
				Input::update();

				// "update" trạng thái hiện tại của game
				states.currentState->update();

				// "render" trạng thái hiện tại của game
				if (states.currentState) states.currentState->draw();

				usleep((useconds_t)100 * 100);

			}
			catch (ChangeException& e){
				states.currentState->unload();
				delete(states.currentState);
				states.currentState = NULL;

				states.currentState = e.newState;
				states.currentState->load();

			}
			catch (QuitException& e) {
				states.currentState->unload();
				delete(states.currentState);
				states.currentState = NULL;

				break;
			}
		}

		// Thoát game
		erase();
		refresh();
		endwin();
		system("xdotool key Alt+t p 1");
		return 0;
}
