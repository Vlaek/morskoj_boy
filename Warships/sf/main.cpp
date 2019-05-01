#include "SFML/include/SFML/Graphics.hpp"
#include "SFML/include/SFML/Audio.hpp"
#include <iostream>
#include <locale.h>
#include <conio.h>
#include <time.h>
#include <vector>
#include <windows.h>
#include <cstring>

using namespace sf;
using namespace std;

const int N = 10;
int Ships_id = 1;
int Ships[16] = { 0 };  //���������� ���������� + 1/

void set_rand_ships(int map[N][N], int size_ship, int ship_id)
{
	int x, y, count = 0, dir = 0, tact = 0;
	while (count < 1)
	{
		tact++;

		if (tact > 1000)
		{
			break;
		}

		x = rand() % N; //��������� ������� 
		y = rand() % N;

		int temp_x = x;
		int temp_y = y;

		dir = rand() % 4; //��������� �����������

		bool possible = 1; //�������� �����������

		for (int i = 0; i < size_ship; i++)
		{
			if (x < 0 || y < 0 || x >= N || y >= N)
			{
				possible = 0;
				break;
			}

			if (map[x][y] >= 1 ||
				map[x + 1][y] >= 1 ||
				map[x - 1][y] >= 1 ||
				map[x + 1][y + 1] >= 1 ||
				map[x + 1][y - 1] >= 1 ||
				map[x - 1][y + 1] >= 1 ||
				map[x - 1][y - 1] >= 1 ||
				map[x][y + 1] >= 1 ||
				map[x][y - 1] >= 1)
			{
				possible = 0;
				break;
			}

			switch (dir)
			{
			case 0:
				x++;
				break;
			case 1:
				y++;
				break;
			case 2:
				x--;
				break;
			case 3:
				y--;
				break;
			}
		}

		if (possible == 1)
		{
			x = temp_x;
			y = temp_y;

			for (int i = 0; i < size_ship; i++)
			{
				map[x][y] = ship_id;

				switch (dir)
				{
				case 0:
					x++;
					break;
				case 1:
					y++;
					break;
				case 2:
					x--;
					break;
				case 3:
					y--;
					break;
				}
			}
			count++;
		}
	}
}

