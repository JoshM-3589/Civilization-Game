## FUNCTIONS 
void TypeText(char *text, int delay);
void MenuChoice(int *choice);
void Intro();
void ExitGame();
void clearText(int row, int col, int length);
void MainGame(Player *p1);
void Tutorial(Player *p);
void Item(Player *p); 
void Skills();
void Stats(); 
int Selector(const int Esize, Enemy e1[], const char *type[]);
void Attack(Player *p, int SelectedEnem, Enemy e1[], const char *type[]);
item *makeItem(char *name, char *desc, int qty, Itemtype type);
void viewInventory(inventory *i1);
inventory *makeInventory(item *i, int Count, int Capacity, int page);
inventory *addItem(inventory *inv, item *newItem);
void clearScreen();
int interactiveMenu(int *imchoice);

## STRUCTURE 
typedef enum{
    PUNCH,
    KICK, 
    HEADBUTT, //Deals tons of Damage but will deal Self Damage
    RUN, //Random Chance ONLY


}AttackType0; //DEFAULT: FIST

typedef enum{
    SMASH, 
    THROW,

}AttackType1; //Throwable equipments (Stone)

typedef enum{
    SLASH,
    STAB, 
    TOSS,
}AttackType2; //Spears & Swords

typedef enum{
    HEAL, 
    DAMAGE_BOOST,
    BUFF,
    EQUIPMENT,
}Itemtype;

typedef struct item{
    char itemName[50];
    char Desc[100];
    int Qty; 
    Itemtype itype;
    struct item *next;
}item;

typedef struct inventory{
    item *head;
    int invCount; 
    int capacity;
    int page;
    struct inventory *next;

}inventory;

typedef enum {
   STONE,
   BRONZE,
   IRON,
   

}Era;
typedef enum{
    MELEE,
    RANGE,
    TANK,
    WITCH,


}EnemyType;

typedef struct {
    int lvl;
    char era[20];
    
}Level;

typedef struct{
    int damage;
    int hp;
    EnemyType Type;
    Level Enemylvl;
    
}Enemy; 

typedef struct {
   double Gold; 
   float increaseRate;
   
   
}Currency;



typedef struct {
    int hp;
    int dmg;
    char Name[50]; 
    Level level;
    Currency Current; 
    Era lvlEra;
    

}Player;


## QUICK RUNDOWN
A CLI Game RPG Like Civilization Game



**bold**  *italic*  `inline code`

- bullet item
- another item

1. numbered
2. list

