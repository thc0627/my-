#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "console.h"
#include "main.h"
#include "start_mplayer.h"

void help()
{
    printf("**********************\n");
    printf("**    1.简单爱      **\n");
    printf("**    2.缘分一道桥  **\n");
    printf("**********************\n");
}

void my_daorugeci(LRC **lrc, long *len, char *geming)
{
    FILE *fp = fopen(geming, "r");
    if (fp == NULL)
    {
        perror("fopen");
        return;
    }

    fseek(fp, 0, 2);

    *len = ftell(fp);

    rewind(fp);

    *lrc = (LRC *)calloc(1, *len);

    fread(*lrc, *len, 1, fp);

    fclose(fp);

    return;
}

void my_qiege(char **geci, LRC *lrc, int *row)
{
    int i = 0;

    geci[i] = strtok((char *)lrc, "\r\n");
    while ((geci[i]) != NULL)
    {
        i++;
        geci[i] = strtok(NULL, "\r\n");
    }

    *row = i - 1;

    return;
}

void insert(LRC **head, LRC tmp) //有序插入
{
    LRC *pi = (LRC *)calloc(1, sizeof(LRC));

    *pi = tmp;

    pi->next = NULL;

    if (*head == NULL)
    {
        *head = pi;
    }
    else
    {
        LRC *pb = *head;
        LRC *pf = *head;

        while ((pb->time < pi->time) && (pb->next != NULL))
        {
            pf = pb;
            pb = pb->next;
        }

        if (pb->time > pi->time)
        {
            if (pb == *head)
            {
                pi->next = *head;
                *head = pi;
            }
            else
            {
                pf->next = pi;
                pi->next = pb;
            }
        }
        else if (pb->next == NULL)
        {
            pb->next = pi;
        }
    }

    return;
}

void my_gecifenxi(char **geci, int row, LRC **head, char **arr)
{
    LRC tmp;
    int i = 0;

    for (i = 0; i < 4; i++)
    {
        arr[i] = (char *)calloc(1, 10);
        sscanf(geci[i], "[%*2c:%[^]]", arr[i]);
    }

    for (i = 4; i < row; i++)
    {
        char *p_lrc = geci[i];

        while ((*p_lrc) == '[')
        {
            p_lrc += 10;
        }

        char *p_t = geci[i];
        while ((*p_t) == '[')
        {
            int m = 0;
            int s = 0;

            strcpy(tmp.lrc, p_lrc);
            sscanf(p_t, "[%d:%d", &m, &s);

            tmp.time = m * 60 + s;

            insert(head, tmp);

            p_t += 10;
        }
    }

    return;
}

void lrc_display(LRC *head, char **arr)
{
    int time = 0;
    int i = 0;
    int flag = 0;
    LRC *p_mov = head;
    LRC *fp = NULL;
    LRC *p_mov2 = NULL;
    LRC *p_mov_front = NULL;
    LRC *p_mov_front2 = NULL;

    while (1)
    {
        clear_screen();

        cusor_moveto(6, 0);
        set_fg_color(COLOR_CYAN);

        printf("\t\t\t|歌名:%s|\n", arr[0]);
        printf("\t\t\t|歌手:%s|\n", arr[1]);
        printf("\t\t\t|专辑:%s|\n", arr[2]);
        printf("\t\t\t|编辑:%s|\n", arr[3]);
        printf("\t\t\t-------------\n");
        printf("\n");

        printf("\t\t\t    %02d:%02d\n", time / 60, time % 60);
        printf("\n");

        if (flag < 4)
        {
            p_mov_front = head;
        }
        if (p_mov->next != NULL)
        {
            if (time == p_mov->next->time)
            {
                p_mov = p_mov->next;
                flag++;
                if (flag > 4)
                {
                    p_mov_front = p_mov_front->next;
                }
            }
        }
        else
        {
            return;
        }

        p_mov2 = p_mov;
        p_mov_front2 = p_mov_front;

        while (p_mov_front2 != p_mov)
        {
            printf("\t\t     %s\n", p_mov_front2->lrc);
            p_mov_front2 = p_mov_front2->next;
        }

        for (i = 0; i < 5; i++)
        {
            if (p_mov2 != NULL)
            {
                if (i == 0)
                {
                    set_fg_color(COLOR_RED);
                }
                else
                {
                    set_fg_color(COLOR_CYAN);
                }

                printf("\t\t     %s\n", p_mov2->lrc);
                p_mov2 = p_mov2->next;
            }
        }

        set_fg_color(COLOR_RED);

        if (p_mov == NULL)
        {
            break;
        }

        for (float y = 1.5; y > -1.5; y -= 0.1)
        {
            for (float x = -1.2; x < 1.5; x += 0.04)
            {
                float a = x * x + y * y - 1;
                putchar(a * a * a - x * x * y * y * y <= 0.0 ? '*' : ' ');
            }
            putchar('\n');
        }

        sleep(1);
        time++;
    }

    return;
}