void drawing(int map[N][N], int mask[N][N], bool useMask) {
	cout << ' ';
	for (int i = 0; i < N; i++) // ����������
	{
		cout << i;
	}
	cout << endl;
	for (int i = 0; i < N; i++)
	{
		cout << i;
		for (int j = 0; j < N; j++)
		{
			if (mask[j][i] == 1 || useMask == 0)
			{
				if (map[j][i] == 0)
				{
					cout << '-';
				}
				else if (map[j][i] == -1)
				{
					cout << 'X';
				}
				else if (map[j][i] == -2)
				{
					cout << 'o';
				}
				else
				{
					cout << map[j][i];
				}
			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}
}

int shot(int x, int y, int map[N][N], int mask[N][N], int ships[11])
{
	int result = 0;

	if (map[x][y] == -1 || map[x][y] == -2)
	{
		result = 3; //bot strelyal yje
	}
	else if (map[x][y] >= 1)
	{
		ships[map[x][y]]--;
		if (ships[map[x][y]] <= 0)
		{
			result = 2; //ybit
		}
		else
		{
			result = 1; //promah
		}
		map[x][y] = -1;
	}
	else
	{
		map[x][y] = -2;
	}
	mask[x][y] = 1;

	return result;
}

void showMenu(RenderWindow & window) {
	Texture NewGame, Rules, Exit, menuBackground, menuBack, PageOfRules, Mouse;

	NewGame.loadFromFile("images/NewGame.png");
	Rules.loadFromFile("images/Rules.png");
	Exit.loadFromFile("images/Exit.png");
	menuBackground.loadFromFile("images/background.png");
	menuBack.loadFromFile("images/back.png");
	Rules.loadFromFile("images/rules.png");
	PageOfRules.loadFromFile("images/PageOfRules.png");
	Mouse.loadFromFile("images/Mouse.png");

	Sprite menu1(NewGame), menu2(Rules), menu3(Exit), back(menuBack), background(menuBackground), rules(PageOfRules), mouse(Mouse);

	int menuNum = 0;

	mouse.setOrigin(Mouse.getSize().x / 2, Mouse.getSize().y / 2);
	menu1.setPosition(5, 310);
	menu2.setPosition(5, 400);
	menu3.setPosition(5, 490);
	background.setPosition(0, 0);
	back.setPosition(80, 700);
	rules.setPosition(320, 70);

	window.setMouseCursorVisible(false);

	while (true)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);

		menuNum = 0;

		if (IntRect(5, 310, 360, 63).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Yellow); menuNum = 1; }
		if (IntRect(5, 400, 400, 63).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Yellow); menuNum = 2; }
		if (IntRect(5, 490, 240, 63).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Yellow); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) 
			{ 
				break;
			} 
			if (menuNum == 2)
			{
				while (true)
				{
					back.setColor(Color::White);
					if (IntRect(80, 675, 160, 80).contains(Mouse::getPosition(window))) 
					{
						back.setColor(Color::Yellow);
						if (Mouse::isButtonPressed(Mouse::Left)) break;
					}
					if (Keyboard::isKeyPressed(Keyboard::Escape)) break;

					window.draw(background);
					window.draw(back);
					window.draw(rules);
					mouse.setPosition(Mouse::getPosition().x, Mouse::getPosition().y - 3);
					window.draw(mouse);
					window.display();
				}
			}
			if (menuNum == 3) 
			{
				exit(0);
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) { exit(0); }

		window.draw(background);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.draw(mouse);
		mouse.setPosition(Mouse::getPosition().x, Mouse::getPosition().y);
		window.draw(mouse);
		window.display();
	}
}

