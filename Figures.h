// 0 - white, 1 - black
#define Color(figure) (figure % 2)

// ���������� ������ ������� ����� �� ����� ������ � �����
#define Figure(figure, color) ( figure - color )

// ���������� ������ char �� �����
#define FigureToChar(n) ( n == 2 ? 'p' : n == 4 ? 'r' : n == 6 ? 'n' : n == 8 ? 'b' : n == 10 ? 'q' : n == 12 ? 'k' : n == 1 ? 'P' : n == 3 ? 'R' : n == 5 ? 'N' : n == 7 ? 'B' : n == 9 ? 'Q' : n == 11 ? 'K' : 'e')

// ������ ����
#define e 0

// ����� ������ - ������
#define p 2
#define r 4
#define n 6
#define b 8
#define q 10
#define k 12

// ������ ������ - ��������
#define P 1
#define R 3
#define N 5
#define B 7
#define Q 9
#define K 11