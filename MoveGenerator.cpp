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
//		// ���������� � ������ ����� ������ ��� ����� �����
//		static void GenerateKingMoves(list<Move>* moves, Position* position, int field, bool isKingMoved, bool isRookAMoved, bool isRookHMoved)
//		{
//			int color = Color(field);
//
//			// ��������� ��� �������� ������
//			for(int i = -1; i <= 1; i++)
//				for (int j = -1; j <= 1; j++)
//					if ((i != 0) || (j != 0))
//					{
//						int fieldTo = OffsetField(field, i, j);
//						if (fieldTo == unrealField) continue;
//
//						// ������ ��� ������ ����� �� ����, ���� ������� ��������
//						int onFieldTo = (*position)[fieldTo];
//
//						// ���� �� ���� �� ������ ������ �����, ��������� � ��������� ����
//						if ((onFieldTo == e) ||
//							(color != Color(onFieldTo)))
//						{
//							moves->push_back(Move(field, fieldTo, (*position)[field]));
//						}
//					}
//
//			// �������� ��������� ���������
//			if ((!isKingMoved) && (!isRookHMoved))
//			{
//				if (((*position)[OffsetField(field, 1, 0)] == e) &&
//					((*position)[OffsetField(field, 2, 0)] == e))
//				{
//					moves->push_back(Move(field, OffsetField(field, 2, 0), (*position)[field]));
//				}
//			}
//
//			// ������� ��������� ���������
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
//		// ���������� � ������ ����� ���� ��� ����� �����
//		static void GenerateKnightMoves(list<Move>* moves, Position* position, int field)
//		{
//			int color = Color(field);
//
//			// ��������� 8 ������ ������ ����
//			for (int i = -2; i <= 2; i++)
//				for (int j = -2; j <= 2; j++)
//					if ((i != 0) && (j != 0) && (abs(i) != abs(j)))
//					{
//						int fieldTo = OffsetField(field, i, j);
//						if (fieldTo == unrealField) continue;
//
//						// ������ ��� ������ ����� �� ����, ���� ������� ��������
//						int onFieldTo = (*position)[fieldTo];
//
//						// ���� �� ���� �� ������ ������ �����, ��������� � ��������� ����
//						if ((onFieldTo == e) ||
//							(color != Color(onFieldTo)))
//						{
//							moves->push_back(Move(field, fieldTo, (*position)[field]));
//						}
//					}
//		}
//
//		// ���������� � ������ ����� ����� ��� ����� �����
//		static void GenerateRookMoves(list<Move>* moves, Position* position, int field)
//		{
//			int color = Color(field);
//
//			// ��������� ������ �� ������� ������������
//			for (int i = -1; i <= 1; i++)
//				for (int j = -1; j <= 1; j++)
//					if ((i == 0) ^ (j == 0))
//					{
//						int fieldTo = field;
//						while ((fieldTo = OffsetField(fieldTo, i, j)) != unrealField);
//						{
//							// ������ ��� ������ ����� �� ����, ���� ������� ��������
//							int onFieldTo = (*position)[fieldTo];
//
//							// ���� �� ���� �� ������ ������ �����, ��������� � ��������� ����
//							if ((onFieldTo == e) ||
//								(color != Color(onFieldTo)))
//							{
//								moves->push_back(Move(field, fieldTo, (*position)[field]));
//							}
//							else // ���������� �� ���� ������ - ������� �� �����
//								break;
//						}
//					}
//		}
//
//		// ���������� � ������ ����� ����� ��� ����� �����
//		static void GenerateBishopMoves(list<Move>* moves, Position* position, int field)
//		{
//			int color = Color(field);
//
//			// ��������� ������ �� ������� ������������
//			for (int i = -1; i <= 1; i++)
//				for (int j = -1; j <= 1; j++)
//					if ((i != 0) && (j != 0))
//					{
//						int fieldTo = field;
//						while ((fieldTo = OffsetField(fieldTo, i, j)) != unrealField);
//						{
//							// ������ ��� ������ ����� �� ����, ���� ������� ��������
//							int onFieldTo = (*position)[fieldTo];
//
//							// ���� �� ���� �� ������ ������ �����, ��������� � ��������� ����
//							if ((onFieldTo == e) ||
//								(color != Color(onFieldTo)))
//							{
//								moves->push_back(Move(field, fieldTo, (*position)[field]));
//							}
//							else // ���������� �� ���� ������ - ������� �� �����
//								break;
//						}
//					}
//		}
//
//		// ���������� � ������ ����� ����� ��� ����� �����
//		static void GenerateQueenMoves(list<Move>* moves, Position* position, int field)
//		{
//			GenerateRookMoves(moves, position, field);
//			GenerateBishopMoves(moves, position, field);
//		}
//
//		// ���������� � ������ ����� ����� ��� ����� �����
//		static void GeneratePawnMoves(list<Move>* moves, Position* position, int field, Move lastMove)
//		{
//			int color = Color(field);
//			int dir = (color == white) ? 1 : -1; // ����������� �������� �����
//			int hor = Number(field); // �����������, �� ������� ����� �����
//
//			// ��� ����� �� ���� ���� ��� �����������
//			if ((hor + dir != 1) && (hor + dir != 8))
//			{
//				int fieldTo = OffsetField(field, 0, 2 * dir);
//				int onFieldTo = (*position)[fieldTo];
//
//				// ���� ���� ������, ��������� � ��������� ����
//				if (onFieldTo == e)
//				{
//					moves->push_back(Move(field, fieldTo, (*position)[field]));
//				}
//			}
//
//			// ��� ����� �� ���� ���� � ������������
//			if ((hor + dir == 1) || (hor + dir == 8))
//			{
//				int fieldTo = OffsetField(field, 0, 2 * dir);
//				int onFieldTo = (*position)[fieldTo];
//
//				// ���� ���� ������, ��������� � ��������� ����
//				if (onFieldTo == e)
//				{
//					moves->push_back(Move(field, fieldTo, Figure(q, color)));
//					moves->push_back(Move(field, fieldTo, Figure(r, color)));
//					moves->push_back(Move(field, fieldTo, Figure(b, color)));
//					moves->push_back(Move(field, fieldTo, Figure(n, color)));
//				}
//			}
//
//			// ��� ����� �� ��� ���� ������
//			if (((hor == 2) && (color == white)) ||
//				((hor == 7) && (color == black)))
//			{
//				int fieldBetween = OffsetField(field, 0, dir);
//				int onFieldBetween = (*position)[fieldBetween];
//
//				int fieldTo = OffsetField(field, 0, 2 * dir);
//				int onFieldTo = (*position)[fieldTo];
//				
//				// ���� ������ ����� ����� ������
//				if (onFieldBetween == e)
//				// ���� ���� ������, ��������� � ��������� ����
//				if (onFieldTo == e)
//				{
//					moves->push_back(Move(field, fieldTo, (*position)[field]));
//				}
//			}
//
//			// ��� ��� �����������
//			if ((hor + dir != 1) && (hor + dir != 8))
//			{
//				for (int i = -1; i <= 1; i += 2)
//				{
//					int fieldTo = OffsetField(field, i, dir);
//					if (fieldTo == unrealField) continue;
//					int onFieldTo = (*position)[fieldTo];
//
//					if ((onFieldTo != e) && (color != Color(onFieldTo))) // ���� �� ���� ����� ������
//					{
//						moves->push_back(Move(field, fieldTo, (*position)[field]));
//					}
//				}
//			}
//
//			// ��� � ������������
//			if ((hor + dir == 1) && (hor + dir == 8))
//			{
//				for (int i = -1; i <= 1; i += 2)
//				{
//					int fieldTo = OffsetField(field, i, dir);
//					if (fieldTo == unrealField) continue;
//					int onFieldTo = (*position)[fieldTo];
//
//					if ((onFieldTo != e) && (color != Color(onFieldTo))) // ���� �� ���� ����� ������
//					{
//						moves->push_back(Move(field, fieldTo, Figure(q, color)));
//						moves->push_back(Move(field, fieldTo, Figure(r, color)));
//						moves->push_back(Move(field, fieldTo, Figure(b, color)));
//						moves->push_back(Move(field, fieldTo, Figure(n, color)));
//					}
//				}
//			}
//
//			// ������ �� �������
//			if ((lastMove.figure == p) ||
//				(lastMove.figure == P))
//			if (((hor == 5) && (color == white)) ||
//				((hor == 4) && (color == black)))
//			{
//				for (int i = -1; i <= 1; i += 2)
//				{
//					// ����� ������ ��� ���� ��������� ��� ��� ����������� ������ �� �������
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