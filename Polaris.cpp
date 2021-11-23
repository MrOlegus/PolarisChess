// Polaris.cpp : Определяет точку входа для приложения.

#include <Windows.h>
#include <cstdio>
#include <string>
#include <ctime>
#include "framework.h"
#include <list>
#include "Colors.h"
#include "Figures.h"
#include "Fields.h"
//#include "Move.cpp"
//#include "Position.cpp"
//#include "MoveGenerator.cpp"

using namespace std;

struct Move {
	int from;
	int to;
	int figure;

public:
	Move(int from, int to, int figure)
	{
		this->from = from;
		this->to = to;
		this->figure = figure;
	}

	Move(char* strMove)
	{
		int lFrom = strMove[0] - 'a';
		int nFrom = strMove[1] - '1';

		int lTo = strMove[3] - 'a';
		int nTo = strMove[4] - '1';

		int figure;
		switch (strMove[6])
		{
			case 'p': figure = p; break;
			case 'r': figure = r; break;
			case 'b': figure = b; break;
			case 'n': figure = n; break;
			case 'q': figure = q; break;
			case 'k': figure = k; break;
			case 'P': figure = P; break;
			case 'R': figure = R; break;
			case 'B': figure = B; break;
			case 'N': figure = N; break;
			case 'Q': figure = Q; break;
			case 'K': figure = K; break;
		}

		this->from = Field(lFrom, nFrom);
		this->to = Field(lTo, nTo);
		this->figure = figure;
	}

	char* ToString()
	{
		char strMove[8];

		strMove[0] = Letter(from) + 'a';
		strMove[1] = Number(from) + '0';
		strMove[2] = ' ';
		strMove[3] = Letter(to) + 'a';
		strMove[4] = Number(to) + '0';
		strMove[5] = ' ';
		
		switch (figure)
		{
		case p: strMove[6] = 'p'; break;
		case r: strMove[6] = 'r'; break;
		case b: strMove[6] = 'b'; break;
		case n: strMove[6] = 'n'; break;
		case q: strMove[6] = 'q'; break;
		case k: strMove[6] = 'k'; break;
		case P: strMove[6] = 'P'; break;
		case R: strMove[6] = 'R'; break;
		case B: strMove[6] = 'B'; break;
		case N: strMove[6] = 'N'; break;
		case Q: strMove[6] = 'Q'; break;
		case K: strMove[6] = 'K'; break;
		}

		strMove[7] = '\0';

		return strMove;
	}
};

Move get(list<Move> _list, int _i) {
	list<Move>::iterator it = _list.begin();
	for (int i = 0; i < _i; i++) {
		++it;
	}
	return *it;
}

class Position {
public: // индексатор
	int operator [] (int index)
	{
		return fields[index];
	}

	bool isRookAMoved[2] = { false, false };
	bool isRookHMoved[2] = { false, false };
	bool isKingMoved[2] = { false, false };

	Move lastMove = *(new struct Move(e8, e8, K));

private:
	int fields[64];

public:
	Position()
	{
		this->Reset();
	}

	Position* Clear()
	{
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				fields[Field(i, j)] = e;
		return this;
	}

	Position* Reset()
	{
		Clear();

		fields[a1] = r; fields[a8] = R;
		fields[b1] = n; fields[b8] = N;
		fields[c1] = b; fields[c8] = B;
		fields[d1] = q; fields[d8] = Q;
		fields[e1] = k; fields[e8] = K;
		fields[f1] = b; fields[f8] = B;
		fields[g1] = n; fields[g8] = N;
		fields[h1] = r; fields[h8] = R;

		fields[a2] = p; fields[a7] = P;
		fields[b2] = p; fields[b7] = P;
		fields[c2] = p; fields[c7] = P;
		fields[d2] = p; fields[d7] = P;
		fields[e2] = p; fields[e7] = P;
		fields[f2] = p; fields[f7] = P;
		fields[g2] = p; fields[g7] = P;
		fields[h2] = p; fields[h7] = P;

		return this;
	}

