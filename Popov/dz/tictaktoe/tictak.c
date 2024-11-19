#include <stdio.h>
#include <stdlib.h>


struct sNode{
    struct sNode *next;
    int v_array [3][3];
};

enum symbol{_,x,o,d};

int count_field(int sym,int array[3][3]);
void good_move(int array_struct[3][3],int array[3][3]);
void play(void);


void free_list(struct sNode* list){
    struct sNode* cop_list = NULL;
    while(list != NULL){
        cop_list = (*list).next; 
        free(list);
        list = cop_list;
    }
}

char* check_sym(int value){
    if(!value){
        return "|_|";
    }else{
        return value == 1 ? "|x|" : "|o|";
    }
}

int change_turn(int value){
    return value == x ? o : x;
}

int max(int a, int b){
    return a > b ? a : b;
}

int min(int a, int b){
    return a > b ? b : a;
}

void field(int array[3][3]){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            printf("%s",check_sym(array[i][j]));
        }
        printf("\n");
    }
}

int count_line_win(int array[3][3],int x,int sym){
    int count = 1;
    if(sym){
    for(int i = 1; i < 3;i++){
            if(array[x][i] == sym){
                count += 1;
            }
        }
    }
    return count;
}

int count_column_win(int array[3][3],int y,int sym){
    int count = 1;
    if(sym){
        for(int i = 1; i < 3;i++){
            if(array[i][y] == sym){
                count += 1;
            }
        }
    }
    return count;
}

int diagonal_right(int array [3][3],int sym,int one){
    int count = 1;
    if(sym){
        for(int i = 1; i < 3; i++){
            if(array[i][one] == sym){
                one += 1;
                count += 1;
            }
        }
    }
    return count;
}

int diagonal_left(int array [3][3],int sym,int one){
    int count = 1;
    if(sym){
    for(int i = 1; i < 3; i++){
            if(array[i][one] == sym){
                one -= 1;
                count += 1;
            }
        }
    }
    return count;
}

int draft(int array[3][3]){
    int count = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(!array[i][j]){
                count += 1;
            }
        }
    }
    return count;
}

int check_winner(int array[3][3]){
    for(int i = 0; i < 3; i++){
        int sym = array[0][i];
        if(count_column_win(array,i,sym) == 3){
            return sym == x ? x : o;
        }
    }

    for(int i = 0; i < 3; i++){
        int sym = array[i][0];
        if(count_line_win(array,i,sym) == 3){
            return sym == x ? x : o;
        }
    }

    int sym = array[0][0];
    if(diagonal_right(array,sym,1) == 3){
        return sym == x ? x : o;
    }
    sym = array[0][2];
    if(diagonal_left(array,sym,1) == 3){
        return sym == x ? x : o;
    }

    if(!draft(array)){
        return d;
    }
    return _;
}

struct sNode* add_array(int array[3][3],struct sNode* pos_move){
    struct sNode* pos_move_add;
    pos_move_add = malloc(sizeof(struct sNode));

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            (*pos_move_add).v_array[i][j] = array[i][j];
        }
    }
    (*pos_move_add).next = pos_move;
    return pos_move_add;
}

int leng(struct sNode* move){
    int len = 0;
    while(move != NULL){
        len += 1;
        move = (*move).next;
    }
    return len;
}

void print_move(struct sNode* move){
    while(move != NULL){
        field((*move).v_array);
        printf("\n");
        move = (*move).next;
    }
}

struct sNode* potentional_move(int array[3][3],int sym){
    struct sNode* pos_move = NULL;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(!array[i][j]){
                array[i][j] = sym;
                pos_move = add_array(array,pos_move);
                array[i][j] -= sym;
            }
        }
    }
    return pos_move;
}

int value_field(int sym,int array[3][3]){
    if(check_winner(array) == x){
        return -1;
    }
    if(check_winner(array) == o){
        return 1;
    }
    if(check_winner(array) == d){
        return 0;
    }
    int min_v = 1;
    int max_v = -1;
    struct sNode* move = NULL;
    // struct sNode* free_l = move;
    sym = change_turn(sym);
    move = potentional_move(array,sym);
    struct sNode* free_l = move;
    while(move != NULL){
        min_v = min(value_field(sym,(*move).v_array),min_v);
        max_v = max(value_field(sym,(*move).v_array),max_v);
        
        move = (*move).next;
    }
    free_list(free_l);
    return sym == x ? min_v : max_v;
}

