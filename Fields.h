// возвращает поле по букве и цифе
#define Field(l, n) ( ((l) >= 0 && (l) <= 7 && (n) >= 0 && (n) <=7 ) ? ((l) + (n) * 8) : (unrealField) )

// определение горизонтали поля
#define Number(field) ( (field) / 8 + 1 )
#define Number0to7(field) ( (field) / 8 )

// определение вертикали поля a - 0, ..., h - 7
#define Letter(field) ( (field) % 8 )

// возвращает новое поле по текущему полю, смещению по l, смещению по n
#define OffsetField(f, l, n) ( Field(Letter(f) + l, Number0to7(f) + n) )

#define unrealField -1

#define a1 0
#define b1 1
#define c1 2
#define d1 3
#define e1 4
#define f1 5
#define g1 6
#define h1 7

#define a2 8
#define b2 9
#define c2 10
#define d2 11
#define e2 12
#define f2 13
#define g2 14
#define h2 15

#define a3 16
#define b3 17
#define c3 18
#define d3 19
#define e3 20
#define f3 21
#define g3 22
#define h3 23

#define a4 24
#define b4 25
#define c4 26
#define d4 27
#define e4 28
#define f4 29
#define g4 30
#define h4 31

#define a5 32
#define b5 33
#define c5 34
#define d5 35
#define e5 36
#define f5 37
#define g5 38
#define h5 39

#define a6 40
#define b6 41
#define c6 42
#define d6 43
#define e6 44
#define f6 45
#define g6 46
#define h6 47

#define a7 48
#define b7 49
#define c7 50
#define d7 51
#define e7 52
#define f7 53
#define g7 54
#define h7 55

#define a8 56
#define b8 57
#define c8 58
#define d8 59
#define e8 60
#define f8 61
#define g8 62
#define h8 63