	Position* Move(Move move)
	{
		this->lastMove = move;

		// короткая рокировка за белых
		if ((move.figure == k) && (move.from == e1) && (move.to == g1))
		{
			fields[e1] = e;
			fields[g1] = k;
			fields[h1] = e;
			fields[f1] = r;
		} else
		// короткая рокировка за черных
		if ((move.figure == K) && (move.from == e8) && (move.to == g8))
		{
			fields[e8] = e;
			fields[g8] = K;
			fields[h8] = e;
			fields[f8] = R;
		} else
		// длинная рокировка за белых
		if ((move.figure == k) && (move.from == e1) && (move.to == c1))
		{
			fields[e1] = e;
			fields[c1] = k;
			fields[a1] = e;
			fields[d1] = r;
		}
		else
		// длинная рокировка за черных
		if ((move.figure == K) && (move.from == e8) && (move.to == c8))
		{
			fields[e8] = e;
			fields[c8] = K;
			fields[a8] = e;
			fields[d8] = R;
		}
		else
		// взятие на проходе за белых
		if ((fields[move.from] == p) && 
			(Letter(move.from) != Letter(move.to)) &&
			(fields[move.to] == e))
		{
			fields[move.from] = e;
			fields[move.to] = move.figure;
			fields[OffsetField(move.to, 0, -1)] = e;
		} else
		// взятие на проходе за черных
		if ((fields[move.from] == P) &&
			(Letter(move.from) != Letter(move.to)) &&
			(fields[move.to] == e))
		{
			fields[move.from] = e;
			fields[move.to] = move.figure;
			fields[OffsetField(move.to, 0, 1)] = e;
		} else
		// нормальный ход
		{
			fields[move.from] = e;
			fields[move.to] = move.figure;
		}

		if (move.figure == k) isKingMoved[0] = true; else
		if (move.figure == K) isKingMoved[1] = true; else
		if ((move.figure == r) && (move.from == a1)) isRookAMoved[0] = true; else
		if ((move.figure == R) && (move.from == a8)) isRookAMoved[1] = true; else
		if ((move.figure == r) && (move.from == h1)) isRookHMoved[0] = true; else
		if ((move.figure == R) && (move.from == h8)) isRookHMoved[1] = true;

		return this;
	}
};

class MoveGenerator {
public:
	static list<Move>* Generate(Position* position)
	{
		Move lastMove = position->lastMove;
		int color = Color(lastMove.figure) ^ 1;
		bool isKingMoved = position->isKingMoved[color];
		bool isRookAMoved = position->isRookAMoved[color];
		bool isRookHMoved = position->isRookHMoved[color];

		list<Move>* moves = new list<Move>();

		for (int i = a1; i <= h8; i++)
			if (Color((*position)[i]) == color)
				switch ((*position)[i]) {
				case r: case R:
					GenerateRookMoves(moves, position, i);
					break;
				case n: case N:
					GenerateKnightMoves(moves, position, i);
					break;
				case b: case B:
					GenerateBishopMoves(moves, position, i);
					break;
				case q: case Q:
					GenerateQueenMoves(moves, position, i);
					break;
				case k: case K:
					GenerateKingMoves(moves, position, i, isKingMoved, isRookAMoved, isRookHMoved);
					break;
				case p: case P:
					GeneratePawnMoves(moves, position, i, lastMove);
					break;
				}
		return moves;
	}

private:
	// добавление в список ходов короля без учета шахов
	static void GenerateKingMoves(list<Move>* moves, Position* position, int field, bool isKingMoved, bool isRookAMoved, bool isRookHMoved)
	{
		int color = Color((*position)[field]);

		// проверяем все соседние клетки
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++)
				if ((i != 0) || (j != 0))
				{
					int fieldTo = OffsetField(field, i, j);
					if (fieldTo == unrealField) continue;

					// фигура или пустое место на поле, куда пробуем походить
					int onFieldTo = (*position)[fieldTo];

					// если на поле не фигура своего цвета, добавляем в возможные ходы
					if ((onFieldTo == e) ||
						(color != Color(onFieldTo)))
					{
						moves->push_back(Move(field, fieldTo, (*position)[field]));
					}
				}

