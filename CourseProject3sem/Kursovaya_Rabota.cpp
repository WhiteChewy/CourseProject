#include <iostream>
#include <fstream>
#include <clocale>
#include <cmath>
#include <string>
#include <Windows.h>
#include <cstdlib>

using namespace std;
bool cinError = false, Null_search = false;

struct Worker{
	string name[3];
	string proffesion;
	int year[3];

	Worker *next;
};

void line(int n, char f){
	for (int i = 0; i < n; i++){
		cout << f;
		if (i == n-1) cout << f;
	}
}
int ChoiceMenuOutput(int outputind,bool &cinError){
	int choice;
	cinError = false;
		cin.sync();
		cin.clear();
		if (outputind == 1){
			cout << "\nПо какому критерию будем искать увольняемого?\n";
		}
		else if (outputind == 2){
			cout << "\nЧто будете редактировать?\n";
		}
		else if (outputind == 3){
			cout << "\nПо какому критерию будем искать?\n";
		}
		else if (outputind == 4) cout << "\n По какому критерию будем сортировать\n";
		else if (outputind == 5) cout << "\n По какому критерию, вы хотите найти запись для исправления?\n";
		line(40, '-');
	    cout << "\t\n[1] - Имя, Фамилия, Отчество.";
		cout << "\t\n[2] - Должность.";
		cout << "\t\n[3] - Дата найма.";
		if (outputind == 2){ cout << "\t\n[4] - Все вместе."; }
		else if (outputind == 3){ cout << "\t\n[4] - Поиск людей отработавших больше чем надо."; }
		cout << "\n\n Критерий №";
		cin >> choice;
		cin.fail();
		if (outputind == 1 || outputind == 4 || outputind == 5){
			if (choice > 3 || choice < 1 || cin.fail()){
				cinError = true;
			}
		}
		else if (outputind == 2 || outputind == 3){
			if (choice > 4 || choice < 1 || cin.fail()){
				cinError = true;
			}
		}
return choice;
}
int read(Worker *begin, Worker *elem){
	fstream DataBase;
	DataBase.open("database.txt");
	if (!DataBase){
		cout << "Ошибка! Не удалось открыть файл!\n";
	}

	while (!DataBase.eof())
	{
		Worker *tmp = new Worker;
		for (int i = 0; i < 3; i++){
			DataBase >> tmp->name[i];
		}
		DataBase >> tmp->proffesion;
		for (int i = 0; i < 3; i++){
			DataBase >> tmp->year[i];
		}
		tmp->next = NULL;
		elem->next = tmp;
		elem = elem->next;
	}
	
	int file_size;
	file_size = DataBase.tellg();

	DataBase.close();
	if (file_size == 0) return 1;
	return 0;
}
void outputDataBase(Worker *begin)
{
	int counter = 1;
	Worker *elem;
	elem = begin->next;
	while (elem)
	{
		line(50, '-');
		cout << endl << elem->name[0] << " " << elem->name[1] << " " << elem -> name[2] << endl;
		cout << "Должность: " << elem->proffesion << endl;
		cout << "Дата найма: " << elem->year[0] << '.' << elem->year[1] << '.' << elem->year[2] << endl;


		counter++;
		elem = elem->next;
	}
	if (counter == 0) cout << "\nБаза Данных пуста.\n";
}
void addDataBase(Worker *begin, Worker *elem){
	cout << "С пополнением!\n";
	line(30, '-');
	elem = begin->next;
	while (elem){
		if (elem->next == NULL){
			Worker *tmp = new Worker;
			cout << "\nВведите фамилию сотрудника: ";
			cin >> tmp->name[0];
			cout << "Введите имя сотрудника: ";
			cin >> tmp->name[1];
			cout << "Введите отчество сотрудника: ";
			cin >> tmp->name[2];
			cout << "Введите должность: ";
			cin >> tmp->proffesion;
			cout << "Введите день приема на работу в формате ДД: ";
			cin >> tmp->year[0];
			cout << "Введите месяц приема на работу в числовом формате ММ: ";
			cin >> tmp->year[1];
			cout << "Введите год приема на работу в формате ГГГГ: ";
			cin >> tmp->year[2];
			tmp->next = NULL;
			elem->next = tmp;
			break;
		}
		elem = elem->next;
	}
}
void delDataBase(Worker *begin, Worker *elem, int delarg, string searchkey, int searchday[3]){
	int counter = 1;
	Worker *prev = begin;
	if (delarg == 1){
		while (elem){
			if (searchkey == elem->name[0] || searchkey == elem->name[1] || searchkey == elem->name[2]){
				cout << "\nНайдено и удалено!\n";
				Worker *tmp = new Worker;
				*tmp = *elem;
				prev->next = elem->next;
			}
			prev = elem;
			elem = elem->next;
		}
	}
	else if (delarg == 2){
		while (elem){
			if (searchkey == elem->proffesion){
				cout << "\nНайдено и удалено!\n";
				Worker *tmp = new Worker;
				*tmp = *elem;
				prev->next = elem->next;
			}
			prev = elem;
			elem = elem->next;
		}
	}
	else if (delarg == 3){
		while (elem){
			if (searchday[0] == elem->year[0] && searchday[1] == elem->year[1] && searchday[2] == elem->year[2]){
				cout << "\nНайдено и удалено!\n";
				Worker *tmp = new Worker;
				*tmp = *elem;
				prev->next = elem->next;
			}
			prev = elem;
			elem = elem->next;
		}
	}
	system("pause");
}
void searchDataBase(Worker *begin, Worker *elem, bool &Null_search, int searcharg, string searchKey, int worktime, int searchday[3], int CurrentDate[3]){
	int unnullcounter;
	elem = elem->next;
	if (searcharg == 1){
		int unnullcounter = 0;
		while (elem){
			if (elem->name[0] == searchKey || elem->name[1] == searchKey || elem->name[2] == searchKey){
				unnullcounter++;
				line(50, '-');
				cout << endl << elem->name[0] << " " << elem->name[1] << " " << elem->name[2] << endl;
				cout << "Должность: " << elem->proffesion << endl;
				cout << "Дата найма: " << elem->year[0] << '.' << elem->year[1] << '.' << elem->year[2] << endl;
			}
			elem = elem->next;
		}
		if (unnullcounter == 0) Null_search = true;
	}
		else if (searcharg == 3){
			unnullcounter = 0;
			while (elem){
				if (elem->year[0] == searchday[0] && elem->year[1] == searchday[1] && elem->year[2] == searchday[2]){
					unnullcounter++;
					line(50, '-');
					cout << endl << elem->name[0] << " " << elem->name[1] << " " << elem->name[2] << endl;
					cout << "Должность: " << elem->proffesion << endl;
					cout << "Дата найма: " << elem->year[0] << '.' << elem->year[1] << '.' << elem->year[2] << endl;
				}
				elem = elem->next;
				if (unnullcounter == 0) Null_search = true;
			}
		}
		else if (searcharg == 2){
			unnullcounter = 0;
			while (elem){
				if (elem->proffesion == searchKey){
					unnullcounter++;
					line(50, '-');
					cout << endl << elem->name[0] << " " << elem->name[1] << " " << elem->name[2] << endl;
					cout << "Должность: " << elem->proffesion << endl;
					cout << "Дата найма: " << elem->year[0] << '.' << elem->year[1] << '.' << elem->year[2] << endl;
				}
				elem = elem->next;
			}
			if (unnullcounter == 0) Null_search = true;
		}
		else if (searcharg == 4){
			unnullcounter = 0;
			while (elem){
				int day, month, year = 0;
				day = CurrentDate[0] - elem->year[0];
				month = CurrentDate[1] - elem->year[1];
				year = CurrentDate[2] - elem->year[2];
				if (day < 0){
					day = 31 - abs(day);
					month--;
					if (month < 0){
						month = abs(month);
						year--;
					}
				}
				if (month < 0){
					month = 12 - abs(month);
					year--;
				}
				if (year > worktime){
					unnullcounter++;
					line(50, '-');
					cout << endl << elem->name[0] << " " << elem->name[1] << " " << elem->name[2] << endl;
					cout << "Должность: " << elem->proffesion << endl;
					cout << "Дата найма: " << elem->year[0] << '.' << elem->year[1] << '.' << elem->year[2] << endl;
				}
				elem = elem->next;
				if (unnullcounter == 0) Null_search = true;
			}
		}
	}
