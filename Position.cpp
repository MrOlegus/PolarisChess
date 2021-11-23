//#include "Position.h"
//
//#include "Figures.h"
//#include "Fields.h"
//#include "Move.cpp"
//
//using namespace std;
//
//class Position {
//	public: // индексатор
//		int operator [] (int index)
//		{
//			return fields[index];
//		}
//
//	private:
//		int fields[64];
//
//	public:
//		Position()
//		{
//			this->Reset();
//		}
//
//		Position Clear()
//		{
//			for (int i = 0; i < 8; i++)
//				for (int j = 0; j < 8; j++)
//					fields[Field(i, j)] = e;
//			return *this;
//		}
//
//		Position Reset()
//		{
//			fields[a1] = r; fields[a8] = R;
//			fields[b1] = n; fields[b8] = N;
//			fields[c1] = b; fields[c8] = B;
//			fields[d1] = q; fields[d8] = Q;
//			fields[e1] = k; fields[e8] = K;
//			fields[f1] = b; fields[f8] = B;
//			fields[g1] = n; fields[g8] = N;
//			fields[h1] = r; fields[h8] = R;
//
//			fields[a2] = p; fields[a7] = P;
//			fields[b2] = p; fields[b7] = P;
//			fields[c2] = p; fields[c7] = P;
//			fields[d2] = p; fields[d7] = P;
//			fields[e2] = p; fields[e7] = P;
//			fields[f2] = p; fields[f7] = P;
//			fields[g2] = p; fields[g7] = P;
//			fields[h2] = p; fields[h7] = P;
//
//			return *this;
//		}
//};