		// короткая рокировка ИСПРАВИТЬ
		if ((!isKingMoved) && (!isRookHMoved))
		{
			if (((*position)[OffsetField(field, 1, 0)] == e) &&
				((*position)[OffsetField(field, 2, 0)] == e))
			{
				moves->push_back(Move(field, OffsetField(field, 2, 0), (*position)[field]));
			}
		}

		// длинная рокировка ИСПРАВИТЬ
		if ((!isKingMoved) && (!isRookAMoved))
		{
			if (((*position)[OffsetField(field, -1, 0)] == e) &&
				((*position)[OffsetField(field, -2, 0)] == e) &&
				((*position)[OffsetField(field, -3, 0)] == e))
			{
				moves->push_back(Move(field, OffsetField(field, -2, 0), (*position)[field]));
			}
		}
	}

	// добавление в список ходов коня без учета шахов
	static void GenerateKnightMoves(list<Move>* moves, Position* position, int field)
	{
		int color = Color((*position)[field]);

		// проверяем 8 клеток вокруг поля
		for (int i = -2; i <= 2; i++)
			for (int j = -2; j <= 2; j++)
				if ((i != 0) && (j != 0) && (abs(i) != abs(j)))
				{
					int fieldTo = OffsetField(field, i, j);
					if (fieldTo == unrealField) continue;

					// фигура или пустое место на поле, куда пробуем походить
					int onFieldTo = (*position)[fieldTo];

					// если на поле не фигура своего цвета, добавляем в возможные ходы
					if ((onFieldTo == e) ||
						(color != Color(onFieldTo)))
					{
						moves->push_back(Move(field, fieldTo, (*position)[field]));
					}
				}
	}

	// добавление в список ходов ладьи без учета шахов
	static void GenerateRookMoves(list<Move>* moves, Position* position, int field)
	{
		int color = Color((*position)[field]);

		// проверяем клетки по четырем направлениям
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++)
				if ((i == 0) ^ (j == 0))
				{
					int fieldTo = field;
					while ((fieldTo = OffsetField(fieldTo, i, j)) != unrealField)
					{
						// фигура или пустое место на поле, куда пробуем походить
						int onFieldTo = (*position)[fieldTo];

						// если на поле не фигура своего цвета, добавляем в возможные ходы
						if ((onFieldTo == e) ||
							(color != Color(onFieldTo)))
						{
							moves->push_back(Move(field, fieldTo, (*position)[field]));
						}
						
						// наткнулись на свою фигуру или побили - выходим из цикла
						if (onFieldTo != e)
						{
							break;
						}
					}
				}
	}

	// добавление в список ходов слона без учета шахов
	static void GenerateBishopMoves(list<Move>* moves, Position* position, int field)
	{
		int color = Color((*position)[field]);

		// проверяем клетки по четырем направлениям
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++)
				if ((i != 0) && (j != 0))
				{
					int fieldTo = field;
					while ((fieldTo = OffsetField(fieldTo, i, j)) != unrealField)
					{
						// фигура или пустое место на поле, куда пробуем походить
						int onFieldTo = (*position)[fieldTo];

						// если на поле не фигура своего цвета, добавляем в возможные ходы
						if ((onFieldTo == e) ||
							(color != Color(onFieldTo)))
						{
							moves->push_back(Move(field, fieldTo, (*position)[field]));
						}
						
						// наткнулись на свою фигуру или побили - выходим из цикла
						if (onFieldTo != e)
						{
							break;
						}
					}
				}
	}

	// добавление в список ходов ферзя без учета шахов
	static void GenerateQueenMoves(list<Move>* moves, Position* position, int field)
	{
		GenerateRookMoves(moves, position, field);
		GenerateBishopMoves(moves, position, field);
	}

	// добавление в список ходов пешек без учета шахов
	static void GeneratePawnMoves(list<Move>* moves, Position* position, int field, Move lastMove)
	{
		int color = Color((*position)[field]);
		int dir = (color == white) ? 1 : -1; // направление движения пешки
		int hor = Number(field); // горизонталь, на которой стоит пешка

		// ход пешки на одно поле без превращений
		if ((hor + dir != 1) && (hor + dir != 8))
		{
			int fieldTo = OffsetField(field, 0, dir);
			int onFieldTo = (*position)[fieldTo];

			// если поле пустое, добавляем в возможные ходы
			if (onFieldTo == e)
			{
				moves->push_back(Move(field, fieldTo, (*position)[field]));
			}
		}

		// ход пешки на одно поле с превращением
		if ((hor + dir == 1) || (hor + dir == 8))
		{
			int fieldTo = OffsetField(field, 0, dir);
			int onFieldTo = (*position)[fieldTo];

			// если поле пустое, добавляем в возможные ходы
			if (onFieldTo == e)
			{
				moves->push_back(Move(field, fieldTo, Figure(q, color)));
				moves->push_back(Move(field, fieldTo, Figure(r, color)));
				moves->push_back(Move(field, fieldTo, Figure(b, color)));
				moves->push_back(Move(field, fieldTo, Figure(n, color)));
			}
		}

		// ход пешки на два поля вперед
		if (((hor == 2) && (color == white)) ||
			((hor == 7) && (color == black)))
		{
			int fieldBetween = OffsetField(field, 0, dir);
			int onFieldBetween = (*position)[fieldBetween];

			int fieldTo = OffsetField(field, 0, 2 * dir);
			int onFieldTo = (*position)[fieldTo];

			// если клетка после пешки пустая
			if (onFieldBetween == e)
				// если поле пустое, добавляем в возможные ходы
				if (onFieldTo == e)
				{
					moves->push_back(Move(field, fieldTo, (*position)[field]));
				}
		}

		// бой без превращения
		if ((hor + dir != 1) && (hor + dir != 8))
		{
			for (int i = -1; i <= 1; i += 2)
			{
				int fieldTo = OffsetField(field, i, dir);
				if (fieldTo == unrealField) continue;
				int onFieldTo = (*position)[fieldTo];

				if ((onFieldTo != e) && (color != Color(onFieldTo))) // если на поле чужая фигура
				{
					moves->push_back(Move(field, fieldTo, (*position)[field]));
				}
			}
		}

		// бой с превращением
		if ((hor + dir == 1) || (hor + dir == 8))
		{
			for (int i = -1; i <= 1; i += 2)
			{
				int fieldTo = OffsetField(field, i, dir);
				if (fieldTo == unrealField) continue;
				int onFieldTo = (*position)[fieldTo];

				if ((onFieldTo != e) && (color != Color(onFieldTo))) // если на поле чужая фигура
				{
					moves->push_back(Move(field, fieldTo, Figure(q, color)));
					moves->push_back(Move(field, fieldTo, Figure(r, color)));
					moves->push_back(Move(field, fieldTo, Figure(b, color)));
					moves->push_back(Move(field, fieldTo, Figure(n, color)));
				}
			}
		}

		// взятие на проходе
		if ((lastMove.figure == p) ||
			(lastMove.figure == P))
			if (((hor == 5) && (color == white)) ||
				((hor == 4) && (color == black)))
			{
				for (int i = -1; i <= 1; i += 2)
				{
					// какой должен был быть последний ход для возможности взятия на проходе
					int lastFieldFrom = OffsetField(field, i, 2 * dir);
					int lastFieldTo = OffsetField(field, i, 0);

					if ((lastMove.from == lastFieldFrom) &&
						(lastMove.to == lastFieldTo))
					{
						int fieldTo = OffsetField(field, i, dir);
						moves->push_back(Move(field, fieldTo, Figure(p, color)));
					}
				}
			}
	}
};