void saveDataBase(Worker *begin, Worker *elem){
	fstream DataBase;
	DataBase.open("database.txt");
	if (!DataBase){
		cout << "Ошибка! Не удалось открыть файл!\n";
	}
	elem = elem->next;
	while (elem)
	{

		for (int i = 0; i < 3; i++){
			DataBase << elem->name[i] << " ";
		}
		DataBase << elem->proffesion << " ";
		for (int i = 0; i < 3; i++){
			if (elem->next == NULL){
				DataBase << elem->year[i];
				break;
			}
			else if (i == 2){
				DataBase << elem->year[i] << endl;
				break;
			}
			else DataBase << elem->year[i] << " ";
		}
		elem = elem->next;
	}
	DataBase.close();
}
void sortDataBase(Worker *begin, Worker *elem, int sortid){
	if (sortid == 3){
		for (elem = begin; elem; elem = elem->next)
		{
			for (Worker *Next = elem->next; Next; Next = Next->next)
			{
				if (elem->year[2] > Next->year[2])
				{
					Worker  valtmp = *elem;
					*elem = *Next;
					*Next = valtmp;

					Worker  *tmp = elem->next;
					elem->next = Next->next;
					Next->next = tmp;
				}
				else if (elem->year[2] == Next->year[2]){
					if (elem->year[1] > Next->year[1])
					{
						Worker  valtmp = *elem;
						*elem = *Next;
						*Next = valtmp;

						Worker  *tmp = elem->next;
						elem->next = Next->next;
						Next->next = tmp;
					}
					else if (elem->year[1] == Next->year[1]){
						if (elem->year[0] > Next->year[0])
						{
							Worker  valtmp = *elem;
							*elem = *Next;
							*Next = valtmp;

							Worker  *tmp = elem->next;
							elem->next = Next->next;
							Next->next = tmp;
						}
					}
				}
			}
		}
	}
	else if (sortid == 2){
		for (elem = begin; elem; elem = elem->next)
		{
			for (Worker *Next = elem->next; Next; Next = Next->next)
			{
				if (elem->proffesion > Next->proffesion)
				{
					Worker  valtmp = *elem;
					*elem = *Next;
					*Next = valtmp;

					Worker  *tmp = elem->next;
					elem->next = Next->next;
					Next->next = tmp;
				}
			}
		}
	}
	else if (sortid == 1){
		for (elem = begin; elem; elem = elem->next)
		{
			for (Worker *Next = elem->next; Next; Next = Next->next)
			{
				if (elem->name[0] > Next->name[0])
				{
					Worker  valtmp = *elem;
					*elem = *Next;
					*Next = valtmp;

					Worker  *tmp = elem->next;
					elem->next = Next->next;
					Next->next = tmp;
				}
				else if (elem->name[0] == Next->name[0]){
							if (elem->name[1] > Next->name[1])
							{
								Worker  valtmp = *elem;
								*elem = *Next;
								*Next = valtmp;

								Worker  *tmp = elem->next;
								elem->next = Next->next;
								Next->next = tmp;
							}
							else if (elem->name[1] == Next->name[1]){
								if (elem->name[1] > Next->name[1])
								{
									Worker  valtmp = *elem;
									*elem = *Next;
									*Next = valtmp;

									Worker  *tmp = elem->next;
									elem->next = Next->next;
									Next->next = tmp;
								}
							}
				}
			}
		}
	}
}
void fixDataBase(Worker *begin, Worker *elem, int fixarg, string searchKey, int searchday[3]){
	int unnullcounter; int command = 0;
	if (fixarg == 1){
		int unnullcounter = 0;
		while (elem){
			if (elem->name[0] == searchKey || elem->name[1] == searchKey || elem->name[2] == searchKey){
				unnullcounter++;
				do{
					cin.clear();
					cin.fail();
					cout << "\nЧто вы хотите исправить?: \n";
					cout << "\n [1] - Имя";
					cout << "\n [2] - Фамилию";
					cout << "\n [3] - Отчество";
					cout << "\n [4] - Имя, Фамилию и Отчество";
					cout << "\n [5] - Должность";
					cout << "\n [6] - Дату приема.";
					cout << "\n [7] - Завершение редактирования.";
					cout << "\n Ваша команда: ";
					cin >> command;
				
				if (command == 1 || command == 4){
					cout << "\n Введите новое Имя: ";
					cin >> elem->name[1];
				}
				else if (command == 2 || command == 4){
					cout << "\n Введите новую Фамилию: ";
					cin >> elem->name[0];
				}
				else if (command == 3 || command == 4){
					cout << "\n Введите новое Отчество: ";
					cin >> elem->name[2];
				}
				else if (command == 5){
					cout << "\n Введите новую должность: ";
					cin >> elem->proffesion;
				}
				else if (command == 6){
					cout << "\n Введите новую дату приема: ";
					do{
						cin.clear();
						cin.sync();
						cout << "\n День: ";
						cin >> elem->year[0];
					} while (elem->year[0] < 0 || elem->year[0] > 31 || cin.fail());
					do{
						cin.clear();
						cin.sync();
						cout << "\n Месяц: ";
						cin >> elem->year[1];
					} while (elem->year[1] < 0 || elem->year[1] > 12 || cin.fail());
					do{
						cin.clear();
						cin.sync();
						cout << "\n Год: ";
						cin >> elem->year[2];
					} while (elem->year[2] < 0 || elem->year[2] > 2014 || cin.fail());
				}
				} while (command != 7);
			}
			elem = elem->next;
		}
		if (unnullcounter == 0) Null_search = true;
	}
	else if (fixarg == 3){
		unnullcounter = 0;
		while (elem){
			if (elem->year[0] == searchday[0] && elem->year[1] == searchday[1] && elem->year[2] == searchday[2]){
				unnullcounter++;
				do{
					cin.clear();
					cin.fail();
					cout << "\nЧто вы хотите исправить?: \n";
					cout << "\n [1] - Имя";
					cout << "\n [2] - Фамилию";
					cout << "\n [3] - Отчество";
					cout << "\n [4] - Имя, Фамилию и Отчество";
					cout << "\n [5] - Должность";
					cout << "\n [6] - Дату приема.";
					cout << "\n [7] - Завершение редактирования.";
					cout << "\n Ваша команда: ";
					cin >> command;
				
				if (command == 1 || command == 4){
					cout << "\n Введите новое Имя: ";
					cin >> elem->name[1];
				}
				else if (command == 2 || command == 4){
					cout << "\n Введите новую Фамилию: ";
					cin >> elem->name[0];
				}
				else if (command == 3 || command == 4){
					cout << "\n Введите новое Отчество: ";
					cin >> elem->name[2];
				}
				else if (command == 5){
					cout << "\n Введите новую должность: ";
					cin >> elem->proffesion;
				}
				else if (command == 6){
					cout << "\n Введите новую дату приема: ";
					do{
						cin.clear();
						cin.sync();
						cout << "\n День: ";
						cin >> elem->year[0];
					} while (elem->year[0] < 0 || elem->year[0] > 31 || cin.fail());
					do{
						cin.clear();
						cin.sync();
						cout << "\n Месяц: ";
						cin >> elem->year[1];
					} while (elem->year[1] < 0 || elem->year[1] > 12 || cin.fail());
					do{
						cin.clear();
						cin.sync();
						cout << "\n Год: ";
						cin >> elem->year[2];
					} while (elem->year[2] < 0 || elem->year[2] > 2014 || cin.fail());
				}
				} while (command != 7);
			}
			elem = elem->next;
		}
		if (unnullcounter == 0) Null_search = true;
	}
	 if (fixarg == 2){
		unnullcounter = 0;
		while (elem){
			if (elem->proffesion == searchKey){
				unnullcounter++;
				do{
					cin.clear();
					cin.fail();
					cout << "\nЧто вы хотите исправить?: \n";
					cout << "\n [1] - Имя";
					cout << "\n [2] - Фамилию";
					cout << "\n [3] - Отчество";
					cout << "\n [4] - Имя, Фамилию и Отчество";
					cout << "\n [5] - Должность";
					cout << "\n [6] - Дату приема.";
					cout << "\n [7] - Завершение редактирования.";
					cout << "\n Ваша команда: ";
					cin >> command;
				
				if (command == 1 || command == 4){
					cout << "\n Введите новое Имя: ";
					cin >> elem->name[1];
				}
				else if (command == 2 || command == 4){
					cout << "\n Введите новую Фамилию: ";
					cin >> elem->name[0];
				}
				else if (command == 3 || command == 4){
					cout << "\n Введите новое Отчество: ";
					cin >> elem->name[2];
				}
				else if (command == 5){
					cout << "\n Введите новую должность: ";
					cin >> elem->proffesion;
				}
				else if (command == 6){
					cout << "\n Введите новую дату приема: ";
					do{
						cin.clear();
						cin.sync();
						cout << "\n День: ";
						cin >> elem->year[0];
					} while (elem->year[0] < 0 || elem->year[0] > 31 || cin.fail());
					do{
						cin.clear();
						cin.sync();
						cout << "\n Месяц: ";
						cin >> elem->year[1];
					} while (elem->year[1] < 0 || elem->year[1] > 12 || cin.fail());
					do{
						cin.clear();
						cin.sync();
						cout << "\n Год: ";
						cin >> elem->year[2];
					} while (elem->year[2] < 0 || elem->year[2] > 2014 || cin.fail());
				}
				} while (command != 7);
			}
			elem = elem->next;
		}
		if (unnullcounter == 0) Null_search = true;
		}
	}
