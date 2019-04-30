#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <SFML/Graphics.hpp>
#include <iostream>
#include <clocale>
#include <ctime>
#include <string>
#include <math.h>
#include <dos.h>
#include <windows.h>
#define field_size 10

sf::RenderWindow window(sf::VideoMode(1280, 720), "WarShips", sf::Style::Close);

class Field
{
public:
	int map[field_size][field_size];
	int mask[field_size][field_size];
	sf::Texture texture;
	sf::Sprite sprite;

	Field(int type)
	{
		texture.loadFromFile("images/background.png");
		sprite.setTexture(texture);
		if (type == 1)
		{
			sprite.setTextureRect(sf::IntRect(0, 0, 640, 720));
			sprite.setPosition(0, 0);
		}
		else if (type == 2) 
		{
			sprite.setTextureRect(sf::IntRect(640, 0, 640, 720));
			sprite.setPosition(640, 0);
		}

	}

	void restart()
	{
		//map[field_size][field_size] = { 0 };
		//mask[field_size][field_size] = { 0 };

		for (int i = 0; i < field_size; i++)
		{
			for (int j = 0; j < field_size; j++)
			{
				map[i][j] = 0;
				mask[i][j] = 0;
			}
		}
	}

	void rand_set_ship(int size_ship, int num_ships)
	{
		int x, y;  // координаты

		int dir = 0;  // направление генерации корабля

		int count_ship = 0;  // количество установленных кораблей

		int count_tact = 0;  // количество отработок цикла

		while (count_ship < num_ships)
		{
			count_tact++;

			if (count_tact > 500)   // защита от бесконечного цикла
			{
				break;
			}

			x = rand() % field_size;
			y = rand() % field_size;


			int temp1_x = x;
			int temp1_y = y;

			bool setting_is_possible = 1;

			dir = rand() % 4;

			for (int i = 0; i < size_ship; i++)
			{
				if (x < 0 || y < 0 || x >= field_size || y >= field_size) // проверка выхода за карту
				{
					setting_is_possible = 0;
					break;
				}

				if (map[x][y] == 1 ||             // проверка наличия корабля в радиусе 1 клетки
					map[x][y + 1] == 1 ||
					map[x][y - 1] == 1 ||
					map[x + 1][y] == 1 ||
					map[x + 1][y + 1] == 1 ||
					map[x + 1][y - 1] == 1 ||
					map[x - 1][y] == 1 ||
					map[x - 1][y + 1] == 1 ||
					map[x - 1][y - 1] == 1)
				{
					setting_is_possible = 0;
					break;
				}

				switch (dir)                             // направление проверки
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

			if (setting_is_possible)				// генерация кораблей
			{
				x = temp1_x;
				y = temp1_y;

				for (int i = 0; i < size_ship; i++)
				{
					map[x][y] = 1;

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
				count_ship++;
			}
		}
	}

	void Draw()
	{
		window.draw(sprite);
	}

	
};



int main()
{
	setlocale(0, "");
	srand(time(0));

	sf::Texture t_title1;
	t_title1.loadFromFile("images/title.png");
	sf::Sprite s_title1;
	s_title1.setTexture(t_title1); 
	
	sf::Texture t_title2;
	t_title2.loadFromFile("images/title.jpg");
	sf::Sprite s_title2;
	s_title2.setTexture(t_title2);
	
	sf::Texture t_marks;
	t_marks.loadFromFile("images/marks.png");
	sf::Sprite s_marks;
	s_marks.setTexture(t_marks);

	sf::Texture t_win1;
	t_win1.loadFromFile("images/WinPlayerOne.jpg");
	sf::Sprite s_win1;
	s_win1.setTexture(t_win1);

	sf::Texture t_win2;
	t_win2.loadFromFile("images/WinPlayerTwo.jpg");
	sf::Sprite s_win2;
	s_win2.setTexture(t_win2);

	Field field1(1);
	Field field2(2);

	sf::FloatRect StartButton(880, 335, 250, 70);
	sf::FloatRect RestartButton(920, 550, 210, 70);
	sf::FloatRect MainMenuButton(925, 640, 210, 65);


	


	int count1;
	int count2;

	int x, y, temp1_x, temp1_y, temp2_x, temp2_y;

	bool Start ;
	bool change;
	bool shipIsAlive;


	
	Start = false;



	count1 = 20;
	count2 = 20;

	field1.restart();
	field2.restart();

	field1.rand_set_ship(4, 1);
	field1.rand_set_ship(3, 2);
	field1.rand_set_ship(2, 3);
	field1.rand_set_ship(1, 4);

	field2.rand_set_ship(4, 1);
	field2.rand_set_ship(3, 2);
	field2.rand_set_ship(2, 3);
	field2.rand_set_ship(1, 4);

	//field1.map_show();
	//field2.map_show();
	
	
	change = false;

	x = 0;
	y = 0;
	

	while (window.isOpen())
	{
	

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}
		}
		
	              //Рестарт игры

		while (window.isOpen() && (!Start))
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
					break;
				}

