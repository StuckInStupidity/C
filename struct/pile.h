#ifndef DEF_PILE
#define DEF_PILE

typedef struct Element Element;

struct Element
{
	int nombre;
	Element* suivant;
};

typedef struct Pile Pile;

struct Pile
{
	Element *premier;
};

#endif // !DEF_PILE