void showGameScene(RenderWindow &window) {

	int map[10][10] = { 0 }; //�������
	int map2[10][10] = { 0 }; //����

	int ships1[11] = { 0, 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 }; //�����
	int ships2[11] = { 0, 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };

	int mask[N][N] = { 0 }; //chelovek
	int mask2[N][N] = { 0 }; //peka

	Music music;
	music.openFromFile("sounds/musicGame.ogg");
	music.play();
	music.setLoop(true);
	music.setVolume(50);

	RectangleShape playerfield(Vector2f(444,444)), enemyfield(Vector2f(444,444));
	RectangleShape playerShip[10][10], enemyShip[10][10];
	Texture PlayerFlot, BotFlot, menuBackground, Mouse, menuBack, PlusSound, MinusSound, Lose;

	PlayerFlot.loadFromFile("images/PlayerFlot.png");
	BotFlot.loadFromFile("images/BotFlot.png");
	menuBackground.loadFromFile("images/background.png");
	Mouse.loadFromFile("images/Mouse.png");
	menuBack.loadFromFile("images/back.png");
	PlusSound.loadFromFile("images/PlusSound.png");
	MinusSound.loadFromFile("images/MinusSound.png");
	Lose.loadFromFile("Lose.jpg");

	Sprite PF(PlayerFlot), BF(BotFlot), background(menuBackground), mouse(Mouse), back(menuBack), plus(PlusSound), minus(MinusSound), lose(Lose);

	PF.setPosition(555, 135);
	BF.setPosition(1060, 135);
	background.setPosition(0, 0);
	back.setPosition(75, 700);
	plus.setPosition(75, 430);
	minus.setPosition(75, 500);
	lose.setPosition(0, 0);


	window.draw(background);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			playerShip[i][j].setSize(Vector2f(40, 40));
			playerShip[i][j].setPosition(519 + i * 44, 204 + j * 44);
			enemyShip[i][j].setSize(Vector2f(40, 40));
			enemyShip[i][j].setPosition(1044 + i * 44, 204 + j * 44);
		}
	}

	playerfield.setPosition(515, 200); enemyfield.setPosition(1040, 200);
	playerfield.setFillColor(Color::Black); enemyfield.setFillColor(Color::Black);

	for(int i = 1; i <= 10; i++)
	{
		set_rand_ships(map, ships1[i], i);
	}

	for (int i = 1; i <= 10; i++)
	{
		set_rand_ships(map2, ships2[i], i);
	}

	Clock clock;
	float timerMicroseconds = 0, clickTime = 0;

	int x = 0, y = 0; //////////////////////////////////////////////

	int firstHitX = 0;
	int firstHitY = 0;

	int mode = 0;

	int xBot = 0;
	int yBot = 0;

	int dir = 0;
	bool draw = 0; // �������� ��������� �������

	vector <int> dirs;

	dirs.push_back(3);
	dirs.push_back(2);
	dirs.push_back(1);
	dirs.push_back(0);

	bool winPlayer = 0;
	bool winBot = 0;
	
	bool step = 1; // ��� ����� ������ (1 - �����, 0 - ���)

	while (window.isOpen()) 
	{
		float cputime = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		timerMicroseconds += cputime/1000;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (draw == 0) {              /////////////////////// ��������� ��������� ��������
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (map[i][j]) playerShip[i][j].setFillColor(Color(73, 85, 97));
					else playerShip[i][j].setFillColor(Color::White);
					//if (map2[i][j]) enemyShip[i][j].setFillColor(Color(73, 85, 97));    //�����
					//else enemyShip[i][j].setFillColor(Color::White);
				}
			}
			draw = 1;
		}

		back.setColor(Color::White);

		if (IntRect(75, 660, 160, 80).contains(Mouse::getPosition(window)))
		{
			back.setColor(Color::Yellow);
			if (Mouse::isButtonPressed(Mouse::Left) ) showMenu(window);
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) showMenu(window);

		plus.setColor(Color::White);
		minus.setColor(Color::White);
		
		if (IntRect(75, 410, 60, 60).contains(Mouse::getPosition(window)))
		{
			plus.setColor(Color::Yellow);
			if (Mouse::isButtonPressed(Mouse::Left) && music.getVolume() <= 90 && timerMicroseconds > clickTime + 100) {
				clickTime = timerMicroseconds;
				music.setVolume(music.getVolume() + 10);
			}
			
		}

		if (IntRect(75, 480, 60, 60).contains(Mouse::getPosition(window)))
		{
			minus.setColor(Color::Yellow);
			if (Mouse::isButtonPressed(Mouse::Left) && music.getVolume() >= 0 && timerMicroseconds > clickTime + 100) {
				clickTime = timerMicroseconds;
				music.setVolume(music.getVolume() - 10);
			}
		}

		window.clear();
		window.draw(background);
		window.draw(playerfield);
		window.draw(PF);
		window.draw(enemyfield);
		window.draw(BF);
		window.draw(back);
		window.draw(plus);
		window.draw(minus);

		for (int i = 0; i < 10; i++) 
		{
			for (int j = 0; j < 10; j++) 
			{
				//if (playerShip[i][j].getGlobalBounds().contains(Mouse::getPosition().x, Mouse::getPosition().y)) playerShip[i][j].setFillColor(Color::Yellow);
				//if (enemyShip[i][j].getGlobalBounds().contains(Mouse::getPosition().x, Mouse::getPosition().y)) enemyShip[i][j].setFillColor(Color::Yellow);
				window.draw(playerShip[i][j]);
				window.draw(enemyShip[i][j]);
			}
		}

	mouse.setPosition(Mouse::getPosition().x, Mouse::getPosition().y - 3);
	window.draw(mouse);
	window.display();

	//while (winPlayer == false && winBot == false) 