//work
void field_max(int array[3][3],int sym){
    struct sNode* move = NULL;
    struct sNode* pos_m = NULL;
    move = potentional_move(array,sym);
    pos_m = move;
    int len = leng(move);
    int move_len[len];
    int value_oc = -1;
    int value = 0;

    for(int i = 0; i < len; i++){
        move_len[i] = value_field(sym,(*move).v_array);
        value_oc = max(value_oc,move_len[i]);
        move = (*move).next;
    }
    move = pos_m;
    
    while(move != NULL){
        value = value_field(sym,(*move).v_array);
        if(value == value_oc){
            good_move((*move).v_array,array);
        }
        printf("%d %d ",value_oc,value);
        move = (*move).next;
    }
}

//
void move_AI(int array[3][3],int sym){
    struct sNode* move = NULL;
    move = potentional_move(array,sym);
    int max_v = -1;
    int value = 0;
    struct sNode* free_l = move;
    while(move != NULL){
        value = value_field(sym,(*move).v_array);
        if(max_v < value){
            max_v = value;
            good_move((*move).v_array,array);
        }
        move = (*move).next;
    }
    free_list(free_l);
}

void good_move(int array_struct[3][3],int array[3][3]){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            array[i][j] = array_struct[i][j];
        }
    }
}


void field_num(int array[3][3]){
    int count = 1;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(!array[i][j]){
                array[i][j] = count;
                printf("|%d|",count); 
                array[i][j] = _;
            }else{
                printf("%s",check_sym(array[i][j]));
            }
            count += 1;
        }
        printf("\n");
    }
}

void move_player(int array[3][3],int value){
    int count = 1;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(count == value){
                array[i][j] = x; 
            }
            count += 1;
        }
    }
}

int check_move(int array[3][3],int value){
    int count = 1;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(count == value){
                if(array[i][j]){
                    return 0;
                }else{
                    return 1;
                }
            }
            count += 1;
        }
    }
}

char* print_win(int sym){
    if(sym == x){
        return "Win x";
    }else if(sym == o){
        return "Win o";
    }else{
        return "Draft";
    }
}

void clear_field(int array[3][3]){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            array[i][j] = _;
        }
    }
}
//re
void res(void){
    char re[20];
    printf("restart or exit\n");
    scanf("%s",&re);
    printf("%s",re);
    if(re == "restart"){
        play();
    }else{
        printf("\nExit\n");
        exit (1);
    }
}

void play(void){
    int sym = x;
    int array [3][3] =
    {
        {_,_,_},
        {_,_,_},
        {_,_,_}
    };
    int num = 1;
    while(1){
        if(check_winner(array)){
            field(array);
            printf("%s\n",print_win(check_winner(array)));
            clear_field(array);
            sym = x;
            break;
        }
        field_num(array);
        if(!num){
            printf("\nexit game\n");
            exit(1);
        }
        if(sym == x){
            scanf("%d",&num);
            if(check_move(array,num)){
                move_player(array,num);
            }else{
                printf("\nplace_hold\n");
            }
        }else if(sym == o){
            move_AI(array,sym);
            printf("\nyou turn\n");
        }
        sym = change_turn(sym); 
    }
    res();
}


int count_field(int sym,int array[3][3]){
    if(check_winner(array) == x){
        return 1;
    }
    if(check_winner(array) == o){
        return 1;
    }
    if(check_winner(array) == d){
        return 1;
    }
    struct sNode* move = NULL;
    int count = 1;
    move = potentional_move(array,sym);
    sym = change_turn(sym);

    while(move != NULL){
        count += count_field(sym,(*move).v_array);
        move = (*move).next;
    }
    
    return count;
}


int main(){
    int sym = x;
    int array [3][3] =
    {
        {_,_,_},
        {_,_,_},
        {_,_,_}
    };

    play();



    return 0;
}