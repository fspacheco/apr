#include "objects.h"

void InitPlayer(struct PLAYER *player)
{
    int i;
    player->width = 60;
    player->height = 100;
    player->pos_inicial_x = 75;
    player->pos_inicial_y = 535 - player->height;
    player->x = player->pos_inicial_x;
    player->y = player->pos_inicial_y;
    player->dy = 0;
    player->move_speed = 5;
    player->jump_speed = 10;    //mudar a altura do pulo

    player->colidiu = false;
    player->is_on_solid_ground = true;
    player->may_jump = false;
    for(i=0; i<NUM_BIRDS; i++)
        player->seqJogador[i] = 24;
    player->lives = 3;  // numero de vidas

    player->frame_count = 0;
    player->frame_delay = 10; //definir a velocidade das frames
    player->frame_act = STAND;//STAND = 0, WALK = 1, JUMP = 2
    player->frame_dir = RIGHT;//RIGHT = 0,  LEFT = 1
    player->frame_cur = 0;

}

void MovePlayerRight(struct PLAYER *player)
{
    player->x += player->move_speed;
    if(player->x + player->width > SCREEN_W)
    {
        player->x = SCREEN_W - player->width;
    }
}

void MovePlayerLeft(struct PLAYER *player)
{
    player->x -= player->move_speed;
    if(player->x < 0 )
    {
        player->x = 0;
    }
}

void PlayerJump(struct PLAYER *player, int key)
{
    player->is_on_solid_ground = (player->y == player->pos_inicial_y);
    if(player->is_on_solid_ground) //testa se pode pular
    {
        if(key && player->y >= player->pos_inicial_y)
        {
            if(player->may_jump)
            {
                player->dy -= player->jump_speed;
                player->may_jump = false;
            }
            else
            {
                player->may_jump = true;
            }
        }
    }
    if(!player->is_on_solid_ground)
    {
        player->dy += gravity; //come�a a descer com a gravidade
    }
    if(player->dy > player->jump_speed)
    {
        player->dy = player->jump_speed; //limita uma velocidade maxima pro pulo, o que afeta na altura do pulo
    }

    player->y += player->dy; //aplica as altera��es
    if(player->y > player->pos_inicial_y) //determina o limite com o ch�o depois de pular
    {
        player->dy = 0;
        player->y = player->pos_inicial_y;
    }
}

void DrawPlayer(struct PLAYER *player)
{
    al_draw_bitmap(player->sprite[player->frame_act][player->frame_dir][player->frame_cur], player->x, player->y, 0);
}
