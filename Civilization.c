
#include<stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#define INVCAP 10
#define DTalk 50000
#define EnSize 4

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
typedef struct{
    int EnemyCount;
    Enemy En[EnSize]; 
    Era EnlvlEra;
    int waveCount;

}EnemyStack;

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
int viewInventory(inventory *i1);
inventory *makeInventory(item *i, int Count, int Capacity, int page);
inventory *addItem(inventory *inv, item *newItem);
void clearScreen();
int interactiveMenu(int *imchoice);
void displayEnemy(const int Esize, Enemy e1[], const char *type[]);
EnemyStack makeEnemy()

void displayEnemy(const int Esize, Enemy e1[], const char *type[]){
    int i = 0;
    printf("==================================================\n");
    printf("| [%d] Enemy %d %s          [%d] Enemy %d %s   |\n", i + 1, i + 1, type[e1[i].Type], i + 2, i + 2, type[e1[i + 1].Type]);
    printf("|  HP: %d                      HP:%d             |\n", e1[i].hp, e1[i+1].hp);
    printf("| [%d] Enemy %d %s          [%d] Enemy %d %s    |\n", i + 3, i + 3, type[e1[i + 2].Type], i + 4, i + 4, type[e1[i + 3].Type]);
    printf("|  HP: %d                      HP:%d             |\n", e1[i].hp, e1[i+1].hp);
    printf("==================================================\n");
}

int interactiveMenu(int *imchoice){
    printf("==================================================\n");
    printf("| [1] ATTACK                  [2] SKILLS         |\n");
    printf("| [3] ITEMS                   [3] STATS          |\n");
    printf("==================================================\n");
    TypeText("Your Turn: ", 5000);
    return scanf("%d", imchoice);
}

void clearScreen(){
    system("cls");

}


inventory *makeInventory(item *i, int Count, int Capacity, int page){
    inventory *inv = malloc(sizeof(inventory)); 
    if(inv == NULL)return NULL;
    
    inv->head = i;
    inv->invCount = Count;
    inv->capacity = Capacity; 
    inv->page = page;
    return inv;
}
item *makeItem(char *name, char *desc, int qty, Itemtype type){
    item *n = malloc(sizeof(item)); 
    if(n == NULL)return NULL;
    snprintf(n->itemName, sizeof(n->itemName), "%s", name);
    snprintf(n->Desc, sizeof(n->Desc), "%s", desc);
    n->Qty = qty; 
    n->itype = type; 
    n->next = NULL;
    return n; 
}
inventory *addItem(inventory *inv, item *newItem){
    if(inv == NULL) return NULL;
    if(inv->invCount >= inv->capacity){
        printf("Inventory %d Full!\n", inv->page);
        printf("Creating a Inventory %d\n", inv->page++);
        inventory *newPage = makeInventory(NULL, 0, INVCAP, inv->page + 1);
        inv->next = newPage;
        inv = newPage;
    }
    //Insertion (Alphabetically)
    item *curr = NULL;
    for(curr = inv->head; curr != NULL && strcmp(newItem->itemName, inv->head->itemName) < 0; curr = curr->next);
    newItem->next = inv->head;
    inv->head = newItem; 
    inv->invCount++;
    return inv;
}
int viewInventory(inventory *i1){
    if(i1 == NULL)return; 
    printf("Inventory Page: %d [%d/%d]\n", i1->page, i1->invCount, i1->capacity);
    for(item *trav = i1->head; trav != NULL; trav = trav->next){
        printf("  %s (x%d) - %s\n", trav->itemName, trav->Qty, trav->Desc);
    }
    TypeText("Choose an Item:", DTalk);
    
    return;
}

void Attack(Player *p, int SelectedEnem, Enemy e1[], const char *type[]){
    TypeText("Attacking Enemy: \n", 50000); 
    printf("[%d]Enemy %d %s:\n", SelectedEnem, SelectedEnem, type[e1[SelectedEnem].Type]);

}



void TypeText(char *text, int delay){
    for(int i = 0; text[i] != '\0'; i++){
        printf("%c", text[i]);
        fflush(stdout);
        usleep(delay);
    }
    
}
int Selector(const int Esize, Enemy e1[], const char *type[]){
    int i, enemyattk;
    bool choice = false;
    do {
        TypeText("Select an enemy to attack: \n", 50000); 
    

        for (i = 0; i < Esize; i++){
            printf("[%d]Enemy %d %s:\n", i + 1, i + 1, type[e1[i].Type]);
            printf("HP: %d\n", e1[i].hp);
        }
        scanf("%d", &enemyattk); 
    choice = true;
    }while(choice == false);

    return enemyattk;
}
void Item(Player *p){

}

void Skills(){

}

void Stats(){

}
//If player choose "3" Exit//
void ExitGame(){
    clearScreen();

    TypeText("Exiting", 5000);
    int i = 0;
    while (i <= 5){
        TypeText(".", 500000);
        i++;
    }

    printf("\033[2J");
    printf("\033[H");

    exit(1);


}
void Tutorial(Player *p){


}

void MenuChoice(int *choice){

     scanf("%d", choice);
     switch (*choice){
        case 1: Intro();  break;
        case 2: ExitGame(); break;
        default: printf("Invalid Choice!");
     
     
     }


}