#pragma comment(lib, "Msimg32.lib")

class Drawer {
private:

	HBITMAP hBackground = NULL;
	int bgWidth = 0;
	int bgHeight = 0;

	HBITMAP hBoard = NULL;
	int brdWidth = 0;
	int a8Corner = 0;
	int h1Corner = 0;

	HBITMAP hFigures[13] = { {NULL} };
	int fgrWidth = 0;

	Position* position = NULL;
	int side = white; // сторона, за которую необходимо отображать доску

	float offset = 0.03; // пространство между компонентами относительно ширины окна
	int colorError = 10; // максимально возможная дисперсия двух цветов при проверке на равенство

	int activeX = 0;
	int activeY = 0;
	int activeWidth = 0; // область доски от a8 до h1 в окне

	int selectedField = unrealField;

public:

	Drawer()
	{
	}

	Drawer(Position* position)
	{
		this->position = position;
	}

	void SetPosition(Position* position)
	{
		this->position = position;
	}

	void SetBackground(LPCWSTR path)
	{
		hBackground = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		BITMAP bm;
		GetObject(hBackground, sizeof(BITMAP), &bm);
		bgWidth = bm.bmWidth;
		bgHeight = bm.bmHeight;
	}

	void SetBoard(LPCWSTR path)
	{
		hBoard = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		BITMAP bm;
		GetObject(hBoard, sizeof(BITMAP), &bm);
		brdWidth = bm.bmWidth;

		// определение границ доски
		HDC hdc = CreateCompatibleDC(GetDC(FindWindow(L"Polaris", L"Polaris")));
		SelectObject(hdc, hBoard);
		int d = brdWidth / 16;
		int whiteColor = GetPixel(hdc, brdWidth / 2 + d, brdWidth / 2 + d);

		byte red0 = whiteColor >> 16;
		byte green0 = (whiteColor >> 8) & 255;
		byte blue0 = whiteColor & 255;

		int x = 0;
		int D = 11;
		while (D > colorError)
		{
			x++;
			int color = GetPixel(hdc, x, x);
			byte red = color >> 16;
			byte green = (color >> 8) & 255;
			byte blue = color & 255;
			
			D = pow(red - red0, 2) + pow(green - green0, 2) + pow(blue - blue0, 2);
		}
		a8Corner = x;
		h1Corner = brdWidth - x;

		DeleteDC(hdc);
		// определение границ доски
	}