				if (StartButton.contains(sf::Vector2f(sf::Mouse::getPosition(window))))
				{
					window.draw(s_title2);
					
					if (event.type == sf::Event::MouseButtonReleased)
					{

						if (event.mouseButton.button == sf::Mouse::Left)
						{
							Start = true;
						}
					}
				}
				else
				{
					window.draw(s_title1);
				}
				window.display();
			}
		}
			

		while ((count1) && (count2) && (window.isOpen()))
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

				if (event.type == sf::Event::MouseButtonPressed)
				{

					if (event.mouseButton.button == sf::Mouse::Left)
					{
						temp1_x = sf::Mouse::getPosition(window).x;
						temp1_y = sf::Mouse::getPosition(window).y;
					}
				}
					
			}

			window.clear(sf::Color::White);
			field1.Draw();
			field2.Draw();

			for (int i = 0; i <= 9; i++)
			{
				for (int j = 0; j <= 9; j++)
				{
					x = 0; y = 0;

					if (field1.mask[i][j] == 1)
					{
						if (field1.map[i][j] == 0)
						{
							s_marks.setTextureRect(sf::IntRect(0, 0, 50, 54));
						}
						if ((field1.map[i][j] == 1) || (field1.map[i][j] == 2))
						{
							s_marks.setTextureRect(sf::IntRect(50, 0, 50, 54));
						}
						if (field1.map[i][j] == 3)
						{
							s_marks.setTextureRect(sf::IntRect(100, 0, 50, 54));
							x = 1; y = 0;
						}

						s_marks.setPosition(((i * 50) + 92 - x), ((j * 54) + 97 - y));
						window.draw(s_marks);
					}
				}
			}

			for (int i = 0; i <= 9; i++)
			{
				for (int j = 0; j <= 9; j++)
				{
					x = 0; y = 0;

					if (field2.mask[i][j] == 1)
					{
						if (field2.map[i][j] == 0)
						{
							s_marks.setTextureRect(sf::IntRect(0, 0, 50, 54));
						}
						if ((field2.map[i][j] == 1) || (field2.map[i][j] == 2))
						{
							s_marks.setTextureRect(sf::IntRect(50, 0, 50, 54));
						}
						if (field2.map[i][j] == 3)
						{
							s_marks.setTextureRect(sf::IntRect(100, 0, 50, 54));
							x = -1; y = 0;
						}

						s_marks.setPosition(((i * 50) + 738 - x), ((j * 54) + 98 - y));
						window.draw(s_marks);
					}
				}
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{

				if (event.mouseButton.button == sf::Mouse::Left)
				{
					temp1_x = sf::Mouse::getPosition(window).x;
					temp1_y = sf::Mouse::getPosition(window).y;

					//system("cls");                       //
					//field1.map_show();                   //  Упрощение отладки
					//field2.map_show();                   //

					if (change)
					{
						if ((temp1_x < 592) && (temp1_y < 637) && (temp1_x > 92) && (temp1_y > 97))  // Атака на первое поле
						{
							x = (temp1_x - 92) / 50;
							y = (temp1_y - 97) / 54;
							if (field1.mask[x][y] == 0)
							{
								field1.mask[x][y] = 1;
								if (field1.map[x][y] == 1)
								{
									field1.map[x][y] = 2;
									count1--;
									shipIsAlive = false;
									for (int j = 0; j < 4; j++)
									{
										temp2_x = x;
										temp2_y = y;
										for (int i = 0; i < 3; i++) //_________________________
										{
											switch (j)                             // направление проверки
											{
											case 0:
												temp2_x++;
												break;
											case 1:
												temp2_y++;
												break;
											case 2:
												temp2_x--;
												break;
											case 3:
												temp2_y--;
												break;
											}

											if ((temp2_x > -1) && (temp2_y > -1) && (temp2_x < field_size) && (temp2_y < field_size))
											{
												if (field1.map[temp2_x][temp2_y] == 1)
												{
													shipIsAlive = true;
													break;
												}
												if (field1.map[temp2_x][temp2_y] == 0)
												{
													break;
												}
											}
										}
									}

									if (!shipIsAlive)
									{
										field1.map[x][y] = 2;
										for (int j = 0; j < 4; j++)
										{
											temp2_x = x;
											temp2_y = y;
											for (int i = 0; i < 4; i++) //_________________________
											{
												if (field1.map[temp2_x][temp2_y] == 2)
												{
													field1.map[temp2_x][temp2_y] = 3;
													for (int ik = -1; ik < 2; ik++)
													{
														for (int jk = -1; jk < 2; jk++)
														{
															if (field1.map[temp2_x + ik][temp2_y + jk] == 0)
															{
																if ((temp2_x + ik > -1) && (temp2_y + jk > -1) && (temp2_x + ik < field_size) && (temp2_y + jk < field_size))
																{
																	field1.mask[temp2_x + ik][temp2_y + jk] = 1;
																}
															}
														}
													}
												}
												if (field1.map[temp2_x][temp2_y] == 0)
												{
													break;
												}

												switch (j)                             // направление проверки
												{
												case 0:
													temp2_x++;
													break;
												case 1:
													temp2_y++;
													break;
												case 2:
													temp2_x--;
													break;
												case 3:
													temp2_y--;
													break;
												}

											}
										}
									}
								}



								if (field1.map[x][y] == 0)
								{
									change = (!change);
								}
							}
						}
					}
					else
					{
						if ((temp1_x < 1238) && (temp1_y < 637) && (temp1_x > 740) && (temp1_y > 97))  // Атака на второе поле
						{
							x = (temp1_x - 740) / 50;
							y = (temp1_y - 100) / 54;
							if (field2.mask[x][y] == 0)
							{
								field2.mask[x][y] = 1;
								if (field2.map[x][y] == 1)
								{
									field2.map[x][y] = 2;
									count2--;

									shipIsAlive = false;
									for (int j = -1; j < 4; j++)
									{
										temp2_x = x;
										temp2_y = y;
										for (int i = 0; i < 3; i++) //_________________________
										{
											switch (j)                             // направление проверки
											{
											case 0:
												temp2_x++;
												break;
											case 1:
												temp2_y++;
												break;
											case 2:
												temp2_x--;
												break;
											case 3:
												temp2_y--;
												break;
											}

											if ((temp2_x > -1) && (temp2_y > -1) && (temp2_x < field_size) && (temp2_y < field_size))
											{
												if (field2.map[temp2_x][temp2_y] == 1)
												{
													shipIsAlive = true;
													break;
												}
												if (field2.map[temp2_x][temp2_y] == 0)
												{
													break;
												}
											}
										}
									}
									if (!shipIsAlive)
									{
										field2.map[x][y] = 2;
										for (int j = 0; j < 4; j++)
										{
											temp2_x = x;
											temp2_y = y;
											for (int i = 0; i < 4; i++) //_________________________
											{
												if (field2.map[temp2_x][temp2_y] == 2)
												{
													field2.map[temp2_x][temp2_y] = 3;
													for (int ik = -1; ik < 2; ik++)
													{
														for (int jk = -1; jk < 2; jk++)
														{
															if (field2.map[temp2_x + ik][temp2_y + jk] == 0)
															{
																if ((temp2_x + ik > -1) && (temp2_y + jk > -1) && (temp2_x + ik < field_size) && (temp2_y + jk < field_size))
																{
																	field2.mask[temp2_x + ik][temp2_y + jk] = 1;
																}
															}
														}
													}
												}
												if (field2.map[temp2_x][temp2_y] == 0)
												{
													break;
												}

												switch (j)                             // направление проверки
												{
												case 0:
													temp2_x++;
													break;
												case 1:
													temp2_y++;
													break;
												case 2:
													temp2_x--;
													break;
												case 3:
													temp2_y--;
													break;
												}

											}
										}
									}
								}


								if (field2.map[x][y] == 0)
								{
									change = (!change);
								}
							}
						}
					}
				}
			}

			

			window.display();
		}
			
		if (count1 == 0)
		{
			window.draw(s_win2);
		}
		if (count2 == 0)
		{
			window.draw(s_win1);
		}
		window.display();
		
		if (RestartButton.contains(sf::Vector2f(sf::Mouse::getPosition(window))))
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					count1 = 20;
					count2 = 20;

					field1.restart();
					field2.restart();

					field1.rand_set_ship(4, 1);
					field1.rand_set_ship(3, 2);
					field1.rand_set_ship(2, 3);
					field1.rand_set_ship(1, 4);

					field2.rand_set_ship(4, 1);
					field2.rand_set_ship(3, 2);
					field2.rand_set_ship(2, 3);
					field2.rand_set_ship(1, 4);

					change = false;
				}
			}
		}
		else if (MainMenuButton.contains(sf::Vector2f(sf::Mouse::getPosition(window))))
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					Start = false;

					count1 = 20;
					count2 = 20;

					field1.restart();
					field2.restart();

					field1.rand_set_ship(4, 1);
					field1.rand_set_ship(3, 2);
					field1.rand_set_ship(2, 3);
					field1.rand_set_ship(1, 4);

					field2.rand_set_ship(4, 1);
					field2.rand_set_ship(3, 2);
					field2.rand_set_ship(2, 3);
					field2.rand_set_ship(1, 4);

					change = false;
				}
			}
		}
	}
}
