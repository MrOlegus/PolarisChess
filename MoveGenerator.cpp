//#include "Colors.h"
//#include "Move.cpp"
//#include "Position.cpp"
//#include <list>
//
//using namespace std;
//
//static class MoveGenerator {
//	public:
//		static list<Move>* Generate(Position* position, Move lastMove, bool isKingMoved, bool isRookAMoved, bool isRookHMoved)
//		{
//			list<Move>* moves;
//
//			int color = Color(lastMove.figure) ^ 1;
//			
//			for (int i = a1; i <= h8; i++)
//				if (Color((*position)[i]) == color)
//					switch ((*position)[i]) {
//					case r: case R:
//						GenerateRookMoves(moves, position, i);
//						break;
//					case n: case N:
//						GenerateKnightMoves(moves, position, i);
//						break;
//					case b: case B:
//						GenerateBishopMoves(moves, position, i);
//						break;
//					case q: case Q:
//						GenerateQueenMoves(moves, position, i);
//						break;
//					case k: case K:
//						GenerateKingMoves(moves, position, i, isKingMoved, isRookAMoved, isRookHMoved);
//						break;
//					case p: case P:
//						GeneratePawnMoves(moves, position, i, lastMove);
//						break;
//					}
//			return moves;
//		}
//
//	private:
//		// добавление в список ходов короля без учета шахов
//		static void GenerateKingMoves(list<Move>* moves, Position* position, int field, bool isKingMoved, bool isRookAMoved, bool isRookHMoved)
//		{
//			int color = Color(field);
//
//			// проверяем все соседние клетки
//			for(int i = -1; i <= 1; i++)
//				for (int j = -1; j <= 1; j++)
//					if ((i != 0) || (j != 0))
//					{
//						int fieldTo = OffsetField(field, i, j);
//						if (fieldTo == unrealField) continue;
//
//						// фигура или пустое место на поле, куда пробуем походить
//						int onFieldTo = (*position)[fieldTo];
//
//						// если на поле не фигура своего цвета, добавляем в возможные ходы
//						if ((onFieldTo == e) ||
//							(color != Color(onFieldTo)))
//						{
//							moves->push_back(Move(field, fieldTo, (*position)[field]));
//						}
//					}
//
//			// короткая рокировка ИСПРАВИТЬ
//			if ((!isKingMoved) && (!isRookHMoved))
//			{
//				if (((*position)[OffsetField(field, 1, 0)] == e) &&
//					((*position)[OffsetField(field, 2, 0)] == e))
//				{
//					moves->push_back(Move(field, OffsetField(field, 2, 0), (*position)[field]));
//				}
//			}
//
//			// длинная рокировка ИСПРАВИТЬ
//			if ((!isKingMoved) && (!isRookAMoved))
//			{
//				if (((*position)[OffsetField(field, -1, 0)] == e) &&
//					((*position)[OffsetField(field, -2, 0)] == e))
//				{
//					moves->push_back(Move(field, OffsetField(field, -2, 0), (*position)[field]));
//				}
//			}
//		}
//
//		// добавление в список ходов коня без учета шахов
//		static void GenerateKnightMoves(list<Move>* moves, Position* position, int field)
//		{
//			int color = Color(field);
//
//			// проверяем 8 клеток вокруг поля
//			for (int i = -2; i <= 2; i++)
//				for (int j = -2; j <= 2; j++)
//					if ((i != 0) && (j != 0) && (abs(i) != abs(j)))
//					{
//						int fieldTo = OffsetField(field, i, j);
//						if (fieldTo == unrealField) continue;
//
//						// фигура или пустое место на поле, куда пробуем походить
//						int onFieldTo = (*position)[fieldTo];
//
//						// если на поле не фигура своего цвета, добавляем в возможные ходы
//						if ((onFieldTo == e) ||
//							(color != Color(onFieldTo)))
//						{
//							moves->push_back(Move(field, fieldTo, (*position)[field]));
//						}
//					}
//		}
//
//		// добавление в список ходов ладьи без учета шахов
//		static void GenerateRookMoves(list<Move>* moves, Position* position, int field)
//		{
//			int color = Color(field);
//
//			// проверяем клетки по четырем направлениям
//			for (int i = -1; i <= 1; i++)
//				for (int j = -1; j <= 1; j++)
//					if ((i == 0) ^ (j == 0))
//					{
//						int fieldTo = field;
//						while ((fieldTo = OffsetField(fieldTo, i, j)) != unrealField);
//						{
//							// фигура или пустое место на поле, куда пробуем походить
//							int onFieldTo = (*position)[fieldTo];
//
//							// если на поле не фигура своего цвета, добавляем в возможные ходы
//							if ((onFieldTo == e) ||
//								(color != Color(onFieldTo)))
//							{
//								moves->push_back(Move(field, fieldTo, (*position)[field]));
//							}
//							else // наткнулись на свою фигуру - выходим из цикла
//								break;
//						}
//					}
//		}
//
//		// добавление в список ходов слона без учета шахов
//		static void GenerateBishopMoves(list<Move>* moves, Position* position, int field)
//		{
//			int color = Color(field);
//
//			// проверяем клетки по четырем направлениям
//			for (int i = -1; i <= 1; i++)
//				for (int j = -1; j <= 1; j++)
//					if ((i != 0) && (j != 0))
//					{
//						int fieldTo = field;
//						while ((fieldTo = OffsetField(fieldTo, i, j)) != unrealField);
//						{
//							// фигура или пустое место на поле, куда пробуем походить
//							int onFieldTo = (*position)[fieldTo];
//
//							// если на поле не фигура своего цвета, добавляем в возможные ходы
//							if ((onFieldTo == e) ||
//								(color != Color(onFieldTo)))
//							{
//								moves->push_back(Move(field, fieldTo, (*position)[field]));
//							}
//							else // наткнулись на свою фигуру - выходим из цикла
//								break;
//						}
//					}
//		}
//
//		// добавление в список ходов ферзя без учета шахов
//		static void GenerateQueenMoves(list<Move>* moves, Position* position, int field)
//		{
//			GenerateRookMoves(moves, position, field);
//			GenerateBishopMoves(moves, position, field);
//		}
//
//		// добавление в список ходов пешек без учета шахов
//		static void GeneratePawnMoves(list<Move>* moves, Position* position, int field, Move lastMove)
//		{
//			int color = Color(field);
//			int dir = (color == white) ? 1 : -1; // направление движения пешки
//			int hor = Number(field); // горизонталь, на которой стоит пешка
//
//			// ход пешки на одно поле без превращений
//			if ((hor + dir != 1) && (hor + dir != 8))
//			{
//				int fieldTo = OffsetField(field, 0, 2 * dir);
//				int onFieldTo = (*position)[fieldTo];
//
//				// если поле пустое, добавляем в возможные ходы
//				if (onFieldTo == e)
//				{
//					moves->push_back(Move(field, fieldTo, (*position)[field]));
//				}
//			}
//
//			// ход пешки на одно поле с превращением
//			if ((hor + dir == 1) || (hor + dir == 8))
//			{
//				int fieldTo = OffsetField(field, 0, 2 * dir);
//				int onFieldTo = (*position)[fieldTo];
//
//				// если поле пустое, добавляем в возможные ходы
//				if (onFieldTo == e)
//				{
//					moves->push_back(Move(field, fieldTo, Figure(q, color)));
//					moves->push_back(Move(field, fieldTo, Figure(r, color)));
//					moves->push_back(Move(field, fieldTo, Figure(b, color)));
//					moves->push_back(Move(field, fieldTo, Figure(n, color)));
//				}
//			}
//
//			// ход пешки на два поля вперед
//			if (((hor == 2) && (color == white)) ||
//				((hor == 7) && (color == black)))
//			{
//				int fieldBetween = OffsetField(field, 0, dir);
//				int onFieldBetween = (*position)[fieldBetween];
//
//				int fieldTo = OffsetField(field, 0, 2 * dir);
//				int onFieldTo = (*position)[fieldTo];
//				
//				// если клетка после пешки пустая
//				if (onFieldBetween == e)
//				// если поле пустое, добавляем в возможные ходы
//				if (onFieldTo == e)
//				{
//					moves->push_back(Move(field, fieldTo, (*position)[field]));
//				}
//			}
//
//			// бой без превращения
//			if ((hor + dir != 1) && (hor + dir != 8))
//			{
//				for (int i = -1; i <= 1; i += 2)
//				{
//					int fieldTo = OffsetField(field, i, dir);
//					if (fieldTo == unrealField) continue;
//					int onFieldTo = (*position)[fieldTo];
//
//					if ((onFieldTo != e) && (color != Color(onFieldTo))) // если на поле чужая фигура
//					{
//						moves->push_back(Move(field, fieldTo, (*position)[field]));
//					}
//				}
//			}
//
//			// бой с превращением
//			if ((hor + dir == 1) && (hor + dir == 8))
//			{
//				for (int i = -1; i <= 1; i += 2)
//				{
//					int fieldTo = OffsetField(field, i, dir);
//					if (fieldTo == unrealField) continue;
//					int onFieldTo = (*position)[fieldTo];
//
//					if ((onFieldTo != e) && (color != Color(onFieldTo))) // если на поле чужая фигура
//					{
//						moves->push_back(Move(field, fieldTo, Figure(q, color)));
//						moves->push_back(Move(field, fieldTo, Figure(r, color)));
//						moves->push_back(Move(field, fieldTo, Figure(b, color)));
//						moves->push_back(Move(field, fieldTo, Figure(n, color)));
//					}
//				}
//			}
//
//			// взятие на проходе
//			if ((lastMove.figure == p) ||
//				(lastMove.figure == P))
//			if (((hor == 5) && (color == white)) ||
//				((hor == 4) && (color == black)))
//			{
//				for (int i = -1; i <= 1; i += 2)
//				{
//					// какой должен был быть последний ход для возможности взятия на проходе
//					int lastFieldFrom = OffsetField(field, i, -2 * dir);
//					int lastFieldTo = OffsetField(field, i, 0);
//
//					if ((lastMove.from == lastFieldFrom) &&
//						(lastMove.to == lastFieldTo))
//					{
//						int fieldTo = OffsetField(field, i, dir);
//						moves->push_back(Move(field, fieldTo, Figure(p, color)));
//					}
//				}
//			}
//		}
//};