	void SetFigures(LPCWSTR path)
	{
		for (int j = P; j <= k; j++)
		{
			wchar_t color = ColorToChar(Color(j));
			wchar_t figure = FigureToChar(j);

			wstring figurePath = path;
			if (figurePath[figurePath.size() - 1] != '\\') figurePath.push_back('\\');
			figurePath.push_back(color);
			figurePath.push_back(figure);
			figurePath.append(L".bmp");

			hFigures[j] =
				(HBITMAP)LoadImage(NULL, figurePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}

		BITMAP bm;
		GetObject(hFigures[1], sizeof(BITMAP), &bm);
		fgrWidth = bm.bmWidth;
	}

	void SetOffset(float offset)
	{
		this->offset = offset;
	}

	void SetSide(int side)
	{
		this->side = side;
	}
	
	void SetSelectedField(int field)
	{
		this->selectedField = field;
	}

	int GetActiveX() { return activeX; }
	int GetActiveY() { return activeY; }
	int GetActiveWidth() { return activeWidth; }

	void Draw(HDC hdc, int width, int height)
	{
		DrawBackground(hdc, width, height);

		int boardX0 = (int)round(height * offset);
		int boardY0 = boardX0;
		int boardWidth = (int)round(height - 2 * height * offset);
		
		DrawBoard(hdc, boardX0, boardY0, boardWidth);
		DrawFigures(hdc, boardX0, boardY0, boardWidth);
	}

private:

	void DrawBackground(HDC hdc, int width, int height)
	{
		if (hBackground == NULL) return;

		HDC hdcMem = CreateCompatibleDC(hdc);
		SelectObject(hdcMem, hBackground);

		StretchBlt(hdc, 0, 0, width, height, hdcMem, 0, 0, bgWidth, bgHeight, SRCCOPY);
		
		DeleteDC(hdcMem);
	}

	void DrawBoard(HDC hdc, int x0, int y0, int width)
	{
		if (hBoard == NULL) return;

		HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP oldBM = (HBITMAP)SelectObject(hdcMem, hBoard);

		bool f = StretchBlt(hdc, x0, y0, width, width, hdcMem, 0, 0, brdWidth, brdWidth, SRCCOPY);
		
		SelectObject(hdcMem, hBoard);
		DeleteDC(hdcMem);
	}

	void DrawFigures(HDC hdc, int boardX0, int boardY0, int boardWidth)
	{
		HDC hdcMem = CreateCompatibleDC(hdc);

		float fieldWidth = (float)(h1Corner - a8Corner) * boardWidth / brdWidth / 8;
		int xOffset = a8Corner * boardWidth / brdWidth + boardX0;
		int yOffset = a8Corner * boardWidth / brdWidth + boardY0;

		// установка полей
		this->activeX = xOffset;
		this->activeY = yOffset;
		this->activeWidth = boardWidth;
		// установка полей

		for (int i = a1; i <= h8; i++)
			if ((i != selectedField) && ((*position)[i] != e)) // обычная отрисовка
			{
				SelectObject(hdcMem, hFigures[(*position)[i]]);

				int xField = (int)round(xOffset + (Letter(i)) * fieldWidth);
				int yField = side == white ? (int)round(yOffset + (7 - Number0to7(i)) * fieldWidth)
					: (int)round(yOffset + Number0to7(i) * fieldWidth);

				TransparentBlt(hdc, xField, yField, fieldWidth, fieldWidth, hdcMem, 0, 0, fgrWidth, fgrWidth, RGB(255, 0, 0));
			}

		// отрисовка в случае перетаскивания
		if ((selectedField != unrealField) &&
			((*position)[selectedField] != e))
		{
			SelectObject(hdcMem, hFigures[(*position)[selectedField]]);

			POINT cursorPos;
			GetCursorPos(&cursorPos);
			ScreenToClient(FindWindow(L"Polaris", L"Polaris"), &cursorPos);
			TransparentBlt(hdc,
				cursorPos.x - fieldWidth / 2,
				cursorPos.y - fieldWidth / 2,
				fieldWidth,
				fieldWidth,
				hdcMem,
				0, 0, fgrWidth, fgrWidth, RGB(255, 0, 0));
		}

		DeleteDC(hdcMem);
	}
};

class MoveController
{
private:
	Drawer* drawer = NULL; // для получения активной области доски
	MoveGenerator* generator = NULL; // для получения корректных ходов
	Position* position = NULL;