void dell(Worker *begin)
{
	Worker *elem = begin->next;
	while (elem){
		delete begin;
		begin = elem;
		elem = elem->next;
	}
}

int main(){
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	int command, worktime, CurrentDate[3];
	int searcharg = 0;
	int delnumb, fixnumb = 0, sortid;
	char choice, fixchoice, fixarg, delarg;
	string searchkey;
	int searchday[3];
	Worker *begin = new Worker;
	begin->next = NULL;
	Worker *elem = begin;
	read(begin, elem);//Считывание базы данных в список.

	do{
		//	вывод "окна" авторства.
		cout << " ";
		line(46, '~');
		cout << "\n|Добро пожаловать в базу данных!                |\n|Автор: Куликов Никита Группа:4332 ВУЗ: СПбГУАП |\n ";
		line(46, '~');
		//	вывод меню.
		if (read(begin, elem)){
			cout << endl;
			line(22, '-');
			cout << "\n| БАЗА ДАННЫХ ПУСТА! |\n";
			line(22,'-');
			cout << endl;
		}
		cout << "\n\nДля работы с базой данных, пожалуйста, введите одну из команд:\n";
		line(62, '-');
		cout << "\n\t| 1 | Принятие на работу нового сотрудника.            |\n\t";
		line(54, '-');
		cout << "\n\t| 2 | Увольнение работника.                            |\n\t";
		line(54, '-');
		cout << "\n\t| 3 | Исправить имя, дату принятия, должность.         |\n\t";
		line(54, '-');
		cout << "\n\t| 4 | Поиск по базе данных.                            |\n\t";
		line(54, '-');
		cout << "\n\t| 5 | Просмотр базы данных.                            |\n\t";
		line(54, '-');
		cout << "\n\t| 6 | Сортировка базы данных по дате по возрастанию.   |\n\t";
		line(54, '-');
		cout << "\n\t| 7 | Выход                                            |\n";
		line(62, '-');
		cout << "\n\n\nВаша комманда: ";
		cin >> command;
		switch (command){
		case 1:
			system("cls");
			addDataBase(begin, elem);
			system("cls");
			cin.clear();
			cin.sync();
			break;
		case 2:
			system("cls");
			do{
				delarg = ChoiceMenuOutput(1, cinError);
			} while (delarg > 3 || delarg < 1 || cinError);
			if (delarg == 1 || delarg == 2){
				cout << "\nВведите ключевое слово: ";
				cin >> searchkey;
			}
			else if (delarg == 3){
				cout << "\nВведите дату для поиска\t";
				do{
					cin.clear();
					cin.sync();
					cout << "\nВведите День: ";
					cin >> searchday[0];
					if (searchday[0] < 0 && searchday[0] > 31 || cin.fail()) cout << "\nОшибка. Попробуйте еще раз!";
				} while (searchday[0] < 0 && searchday[0] > 31 || cin.fail());
				do{
					cin.clear();
					cin.sync();
					cout << "\nВведите Месяц (в числовом формате): ";
					cin >> searchday[1];
					if (searchday[1] < 0 && searchday[1] > 12 || cin.fail()) cout << "\nОшибка. Попробуйте еще раз!";
				} while (searchday[1] < 0 && searchday[1] > 12 || cin.fail());
				do{
					cin.clear();
					cin.sync();
					cout << "\nВведите год (полностью): ";
					cin >> searchday[2];
					if (cin.fail() || searchday[2] < 0 && searchday[2] > 2014) cout << "\nОшибка. Попробуйте еще раз!";
				} while (cin.fail() || searchday[2] < 0 && searchday[2] > 2014);
			}
			delDataBase(begin, elem, delarg, searchkey, searchday);
			system("cls");
			cin.clear();
			cin.sync();
			break;
		case 3:
			system("cls");
			do{
				fixarg = ChoiceMenuOutput(5, cinError);
			} while (cinError);

			if (fixarg == 1 || fixarg == 2){
				cout << "\nВведите ключевое слово: ";
				cin >> searchkey;
			}
			else if (fixarg == 3){
				cout << "\nВведите дату для поиска\t";
				do{
					cin.clear();
					cin.sync();
					cout << "\nВведите День: ";
					cin >> searchday[0];
					if (searchday[0] < 0 && searchday[0] > 31 || cin.fail()) cout << "\nОшибка. Попробуйте еще раз!";
				} while (searchday[0] < 0 && searchday[0] > 31 || cin.fail());
				do{
					cin.clear();
					cin.sync();
					cout << "\nВведите Месяц (в числовом формате): ";
					cin >> searchday[1];
					if (searchday[1] < 0 && searchday[1] > 12 || cin.fail()) cout << "\nОшибка. Попробуйте еще раз!";
				} while (searchday[1] < 0 && searchday[1] > 12 || cin.fail());
				do{
					cin.clear();
					cin.sync();
					cout << "\nВведите год (полностью): ";
					cin >> searchday[2];
					if (cin.fail() || searchday[2] < 0 && searchday[2] > 2014) cout << "\nОшибка. Попробуйте еще раз!";
				} while (cin.fail() || searchday[2] < 0 && searchday[2] > 2014);
			}
				fixDataBase(begin, elem, fixarg, searchkey, searchday);
				system("cls");
				cin.clear();
				cin.sync();
				break;
		case 4:
			do{
				system("cls");
				if (cinError){
					cout << "\n+";
					line(35, '-');
					cout << "+\n| Ошибка ввода! Попробуйте еще раз!  |\n+";
					line(35, '-');
					cout << "+\n";
				}
				searcharg = ChoiceMenuOutput(3, cinError);
			} while (cinError);
			if (searcharg == 1 || searcharg == 2){
				cout << "\nВведите ключевое слово: ";
				cin >> searchkey;
				searchDataBase(begin, elem, Null_search, searcharg, searchkey, worktime, searchday, CurrentDate);
			}
			else if (searcharg == 3){
				cout << "\nВведите дату для поиска\t";
				do{
					cin.clear();
					cin.sync();
					cout << "\nВведите День: ";
					cin >> searchday[0];
					if (cin.fail() || searchday[0] < 0 || searchday[0] > 31) cout << "Ошибка. Попробуйте еще раз!";
				} while (cin.fail() || searchday[0] < 0 || searchday[0] > 31);
				do{
					cin.clear();
					cin.sync();
					cout << "\nВведите Месяц (в числовом формате): ";
					cin >> searchday[1];
					if (cin.fail() || searchday[1] < 0 || searchday[1] > 12) cout << "Ошибка. Попробуйте еще раз!";
				} while (cin.fail() || searchday[1] < 0 || searchday[1] > 12);
				do{
					cin.clear();
					cin.sync();
					cout << "\nВведите год (полностью): ";
					cin >> searchday[3];
					if (cin.fail() || searchday[3] < 0 || searchday[3] > 2014) cout << "Ошибка. Попробуйте еще раз!";
				} while (cin.fail() || searchday[1] < 0 || searchday[3] > 2014);
				searchDataBase(begin, elem, Null_search, searcharg, searchkey, worktime, searchday, CurrentDate);
			}
			else{
				do{
					cin.clear();
					cin.sync();
					cout << "\nВведите стаж: ";
					cin >> worktime;
					if (cin.fail() || worktime < 0) cout << "\nОшибка. Попробуйте еще раз!";
				} while (cin.fail() || worktime < 0);
				do{
					cin.clear();
					cin.sync();
					cout << "Введите текущий день (ДД): ";
					cin >> CurrentDate[0];
				} while (cin.fail() || CurrentDate[0] < 0 || CurrentDate[0] > 31);
				do{
					cin.clear();
					cin.sync();
					cout << "Введите текущий месяц (ММ): ";
					cin >> CurrentDate[1];
				} while (cin.fail() || CurrentDate[1] < 0 || CurrentDate[1] > 12);
				do{
					cin.clear();
					cin.sync();
					cout << "Введите текущий год(ГГГГ): ";
					cin >> CurrentDate[2];
				} while (cin.fail() || CurrentDate[2] < 0 || CurrentDate[2] > 2014);
				searchDataBase(begin, elem, Null_search, searcharg, searchkey, worktime, searchday, CurrentDate);
			}
			if (Null_search) cout << "\nПо вашему запросу ничего не найдено!\n";
			system("pause");
			system("cls");
			cin.clear();
			cin.sync();
			break;
		case 5:
			system("cls");
			outputDataBase(begin);
			cin.sync();
			cout << "Для продолжения работы с базой, пожалуйста, нажмите Enter! Буквы игнорируются!\n";
			cin.get();
			cin.sync();
			system("cls");
			cin.clear();
			cin.sync();
			break;
		case 6:
			do{
				system("cls");
				if (cinError){
					cout << "\n+";
					line(35, '-');
					cout << "+\n| Ошибка ввода! Попробуйте еще раз! |\n+";
					line(35, '-');
					cout << "+\n";
				}
				sortid = ChoiceMenuOutput(4, cinError);
			} while (cinError);
			sortDataBase(begin, elem, sortid);
			system("pause");
			cin.clear();
			cin.sync();
			break;
		case 7:
			saveDataBase(begin, elem);
			do{
				cout << "Вы точно хотите выйти из программы? (y/n): ";
				cin >> choice;
				if (choice != 'y' && choice != 'n' && choice != 'н' && choice != 'т' || cin.fail()){
					cin.sync();
					line(45, '!');
					cout << "\n! Ошибка ввода команды. Попробуйте еще раз. !\n";
					line(45, '!');
					cout << endl;
					cin.clear();
				}
			} while (choice != 'y' && choice != 'n' && choice != 'н' && choice != 'т');

			if (choice == 'y' || choice == 'н'){
				system("cls");
				cout << "\n Спасибо за работу! До свидания!\n";
				system("exit");
			}
			else if (choice == 'n' || choice == 'т'){
				system("cls");
			}
			}
			if (command<0 || command>7 || cin.fail()){
				cin.sync();
				line(62, '!');
				cout << "\n! Извините вы ввели не известную команду! Попробуйте еще раз! !\n";
				line(62, '!');
				cout << endl;
				system("pause");
				system("cls");
				cin.clear();
		}
			cin.clear();
			cin.sync();
	} while (command != 7);
	dell(begin);
	cout << endl;
	system("pause");
	return 0;
}