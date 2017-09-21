#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 400

struct clip *build_a_lst();
struct clip *append();
int find_length();
void print_lst();
void split_line();

struct clip {
  int views;
  char *user;
  char *time;
  char *title;
  struct clip *next;
} *head;

int main(int argc, char **argv) {
  int n;
  head = build_a_lst(*(argv+1));
  print_lst(head);  
  return 0;
}

struct clip *build_a_lst(char *fn) {
  FILE *fp;
  struct clip *hp;
  char *fields[4];
  char line[LINE_LENGTH];
  int cnt=0;
  hp=NULL;

  fp=fopen(fn ,"r");
  while(fgets(line, LINE_LENGTH, fp)){
    char* temp=strdup(line);
    split_line(fields, temp);
    hp=append(hp, fields);
    cnt++;
  }
  return hp;
}

void split_line(char **fields,char *line) {
  int i=0;
  char *token, *delim;
  delim = ",\n";
  token=strtok(line, delim);
  
  while(token != NULL){
    fields[i]=token;
    i++;
    token=strtok(NULL, delim);
  }
}

struct clip *append(struct clip *hp,char **four) {
  struct clip *cp,*tp;

  cp=hp;
  tp=malloc(sizeof(struct clip));
  tp->views=atoi(four[0]);
  tp->user=malloc(sizeof(char[strlen(four[1])]));
  strcpy(tp->user, four[1]);
  tp->time=malloc(sizeof(char[strlen(four[2])]));
  strcpy(tp->time, four[2]);
  tp->title=malloc(sizeof(char[strlen(four[3])]));
  strcpy(tp->title, four[3]);

  while(1){
    if(hp == NULL){
      hp=tp;
      break;
    }
    else if(cp->next == NULL){
      cp->next=tp;
      break;
    }
    else{
      cp=cp->next;
    }
  }
  return hp;
}

void print_lst(struct clip *cp) {
  while(cp->next){
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("|%8d|%40s|%5s|%s|\n",cp->views,cp->user,cp->time,cp->title);
    cp=cp->next;
  }
}