	int activeX = 0;
	int activeY = 0;
	int activeWidth = 0; // активная область доски

	int predXDown = 0;
	int predYDown = 0; // координаты предыдущего клика

	int xDown = 0;
	int yDown = 0; // координаты последнего ужатия

	int xUp = 0;
	int yUp = 0; // координаты последнего отпускания

	bool isMouseDown; // ужата ли ЛКМ

public:
	MoveController(Position* position, Drawer* drawer, MoveGenerator* generator)
	{
		this->position = position;
		this->drawer = drawer;
		this->generator = generator;
		UpdateActiveBoard();
	}

	Move* LButtonDown(int x, int y)
	{
		UpdateActiveBoard();

		this->isMouseDown = true;
		drawer->SetSelectedField(GetField(x, y));

		if ((x >= activeX) && (x <= activeX + activeWidth) &&
			(y >= activeY) && (y <= activeY + activeWidth))
		{
			this->predXDown = this->xDown;
			this->predYDown = this->yDown;

			this->xDown = x;
			this->yDown = y;

			return GetMove();
		}
		return NULL;
	}

	Move* LButtonUp(int x, int y)
	{
		this->isMouseDown = false;
		drawer->SetSelectedField(unrealField);
		return NULL;
	}

private:

	void UpdateActiveBoard()
	{
		activeX = drawer->GetActiveX();
		activeY = drawer->GetActiveY();
		activeWidth = drawer->GetActiveWidth();
	}

