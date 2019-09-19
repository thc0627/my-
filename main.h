#ifndef __MAIN_H__
#define __MAIN_H__

typedef struct lrc
{
    int time;
    char lrc[256];

    struct lrc *next;
}LRC;

extern void help();
extern void my_daorugeci(LRC **lrc, long *len, char *geming);
extern void my_qiege(char **geci, LRC *lrc, int *row);
extern void my_gecifenxi(char **geci, int row, LRC **head, char **arr);
extern void insert(LRC **head, LRC tmp);
extern void lrc_display(LRC *head, char **arr);


#endif 
