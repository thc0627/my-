#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "console.h"
#include "main.h"
#include "start_mplayer.h"

int main(int argc, char const *argv[])
{
    LRC *head = NULL;
    LRC *lrc = NULL;
    long len = 0;
    char geming[32] = "";
    char gequ[32] = "";
    char *geci[128] = {NULL};
    char *arr[4] ={NULL};
    int row = 0;
    int num = 0;

    help();

    printf("请输入要播放歌曲的数字:");
    scanf("%d", &num);

    if (num == 1)
    {
        strcpy(geming, "jiandanai.lrc");
        strcpy(gequ, "love.mp3");

    }
    else if (num == 2)
    {
        strcpy(geming, "song.lrc");
        strcpy(gequ, "love1.mp3");
    }
    

    cusor_show();

    //将歌词导入堆区空间
    my_daorugeci(&lrc, &len, geming);
   
    //按句切割歌词
    my_qiege(geci, lrc, &row);

    //逐句分析歌词
    my_gecifenxi(geci, row, &head, arr);

    //启动播放器
    mplayer_play(gequ);


    //隐藏光标
    //cusor_hide();

    //动态显示
    lrc_display(head, arr);
    
    //cusor_show();
    return 0;
}