	Move* GetMove()
	{
		int fieldFrom = GetField(predXDown, predYDown);
		int fieldTo = GetField(xDown, yDown);
		
		list<Move>* moves = generator->Generate(position);
		
		for (int i = 0; i < moves->size(); i++)
		{
			Move move = get(*moves, i);
			if ((move.from == fieldFrom) && (move.to == fieldTo))
				return &move;
		}

		return NULL;
	}

	int GetField(int x, int y) // получить поле по координате на доске
	{
		float fieldWidth = (float)activeWidth / 8;
		int letter = (int)floor((x - activeX) / fieldWidth);
		int number = (int)ceil(7 - (y - activeY) / fieldWidth);
		return Field(letter, number);
	}
};

#define BORDERWIDTH 0
#define BORDERHEIGHT 62

// глобальные переменные
const int screenWidth = GetSystemMetrics(SM_CXSCREEN);  // разрешение экрана по горизонтали
const int screenHeight = GetSystemMetrics(SM_CYSCREEN); // разрешение экрана по вертикали
const float screenProportions = (float)screenWidth / screenHeight; // пропорции экрана

Position* position = new Position();
Drawer* drawer = new Drawer(position);
MoveGenerator* generator = new MoveGenerator();
MoveController* controller = new MoveController(position, drawer, generator);
// глобальные переменные


// Прототип функции обработки сообщений с пользовательским названием:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR mainMessage[] = L"Какой то-текст!"; // строка с сообщением

// Управляющая функция:
int WINAPI WinMain(HINSTANCE hInst, // дескриптор экземпляра приложения
	HINSTANCE hPrevInst, // не используем
	LPSTR lpCmdLine, // не используем
	int nCmdShow) // режим отображения окошка
{
	TCHAR szClassName[] = L"Polaris"; // строка с именем класса
	HWND hWnd; // создаём дескриптор будущего окошка
	MSG msg; // создём экземпляр структуры MSG для обработки сообщений

	WNDCLASSEX wc; // создаём экземпляр, для обращения к членам класса WNDCLASSEX
	wc.cbSize = sizeof(wc); // размер структуры (в байтах)
	wc.style = CS_HREDRAW | CS_VREDRAW; // стиль класса окошка
	wc.lpfnWndProc = WndProc; // указатель на пользовательскую функцию
	wc.lpszMenuName = NULL; // указатель на имя меню (у нас его нет)
	wc.lpszClassName = szClassName; // указатель на имя класса
	wc.cbWndExtra = NULL; // число освобождаемых байтов в конце структуры
	wc.cbClsExtra = NULL; // число освобождаемых байтов при создании экземпляра приложения
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO); // декриптор пиктограммы
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO); // дескриптор маленькой пиктограммы (в трэе)
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // дескриптор курсора
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // дескриптор кисти для закраски фона окна
	wc.hInstance = hInst; // указатель на строку, содержащую имя меню, применяемого для класса
	RegisterClassEx(&wc);

	hWnd = CreateWindow(
		szClassName, // имя класса
		L"Polaris", // имя окошка (то что сверху)
		WS_TILEDWINDOW, // режимы отображения окошка
		CW_USEDEFAULT, // позиция окошка по оси х
		NULL, // позиция окошка по оси у (раз дефолт в х, то писать не нужно)
		screenWidth / 2, // ширина окошка
		screenHeight / 2, // высота окошка (раз дефолт в ширине, то писать не нужно)
		(HWND)NULL, // дескриптор родительского окна
		NULL, // дескриптор меню
		HINSTANCE(hInst), // дескриптор экземпляра приложения
		NULL); // ничего не передаём из WndProc

	// создание менюшки
	HMENU hMenu = CreateMenu();
	HMENU hMenuFile = CreatePopupMenu();

	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hMenuFile, L"Файл");

	AppendMenu(hMenuFile, MF_STRING, 11, L"Открыть партию");
	AppendMenu(hMenuFile, MF_STRING, 12, L"Сохранить партию");
	AppendMenu(hMenuFile, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hMenuFile, MF_STRING, 13, L"Открыть позицию");
	AppendMenu(hMenuFile, MF_STRING, 14, L"Сохранить позицию");

	SetMenu(hWnd, hMenu);
	SetMenu(hWnd, hMenuFile);
	// создание менюшки

	// настройка рисовальщика
	drawer->SetBackground(L"pics\\backgrounds\\wood.bmp");
	drawer->SetBoard(L"pics\\boards\\board1.bmp");
	drawer->SetFigures(L"pics\\figures\\pixel");
	drawer->SetSide(white);
	// настройка рисовальщика

	ShowWindow(hWnd, nCmdShow); // отображаем окошко
	UpdateWindow(hWnd); // обновляем окошко

	while (GetMessage(&msg, NULL, NULL, NULL)) { // извлекаем сообщения из очереди, посылаемые фу-циями, ОС
		TranslateMessage(&msg); // интерпретируем сообщения
		DispatchMessage(&msg); // передаём сообщения обратно ОС
	}

	return msg.wParam; // возвращаем код выхода из приложения
}