void MainGame(Player *p){
    inventory *p1 = makeInventory(NULL, 0, INVCAP, 1);
    addItem(p1, makeItem("Health Potion", "Heals 30 HP", 3, HEAL));
    addItem(p1, makeItem("Rock", "Deals additional 10 DMG", 1, EQUIPMENT));

    

    

    if(p->level.lvl <= 10){
        strcpy(p->level.era, "STONE");
        
    }else if(p -> level.lvl <= 15 && p->level.lvl > 10){
        strcpy(p->level.era, "BRONZE");
    }
    printf("\033[2J");
    printf("\033[H");
    int sizeCol = 4;
    int sizeRow = 50;
    int i, j;
    for(i = 0; i < sizeCol; i++){
        for (j = 0; j < sizeRow; j++){
            if(i == 0 || i == sizeCol - 1){
                printf("=");
            }else if (j == 0 || j == sizeRow - 1){
                printf("|");
            }else{
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\033[2;2H");
    printf("Health: %d", p->hp);

    printf("\033[3;2H");
    printf("Gold: %.2f", p->Current.Gold);

    printf("\033[2;40H");
    printf("Level: %d", p->level.lvl);

    printf("\033[4;2H");

    printf("\033[3;40H");
    printf("Era: %s", p->level.era);

    printf("\033[5;2H");

    TypeText("Watch Out!\n", DTalk);

    usleep(1000000);





    //while(p->hp > 0){//
        EnemyStack e1;
        e1.En[EnSize];
        EnemyType Etype;
        e1.En[0] = (Enemy){3, 50, MELEE, p->level};
        e1.En[1] = (Enemy){5, 35, RANGE, p->level};
        e1.En[2] = (Enemy){2, 70, TANK, p->level};
        e1.En[3] = (Enemy){6, 20, WITCH, p->level};
        
        
        const char *EnType[] = {
            "MELEE",
            "RANGE",
            "TANK",
            "WITCH",

        };


        displayEnemy(Enemsize, e1, EnType);

        int Pchoice;
        float ItemBoost; 
        float damage; 
        int selectedEnem; 


        
    
        do{

            int result = interactiveMenu(&Pchoice);
            if(result != 1){
                TypeText("Invalid Choice only Numbers 0 - 3\n", DTalk);
                while(getchar() != '\n');
                Pchoice = -1;
                continue;
            }

            if(Pchoice < 0 || Pchoice > 3){
                TypeText("Invalid Choice!\n", DTalk);
            }

        }while(Pchoice < 0 || Pchoice > 3);

        switch(Pchoice){
            case 1:
            selectedEnem = Selector(Enemsize, e1, EnType); 
            Attack(p, selectedEnem, e1, EnType); 

            break;
            case 2:


            break;

            case 3:

            viewInventory(p1);


            break;

            case 4:

            break;

            default:

        }


        





        
    //}// While Loop until your hp is 0 





}

void Intro(){
    
    bool isSkip = false;
    
    Player p1 = {

    100,

    30,

    "N/A",

    {1, "STONE"},

    {100.0, 0.0f},

    STONE
    };
    //Intro Dialogue//

    //First Line//

    clearScreen();

    printf("Unknown Character:\n");
    TypeText("OOGA BOOGA!", 50000); 

    fflush(stdout);
    usleep(500000);

    clearScreen();

    //Second Line//

    printf("Unknown Character:\n");
    TypeText("BOOOGAAA DOGGAAA WAGOOLAA DOODOO TADOO!!", 50000); 

    fflush(stdout);
    usleep(500000);

    clearScreen();

    //Third Line//

    printf("Unknown Character:\n");
    TypeText("I'm just kidding, Welcome!", 50000); 

    fflush(stdout);
    usleep(500000);

    clearScreen();

    //4th Line//

    printf("Unknown Character:\n");
    TypeText("Name: ", 50000); 

    fflush(stdout);
    usleep(500000);

    scanf("%s", p1.Name);

    TypeText("Greetings! ", DTalk); 

    for(int i = 0; p1.Name[i] != '\0'; i++){
        printf("%c", p1.Name[i]);
        fflush(stdout);
        usleep(DTalk);
    }
    usleep(1000000);


    clearScreen();

    TypeText("Skip Tutorial? Yes[1] No[0]", DTalk);


    int choice;
    scanf("%d", &choice);
    if(choice == 1){
        isSkip = true;
        clearScreen();
        MainGame(&p1);

    }else if(choice == 0){
        isSkip = false;
        clearScreen();
        TypeText("Let's Start!", DTalk);
        Tutorial(&p1);


    }

          

}





int main(void)
{
    clearScreen();

    int choice; 
    TypeText("Loading", 50000);
    int i = 0;
    while (i <= 8){
        TypeText(".", 500000);
        i++;
    }
    TypeText("\nGame Loaded!", 50000);

    fflush(stdout);
    usleep(500000);

    

    
   clearScreen();


    printf("\n");

    int sizeCol = 6;
    int sizeRow = 34;



   //Prints Civilization v0.1 Menu Screen//    
    for(int i = 0; i < sizeCol; i++){
        for(int j = 0; j < sizeRow; j++){
            if (i == 0 || i == sizeCol - 1){
                printf("=");
            }else if (j == 0 || j == sizeRow - 1){
                printf("|");
            }else if (i == 2 && j == 8) {
                TypeText("Civilization v0.1", 50000);
                j+= 16;
            }else if (i == 3 && j == 5){
                TypeText("By Josh Moises P. Cabalda", 50000);
                j+= 24;
            }else{
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n");

    printf("[1]\t\tPlay\t\t");
    printf("\n[2]\t\tQuit\t\t\n");
    

    MenuChoice(&choice); 
    
}