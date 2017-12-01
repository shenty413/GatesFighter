#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "fssimplewindow.h"

#include "player.h"

void drawhead(double x,double y, int facialstate);
void drawneck(double x, double y);
void drawbody(double x, double y);
void drawrightpart(double x, double y,int rpunchstate, double T);
void drawleftpart(double x, double y,int lpunchstate, double T);
void drawrightleg(double x, double y,int rlegstate,int jumpornot);
void drawleftleg(double x, double y,int llegstate,int jumpornot);


using namespace std;

const int default_x = 300;
const int default_y = 400;
const int jumpSpeed = -1000;
const int default_hp = 100;
const int default_attack = 10;
const bool default_dir = 1;
const double dt = 0.01;


Player::Player(void){
    x = default_x;
    y = default_y;
    hp = default_hp;
    attack = default_attack;
    direction = default_dir;
    ay = 2000;
    T = 0;
    Ttemp = 0;
    punchState = 0;
    walkState = 0;
}

Player::Player(int No){
    x = default_x+(No-1)*400;
    y = default_y;
    hp = default_hp;
    attack = default_attack;
    direction = default_dir;
    ay = 2000;
    T = 0;
    Ttemp = 0;
    punchState = 0;
    walkState = 0;
    // test 
}

void Player::SetCharacter(int charNo){
    switch (charNo) {
        case 1:
            attack = 5;
            vx = 500;
            break;
        case 2:
            attack = 10;
            vx = 3000;
            break;
        case 3:
            attack = 20;
            vx = 1000;
            break;
        case 4:
            attack = 30;
            vx = 100;
            break;
    }
}

int Player::getAttack(){
    return attack;
}

int Player::getLeftBoundary(){
    return x - 100;
}

int Player::getRightBoundary(){
    return x + 100;
}

void Player::Move(){
    if (direction == 1){
		x -= vx * dt;
    }
    else{
		x += vx * dt;
    }
    walkState = 1;
}

void Player::ResetWalkState(){
    walkState = 0;
}

// dirc = 1, left; dirc = 0, right
void Player::ChangeDirc(bool dirc){
    direction = dirc;
}

void Player::InitializeJumping(void){
    jumpState = 1;
    ay = 2000;
    // vy = -400;
    vy = jumpSpeed;
}

bool Player::IsJumping(void){
    if (jumpState == 1){
        return true;
    }
    return false;
}

void Player::Jump(void){
    y += vy * dt;
    vy += ay * dt;
    printf("ay: %d, vy: %d, y: %d\n", ay, vy, y);
}

void Player::CheckHitGround(void){
    if (y > 400 && jumpState){
        ay = 0;
        vy = 0;
        y = 400;
        jumpState = 0;
    }
}

void Player::InitializePunching(void){
    punchState = 1;
}

bool Player::IsPunching(void){
    if (punchState == 1){
        return true;
    }
    return false;
}

void Player::Punch(void){
    punchState = 1;
}

bool Player::IfPunchHit(Player &opponent){
    int armLength = 300;
    printf("Left Boundry: %d\n", opponent.getLeftBoundary());
    printf("Right Boundry: %d\n", opponent.getRightBoundary());
    printf("x: %d\n", x);
    printf("left punch point: %d\n",x - armLength);
    printf("right punch point: %d\n",x + armLength);
    if (direction){ // facing left
        if (x - armLength <= opponent.getRightBoundary() && x - armLength >= opponent.getLeftBoundary()){
            printf("Is hit from left!");
            return true;
        }
    }
    if (!direction){ // facing right
        if (x + armLength >= opponent.getLeftBoundary() && x + armLength <= opponent.getRightBoundary()){
            printf("Is hit from Right!");
            return true;
        }
    }
    return false;
}

void Player::ChangeHitState(){
    if (IsHit == 1){
        IsHit = 0;
    }else{
        IsHit = 1;
    }
}

int Player::GetHitState(){
    return IsHit;
}

void Player::HPchange(const int amount){
    hp -= amount;
    printf("HP: %d\n",hp);
}

int Player::GetHP(void) {
	return hp;
}

void Player::Draw(){
    // printf("x=%d,y=%d,direction=%d,punchState=%d,time=%d\n", x, y, direction, punchState, T);
    if (punchState == 1){
        if (T < 5 && (T == 0 || T - Ttemp > 0)){
            Ttemp = T;
            T++;
            // printf("%d\n", IsHit);
        }else{
            T--;
            if (T == 0){
                punchState = 0;
            }
        }
    }
    //printf("T: %d, punchState: %d\n", T, punchState);
    //printf("x: %d, y: %d", x,y);
    
    arm.CalculateRightPart(x, y, direction, punchState, T);
    arm.CalculateLeftPart(x, y, direction, punchState, T);
    arm.DrawRightArm(x, y);
    arm.DrawLeftArm(x, y);

    leg.Calculate(x, y, walkState, walkState);
    leg.DrawRightLeg(jumpState);
    leg.DrawLeftLeg(jumpState);

    body.DrawHead(x, y, direction);
    body.DrawNeck(x, y);
    body.DrawBody(x, y);
}