//	{
	int resultShot = 0;
	/*	do
	{*/

	if (step == 1)
	{
		cout << endl << "������� ���������� ���� (�������): ";

		cin >> x;
		cin >> y;

		resultShot = shot(x, y, map2, mask2, ships2);

		if (resultShot == 1)
		{
			enemyShip[x][y].setFillColor(Color(255, 255, 0)); //�����
			window.draw(enemyShip[x][y]);
		}
		else if (resultShot == 2)
		{
			bool died = 1;
			for (int i = 1; i < 10; i++)
			{
				if (ships2[i] != 0)
				{
					died = 0;
					break;
				}
			}
			if (died == 1)
			{
				winPlayer = 1;
				break;
			}
			enemyShip[x][y].setFillColor(Color(255, 0, 0)); //����
			window.draw(enemyShip[x][y]);
		}
		else
		{
			enemyShip[x][y].setFillColor(Color(0, 255, 0)); //����
			window.draw(enemyShip[x][y]);
		}
	}
	else
	{
		cout << endl << "��� ����������\n";


		if (mode == 0)
		{
			do //�������� ������� �� ��� � ��� �����
			{
				xBot = rand() % N;
				yBot = rand() % N;

				resultShot = shot(xBot, yBot, map, mask, ships1);
			} while (resultShot == 3);

			if (resultShot == 1)
			{
				mode = 1;

				firstHitX = xBot;
				firstHitY = yBot;

				if (!dirs.empty()) //��������� �� ������ �� ������
				{
					dir = dirs[dirs.size() - 1]; //������ � ���������� ��������
					dirs.pop_back();
				}

				playerShip[xBot][yBot].setFillColor(Color(255, 255, 0)); //�����
				window.draw(playerShip[xBot][yBot]);
			}
			else if (resultShot == 2)
			{
				bool died = 1;
				for (int i = 1; i < 10; i++)
				{
					if (ships1[i] != 0)
					{
						died = 0;
						/*break;*/
						window.draw(lose);
					}
				}
				if (died == 1)
				{
					winBot = 1;
					/*break;*/
					window.draw(lose);
				}
				playerShip[xBot][yBot].setFillColor(Color(255, 0, 0));  //����
				window.draw(playerShip[xBot][yBot]);
			}
			else
			{
				playerShip[xBot][yBot].setFillColor(Color(0, 255, 0));
				window.draw(playerShip[xBot][yBot]);
			}
		}
		else if (mode == 1)
		{
			bool changeDir = 0;

			if (dir == 0) //�����
			{
				if (xBot > 0)
					xBot--;
				else
				{
					changeDir = 1;
				}
			}
			else if (dir == 1) //������
			{
				if (xBot < N - 1)
					xBot++;
				else
				{
					changeDir = 1;
				}

			}
			else if (dir == 2) //�����
			{
				if (yBot > 0)
					yBot--;
				else
				{
					changeDir = 1;
				}
			}
			else if (dir == 3) //����
			{
				if (yBot < N - 1)
					yBot++;
				else
				{
					changeDir = 1;
				}
			}

			if (changeDir == 1)
			{
				if (!dirs.empty())
				{
					dir = dirs[dirs.size() - 1];
					dirs.pop_back();
				}
				xBot = firstHitX; //���������� �������, ���� ������� 
				yBot = firstHitY;

				continue;
			}

			resultShot = shot(xBot, yBot, map, mask, ships1);

			if (resultShot == 1)
			{
				playerShip[xBot][yBot].setFillColor(Color(255, 255, 0)); //�����
				window.draw(playerShip[xBot][yBot]);
			}
			else if (resultShot == 2)
			{
				mode = 0;

				dirs.clear();

				dirs.push_back(3);
				dirs.push_back(2);
				dirs.push_back(1);
				dirs.push_back(0);

				bool died = 1;
				for (int i = 1; i < 10; i++)
				{
					if (ships1[i] != 0)
					{
						died = 0;
						/*break;*/
						window.draw(lose);
					}
				}
				if (died == 1)
				{
					winBot = 1;
					/*break;*/
					window.draw(lose);
				}
				playerShip[xBot][yBot].setFillColor(Color(255, 0, 0)); //����
				window.draw(playerShip[xBot][yBot]);
			}
			else
			{
				if (!dirs.empty())
				{
					dir = dirs[dirs.size() - 1];
					dirs.pop_back();
				}

				xBot = firstHitX;
				yBot = firstHitY;

				playerShip[xBot][yBot].setFillColor(Color(0, 255, 0)); //����
				window.draw(playerShip[xBot][yBot]);
			}
		}
	}
								
	/*} while (resultShot != 0);*/
			
	step = !step;
	//}
	if (winPlayer)
	{
		window.draw(lose);
	}
	else if (winBot)
	{
		window.draw(lose);
	}


	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));

	RenderWindow window(VideoMode::getDesktopMode(), "Test!");

	showMenu(window);

	showGameScene(window);
	//
	//			int map[N][N] = { 0 }; //�������
	//			int map2[N][N] = { 0 }; //����
	//
	//			int ships1[10] = { 0, 4, 3, 3, 2, 2, 2, 1, 1, 1 }; //�����
	//			int ships2[10] = { 0, 4, 3, 3, 2, 2, 2, 1, 1, 1 };
	//
	//			int mask[N][N] = { 0 }; //chelovek
	//			int mask2[N][N] = { 0 }; //peka
	//
	//			for (int i = 1; i <= 10; i++)
	//			{
	//				set_rand_ships(map, ships1[i], i);
	//			}
	//			for (int i = 1; i <= 10; i++)
	//			{
	//				set_rand_ships(map2, ships2[i], i);
	//			}   ///////////////////////////////////////////////////////
	//
	//			int x = 0, y = 0;
	//
	//			int firstHitX = 0;
	//			int firstHitY = 0;
	//
	//			int mode = 0;
	//
	//			int xBot = 0;
	//			int yBot = 0;
	//
	//			int dir = 0;
	//
	//			vector <int> dirs;
	//
	//			dirs.push_back(3);
	//			dirs.push_back(2);
	//			dirs.push_back(1);
	//			dirs.push_back(0);
	//
	//			bool winPlayer = 0;
	//			bool winBot = 0;
	//			bool step = 1;      // ��� ����� ������ (1 - �����, 2 - ���)
	//	///////////////////////////////////////////////////////////////////////
	// 
	//			while (winPlayer == false && winBot == false)
	//			{
	//				int resultShot = 0;
	//				do
	//				{
	//					drawing(map, mask, 0);
	//					cout << endl;
	//					drawing(map2, mask2, 1);
	//
	//					if (step == 1)
	//					{
	//						cout << endl << "������� ���������� ���� (�������): ";
	//
	//						cin >> x;
	//						cin >> y;
	//
	//						resultShot = shot(x, y, map2, mask2, ships2);
	//
	//						if (resultShot == 1)
	//						{
	//							cout << "\n�����\n\n";
	//						}
	//						else if (resultShot == 2)
	//						{
	//							bool died = 1;
	//							for (int i = 1; i < 10; i++)
	//							{
	//								if (ships2[i] != 0)
	//								{
	//									died = 0;
	//									break;
	//								}
	//							}
	//							if (died == 1)
	//							{
	//								winPlayer = 1;
	//								break;
	//							}
	//							cout << "\n����\n\n" << endl;
	//						}
	//						else
	//						{
	//							cout << "\n������\n\n" << endl;
	//						}
	//					}
	//					else
	//					{
	//						cout << endl << "��� ����������\n";
	//						Sleep(500);
	//
	//						if (mode == 0)
	//						{
	//							do //�������� ������� �� ��� � ��� �����
	//							{
	//								xBot = rand() % N;
	//								yBot = rand() % N;
	//
	//								resultShot = shot(xBot, yBot, map, mask, ships1);
	//							} while (resultShot == 3);
	//
	//							if (resultShot == 1)
	//							{
	//								mode = 1;
	//
	//								firstHitX = xBot;
	//								firstHitY = yBot;
	//
	//								if (!dirs.empty()) //��������� �� ������ �� ������
	//								{
	//									dir = dirs[dirs.size() - 1]; //������ � ���������� ��������
	//									dirs.pop_back();
	//								}
	//
	//								cout << "\n�����\n\n";
	//							}
	//							else if (resultShot == 2)
	//							{
	//								bool died = 1;
	//								for (int i = 1; i < 10; i++)
	//								{
	//									if (ships1[i] != 0)
	//									{
	//										died = 0;
	//										break;
	//									}
	//								}
	//								if (died == 1)
	//								{
	//									winBot = 1;
	//									break;
	//								}
	//								cout << "\n����\n\n" << endl;
	//							}
	//							else
	//							{
	//								cout << "\n������\n\n" << endl;
	//							}
	//						}
	//						else if (mode == 1)
	//						{
	//							bool changeDir = 0;
	//
	//							if (dir == 0) //�����
	//							{
	//								if (xBot > 0)
	//									xBot--;
	//								else
	//								{
	//									changeDir = 1;
	//								}
	//							}
	//							else if (dir == 1) //������
	//							{
	//								if (xBot < N - 1)
	//									xBot++;
	//								else
	//								{
	//									changeDir = 1;
	//								}
	//
	//							}
	//							else if (dir == 2) //�����
	//							{
	//								if (yBot > 0)
	//									yBot--;
	//								else
	//								{
	//									changeDir = 1;
	//								}
	//							}
	//							else if (dir == 3) //����
	//							{
	//								if (yBot < N - 1)
	//									yBot++;
	//								else
	//								{
	//									changeDir = 1;
	//								}
	//							}
	//
	//							if (changeDir == 1)
	//							{
	//								if (!dirs.empty())
	//								{
	//									dir = dirs[dirs.size() - 1];
	//									dirs.pop_back();
	//								}
	//								xBot = firstHitX; //���������� �������, ���� ������� 
	//								yBot = firstHitY;
	//
	//								continue;
	//							}
	//
	//							resultShot = shot(xBot, yBot, map, mask, ships1);
	//
	//							if (resultShot == 1)
	//							{
	//								cout << "\n�����\n\n";
	//							}
	//							else if (resultShot == 2)
	//							{
	//								mode = 0;
	//
	//								dirs.clear();
	//
	//								dirs.push_back(3);
	//								dirs.push_back(2);
	//								dirs.push_back(1);
	//								dirs.push_back(0);
	//
	//								bool died = 1;
	//								for (int i = 1; i < 10; i++)
	//								{
	//									if (ships1[i] != 0)
	//									{
	//										died = 0;
	//										break;
	//									}
	//								}
	//								if (died == 1)
	//								{
	//									winBot = 1;
	//									break;
	//								}
	//								cout << "\n����\n\n" << endl;
	//							}
	//							else
	//							{
	//								if (!dirs.empty())
	//								{
	//									dir = dirs[dirs.size() - 1];
	//									dirs.pop_back();
	//								}
	//
	//								xBot = firstHitX;
	//								yBot = firstHitY;
	//
	//								cout << "\n������\n\n" << endl;
	//							}
	//						}
	//
	//					}
	//					Sleep(500);
	//					system("cls");
	//				} while (resultShot != 0);
	//
	//				step = !step;
	//			}
	//			if (winPlayer)
	//			{
	//				cout << "������" << endl;
	//			}
	//			else if (winBot)
	//			{
	//				cout << "���������" << endl;
	//			}
	//			_getch();
	//			system("cls");
	//		}
	//		system("pause");
    return 0;
}