// глобальные переменные для работы WndProc
RECT oldClientRect;
// глобальные переменные для работы WndProc

LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	HDC hDC, hCmpDC;
	PAINTSTRUCT ps;
	RECT clientRect, windowRect;
	HBITMAP hBmp;
	int windowWidth, windowHeight;
	int clientWidth, clientHeight;

	switch (Msg)
	{
	case WM_CREATE:
	{
		SetTimer(hWnd, 0, 100, NULL);
		return 0;
	}
	case WM_PAINT:
	{
		GetClientRect(hWnd, &clientRect);
		windowWidth = clientRect.right - clientRect.left;
		windowHeight = clientRect.bottom - clientRect.top;

		hDC = BeginPaint(hWnd, &ps);

		// Создание теневого контекста для двойной буферизации
		hCmpDC = CreateCompatibleDC(hDC);
		hBmp = CreateCompatibleBitmap(hDC, windowWidth, windowHeight);
		SelectObject(hCmpDC, hBmp);
		// Создание теневого контекста для двойной буферизации

		// Рисуем
		drawer->Draw(hCmpDC, windowWidth, windowHeight);
		// Рисуем

		// Копируем изображение из теневого контекста на экран
		SetStretchBltMode(hDC, COLORONCOLOR);
		BitBlt(hDC, 0, 0, windowWidth, windowHeight, hCmpDC, 0, 0, SRCCOPY);
		// Копируем изображение из теневого контекста на экран

		// Удаляем ненужные системные объекты
		DeleteDC(hCmpDC);
		DeleteObject(hBmp);
		hCmpDC = NULL;
		// Удаляем ненужные системные объекты

		EndPaint(hWnd, &ps);
		return 0;
	}
	case WM_SIZE:
	{
		int oldWidth = oldClientRect.right - oldClientRect.left;
		int oldHeight = oldClientRect.bottom - oldClientRect.top;

		GetClientRect(hWnd, &oldClientRect);
		int clientWidth = oldClientRect.right - oldClientRect.left;
		int clientHeight = oldClientRect.bottom - oldClientRect.top;

		bool isWidthChanged = (oldWidth == clientWidth) ? false : true;
		bool isHeightChanged = (oldHeight == clientHeight) ? false : true;

		if (isWidthChanged || isHeightChanged)
		{
			int newWidth = clientWidth;
			int newHeight = clientHeight;

			if (isWidthChanged) newHeight = (int)round(clientWidth / screenProportions);
			else newWidth = (int)round(clientHeight * screenProportions);

			SetWindowPos(hWnd, hWnd, 0, 0, newWidth + 16, newHeight + 59, SWP_NOZORDER | SWP_NOMOVE);
		}
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		Move* move = controller->LButtonDown(LOWORD(lParam), HIWORD(lParam));
		if (move != NULL) position->Move(*move);
		InvalidateRect(hWnd, NULL, false);
		return 0;
	}
	case WM_LBUTTONUP:
	{
		Move* move = controller->LButtonUp(LOWORD(lParam), HIWORD(lParam));
		if (move != NULL) position->Move(*move);
		InvalidateRect(hWnd, NULL, false);
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		InvalidateRect(hWnd, NULL, false);
		return 0;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}