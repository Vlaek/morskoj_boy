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
						if (Mouse::isButtonPressed(Mouse::Left)) { window.close(); break; }
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



int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));

	RenderWindow window(VideoMode::getDesktopMode(), "Test!");

	showMenu(window);

	

			    int map[N][N] = { 0 }; //�������
				int map2[N][N] = { 0 }; //����
	
				int ships1[10] = { 0, 4, 3, 3, 2, 2, 2, 1, 1, 1 }; //�����
				int ships2[10] = { 0, 4, 3, 3, 2, 2, 2, 1, 1, 1 };
	
				int mask[N][N] = { 0 }; //chelovek
				int mask2[N][N] = { 0 }; //peka
	
				for (int i = 1; i <= 10; i++)
				{
					set_rand_ships(map, ships1[i], i);
				}
				for (int i = 1; i <= 10; i++)
				{
					set_rand_ships(map2, ships2[i], i);
				}   ///////////////////////////////////////////////////////
	
				int x = 0, y = 0;
	
				int firstHitX = 0;
				int firstHitY = 0;
	
				int mode = 0;
	
				int xBot = 0;
				int yBot = 0;
	
				int dir = 0;
	
				vector <int> dirs;
	
				dirs.push_back(3);
				dirs.push_back(2);
				dirs.push_back(1);
				dirs.push_back(0);
	
				bool winPlayer = 0;
				bool winBot = 0;
				bool step = 1;      // ��� ����� ������ (1 - �����, 2 - ���)
		///////////////////////////////////////////////////////////////////////
	 
				while (winPlayer == false && winBot == false)
				{
					int resultShot = 0;
					do
					{
						drawing(map, mask, 0);
						cout << endl;
						drawing(map2, mask2, 1);
	
						if (step == 1)
						{
							cout << endl << "������� ���������� ���� (�������): ";
	
							cin >> x;
							cin >> y;
	
							resultShot = shot(x, y, map2, mask2, ships2);
	
							if (resultShot == 1)
							{
								cout << "\n�����\n\n";
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
								cout << "\n����\n\n" << endl;
							}
							else
							{
								cout << "\n������\n\n" << endl;
							}
						}
						else
						{
							cout << endl << "��� ����������\n";
							Sleep(500);
	
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
	
									cout << "\n�����\n\n";
								}
								else if (resultShot == 2)
								{
									bool died = 1;
									for (int i = 1; i < 10; i++)
									{
										if (ships1[i] != 0)
										{
											died = 0;
											break;
										}
									}
									if (died == 1)
									{
										winBot = 1;
										break;
									}
									cout << "\n����\n\n" << endl;
								}
								else
								{
									cout << "\n������\n\n" << endl;
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
									cout << "\n�����\n\n";
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
											break;
										}
									}
									if (died == 1)
									{
										winBot = 1;
										break;
									}
									cout << "\n����\n\n" << endl;
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
	
									cout << "\n������\n\n" << endl;
								}
							}
	
						}
						Sleep(500);
						system("cls");
					} while (resultShot != 0);
	
					step = !step;
				}
				if (winPlayer)
				{
					cout << "������" << endl;
				}
				else if (winBot)
				{
					cout << "���������" << endl;
				}
				_getch();
				system("cls");
			
			system("pause");
    return 0;
}